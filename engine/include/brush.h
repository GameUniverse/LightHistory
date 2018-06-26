/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  文件:   brush.h
 *  内容:   画笔类
 *
 ****************************************************************************/


/*! \file brush.h
 * 画笔类.
 * 此文件是画笔类头文件.
 */


/** 画笔描述符类 */
class LightBrushDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightBrushDesc()
	{
		memset( this, 0, sizeof(LightBrushDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		VEC3( position, 0, 0, 0 );		
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightBrush
 * \brief 画笔类
 *
 *  本类负 2D 和 3D 几何图像的显示，支持 2D 的点、线、矩形、读点， 3D 的点、线、多边形。
 *  每个 LightBrush 实例都必须通过 LightEngine 类的 createBrush 方法分配， releaseBrush 释放。
 */

class LightBrush
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 设置当前作图颜色
	 *	 
	 *  \param int red 颜色红色分量
	 *
	 *  \param int green 颜色绿色分量
	 *
	 *  \param int blue 颜色蓝色分量
	 *	 
	 *  \see 
	 */
	virtual void color( int red, int green, int blue ) = 0;

	/*! \brief 画线段
	 *	 
	 *  \param verts 顶点数组
	 *
	 *  \param vertnum 顶点个数
	 *	 
	 *  \see 
	 */
	virtual void lines( vec3_t *verts, int vertnum ) = 0;

	/*! \brief 画有纹理和光照的线段
	 *	 
	 *  \param verts 顶点数组
	 *
	 *  \param vertnum 顶点个数
	 *	 
	 *  \see 
	 */
	virtual void linesPlus( vertex_t *verts, int vertnum ) = 0;

	/*! \brief 设置线段宽度
	 *	 
	 *  \param width 线段宽度
	 *	 
	 *  \see 
	 */
	virtual void lineWidth( float width ) = 0;

	/*! \brief 画点
	 *
	 *  画点
	 *
	 *  \param vec3_t *verts 顶点数组
	 *
	 *  \param int vertnum 顶点个数
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void points( vec3_t *verts, int vertnum ) = 0;

	/*! \brief 画凸多边形
	 *	 
	 *  \param vertex 顶点数组
	 *
	 *  \param vertexnum 顶点个数	 
	 *
	 *  \see 
	 */
	virtual void polygon ( vertex_t *vertex, int vertexnum ) = 0;

	// 几何图元类型
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

	/*! \brief 画几何图元
	 *
	 *  画几何图元
	 *
	 *  \param vertex_t *vertex 顶点数组
	 *
	 *  \param int vertexnum 顶点个数
	 *
	 *  \param int primitive 图元类型
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void primitive ( vertex_t *vertex, int vertexnum, int primitive ) = 0;

	/*! \brief 渲染一个八面体线框
	 *	 
	 *  \param position 八面体位置
	 *
	 *  \param orientation 八面体方向
	 *
	 *  \param radius 八面体半径
	 *	 
	 *  \see 
	 */
	virtual void octahedronWire( vec3_t position, quat_t orientation, float radius ) = 0;

	/*! \brief 读取光栅点的颜色值（2D）
	 *
	 *  \param int x 光栅点的 x 坐标
	 *
	 *  \param int y 光栅点的 y 坐标
	 *
	 *  \return 返回光栅点的颜色值
	 *
	 *  \see 
	 */
	virtual unsigned long getPoint2D( int x, int y ) = 0;

	/*! \brief 画光栅线段（2D）
	 *
	 *  \param int x1 线段起始点的 x 坐标
	 *
	 *  \param int y1 线段起始点的 y 坐标
	 *
	 *  \param int x2 线段结束点的 x 坐标
	 *
	 *  \param int y2 线段结束点的 y 坐标
	 *
	 *  \see 
	 */
	virtual void line2D( int x1, int y1, int x2, int y2 ) = 0;

	/*! \brief 画光栅矩形（2D）
	 *	 
	 *  \param int x1 矩形左上角的 x 坐标
	 *
	 *  \param int y1 矩形左上角的 y 坐标
	 *
	 *  \param int x2 矩形右下角的 x 坐标
	 *
	 *  \param int y2 矩形右下角的 y 坐标
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void rectangle2D( int x1, int y1, int x2, int y2 ) = 0;

	/*! \brief 画光栅点（2D）
	 *
	 *  在屏幕上指定位置用当前作图颜色画一个光栅点（2D），该函数工作在 2D 模式下。
	 *
	 *  \param int x 光栅点的 x 坐标
	 *
	 *  \param int y 光栅点的 y 坐标
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void point2D( int x, int y ) = 0;

};