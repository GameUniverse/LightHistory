/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   mesh.h
 *  ����:   ��̬������
 *
 ****************************************************************************/


/*! \file mesh.h
 * ��̬������
 * ���ļ��Ǿ�̬������ͷ�ļ�.
 */


class LightEngine;


/** ��̬������������ */
class LightMeshDesc
{
public:

	/** ��̬�������� */
	char   name[17];

	/** ��̬�����ļ����� */
	char file[33];

	/** ��̬��������λ�� */
	vec3_t center;

	/** ��̬��������λ�� */
	vec3_t global_position;

	/** ��̬�������緽�� */
	quat_t global_orientation;

	/** ��̬����ֲ�λ�� */
	vec3_t local_position;

	/** ��̬����ֲ����� */
	quat_t local_orientation;

	/** Ͷ����Ӱ */
	bool shadow_cast;

	/** ������Ӱ */
	bool shadow_receive;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightMeshDesc()
	{
		memset( this, 0, sizeof(LightMeshDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "" );
		strcpy( file, "" );
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		shadow_cast = FALSE;
		shadow_receive = FALSE;
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightMesh
 * \brief ��̬������
 *
 *  ���ฺ��̬�����ļ��Ķ�ȡ����ʾ��Ŀǰ֧�� 3ds ��ʽ�ľ�̬�����ļ��� 
 *  ÿ�� LightMesh ʵ��������ͨ�� LightEngine ��� NewMesh �������䡣 
 */

class LightMesh
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���þ�̬��������
	 *
	 *  ȱʡ��̬��������Ϊ�ա�����̬��������Ϊ��ʱ������ load �����󣬾�̬�������ƻ�ı�Ϊ��̬�����ļ��������򣬾�̬�������Ʋ���ı䡣
	 *
	 *  \param name[in] ��̬�������ƣ�����������ʱ��ֻȡǰ 16 ���ַ����ֽڣ���
	 *	 
	 *  \see 
	 */
	virtual void setName( const char * name ) = 0;

	/*! \brief ��ѯ��̬��������
	 *
	 *  ��̬��������һ��Ϊ��̬�����ļ�����ȱʡ��̬��������Ϊ�ա�
	 *
	 *  \param name[out] ���ؾ�̬�������ƣ�����������С�� 17 �ֽڣ�16 ���ַ����ֽڣ���'\0'����
	 *	
	 *  \see 
	 */
	virtual void getName( char * name ) = 0;

	/*! \brief ����̬�����ļ������ڴ�
	 *	 
	 *  \param mesh[in] ��̬�����ļ���������ָ����չ��
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual bool load( const char * mesh ) = 0;

	/*! \brief ���þ�̬��������λ��
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

	/*! \brief �Ѿ�̬����󶨵�����������ͷ��
	 *	 
	 *  �󶨺󣬾�̬���񽫸���󶨵Ĺ�ͷ�����˶�������λ�úͷ��򣩣�ͬһʱ�̣�ֻ�����󶨵Ĺ�ͷ��Ч��
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

	/*! \brief ���þ�̬��������λ��
	 *	 
	 *  \param x ��̬��������λ�õ� x ����
	 *
	 *  \param y ��̬��������λ�õ� y ����
	 *
	 *  \param z ��̬��������λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief ���þ�̬�������緽��ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õľ�̬�������緽����Ԫ��
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief ���þ�̬�������緽��ʹ��������ת��
     *
	 *  ���þ�̬�������緽��ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ��̬����������ת�Ƕ�
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

	/*! \brief ���þ�̬����ֲ�λ��
	 *	 
	 *  \param x ��̬����ֲ�λ�õ� x ����
	 *
	 *  \param y ��̬����ֲ�λ�õ� y ����
	 *
	 *  \param z ��̬����ֲ�λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief ���þ�̬����ֲ�����ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õľ�̬����ֲ�������Ԫ��
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief ���þ�̬����ֲ�����ʹ��������ת��
     *
	 *  ���þ�̬����ֲ�����ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ��̬����������ת�Ƕ�
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

	/*! \fn void render( void ) = 0
	 *  \brief ��Ⱦ��̬����
	 *
	 *  ����̬������Ⱦ����Ļ�򴰿�
	 *
	 *  \param ������û�в�����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void render( void ) = 0;

	/*! \brief ���þ�̬����������󣨾������λ�úͷ�����Ϣ��
	 *	
	 *  \param mat[in] Ҫ���õľ�̬�������4x4����
	 */
	virtual	void setGlobalPose( const mat44_t & mat ) = 0;

	/*! \brief ���þ�̬������ת����
	 *
	 *  \param rotate[in] ��ָ��ָ��һ�� 4x3 ����ת����	 
	 */
    virtual void setRotateMatrix( const mat34_t & rotate ) = 0;

	/*! \brief ���þ�̬�������ű���
	 *	 
	 *  \param x[in] ������ x ������ű���
	 *	
	 *  \param y[in] ������ y ������ű���
	 *	
	 *  \param z[in] ������ z ������ű���
	 *	
	 *  \remarks �� ��x��y��z�������� 1.0f ʱ�������С���䣬���������ȱʡ������
	 *
	 *  \return �˺���û�з���ֵ��
	 */
    virtual void scale( float x, float y, float z ) = 0;

	/*! \brief ��ѯ��̬����λ��
	 *
	 *  ��ѯ��̬�����ڳ����е�λ�����ꡣ
	 *
	 *  \param position[out] ���ؾ�̬����λ��
	 *	
	 *  \remarks ������û�������Ϣ��	  
	 */
	virtual void getGlobalPosition( vec3_t position ) = 0;

	/*! \brief �����������������
	 *	 
	 *  \return �µ�����������
	 *
	 *  \see 
	 */
	virtual LightTriangleMesh * createTriangleMesh() = 0;

	/*! \brief �ͷ��������������
	 *	 
	 *  \param mesh[in] Ҫ�ͷŵ�����������
	 *
	 *  \see 
	 */	
	virtual void releaseTriangleMesh( LightTriangleMesh * mesh ) = 0;

	/*! \brief �ͷž�̬�����ļ���ռ�ڴ�
	 *	 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual bool unload( void ) = 0;

};