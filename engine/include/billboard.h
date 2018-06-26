/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   billboard.h
 *  ����:   �����غ���
 *
 ****************************************************************************/


/*! \file billboard.h
 * �����غ���.
 * ���ļ��ǲ���庯��ͷ�ļ�.
 */


/** �����ģʽ */
#define  LIGHT_BILLBOARD_POINT      0
#define  LIGHT_BILLBOARD_ROTATE_X   1
#define  LIGHT_BILLBOARD_ROTATE_Y   2
#define  LIGHT_BILLBOARD_ROTATE_Z   3
#define  LIGHT_BILLBOARD_FIX_YZ     4
#define  LIGHT_BILLBOARD_FIX_XZ     5
#define  LIGHT_BILLBOARD_FIX_XY     6


/** �������������� */
class LightBillboardPoolDesc
{
public:

	/** �����ģʽ */
	int mode;

	/** ����������λ�� */
	vec3_t center;

	/** ����������λ�� */
	vec3_t global_position;

	/** ���������緽�� */
	quat_t global_orientation;

	/** �����ؾֲ�λ�� */
	vec3_t local_position;

	/** �����ؾֲ����� */
	quat_t local_orientation;

	/** ������� */
	float width;

	/** �����߶� */
	float height;

	/** �������ɫ��RGBA�����һ�������ԱΪ͸���� */
	int color[4];

	/** ��������ű��� */
	vec3_t scale;

	/** �������ת�Ƕ� */
	quat_t rotate;

	/** ˮƽ��ת���� */
	bool flip_horizintal;

