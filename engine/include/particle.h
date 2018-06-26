/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   particle.h
 *  ����:   ���Ӻ���
 *
 ****************************************************************************/


/*! \file particle.h
 * ���Ӻ���.
 * ���ļ������Ӻ���ͷ�ļ�.
 */


/** �������ݽṹ */
typedef struct
{
	
} LightParticleData;


/** �������� */
enum LightParticleType
{
	/** ��׼���� */
	LIGHT_PARTICLE_NORMAL,

	/** ��״���� */
	LIGHT_PARTICLE_CURRENT,


	LIGHT_PARTICLE_COMPOUND,

	LIGHT_PARTICLE_COUNT,

	LIGHT_PARTICLE_FORCE_DWORD = 0x7fffffff
};


// �����˶��켣

/** ��ֹ��������ָ�켣�� */
#define  LIGHT_TRACK_POINT       0
/** ���� */
#define  LIGHT_TRACK_RADIAL      1

#ifdef LIGHT_CORPORATION_EDITION

/** ������� */
#define  LIGHT_TRACK_RADIATE     2
/** ��һ��ۼ� */
#define  LIGHT_TRACK_CONVERGE    3
/** ������ */
#define  LIGHT_TRACK_GYROIDAL    4
/** ���� */
#define  LIGHT_TRACK_CIRCLE      5

#endif


/** ������������ */
class LightParticleDesc
{
public:

	/** �������� */
	char   name[17];

	/** �������� */
	LightParticleType  type;

	/** �����˶��켣 */
	int    track;

	/** ���ӷ���Դ����λ�� */
	vec3_t center;

	/** ���ӷ���Դ����λ�� */
	vec3_t global_position;

	/** ���ӷ���Դ���緽�� */
	quat_t global_orientation;

	/** ���ӷ���Դ�ֲ�λ�� */
	vec3_t local_position;

	/** ���ӷ���Դ�ֲ����� */
	quat_t local_orientation;

	vec3_t vector;              // ���ӷ��䷽��
	int    numparticle;         // ������
	int    billboard_mode;      // ���Ӳ����ģʽ
	float  billboard_width;     // �������Ӳ����Ŀ��
	float  billboard_height;    // �������Ӳ����ĸ߶�
	float  rise;                // �������Ĵ�С�����̡���ȣ�   
	int    life;                // ���ӷ���Դ��������ǧ��֮һ��Ϊ��λ
	int    particle_life;       // ������������ǧ��֮һ��Ϊ��λ
	float  emission_rate;       // ���ӷ����ٶȣ��ԣ���/�룩Ϊ��λ
	vec3_t homeplace_box;       // ���ӳ����д�С
	bool   disable_texture;	    // ���ã���ʹ�ã����������
	char   texture[170];        // �����ļ�����
	int    grid_width;          // դ����
	int    grid_height;         // դ��߶�
	int    num_grid;            // ����դ����
	int    min_frame;           // ��С��ʼ����֡��
	int    max_frame;           // �����ʼ����֡��
	bool   flip_horizintal;     // ����ˮƽ��ת����
	bool   flip_vertical;       // ����ֱ��ת����
	float  left_point;          // ��ת�۵㣨ȡֵ��Χ[0,1]��
	float  right_point;         // ��ת�۵㣨ȡֵ��Χ[0,1]��
	int    color[4][4];         // ��ɫ��RGBA����͸���ȣ���ֵ�б�[��ʼ�����У����У�����]
	vec3_t scale[4];            // ���Ų�ֵ�б�[��ʼ�����У����У�����]
	quat_t rotate[4];           // ��ת��ֵ�б�[��ʼ�����У����У�����]
	vec3_t gyroidal[4];         // �������뾶����ת�Ƕȣ��߶ȣ���Ϊ·����ֵ����ֵ�б�[��ʼ�����У����У�����]
	//int    material[4];         // ��ͼ��ֵ�б�[��ʼ�����У����У�����]

	/** ��״������� */
	struct
	{
		/** �˵� 1 ����������Ϊ p1->p2�� */
		vec3_t p1;

