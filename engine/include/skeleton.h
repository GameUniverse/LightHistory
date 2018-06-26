/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   skeleton.h
 *  ����:   ������������
 *
 ****************************************************************************/


/*! \file skeleton.h
 * ������������.
 * ���ļ��ǹ�����������ͷ�ļ�.
 */


class LightEngine;


/** ���������������� */
class LightSkeletonDesc
{
public:

	/** ������������ */
	char name[17];

	/** ���������ļ����� */
	char file[33];

	/** ������������ */
	//LightParticleType  type;

	/** ������������λ�� */
	vec3_t center;

	/** ������������λ�� */
	vec3_t global_position;

	/** �����������緽�� */
	quat_t global_orientation;

	/** ���������ֲ�λ�� */
	vec3_t local_position;

	/** ���������ֲ����� */
	quat_t local_orientation;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightSkeletonDesc()
	{
		memset( this, 0, sizeof(LightSkeletonDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "" );
		strcpy( file, "" );
		//type = LIGHT_PARTICLE_NORMAL;
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightSkeleton
 *  \brief ����������
 *
 *  ���ฺ����������ļ��Ķ�ȡ�����ƺ���Ⱦ��֧����ʵ�Ĺ���������֧�ֶද����ϣ�֧�����⶯������֡�Ļ�ϡ� 
 *  ÿ�� LightSkeleton ʵ��������ͨ�� LightEngine ��� createSkeleton �������䣬 releaseSkeleton �ͷš�
 */

class LightSkeleton
{

public:

	/*! \brief ��ѯ������
	 *	 	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ��ȡ���������ļ�
	 *
	 *  ��ȡ���������ļ���֧����ʵ�Ĺ��������ļ���
	 *
	 *  \param filename[in] ���������ļ������������ı���ʽ����Ҫ�ֹ���д��ͨ���� cfg Ϊ�ļ�����׺�������ʽ��ʾ������
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int load( const char *filename ) = 0;


	// λ�úͷ���

	/*! \brief ���ù�����������λ��
	 *	 
	 *  \param x ����λ�õ� x ����
	 *
	 *  \param y ����λ�õ� y ����
	 *
	 *  \param z ����λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setCenter( float x, float y, float z ) = 0;

	/*! \brief �ѹ��������󶨵�����������ͷ��
	 *	 
	 *  �󶨺󣬹�������������󶨵Ĺ�ͷ�����˶�������λ�úͷ��򣩣�ͬһʱ�̣�ֻ�����󶨵Ĺ�ͷ��Ч��
	 *
	 *  \param skeleton[in] Ҫ�󶨵Ĺ������������ò���Ϊ NULL ʱ�����
	 *
	 *  \param bone[in] Ҫ�󶨵Ĺ�ͷ
	 *
	 *  \return ����������óɹ������� 0�����򣬷��ش�����롣
	 *
	 *  \see 
	 */
	virtual int attach( LightSkeleton * skeleton, int bone ) = 0;

	/*! \brief ���ù�����������λ��
	 *	 
	 *  \param x ����λ�õ� x ����
	 *
	 *  \param y ����λ�õ� y ����
	 *
	 *  \param z ����λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief ���ù����������緽��ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õĹ����������緽����Ԫ��
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief ���ù����������緽��ʹ��������ת��
     *
	 *  ���ù����������緽��ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ��������������ת�Ƕ�
     *
     *  \param x[in] ��ת������ x ����
     *
	 *  \param y[in] ��ת������ y ����
     *
	 *  \param z[in] ��ת������ z ����
     *
	 *  \remarks ��תʱ��ԭ��͸�������ɵ��߶�Ϊ�������ת��
	 *
     */
	virtual	void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;

	/*! \brief ���ù��������ֲ�λ��
	 *	 
	 *  \param x �ֲ�λ�õ� x ����
	 *
	 *  \param y �ֲ�λ�õ� y ����
	 *
	 *  \param z �ֲ�λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief ���ù��������ֲ�����ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õĹ��������ֲ�������Ԫ��
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief ���ù��������ֲ�����ʹ��������ת��
     *
	 *  ���ù��������ֲ�����ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ��������������ת�Ƕ�
     *
     *  \param x[in] ��ת������ x ����
     *
	 *  \param y[in] ��ת������ y ����
     *
	 *  \param z[in] ��ת������ z ����
     *
	 *  \remarks ��תʱ��ԭ��͸�������ɵ��߶�Ϊ�������ת��
	 *
     */
	virtual	void setLocalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;

	/*! \brief ��ѯ������������λ��
	 *	 
	 *  \param position[out] ���ع�����������λ��
	 *	 
	 *  \see 
	 */
	virtual void getGlobalPosition( vec3_t position ) = 0;

	/*! \brief ��ѯ�����������緽��ʹ����Ԫ����
     *	 
     *  \param orientation[out] ���ع����������緽����Ԫ��
     *	 
     */
	virtual	void getGlobalOrientationQuat( quat_t orientation ) = 0;

	/*! \brief ��ѯ�����������緽��ʹ��������ת��
     *
	 *  ��ѯ�����������緽��ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[out] ����������ת�Ƕ�
     *
     *  \param axis[out] ������ת������
     *	 
	 *  \remarks ��תʱ��ԭ��͸�������ɵ��߶�Ϊ�������ת��
	 *
     */
	virtual	void getGlobalOrientationAngleAxis( float & angle, vec3_t axis ) = 0;

	/*! \brief ��ѯ��ͷ��ʶ����ID��
	 *	 
	 *  \param name[in] Ҫ��ѯ��ͷ������
	 *
	 *  \return ���Ҫ��ѯ�Ĺ�ͷ���ڣ����ع�ͷ��ʶ����ID����һ���������������򣬷��� -1 ��
	 *
	 *  \see 
	 */
	virtual int getBoneId( const char * name ) = 0;

	/*! \brief ��ѯ��ͷλ��
	 *	 
	 *  \param bone[in] ��ͷ��ʶ����ID��
	 *	 
	 *  \param position[out] ���ع�ͷλ��
	 *	 
	 *  \see 
	 */
	virtual void getBonePosition( int bone, vec3_t position ) = 0;

	/*! \brief ��ѯ��ͷ����ʹ����Ԫ����
     *	 
	 *  \param bone[in] ��ͷ��ʶ����ID��
	 *	 
     *  \param quat[out] ���ع�ͷ����ʹ����Ԫ����
     *	 
     */
	virtual	void getBoneOrientationQuat( int bone, quat_t quat ) = 0;


#ifdef LIGHT_CORPORATION_EDITION

	// �������

	/*! \brief ������ײ����õ��������
	 *
	 *  \param scene Ҫ������������ĳ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int createSkeleton( LightScene * scene ) = 0;

	/*! \brief ��ѯ�����������ͷ��
	 *
	 *  \return �����������Ѿ����������������ͷ�������򣬷����㡣
	 *
	 *  \see 
	 */
	virtual int getNumberBones() = 0;

	/*! \brief ��ѯ�����ͷ��ɫָ��
	 *
	 *  \return �����������Ѿ����������������ͷ����ָ�룻���򣬷��� NULL ��
	 *
	 *  \see 
	 */
	virtual LightActor * const * getBones() = 0;

	/*! \brief ���¹�������״̬
	 * 
	 *  ͬʱ��������״̬
	 *
	 *  \see 
	 */
	virtual void update() = 0;


	// ��װ

	/*! \brief ��ȡ�������������ļ�
	 *
	 *  ��ȡ�������������ļ�
	 *
	 *  \param filename[in] �������������ļ�����ͨ���� cmf �� xmf Ϊ�ļ�����׺��
	 *
	 *  \return ����������óɹ�����������ľ���������������ʧ�ܣ����� 0��
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·���������
	 *
	 *  \see 
	 */
	virtual int loadMesh( const char *filename ) = 0;

	/*! \brief ��ѯ����������������
	 *	 
	 *  \return ����������óɹ�����������������������������ʧ�ܣ����� 0��
	 *
	 *  \remarks 
	 *
	 *  \see 
	 */
	virtual int getMeshCount( void ) = 0;

	/*! \brief ��ѯ������������������
	 *	 
	 *  \param mesh[in] Ҫ��ѯ�Ĺ�����������
	 *
	 *  \return ����������óɹ�������������������������������ʧ�ܣ����� 0��
	 *
	 *  \remarks 
	 *
	 *  \see 
	 */
	virtual int getSubmeshCount( int mesh ) = 0;

	/*! \brief ��ȡ�������������ļ�
	 *	 
	 *  \param filename[in] �������������ļ�����ͨ���� crf �� xrf Ϊ�ļ�����׺��
	 *
	 *  \return ����������óɹ�����������ľ���������������ʧ�ܣ����� 0��
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·��������Ĳ��ʡ�
	 *
	 *  \see 
	 */
	virtual int loadMaterial( const char *filename ) = 0;

	/*! \brief ��ѯ����������������ʾ��
	 *	 
	 *  \param mesh[in] Ҫ��ѯ�Ĺ�������������
	 *
	 *  \param submesh[in] Ҫ��ѯ�Ĺ���������������
	 *
	 *  \return ����������óɹ������ع���������������ʵľ���������������ʧ�ܣ����� 0��
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·��������Ĳ��ʡ�
	 *
	 *  \see 
	 */
	virtual int getSubmeshMaterial( int mesh, int submesh ) = 0;

	/*! \brief ָ�������������������
	 *	 
	 *  \param mesh[in] Ҫָ���Ĺ�������������
	 *
	 *  \param submesh[in] Ҫָ���Ĺ���������������
	 *
	 *  \param material[in] Ҫָ���Ĺ���������������ʾ��
	 *	 
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·��������Ĳ��ʡ�
	 *
	 *  \see 
	 */
	virtual void setSubmeshMaterial( int mesh, int submesh, int material ) = 0;

	/*! \brief ���ڴ����ͷŹ�����������
	 *	 
	 *  \param material[in] Ҫ�ͷŵĹ����������ʾ��
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·��������Ĳ��ʡ�
	 *
	 *  \see 
	 */
	virtual int unloadMaterial( int material ) = 0;

	/*! \brief �����������Ʋ�ѯ������
	 *	 
	 *  \param meshname[in] ���������������ƣ�����������Ѿ������ڴ��С�
	 *
	 *  \return ����������óɹ�����������ľ���������������ʧ�ܣ����� 0��
	 *
	 *  \remarks 
	 *
	 *  \see 
	 */
	virtual int getMeshId( const char *meshname ) = 0;

	/*! \brief ������������
	 *	 
	 *  \param mesh[in] Ҫ�������Ƶ�������
	 *
	 *  \param name[in] Ҫ���õĹ���������������
	 *	 
	 *  \see 
	 */
	virtual void setMeshName( int mesh, const char *name ) = 0;

	/*! \brief �������������
	 *
	 *  �Թ�����������������ţ�����Ч�����ۻ���ÿ�����Ŷ�����ǰ�����ŵĽ���Ͻ��еġ�
	 *
	 *  \param mesh[in] Ҫ�������ŵĹ�������������
	 *	
	 *  \param factor[in] �������������������ӣ�1.0 Ϊ������С��
	 *	 
	 *  \return  ������û�з���ֵ
	 */
    virtual void scaleMesh( int mesh, float factor ) = 0;

	/*! \brief ������󶨵���������
	 *	 
	 *  \param mesh[in] Ҫ������ľ��
	 *
	 *  \return ����������óɹ������� TRUE�������������ʧ�ܣ����� FALSE��
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·���������
	 *
	 *  \see 
	 */
	virtual bool attachMesh( int mesh ) = 0;

	/*! \brief ������ӹ�����������
	 *
	 *  ������ӹ����������롣�����������������Դ������ڴ��У������μ��������ʾ���������ٴΰ󶨵��������������Ҫ���״��ڴ���ɾ������������� UnloadMesh ������
	 *
	 *  \param mesh[in] Ҫ��������ľ��
	 *
	 *  \return ����������óɹ������� TRUE�������������ʧ�ܣ����� FALSE��
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·���������
	 *
	 *  \see 
	 */
	virtual bool detachMesh( int mesh ) = 0;

	/*! \brief �ͷŹ�������������ռ�ڴ�
	 *	 
	 *  \param mesh[in] Ҫ�ͷ�����ľ��
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *
	 *  \remarks �˺���ͨ��ʹ���ڻ�װϵͳ�У�������Ϸ�����ж�̬�����·���������
	 *
	 *  \see 
	 */
	virtual int unloadMesh( int mesh ) = 0;

	/*! \brief �༭ָ������
	 *
	 *  �༭ָ����������Ҫ���ھ�ȷ��֡�Ķ�����ϡ�
	 *
	 *  \param state[in] Ҫ�༭�Ķ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int editState( int state ) = 0;

	/*! \brief ����ָ���Ķ���֡
	 *
	 *  ����ָ���Ķ���֡����Ҫ���ھ�ȷ��֡�Ķ�����ϡ�
	 *
	 *  \param destframe[in] Ŀ��֡�ĵ�һ֡��һ�����ƶ���֡�� numframe ����
	 *
	 *  \param bone[in] Ҫ���ƵĹ�ͷͨ��
	 *
	 *  \param state[in] Ҫ���ƵĶ���
	 *
	 *  \param startframe[in] Ҫ���Ƶĵ�һ֡����
	 *
	 *  \param numframe[in] Ҫ���ƵĶ���֡��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int copyState( int destframe, const char *bone, int state, int startframe, int numframe ) = 0;

	/*! \brief ��ʾ/����ָ��������
	 *	 
	 *  \param mesh[in] Ҫ��ʾ/���ص�����
	 *
	 *  \param show[in] Ҫ��ʾ/���ص������Ϊ TRUE ʱ����ʾ���������Ϊ FALSE�������ظ�����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int showMesh( int mesh, bool show ) = 0;

	/*! \brief ��϶���
	 *	 
	 *  \param animation[in] Ҫ��ϵĶ���
	 *
	 *  \param weight[in] �ö�����Ȩ�أ�1.0 Ϊ���
	 *
	 *  \param animation[in] �ӿ�ʼ��ϵ������������Ҫʱ�䣬����Ϊ��λ
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual bool blendCycle( int animation, float weight, float delay ) = 0;

	/*! \brief �����϶���
	 *	 
	 *  \param animation[in] Ҫ����Ķ���
	 *	 
	 *  \param animation[in] �ӿ�ʼ����������������Ҫʱ�䣬����Ϊ��λ
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual bool clearCycle( int animation, float delay ) = 0;

	/*! \brief ִ�е�������
	 *	 
	 *  \param animation[in] Ҫִ�еĶ���
	 *
	 *  \param delayIn[in] �ö��������ʱ��
	 *
	 *  \param delayOut[in] �ö���������ʱ��
	 *
	 *  \param weightTarget[in] �ö�����Ŀ��Ȩ�أ����ֵΪ 1.0f
	 *
	 *  \param autoLock[in] ѭ�����ű�־��false = ѭ������
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual bool executeAction( int animation, float delayIn, float delayOut, float weightTarget, bool autoLock ) = 0;

	/*! \brief �����������
	 *	 
	 *  \param animation[in] Ҫ����Ķ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual bool removeAction( int animation ) = 0;

#endif


	/*! \brief ��ѯ��������ϸ�ڵȼ�
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual float getLodLevel() = 0;

	/*! \brief ���ù�������ϸ�ڵȼ�
	 *	 
	 *  \param lodLevel[in] ��������ϸ�ڵȼ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual void setLodLevel( float lodLevel ) = 0;

	// ��������
    #define LIGHT_TYPE_CYCLE    0  // ѭ������
    #define LIGHT_TYPE_ACTION   1  // ���β���
    #define LIGHT_TYPE_POSE     2  // ��ֹ����

	/*! \brief ���õ�ǰ��������
	 *	 
	 *  \param type[in] Ҫ���õĶ�������
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void animationType( int type ) = 0;

	/*! \brief ��ѯ��ǰ��������
	 *	 
	 *  \return ���ص�ǰ�������ȣ�����Ϊ��λ��
	 */
	virtual float getAnimationDuration( void ) = 0;

	/*! \brief ��ѯ��ǰ�����Ѳ���ʱ��
	 *	 
	 *  \return ���ص�ǰ�����Ѳ���ʱ�䣬����Ϊ��λ��
	 */
	virtual float getAnimationTime( void ) = 0;

	/*! \brief ���õ�ǰ�����Ѳ���ʱ��
	 *	 
	 *  \param time[in] Ҫ���õĵ�ǰ�����Ѳ���ʱ�䣬����Ϊ��λ
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void setAnimationTime( float time ) = 0;

	/*! \brief ���ö�������ʱ������
	 *	 
	 *  \param factor[in] Ҫ���õ�ʱ�����ӣ�1.0 = �����ٶȲ��ţ�2.0 = �������ٶȲ��ţ�0.5 = ����֮һ���ٶȲ��ţ��Դ����ơ�
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void setTimeFactor( float factor ) = 0;

	/*! \brief ��ѯ��������ʱ������
	 *	 
	 *  \param factor[in] ������û�в�����
	 *
	 *  \return ����Ҫ��ѯ��ʱ�����ӣ�����ֵ�ľ��庬��� SetTimeFactor ������
	 */
	virtual float getTimeFactor( void ) = 0;

	/*! \brief ָ����ǰ����
	 *	 
	 *  \param animation[in] ָ���Ķ���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void animation( int animation ) = 0;

    /*! \brief ���ù�������������󣨾������λ�úͷ�����Ϣ��
 	 *	
	 *  \param mat[in] Ҫ���õĹ�����������4x4����
	 */
	virtual	void setGlobalPose( const mat44_t & mat ) = 0;

	/*! \brief ���ù���������ת����
	 *
	 *  \param rotate[in] ��ָ��ָ��һ�� 4x3 ����ת����	 
	 */
    virtual void setRotateMatrix( const mat34_t & rotate ) = 0;

	/*! \brief �Թ���������������
	 *
	 *  �Թ��������������ţ�����Ч�����ۻ���ÿ�����Ŷ�����ǰ�����ŵĽ���Ͻ��еġ�
	 *
	 *  \param factor[in] ���������������ӣ�1.0 Ϊ������С��
	 *	 
	 *  \return  ������û�з���ֵ
	 */
    virtual void scale( float factor ) = 0;

	/*! \brief ��ѯ���������İ�Χ��
	 *
	 *  \return  ����������һ�� vec3_t ���͵�ָ�룬�������������ֱ��ʾ AABB �е���������
	 */
	virtual vec3_t * getBoundingBox() = 0;

	/*! \brief ��Ⱦ��������
	 *
	 *  \remarks ������û�������Ϣ��
	 */
	virtual void render() = 0;

	/*! \brief ���Ź�������
	 *
	 *  \remarks ������û�������Ϣ��
	 */
	virtual void play() = 0;

	/*! \brief ��ͣ��������
	 *
	 *  ʹ��������ͣ���ڵ�ǰ֡�ϲ���
	 *
	 *  \remarks ������û�������Ϣ��
	 */
	virtual void pause() = 0;

	/*! \brief ֹͣ��������
	 *
	 *  ��������ֹͣ���ţ����ص���һ֡��λ��
	 *
	 *  \remarks ������û�������Ϣ��
	 */
	virtual void stop() = 0;

	/*! \fn void Unload ( void ) = 0
	 *  \brief �ͷŹ���������ռ�ڴ�
	 *
	 *  �ͷŹ���������ռ�ڴ�
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void unload ( void ) = 0;

};