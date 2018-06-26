/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �ļ�:   brush.h
 *  ����:   ������
 *
 ****************************************************************************/


/*! \file brush.h
 * ������.
 * ���ļ��ǻ�����ͷ�ļ�.
 */


/** ������������ */
class LightBrushDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightBrushDesc()
	{
		memset( this, 0, sizeof(LightBrushDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		VEC3( position, 0, 0, 0 );		
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightBrush
 * \brief ������
 *
 *  ���ฺ 2D �� 3D ����ͼ�����ʾ��֧�� 2D �ĵ㡢�ߡ����Ρ����㣬 3D �ĵ㡢�ߡ�����Ρ�
 *  ÿ�� LightBrush ʵ��������ͨ�� LightEngine ��� createBrush �������䣬 releaseBrush �ͷš�
 */

class LightBrush
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���õ�ǰ��ͼ��ɫ
	 *	 
	 *  \param int red ��ɫ��ɫ����
	 *
	 *  \param int green ��ɫ��ɫ����
	 *
	 *  \param int blue ��ɫ��ɫ����
	 *	 
	 *  \see 
	 */
	virtual void color( int red, int green, int blue ) = 0;

	/*! \brief ���߶�
	 *	 
	 *  \param verts ��������
	 *
	 *  \param vertnum �������
	 *	 
	 *  \see 
	 */
	virtual void lines( vec3_t *verts, int vertnum ) = 0;

	/*! \brief ��������͹��յ��߶�
	 *	 
	 *  \param verts ��������
	 *
	 *  \param vertnum �������
	 *	 
	 *  \see 
	 */
	virtual void linesPlus( vertex_t *verts, int vertnum ) = 0;

	/*! \brief �����߶ο��
	 *	 
	 *  \param width �߶ο��
	 *	 
	 *  \see 
	 */
	virtual void lineWidth( float width ) = 0;

	/*! \brief ����
	 *
	 *  ����
	 *
	 *  \param vec3_t *verts ��������
	 *
	 *  \param int vertnum �������
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void points( vec3_t *verts, int vertnum ) = 0;

	/*! \brief ��͹�����
	 *	 
	 *  \param vertex ��������
	 *
	 *  \param vertexnum �������	 
	 *
	 *  \see 
	 */
	virtual void polygon ( vertex_t *vertex, int vertexnum ) = 0;

	// ����ͼԪ����
    #define LIGHT_PRIMITIVE_POINTS         0x0000
	#define LIGHT_PRIMITIVE_LINES          0x0001
    #define LIGHT_PRIMITIVE_LINE_STRIP     0x0003
	#define LIGHT_PRIMITIVE_LINE_LOOP      0x0002
	#define LIGHT_PRIMITIVE_TRIANGLES      0x0004
	#define LIGHT_PRIMITIVE_TRIANGLE_STRIP 0x0005
	#define LIGHT_PRIMITIVE_TRIANGLE_FAN   0x0006
	#define LIGHT_PRIMITIVE_QUADS          0x0007
	#define LIGHT_PRIMITIVE_QUAD_STRIP     0x0008
	#define LIGHT_PRIMITIVE_POLYGON        0x0009

	/*! \brief ������ͼԪ
	 *
	 *  ������ͼԪ
	 *
	 *  \param vertex_t *vertex ��������
	 *
	 *  \param int vertexnum �������
	 *
	 *  \param int primitive ͼԪ����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void primitive ( vertex_t *vertex, int vertexnum, int primitive ) = 0;

	/*! \brief ��Ⱦһ���������߿�
	 *	 
	 *  \param position ������λ��
	 *
	 *  \param orientation �����巽��
	 *
	 *  \param radius ������뾶
	 *	 
	 *  \see 
	 */
	virtual void octahedronWire( vec3_t position, quat_t orientation, float radius ) = 0;

	/*! \brief ��ȡ��դ�����ɫֵ��2D��
	 *
	 *  \param int x ��դ��� x ����
	 *
	 *  \param int y ��դ��� y ����
	 *
	 *  \return ���ع�դ�����ɫֵ
	 *
	 *  \see 
	 */
	virtual unsigned long getPoint2D( int x, int y ) = 0;

	/*! \brief ����դ�߶Σ�2D��
	 *
	 *  \param int x1 �߶���ʼ��� x ����
	 *
	 *  \param int y1 �߶���ʼ��� y ����
	 *
	 *  \param int x2 �߶ν������ x ����
	 *
	 *  \param int y2 �߶ν������ y ����
	 *
	 *  \see 
	 */
	virtual void line2D( int x1, int y1, int x2, int y2 ) = 0;

	/*! \brief ����դ���Σ�2D��
	 *	 
	 *  \param int x1 �������Ͻǵ� x ����
	 *
	 *  \param int y1 �������Ͻǵ� y ����
	 *
	 *  \param int x2 �������½ǵ� x ����
	 *
	 *  \param int y2 �������½ǵ� y ����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void rectangle2D( int x1, int y1, int x2, int y2 ) = 0;

	/*! \brief ����դ�㣨2D��
	 *
	 *  ����Ļ��ָ��λ���õ�ǰ��ͼ��ɫ��һ����դ�㣨2D�����ú��������� 2D ģʽ�¡�
	 *
	 *  \param int x ��դ��� x ����
	 *
	 *  \param int y ��դ��� y ����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void point2D( int x, int y ) = 0;

};