/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   camera.h
 *  内容:   摄像机函数
 *
 ****************************************************************************/


/*! \file camera.h
 * 摄像机函数
 */


class LightEngine;


/** 摄像机状态类 */
typedef struct
{
	/** 摄像机位置 */
	vec3_t position;

	/** 摄像机焦点位置 */
	vec3_t focus;

	/** 摄像机向上的方向 */
	vec3_t up;

} LightCameraState;

/** 摄像机描述符 */
typedef struct
{
	/** 摄像机位置 */
	vec3_t position;

	/** 摄像机焦点位置 */
	vec3_t focus;

	/** 摄像机向上的方向 */
	vec3_t up;

} LightCameraDesc;


/*! \class LightCamera
 * \brief 摄像机类
 *
 *  本类负责摄像机的控制。
 *  每个 LightCamera 实例都必须通过 LightEngine 类的 NewCamera 方法分配。 
 */

class LightCamera
{

public:

	/*! \brief 查询父引擎 
	*	 
	*  \return 返回引擎指针
	*
	*  \see 
	*/	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn  void Viewport( int x, int y, int width, int height ) = 0
	 *  \brief 定义视口
	 *
	 *  定义视口
	 *
	 *  \param int x 视口左上角 x 坐标
	 *
	 *  \param int y 视口左上角 y 坐标
	 *
	 *  \param int width 视口宽度
	 *
	 *  \param int height 视口高度
	 *
	 *  \return 无如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual void viewport( int x, int y, int width, int height ) = 0;

	/*! \fn  void Perspective( double fovy, double aspect, double znear, double zfar ) = 0
	 *  \brief 定义对称透视视图体
	 *
	 *  定义对称透视视图体
	 *
	 *  \param double fovy 在 x-z 平面内视区的角度，其值必须在区间 [0.0，180.0] 内。
	 *
	 *  \param double aspect 长宽比，是平截台体的宽度和高度之比。
	 *
	 *  \param double znear 视点（沿 z 轴负方向）与近裁剪平面的距离。
	 *
	 *  \param double zfar 视点（沿 z 轴负方向）与远裁剪平面的距离。
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void perspective( double fovy, double aspect, double znear, double zfar ) = 0;

	/*! \fn  void Ortho( double left, double right, double bottom, double top, double zNear, double zFar ) = 0
	 *  \brief 定义正交视图体
	 *
	 *  定义正交视图体
	 *
	 *  \param double left 远近裁剪平面的矩形左 x 坐标
	 *
	 *  \param double right 远近裁剪平面的矩形右 x 坐标
	 *
	 *  \param double bottom 远近裁剪平面的矩形下 y 坐标
	 *
	 *  \param double top 远近裁剪平面的矩形上 y 坐标
	 *
	 *  \param double znear 视点（沿 z 轴负方向）与近裁剪平面的距离。
	 *
	 *  \param double zfar 视点（沿 z 轴负方向）与远裁剪平面的距离。
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void ortho( double left, double right, double bottom, double top, double zNear, double zFar ) = 0;

	/*! \fn  void LookAt( double eyex, double eyey, double eyez,
     *                    double centerx, double centery, double centerz,
	 *                    double upx, double upy, double upz ) = 0
	 *  \brief 设置摄像机参数
	 *
	 *  设置摄像机参数
	 *
	 *  \param double eyex 视点（眼睛所在位置） x 坐标
	 *
	 *  \param double eyey 视点（眼睛所在位置） y 坐标
	 *
	 *  \param double eyez 视点（眼睛所在位置） z 坐标
	 *
	 *  \param double centerx 视线上的任意一点 x 坐标
	 *
	 *  \param double centery 视线上的任意一点 y 坐标
	 *
	 *  \param double centerz 视线上的任意一点 z 坐标
	 *
	 *  \param double upx 向上方向（即视图体自下而上的方向）上一点的 x 坐标
	 *
	 *  \param double upy 向上方向（即视图体自下而上的方向）上一点的 y 坐标
	 *
	 *  \param double upz 向上方向（即视图体自下而上的方向）上一点的 z 坐标
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void lookAt( double eyex, double eyey, double eyez,
                 double centerx, double centery, double centerz,
	             double upx, double upy, double upz ) = 0;

	/*! \brief 设置为当前活动摄像机
	 *
	 *  \see 
	 */
	virtual void active() = 0;

