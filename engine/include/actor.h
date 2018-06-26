/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   actor.h
 *  ����:   ��ɫ����
 *
 ****************************************************************************/


/*! \file actor.h
 * ��ɫ����
 * ���ļ��ǽ�ɫ����ͷ�ļ�.
 */


class LightTriangleMesh;
class LightHeightField;
class LightScene;
class LightActor;


/** ˯�߼�� */
#define LIGHT_SLEEP_INTERVAL (1.0f/60.0f*20.0f)		// Corresponds to 20 frames for the standard time step.

/** ��ײ����飨����< 32��*/
typedef unsigned short LightCollisionGroup;

/** ��ײ������ʹ�õ� 128-bit ���� */
typedef struct
{
	unsigned long bits0, bits1, bits2, bits3;

} LightGroupsMask;

/** ȷ��һ���ض�����״���� */
enum LightShapeType
{
	/** һ������ƽ�� */
	LIGHT_SHAPE_PLANE,

	/** һ���������� */
	LIGHT_SHAPE_SPHERE,

	/** һ��������� (OBB) */
	LIGHT_SHAPE_BOX,

	/** һ�������� (LSS) */
	LIGHT_SHAPE_CAPSULE,

	/* A wheel for raycast cars */
	LIGHT_SHAPE_WHEEL,

	/** һ������͹������ */
	LIGHT_SHAPE_CONVEX,

	/** һ���������� */
	LIGHT_SHAPE_MESH,

	/** һ��������Σ��߶ȳ���*/
	LIGHT_SHAPE_HEIGHTFIELD,

	/* �����ڲ�ʹ��! */
	LIGHT_SHAPE_RAW_MESH,

	LIGHT_SHAPE_COMPOUND,

	LIGHT_SHAPE_COUNT,

	LIGHT_SHAPE_FORCE_DWORD = 0x7fffffff
};

/** ��ɫ�������� */
class LightActorDesc
{
public:

	/** ��ɫ���� */
	LightShapeType    type;

	/** �Ƿ�̬��ɫ */
	bool   dynamic;

	/** ����ɫ�������Ϊ NULL���򴴽�һ�� parent ���ӽ�ɫ */
	LightActor * parent;

	/** ��Ч���ݱ�־λ */
	int    flag;

	/** ��ɫ��ʼλ�� */
	vec3_t pos;

	/** ��ɫ����ת�Ƕ� */
	float  angle;

	/** ͨ��ԭ�����ת���ϵ�һ�� */
	vec3_t rotate;

	/** ��ɫ��������ײ����飨�� LightActor::setGroup() ˵����*/
	LightCollisionGroup  group;

	/** ��ɫ��Ʒ�ʣ�Բ��������Բ�ܷ���Ķ��� */
	int    quality_slices;

	/** ��ɫ��Ʒ�ʣ�Բ�������ظ߶ȷ���Ķ��� */
	int    quality_stacks;

	/** ��ɫ������ȡֵ��ΧΪ [0��+-�����]��ȱʡֵΪ -1.0���� <= 0 ʱ�������ܶȼ���������*/
	float  mass;

	/** ��ɫ���ر�־��TRUE = ���أ�FALSE = ��ʾ�����ڽ�ɫ����ʱ��ֻ���ڴ��ڲ���ʾ��������ģ�ͼ������ڡ�*/
	bool   hide;

	/** ����������� */
	int    physicsMaterialIndex;

	/** ��������� */
	struct 
	{
		/** �����峤������ */
		vec3_t size;
	
	} box;

	/** ������� */
	struct
	{
		/** ����뾶 */
		float  radius;
	
	} sphere;

	/** ƽ����� */
	struct
	{ 
		/** ƽ�淨�� */
		vec3_t normal;

		/** ƽ�浽ԭ��ľ��� */
		float  distance;

	} plane;

    /** ��������� */
	struct 
	{ 
		/** ������뾶 */
		float  radius;
		/** ������� */
		float  height;

	} capsule;

	 /** ������������� */
	struct 
	{ 
		/** ����������ָ�� */
		LightTriangleMesh * triangleMesh;

	} mesh;

	/** �߶ȳ����� */
	struct 
	{ 
		/** �߶ȳ�ָ�� */
		LightHeightField * heightField;

	} height_field;

