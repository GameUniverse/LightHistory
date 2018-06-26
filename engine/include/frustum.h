/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   frustum.h
 *  内容:   视锥体函数
 *
 ****************************************************************************/


/*! \file frustum.h
 * 视锥体函数.
 * 此文件是视锥体函数头文件.
 */

/*! \class LightFrustum
 * \brief 视锥体类
 *
 *  本类负责视锥体的可见性测试，支持点、立方体、长方体和球体的测试。
 *  每个 LightFrustum 实例都必须通过 LightEngine 类的 NewFrustum 方法分配。  
 */

class LightFrustum
{

public:
	
	/*! \brief 根据投影矩阵和模型视矩阵计算视锥体（每当摄像机旋转和移动时调用）
	 *	 
	 *  \see 
	 */
	virtual void calculateFrustum() = 0;

	/*! \brief 检测指定点是否在视锥体中（如果是返回 TRUE，否则返回 FALSE ）
	 *
	 *  \param float x 要检测点的 x 坐标
	 *
	 *  \param float y 要检测点的 y 坐标
	 *
	 *  \param float z 要检测点的 z 坐标
	 *
	 *  \return 如果是返回 TRUE，否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool pointInFrustum( float x, float y, float z ) = 0;

	/*! \brief 检测指定球体是否与视锥体相交（如果是返回 TRUE，否则返回 FALSE ）
	 *	 
	 *  \param float x 球体圆心的 x 坐标
	 *
	 *  \param float y 球体圆心的 y 坐标
	 *
	 *  \param float z 球体圆心的 z 坐标
	 *
	 *  \param float radius 球体的半径
	 *
	 *  \return 如果是返回 TRUE，否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool sphereInFrustum( float x, float y, float z, float radius ) = 0;

	/*! \brief 检测指定立方体是否与视锥体相交（如果是返回 TRUE，否则返回 FALSE ）
	 *
	 *  \param float x 立方体中心的 x 坐标
	 *
	 *  \param float y 立方体中心的 y 坐标
	 *
	 *  \param float z 立方体中心的 z 坐标
	 *
	 *  \param float size 立方体边长
	 *
	 *  \return 如果是返回 TRUE，否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool cubeInFrustum( float x, float y, float z, float size ) = 0;

	/*! \brief 检测指定长方体是否与视锥体相交（如果是返回 TRUE，否则返回 FALSE ）
	 *
	 *  \param float x 长方体中心的 x 坐标
	 *
	 *  \param float y 长方体中心的 y 坐标
	 *
	 *  \param float z 长方体中心的 z 坐标
	 *
	 *  \param float sizeX 长方体 x 轴方向的边长
	 *
	 *  \param float sizeY 长方体 y 轴方向的边长
	 *
	 *  \param float sizeZ 长方体 z 轴方向的边长
	 *
	 *  \return 如果是返回 TRUE，否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool boxInFrustum( float x, float y, float z, float sizeX, float sizeY, float sizeZ ) = 0;

};