	/*! \fn void setPosition( float x, float y, float z ) = 0
	 *  \brief 设置摄像机位置
	 *
	 *  设置摄像机位置
	 *
	 *  \param float x 摄像机位置 x 坐标
	 *
	 *  \param float y 摄像机位置 y 坐标
	 *
	 *  \param float z 摄像机位置 z 坐标
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void setPosition( float x, float y, float z ) = 0;

	/*! \fn void setFocus( float x, float y, float z ) = 0
	 *  \brief 设置摄像机焦点（视线上的一点）位置
	 *
	 *  设置摄像机焦点（视线上的一点）位置
	 *
	 *  \param float x 摄像机焦点位置 x 坐标
	 *
	 *  \param float y 摄像机焦点位置 y 坐标
	 *
	 *  \param float z 摄像机焦点位置 z 坐标
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void setFocus( float x, float y, float z ) = 0;

	/*! \fn void setUp( float x, float y, float z ) = 0
	 *  \brief 设置摄像机向上的方向
	 *
	 *  设置摄像机向上的方向
	 *
	 *  \param float x 摄像机向上方向的 x 坐标
	 *
	 *  \param float y 摄像机向上方向的 y 坐标
	 *
	 *  \param float z 摄像机向上方向的 z 坐标
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void setUp( float x, float y, float z ) = 0;

	/*! \fn void rotateHorizontal( float angle ) = 0
	 *  \brief 沿水平方向旋转摄像机
	 *
	 *  沿水平方向旋转摄像机
	 *
	 *  \param float angle 摄像机旋转的角度
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void rotateHorizontal( float angle ) = 0;

	/*! \fn void rotateVertical( float angle ) = 0
	 *  \brief 沿垂直于水平面的方向旋转摄像机
	 *
	 *  沿垂直于水平面的方向旋转摄像机
	 *
	 *  \param float angle 摄像机旋转的角度
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void rotateVertical( float angle ) = 0;

	/*! \fn void rotateFocus( float angle ) = 0
	 *  \brief 以视线（摄像机位置到焦点连成的直线）为轴旋转摄像机
	 *
	 *  以视线（摄像机位置到焦点连成的直线）为轴旋转摄像机
	 *
	 *  \param float angle 摄像机旋转的角度
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	//virtual void rotateFocus( float angle ) = 0;

	/*! \fn void translate( float x, float y, float z ) = 0
	 *  \brief 整体平移摄像机
	 *
	 *  整体平移摄像机
	 *
	 *  \param float x 摄像机平移向量的 x 分量
	 *	 
	 *  \param float y 摄像机平移向量的 y 分量
	 *	 
	 *  \param float z 摄像机平移向量的 z 分量
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void translate( float x, float y, float z ) = 0;

	/*! \fn void setFocusDistance( float distance ) = 0
	 *  \brief 设置摄像机的焦距
	 *
	 *  设置摄像机的焦距
	 *
	 *  \param float distance 摄像机的焦距
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void setFocusDistance( float distance ) = 0;

	/*! \fn void lockFocus( bool lock ) = 0
	 *  \brief 锁定/解锁摄像机的焦点
	 *
	 *  锁定/解锁摄像机的焦点
	 *
	 *  \param bool lock 要执行的操作，TRUE = 锁定，FALSE = 解锁
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void lockFocus( bool lock ) = 0;

	/*! \fn void getPosition( vec3_t position ) = 0
	 *  \brief 查询摄像机位置
	 *
	 *  查询摄像机位置
	 *
	 *  \param vec3_t position 向量指针，用于返回摄像机位置
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void getPosition( vec3_t position ) = 0;

	/*! \fn void getFocus( vec3_t focus ) = 0
	 *  \brief 查询摄像机焦点（视线上的一点）位置
	 *
	 *  查询摄像机焦点（视线上的一点）位置
	 *
	 *  \param vec3_t focus 向量指针，用于返回摄像机焦点位置
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void getFocus( vec3_t focus ) = 0;

	/*! \fn void getUp( vec3_t up ) = 0
	 *  \brief 查询摄像机向上的方向
	 *
	 *  查询摄像机向上的方向
	 *
	 *  \param vec3_t up 向量指针，于用返回摄像机向上的方向
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void getUp( vec3_t up ) = 0;

	/*! \fn float getFocusDistance() = 0
	 *  \brief 查询摄像机的焦距
	 *
	 *  查询摄像机的焦距
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回摄像机的焦距。
	 *
	 *  \see 
	 */
	virtual float getFocusDistance() = 0;