	/** ��ֱ��ת���� */
	bool flip_vertical;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */
	LIGHT_INLINE LightBillboardPoolDesc()
	{
		memset( this, 0, sizeof(LightBillboardPoolDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */
	LIGHT_INLINE void setToDefault()
	{
		mode = LIGHT_BILLBOARD_POINT;
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		width = 1.0f;
		height = 1.0f;
		VEC4( color, 255, 255, 255, 255 );	     // �������ɫȱʡΪ��ɫ��͸��
		VEC3( scale, 1.0f, 1.0f, 1.0f );         // �����ȱʡΪ����������
		VEC4( rotate, 0.0f, 0.0f, 1.0f, 0.0f );  // �����ȱʡΪ��������ת
		flip_horizintal = FALSE;                 // ȱʡΪ��ֹˮƽ��ת����
		flip_vertical = FALSE;                   // ȱʡΪ��ֹ��ֱ��ת����
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightBillboardPool
 *  \brief �������� 
 *
 *  ���ฺ�𲼸��Ĺ������ʾ��֧�ֵ�����������͵Ĳ���塣
 *  ÿ�� LightBillboardPool ʵ��������ͨ�� LightScene ��� NewBillboard �������䡣
 */

class LightBillboardPool
{

public:

	/*! \brief ��ѯ������
	 *		 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���ò����ģʽ
	 *	
	 *  \param mode[in] �����ģʽ
	 *
	 *  \see 
	 */
	virtual void mode( int mode ) = 0;

	/*! \brief ���ò���������λ��
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

	/*! \brief ���ò���������λ��
	 *	 
	 *  \param x ����������λ�õ� x ����
	 *
	 *  \param y ����������λ�õ� y ����
	 *
	 *  \param z ����������λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief ���ò��������緽��ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õĲ��������緽����Ԫ��
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief ���ò��������緽��ʹ��������ת��
     *
	 *  ���ò��������緽��ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ������������ת�Ƕ�
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

	/*! \brief ���ò����ؾֲ�λ��
	 *	 
	 *  \param x �����ؾֲ�λ�õ� x ����
	 *
	 *  \param y �����ؾֲ�λ�õ� y ����
	 *
	 *  \param z �����ؾֲ�λ�õ� z ����
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief ���ò����ؾֲ�����ʹ����Ԫ����
     *	 
     *  \param quat[in] Ҫ���õĲ����ؾֲ�������Ԫ��
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief ���ò����ؾֲ�����ʹ��������ת��
     *
	 *  ���ò����ؾֲ�����ʹ��������תָ���Ƕȵı�ʾ��ʽ��
	 *
	 *  \param angle[in] ������������ת�Ƕ�
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

	/*! \brief ���ò�����С
	 *	
	 *  \param width[in] �������	 
	 *  \param height[in] �����߶�
	 *	 
	 *  \see 
	 */
	virtual void size( float width, float height ) = 0;

	/*! \brief ���ò������ɫֵ
	 *	
	 *  ����ɫֵֻӰ������¼���Ĳ���壬ÿ�������ӵ��һ����������ɫֵ��
	 *
	 *  \param[in] red ��ɫ�ĺ�ɫ�ɷ֣�ȡֵ��Χ[0,255]����ͬ��
	 *  \param[in] green ��ɫ����ɫ�ɷ�
	 *  \param[in] blue ��ɫ����ɫ�ɷ�
	 *  \param[in] alpha ��ɫ�� Alpha �ɷ�
	 *	 
	 *  \see 
	 */
	virtual void color( int red, int green, int blue, int alpha ) = 0;

	/*! \brief ���ò�������ű���
	 *	
	 *  �����ű���ֻӰ������¼���Ĳ���壬ÿ�������ӵ��һ�����������ű�����
	 *
	 *  \param[in] x �� x ������ű�����ȡֵ��Χ[������,������]����ͬ��
	 *  \param[in] y �� y ������ű���
	 *  \param[in] z �� z ������ű���
	 *	 
	 *  \see 
	 */
	virtual void scale( float x, float y, float z ) = 0;

	/*! \brief ���ò������ת�Ƕ�
	 *	
	 *  ����ת�Ƕ�ֻӰ������¼���Ĳ���壬ÿ�������ӵ��һ����������ת�Ƕȡ�
	 *
	 *  \param[in] angle ��ָ������ת�ĽǶȣ�ȡֵ��Χ[������,������]��
	 *  \param[in] x ��ʾ��ת�������� x ������ȡֵ��Χ[������,������]����ͬ��
	 *  \param[in] y ��ʾ��ת�������� y ����
	 *  \param[in] z ��ʾ��ת�������� z ����
	 *	 
	 *  \see 
	 */
	virtual void rotate( float angle, float x, float y, float z ) = 0;

	/*! \brief ��ת���������
	 *	 
	 *  \param s[in] ˮƽ��ת����
	 *
	 *  \param t[in] ��ֱ��ת����
	 *	 
	 *  \see 
	 */
	virtual void reversal( bool s, bool t ) = 0;

	/*! \brief ���ã���ʹ�ã����������
	 *	 
	 *  \param disable[in] ���ò���������־��TRUE = ���ã�FALSE = ʹ��
	 *	 
	 *  \see 
	 */
	virtual void disableTexture( bool disable ) = 0;

	/*! \brief ����һ���㲼���
	 *	 
	 *  \param x �����λ�õ� x ����
	 *
	 *  \param y �����λ�õ� y ����
	 *
	 *  \param z �����λ�õ� z ����
	 *	 
	 *  \param frame = 0 ���������֡����ȱʡΪ 0��Ҳ�͵�һ֡
	 *
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void addPoint ( float x, float y, float z, int frame = 0 ) = 0;

	/*! \brief ����һ���᲼���
	 *
	 *  ����һ���᲼��壬�ò����ʼ�մ�ֱ�ڵ��档
	 *
	 *  \param float x �����λ�õ� x ����
	 *
	 *  \param float y �����λ�õ� y ����
	 *
	 *  \param float z �����λ�õ� z ����
	 *	 
	 *  \param int frame = 0 ���������֡����ȱʡΪ 0��Ҳ�͵�һ֡
	 *
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void addAxis ( float x, float y, float z, int frame = 0 ) = 0;

	/*! \brief ��Ⱦ�����
	 *
	 *  ��Ⱦ���м��벼��صĲ���塣
	 *
	 *  \see 
	 */
	virtual void render ( void ) = 0;

};