    /** �������� */
	struct
	{
		/** �����뾶 */
		float  radius;
	
	} teapot;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightActorDesc()
	{
		memset( this, 0, sizeof(LightActorDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		//VEC3( position, 0, 0, 0 );	
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightActor
 * \brief ��ɫ��
 *
 *  ���ฺ���ɫ�Ĵ�������ʾ�Ϳ��ƣ�Ŀǰ֧�ֺ��ӡ����塢���ҡ�ƽ�桢��̬����͹������� 6 �ֽ�ɫ���͡� 
 *  ÿ�� LightActor ʵ��������ͨ�� LightScene ��� createActor �������䣬 releaseActor �ͷš�
 */

class LightActor
{
	protected:
	
	//inline  LightActor() : userData(NULL) {}

	//virtual	~LightActor() {}

    public:

	/*! \fn LightScene * getScene() = 0
	 *  \brief ��ѯ������
	 *
	 *  ��ѯ������
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;


	// ȫ��״̬����

	/*! \brief ���ý�ɫ���󣨾������λ�úͷ�����Ϣ��
     *	 
     *  \param mat Ҫ���õĽ�ɫ����     
     */
	virtual	void setGlobalPose( const mat34_t mat ) = 0;
	
	/*! \fn void setGlobalPosition( const vec3_t vec ) = 0
     *  \brief ���ý�ɫλ��
     *
	 *  ���ý�ɫλ��
	 *
     *  \param const vec3_t vec Ҫ���õĽ�ɫλ��
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual	void setGlobalPosition( const vec3_t vec ) = 0;

	/*! \fn void setGlobalPosition( float x, float y, float z ) = 0
     *  \brief ���ý�ɫλ��
     *
	 *  ���ý�ɫλ��
	 *
     *  \param float x Ҫ���ý�ɫλ�õ� x ����
     *
	 *  \param float y Ҫ���ý�ɫλ�õ� y ����
     *
	 *  \param float z Ҫ���ý�ɫλ�õ� z ����
     *
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual	void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \fn void setGlobalOrientation( const mat33_t mat ) = 0
     *  \brief ���ý�ɫ����ʹ�þ���
     *
	 *  ���ý�ɫ����ʹ�þ���
	 *
     *  \param const mat33_t mat Ҫ���õĽ�ɫ�������
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual	void setGlobalOrientation( const mat33_t mat ) = 0;
	
	/*! \fn void setGlobalOrientationQuat( const quat_t mat ) = 0
     *  \brief ���ý�ɫ����ʹ����Ԫ����
     *
	 *  ���ý�ɫ����ʹ����Ԫ����
	 *
     *  \param const mat33_t mat Ҫ���õĽ�ɫ������Ԫ��
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \fn void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0
     *  \brief ���ý�ɫ����ʹ��������ת��
     *
	 *  ���ý�ɫ����ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param float angle ��ɫ������ת�Ƕ�
     *
     *  \param float x ��ת������ x ����
     *
	 *  \param float y ��ת������ y ����
     *
	 *  \param float z ��ת������ z ����
     *
	 *  \remarks ��תʱ��ԭ��͸�������ɵ��߶�Ϊ�������ת��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual	void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;
	
	/*! \fn void setGlobalPose( const mat34_t mat ) = 0
     *  \brief ��ѯ��ɫ���󣨾������λ�úͷ�����Ϣ��
     *
	 *  ��ѯ��ɫ���󣨾������λ�úͷ�����Ϣ��
	 *
     *  \param const mat34_t mat 
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ����Ҫ��ѯ�Ľ�ɫ����ָ�� float matrix[3][4]��
     */
	virtual	mat34_t &getGlobalPose() const = 0;

	/*! \fn void setGlobalPosition( const vec3_t vec ) = 0
     *  \brief ��ѯ��ɫλ��
     *
	 *  ��ѯ��ɫλ��
	 *
     *  \param ������û�в���
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ����Ҫ��ѯ�Ľ�ɫλ������ָ�� float vector[3]��
     */
	virtual	vec3_t &getGlobalPosition() const = 0;

	/*! \fn void getGlobalPosition( float * x, float * y, float * z ) = 0
     *  \brief ��ѯ��ɫλ��
     *
	 *  ��ѯ��ɫλ��
	 *
     *  \param float * x ��ɫλ�õ� x ����ָ��
     *
	 *  \param float * y ��ɫλ�õ� y ����ָ��
     *
	 *  \param float * z ��ɫλ�õ� z ����ָ��
     *
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ����ɫλ���Ѿ�ͨ��������ָ�뷵���ˡ�
     */
	virtual void getGlobalPosition( float * x, float * y, float * z ) = 0;
	
	/*! \fn void setGlobalOrientation( const mat33_t mat ) = 0
     *  \brief ��ѯ��ɫ����ʹ�þ���
     *
	 *  ��ѯ��ɫ����ʹ�þ���
	 *
     *  \param ������û�в���
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ����Ҫ��ѯ�Ľ�ɫ�������ָ�� float matrix[3][3]��
     */
	virtual	mat33_t &getGlobalOrientation() const = 0; 
	
	/*! \fn void setGlobalOrientationQuat( const quat_t mat ) = 0
     *  \brief ��ѯ��ɫ����ʹ����Ԫ����
     *
	 *  ��ѯ��ɫ����ʹ����Ԫ����
	 *
     *  \param ������û�в���
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ����Ҫ��ѯ�Ľ�ɫ������Ԫ��ָ�� float quat[4]��
     */
	virtual	quat_t &getGlobalOrientationQuat() const	= 0;


	// �ֲ�״̬���ƣ������ӽ�ɫ��Ч��

	/*! \brief setLocal*() ���������ӽ�ɫ�ڸ���ɫ�ռ��е�״̬��Ҳ��������ڸ���ɫ���ѵ�����
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \param mat[in] �ӽ�ɫ����ڸ���ɫ���±任��<b>ȡֵ��Χ:</b> [����任]
     */
	virtual	void setLocalPose( const mat34_t mat ) = 0;

	/*! \brief setLocal*() ���������ӽ�ɫ�ڸ���ɫ�ռ��е�״̬��Ҳ��������ڸ���ɫ���ѵ�����
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \param vec[in] �ӽ�ɫ����ڸ���ɫ����λ�á�<b>ȡֵ��Χ:</b> [λ��ʸ��]
     */
	virtual	void setLocalPosition( const vec3_t vec ) = 0;

	/*! \brief setLocal*() ���������ӽ�ɫ�ڸ���ɫ�ռ��е�״̬��Ҳ��������ڸ���ɫ���ѵ�����
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \param mat[in] �ӽ�ɫ����ڸ���ɫ���·���<b>ȡֵ��Χ:</b> [��ת����]
     */
	virtual	void setLocalOrientation( const mat33_t mat ) = 0;

	/*! \brief getLocal*() ���������ӽ�ɫ�ڸ���ɫ�ռ��е�״̬��Ҳ��������ڸ���ɫ���ѵ�����
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \return �ӽ�ɫ����ڸ���ɫ��״̬ float mat[3][4]��
     */
	virtual	mat34_t &getLocalPose() = 0;

	/*! \brief getLocal*() ���������ӽ�ɫ�ڸ���ɫ�ռ��е�״̬��Ҳ��������ڸ���ɫ���ѵ�����
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \return �ӽ�ɫ����ڸ���ɫ��λ�á�
     */
	virtual	vec3_t &getLocalPosition() = 0;

	/*! \brief getLocal*() ���������ӽ�ɫ�ڸ���ɫ�ռ��е�״̬��Ҳ��������ڸ���ɫ���ѵ�����
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \return �ӽ�ɫ����ڸ���ɫ�ķ���
     */
	virtual	mat33_t &getLocalOrientation() = 0;


	// �ƶ�

	/*! \brief moveGlobal*() �������÷���ȥ�ƶ����ɫ������Ϸ���磨�˽�ɫ���˶������Ƶģ���
     *	 
	 *  ����任ȱʡΪ��λ����
	 *
     *  \param mat[in] �˶���ɫϣ����λ�úͷ����������꣩��<b>ȡֵ��Χ:</b> [����任]
     */
	//virtual	void moveGlobalPose( const mat34_t & mat ) = 0;


	// ����

	/*! \brief ���ö�̬��ɫ����
     *	 
	 *  ������������������ɫ�����Ƕ�̬�ġ�
	 *
     *  \param mass[in] ��ɫ������ֵ��<b>ȡֵ��Χ:</b> [0��������]
     */
	virtual void setMass( float mass ) = 0;

	/*! \brief ��ѯ��ɫ����
     *	
	 *  ��̬��ɫ�����Ƿ��� 0��
	 *
     *  \return �����ɫ��������
     */
	virtual float getMass() = 0;


	// ����

	/*! \brief ������������ϵ��
     *	 
	 *  ���ʾû�����ᣬ����ϵ����������������ɫ�����Ƕ�̬�ġ�
	 *
	 *  <b>ȱʡֵ:</b> 0
	 *
     *  \param linDamp[in] ��������ϵ����<b>ȡֵ��Χ:</b> [0��������]
     */
	virtual	void setLinearDamping( float linDamp ) = 0;

	/*! \brief ��ѯ��������ϵ��
     *	
	 *  ��ɫ�����Ƕ�̬�ģ���̬��ɫ�����Ƿ��� 0��
	 *
     *  \return �����ɫ����������ϵ����
     */
	virtual	float getLinearDamping() = 0;

	/*! \brief ���ýǶ�����ϵ��
     *	 
	 *  ���ʾû�����ᣬ����ϵ����������������ɫ�����Ƕ�̬�ġ�
	 *
	 *  <b>ȱʡֵ:</b> 0.05
	 *
     *  \param linDamp[in] �Ƕ�����ϵ����<b>ȡֵ��Χ:</b> [0��������]
     */
	virtual	void setAngularDamping( float angDamp ) = 0;

	/*! \brief ��ѯ�Ƕ�����ϵ��
     *	
	 *  ��ɫ�����Ƕ�̬�ģ���̬��ɫ�����Ƿ��� 0��
	 *
     *  \return �����ɫ�ĽǶ�����ϵ����
     */
	virtual	float getAngularDamping() = 0;


	// �ٶ�

	/*! \brief ���ý�ɫ���ٶ�
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param linVel[in] �µ����ٶȡ�<b>ȡֵ��Χ:</b> [�ٶ�ʸ��]
     */
	virtual	void setLinearVelocity( const vec3_t & linVel ) = 0;

	/*! \brief ���ý�ɫ���ٶ�
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param angVel[in] �µĽ��ٶȡ�<b>ȡֵ��Χ:</b> [���ٶ�ʸ��]
     */
	virtual	void setAngularVelocity( const vec3_t & angVel ) = 0;

	/*! \brief ��ѯ��ɫ���ٶ�
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param linVel[out] ���ؽ�ɫ���ٶȡ�
     */
	virtual	void getLinearVelocity( vec3_t & linVel ) = 0;

	/*! \brief ��ѯ��ɫ���ٶ�
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param angVel[out] ���ؽ�ɫ���ٶȡ�
     */
	virtual	void getAngularVelocity( vec3_t & angVel ) = 0;

	/*! \brief ���������ɫ����������ٶ�
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param maxAngVel[in] �����ɫ����������ٶȡ�<b>ȡֵ��Χ:</b> [0��������]
     */
	virtual	void setMaxAngularVelocity( float maxAngVel ) = 0;

	/*! \brief ��ѯ�����ɫ����������ٶ�
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \return �����ɫ����������ٶȡ�
     */
	virtual float getMaxAngularVelocity() = 0;


	// ����

	/*! \brief ���ý�ɫ�߶���
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param linMoment[in] �µ��߶�����<b>ȡֵ��Χ:</b> [����ʸ��]
     */
	virtual void setLinearMomentum( const vec3_t & linMoment ) = 0;

	/*! \brief ���ý�ɫ�Ƕ���
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param angMoment[in] �µĽǶ�����<b>ȡֵ��Χ:</b> [�Ƕ���ʸ��]
     */
	virtual void setAngularMomentum( const vec3_t & angMoment ) = 0;

	/*! \brief ��ѯ��ɫ�߶���
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param linMoment[out] ���ؽ�ɫ�߶�����
     */
	virtual void getLinearMomentum( vec3_t & linMoment ) = 0;

	/*! \brief ��ѯ��ɫ�Ƕ���
     *	 
	 *  ��ɫ�����Ƕ�̬�ġ�
	 *
     *  \param angMoment[out] ���ؽ�ɫ�Ƕ�����
     */
	virtual void getAngularMomentum( vec3_t & angMoment ) = 0;


	// ��

	/*! \fn void addForce( float x, float y, float z, int mode ) = 0
     *  \brief �Խ�ɫʩ��һ�������������ʾ����
     *
	 *  �Խ�ɫʩ��һ�������������ʾ����
	 *
     *  \param float x �������� x ����
     *
	 *  \param float y �������� y ����
     *
	 *  \param float z �������� z ����
     *
	 *  \param int mode ʩ������ģʽ��0 = ֡����Ч��1 = �����ۼ�
     *
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual void addForce( float x, float y, float z, int mode = 0 ) = 0;

	/*! \fn void addLocalForce( float x, float y, float z, int mode ) = 0
     *  \brief �Խ�ɫʩ��һ���þֲ������ʾ����
     *
	 *  �Խ�ɫʩ��һ���þֲ������ʾ����
	 *
     *  \param float x �������� x ����
     *
	 *  \param float y �������� y ����
     *
	 *  \param float z �������� z ����
     *
	 *  \param int mode ʩ������ģʽ��0 = ֡����Ч��1 = �����ۼ�
     *
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual void addLocalForce( float x, float y, float z, int mode = 0 ) = 0;

	/*! \brief ��Ⱦ��ɫ
     *	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual void render( void ) = 0;


	// ��ײ�����

    /*! \brief ���������״���ĸ���ײ������һ����
 	 *	 
	 *  \param collisionGroup[in] �����״����ײ����飬<b>ȡֵ��Χ:</b> [0,31]
	 */
	virtual	void setGroup( LightCollisionGroup collisionGroup ) = 0;

	/*! \brief ��ѯ setGroup() ���õ�ֵ
	 *	 
	 *  \return �����״��������ײ�����
	 */	
	virtual	LightCollisionGroup getGroup() = 0;

	/*! \brief ������ײ������ʹ�õ� 128-bit ���루�� LightGroupsMask ��ע�ͣ�
	 *	 
	 *  \param mask[in] �����״����ײ���������
	 */
	virtual	void setGroupsMask( const LightGroupsMask & mask ) = 0;

	/*! \brief ��ѯ��ײ������ʹ�õ� 128-bit ���루�� LightGroupsMask ��ע�ͣ�
	 *	
	 *  \return �����״����ײ���������
	 */
	virtual	const LightGroupsMask & getGroupsMask() = 0;


	// ˯��

	/*! \brief �����ɫ����˯��״̬�����ѽ�ɫ
     *	 
     *  \param wakeCounterValue[in] �µ�˯�߼�����ֵ��<b>ȡֵ��Χ:</b> [0,������]
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual	void wakeUp( float wakeCounterValue=LIGHT_SLEEP_INTERVAL ) = 0;


	/*! \brief ����/��ʾ��ɫ
     *	 
     *  \param hide ����/��ʾ���TRUE = ���أ�FALSE = ��ʾ������ɫ����ʱ����ɫ������ģ���Ծ��������ڡ�
     *	 	 
	 *  \remarks �˺���ͨ���ڵ��Գ���ʱʹ�ã�ȱʡ����½�ɫ�����صģ������Գ���ʱ������Ҫ��ʾ��ɫ�� 
     */
	virtual void hide( bool hide ) = 0;

   /*! \brief ��ѯ��ɫ���󣨾������λ�úͷ�����Ϣ��
	*
	*  \return ����Ҫ��ѯ�Ľ�ɫ�������� float matrix[4][4]��
	*/
	virtual	mat44_t &getGlobalPoseMatrix44() = 0;

   /*! \brief ��ѯ��ɫ����ʹ�þ��� ע����ʱ�������ṩһ�� 3x4 �ľ���
	*	
	*  \return ����Ҫ��ѯ�Ľ�ɫ�������ָ�� float matrix[4][3]��
	*/
	virtual	mat34_t &getGlobalOrientationMatrix34() = 0;


	/*! \brief ��ָλ��ʩ����
     *	 
     *  \param float fx ��ʸ���� x ����
     *
	 *  \param float fy ��ʸ���� y ����
     *
	 *  \param float fz ��ʸ���� z ����
     *
	 *  \param float px λ�õ� x ����
     *
	 *  \param float py λ�õ� y ����
     *
	 *  \param float pz λ�õ� z ����
     *
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ������û�з���ֵ��
     */
	virtual void AddForceAtPos( float fx, float fy, float fz, float px, float py, float pz ) = 0;


	// ����������

	/** ���ܽ��������κ���;��ͨ��������һ�����󴴽� 1:1 ��Ӧ�Ĺ�ϵ��*/
	void * userData;

};