	/*! \fn void move( float forwardBack, float leftRight, float upDown ) = 0
	 *  \brief 以摄像机方向为基准整体移动摄像机
	 *
	 *  以摄像机方向为基准整体移动摄像机
	 *
	 *  \param float forwardBack 摄像机前进/后退的距离，> 0 为前进，< 0 为后退，= 0 为此方向静止
	 *	 
	 *  \param float leftRight 摄像机左移/右移的距离，> 0 为左移，< 0 为右移，= 0 为此方向静止
	 *	 
	 *  \param float upDown 摄像机上升/下降的距离，> 0 为上升，< 0 为下降，= 0 为此方向静止
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void move( float forwardBack, float leftRight, float upDown ) = 0;

	/*! \fn void movePreview( LightCameraState * state, float forwardBack, float leftRight, float upDown ) = 0
	 *  \brief 获取以预览的方式整体移动摄像机（方向为基准）后的摄像机状态
	 *
	 *  获取以预览的方式整体移动摄像机（方向为基准）后的摄像机状态。仅计算摄像机移动后的状态，并不实际移动摄像机。
	 *
	 *  \param LightCameraState * state 返回摄像机状态的指针
	 *	 
	 *  \param float forwardBack 摄像机前进/后退的距离，> 0 为前进，< 0 为后退，= 0 为此方向静止
	 *	 
	 *  \param float leftRight 摄像机左移/右移的距离，> 0 为左移，< 0 为右移，= 0 为此方向静止
	 *	 
	 *  \param float upDown 摄像机上升/下降的距离，> 0 为上升，< 0 为下降，= 0 为此方向静止
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void movePreview( LightCameraState * state, float forwardBack, float leftRight, float upDown ) = 0;

	/*! \fn  void Rotate( vec3_t pos, vec3_t rotate, float length, vec3_t translation, bool fly, vec3_t eye, vec3_t center, vec3_t up ) = 0
     *  \brief 根据摄像机旋转角度和平移量计算视线坐标
	 *
	 *  根据摄像机旋转角度和平移量计算视线坐标。本函数只计算并返回 LookAt 函数所需要的三个坐标值，并不影响摄像机的实际参数；
	 *  通常在计算第一、第二、第三人称视角时使用，如果要将计算结果应用于摄像机，还需要调用 LookAt 函数。此函数前5个参数为
	 *  输入参数，最后三个参数输出计算结果。
	 *  
	 *
	 *  \param vec3_t pos 摄像机（也即眼睛）所在位置的坐标值                                                                  [输入参数]
	 *
	 *  \param vec3_t rotate 摄像机旋转角度 rotate[0] = 水平旋转角度（可以理解为左右转动头部）
	 *                                      rotate[1] = 垂直旋转角度（可以理解为抬起头部向上看）
	 *                                      rotate[2] = 沿视线旋转角度（目前不支持此功能，无效）                              [输入参数]
	 *
	 *  \param float length 视线长度，也即从眼睛到视点（视线上的任意一点）的距离                                              [输入参数]
	 *
	 *  \param vec3_t translation 摄像机的移动量，translation[0] = 前进（> 0）、后退（< 0）
	                                              translation[1] = 左移（> 0）、右移（< 0）
												  translation[2] = 上升（> 0）、下降（< 0），此参数不受 fly 标志的限制        [输入参数]
	 *
	 *  \param bool fly 是否为飞行模式， 0 为步行模式，摄像机沿视线在水平面上移动，不能上下移动（仅指 translation[0]）
	 *                                   1 为飞行模式，摄像机沿视线移动                                                       [输入参数]
	 *
	 *  \param vec3_t eye 视点（眼睛所在位置）坐标                                                                            [输出结果]
	 *
	 *  \param vec3_t center 视线上的任意一点坐标                                                                             [输出结果]
	 *
	 *  \param vec3_t up 向上方向（即视图体自下而上的方向）上一点的坐标                                                       [输出结果]
	 *
	 *  \return 本函数没有返回值。
	 *
	 *  \see LookAt
	 */
	virtual void rotate( vec3_t pos, vec3_t rotate, float length, vec3_t translation, bool fly, vec3_t eye, vec3_t center, vec3_t up ) = 0;

	/*! \fn  int Push ( void ) = 0
	 *  \brief 将摄像机当前状态压入堆栈
	 *
	 *  将摄像机当前状态压入堆栈
	 *
	 *  \param 无
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int push ( void ) = 0;

	/*! \fn  int Pop ( void ) = 0
	 *  \brief 弹出摄像机状态堆栈，并设置为当前状态
	 *
	 *  弹出摄像机状态堆栈，并设置为当前状态
	 *
	 *  \param 无
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int pop ( void ) = 0;

	/*! \fn  int UpdateCamera( void ) = 0
	 *  \brief 应用摄像机设置
	 *
	 *  应用摄像机设置
	 *
	 *  \param 无
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual void updateCamera( void ) = 0;

};