		/** �˵� 2 */
		vec3_t p2;

		/** �뾶 */
		float radius;

	} current;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */
	LIGHT_INLINE LightParticleDesc()
	{
		memset( this, 0, sizeof(LightParticleDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "particle" );
		type = LIGHT_PARTICLE_NORMAL;
		track = LIGHT_TRACK_POINT;
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( vector, 0.0f, 0.0f, 1.0f );
		numparticle = 16;
		//billboard_mode = LIGHT_BILLBOARD_POINT;
		billboard_mode = 0;
		billboard_width = 1.0f;
		billboard_height = 1.0f;
		rise = 1.5f;
		//life = 0;
		particle_life = 1000;
		emission_rate = 8;
		VEC3( homeplace_box, 0.1f, 0.1f, 0.1f );
		disable_texture = FALSE;
	    texture[0] = '\0';
		grid_width = 64;
		grid_height = 64;
		num_grid = 1;
		min_frame = 0;
		max_frame = 4;
		flip_horizintal = FALSE;
		flip_vertical = FALSE;
		left_point = 0.33f;
		right_point = 0.66f;
		VEC4( color[0], 255, 255, 255, 0 );
		VEC4( color[1], 255, 255, 255, 255 );
		VEC4( color[2], 255, 255, 255, 255 );
		VEC4( color[3], 255, 255, 255, 0 );
		VEC3( scale[0], 1.0f, 1.0f, 1.0f );
		VEC3( scale[1], 1.0f, 1.0f, 1.0f );
		VEC3( scale[2], 1.0f, 1.0f, 1.0f );
		VEC3( scale[3], 1.0f, 1.0f, 1.0f );
		VEC4( rotate[0], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC4( rotate[1], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC4( rotate[2], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC4( rotate[3], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( gyroidal[0], 1.0f, 0.0f, 0.0f );
		VEC3( gyroidal[1], 1.0f, 120.0f, 1.0f );
		VEC3( gyroidal[2], 1.0f, 240.0f, 2.0f );
		VEC3( gyroidal[3], 1.0f, 360.0f, 3.0f );

		VEC3( current.p1, -1.0f, 0.0f, 0.0f );
		VEC3( current.p2,  1.0f, 0.0f, 0.0f );
		current.radius = 0.5f;

		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightParticle
 *  \brief ������ 
 *
 *  ���ฺ�����ӵĴ������������ʾ��ÿ�� LightParticle ʵ��������ͨ�� LightEngine ��� NewParticle �������䡣 
 */

class LightParticle
{

public:

	/*! \brief ��ѯ������
	 *	 	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���ļ��ж�ȡ��������
	 *	 
	 *  \param filename Ҫ��ȡ�����������ļ�����
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *	 
	 *  \see 
	 */
	virtual int load( const char *filename ) = 0;

	/*! \brief �����������ݵ��ļ���
	 *	 
	 *  \param filename Ҫ����ĵ����������ļ�����
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *	 
	 *  \see 
	 */
	virtual int save( const char *filename ) = 0;

	/*! \brief ���������ж�ȡ��������
	 *	 
	 *  \param particleDesc Ҫ��ȡ����������������
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *	 
	 *  \see 
	 */
	virtual int loadFromDesc( LightParticleDesc &particleDesc ) = 0;

	/*! \brief �����������ݵ���������
	 *	 
	 *  \param particleDesc Ҫ�������������������
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *	 
	 *  \see 
	 */
	virtual int saveToDesc( LightParticleDesc &particleDesc ) = 0;

	/*! \brief �ͷ��ڴ��е���������
	 *		 
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ش�����롣
	 *	 
	 *  \see 
	 */
	virtual int unload() = 0;

	/*! \brief �������ӷ���Դ����λ��
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

	/*! \brief �����Ӱ󶨵�����������ͷ��
	 *	 
	 *  �󶨺����ӽ�����󶨵Ĺ�ͷ�����˶�������λ�úͷ��򣩣�ͬһʱ�̣�ֻ�����󶨵Ĺ�ͷ��Ч��
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

	/*! \brief �������ӷ���Դ����λ��
	 *	 
	 *  \param x ����Դ����λ�õ� x ����
	 *
	 *  \param y ����Դ����λ�õ� y ����
	 *
	 *  \param z ����Դ����λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief �������ӷ���Դ���緽��ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õ����ӷ���Դ���緽����Ԫ��
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief �������ӷ���Դ���緽��ʹ��������ת��
     *
	 *  �������ӷ���Դ���緽��ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ���ӷ���Դ������ת�Ƕ�
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

	/*! \brief �������ӷ���Դ�ֲ�λ��
	 *	 
	 *  \param x ����Դ�ֲ�λ�õ� x ����
	 *
	 *  \param y ����Դ�ֲ�λ�õ� y ����
	 *
	 *  \param z ����Դ�ֲ�λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief �������ӷ���Դ�ֲ�����ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õ����ӷ���Դ�ֲ�������Ԫ��
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief �������ӷ���Դ�ֲ�����ʹ��������ת��
     *
	 *  �������ӷ���Դ�ֲ�����ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ���ӷ���Դ������ת�Ƕ�
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

	/*! \brief �������ӷ��䷽��
	 *
	 *  �������ӷ��䷽��
	 *
	 *  \param float x ���䷽��� x ����
	 *
	 *  \param float y ���䷽��� y ����
	 *
	 *  \param float z ���䷽��� z ����
	 *
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void setVector ( float x, float y, float z ) = 0;

	/*! \brief �������ӷ���Դ���ڽǶ�
	 *
	 *  �������ӷ���Դ���ڽǶȡ�
	 *
	 *  \param float angle ����Դ���ڽǶ�
	 *	 
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void setAngle ( float angle ) = 0;

	/*! \brief �������ӳ�ʼ�ٶ�
	 *
	 *  �������ӳ�ʼ�ٶ�
	 *
	 *  \param float speed ���ӳ�ʼ�ٶ�
	 *	 
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void speed ( float speed ) = 0;

	/*! \brief ������������
	 *
	 *  ������������
	 *
	 *  \param int life ÿ�����ӵĴ��ʱ�䣨��ǧ��֮һ��Ϊ��λ��
	 *	 
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void life ( int life ) = 0;

	/*! \brief ��������׷������
	 *
	 *  ��������׷�����ӡ�ͨ������£������뿪����Դ�󣬾Ͳ����ܷ���Դλ�õ�Ӱ�죻���ܵ������������޵ģ���ʱΪ�˸������ģ������ƶ������壬
	 *  ������Ҫ�����Ӹ��ŷ���Դ��λ���ƶ���ͨ������׷�����ӣ����Ǿ���ģ����������
	 *
	 *  \param float factor Ҫ���õ�׷�����ӣ�ȡֵ��Χ��0~1����0 ��ʾ�����뿪����Դ��Ͳ����ܷ���Դλ�õ�Ӱ�죬1 ��ʾ���ӵ�λ����ȫ�ɷ���Դ��λ��ȷ����
	 *	 
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void follow ( float factor ) = 0;

	/*! \brief ���ô��������
	 *
	 *  ���ô��������
	 *
	 *  \param int sum ���д�����ӵ�����
	 *	 
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void sum ( int sum ) = 0;

	/*! \brief ���õ������Ӵ�С
	 *
	 *  ���õ������Ӵ�С
	 *
	 *  \param float width �������ӵĿ��
	 *
	 *  \param float height �������ӵĸ߶�
	 *
	 *  \return �������޷���ֵ��
	 *
	 *  \see 
	 */
	virtual void size ( float width, float height ) = 0;

	/*! \brief ��Ⱦ����
	 *
	 *  ��Ⱦ���ӡ�
	 *
	 *  \param �������޲�����
	 *
	 *  \return �������޷���ֵ������������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual void render ( void ) = 0;

	/*! \brief ���¼������ӷ���Դ
	 *
	 *  �˺����������¼����������ڽ��������ӷ���Դ
	 *	 
	 *  \see 
	 */
	virtual void active( void ) = 0;

};