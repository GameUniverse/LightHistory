/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2007 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  文件:   md3.h
 *  内容:   md3 模型函数
 *
 ****************************************************************************/


/*! \file md3.h
 * md3 模型函数
 * 此文件是 md3 模型函数头文件.
 */

struct t3DModel;

// 模型部件 ID
#define LIGHT_MD3_LOWER   0	  // 下肢模型 ID
#define LIGHT_MD3_UPPER	  1	  // 上肢模型 ID
#define LIGHT_MD3_HEAD	  2	  // 头部模型 ID
#define LIGHT_MD3_WEAPON  3	  // 武器模型 ID

/*! \class LightModelMD3
 * \brief MD3 模型类
 *
 *  本类负责 MD3 模型文件的读取和显示，支持身体上部和下部独立设置动作，支持武器绑定。 
 *  每个 LightModelMD3 实例都必须通过 LightEngine 类的 NewModelMD3 方法分配。 
 */

class LightModelMD3
{

public:
	
	/*! \fn bool LoadModel( LPSTR strModel ) = 0
	 *  \brief 将模型文件读入内存
	 *
	 *  文件名前缀将会被加到 _upper.md3, _lower.md3 or _head.md3 前面，然后再将其读入内存。
	 *	 
	 *  \param LPSTR strModel 模型文件名前缀
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual bool LoadModel( LPSTR strModel ) = 0;

	/*! \fn bool LoadWeapon( LPSTR strModel ) = 0
	 *  \brief 将武器模型读入内存
	 *
	 *  文件名前缀将会被加到 .md3 前面，然后再将其读入内存。
	 *	 
	 *  \param LPSTR strModel 模型文件名前缀
	 *
	 *  \remarks 武器模型被读入内存后，会自动和人物的模型绑定，随人物模型正确运动。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual bool LoadWeapon( LPSTR strModel ) = 0;

	/*! \fn void SetBoundBox ( float x, float y, float z ) = 0
	 *  \brief 设置模型包围盒大小
	 *
	 *  设置模型包围盒大小
	 *
	 *  \param float x 包围盒 x 轴方向的大小
	 *	
	 *  \param float y 包围盒 y 轴方向的大小
	 *	
	 *  \param float z 包围盒 z 轴方向的大小
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void SetBoundBox ( float x, float y, float z ) = 0;

	/*! \fn const float * GetBoundBox ( void ) = 0
	 *  \brief 查询模型包围盒大小
	 *
	 *  查询模型包围盒大小
	 *
	 *  \param 本函数没有参数。
	 *		 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 返回指向包围盒大小的只读指针。
	 */
	virtual const float * GetBoundBox ( void ) = 0;

	/*! \fn void SetUpperState( LPSTR UpperState ) = 0
	 *  \brief 设置模型上部动作
	 *
	 *  设置模型上部动作
	 *
	 *  \param LPSTR UpperState 模型上部动作
	 *	
	 *  \remarks 动作由一个字符串指定。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual void SetUpperState( LPSTR UpperState ) = 0;

	/*! \fn void SetLowerState( LPSTR LowerState ) = 0
	 *  \brief 设置模型下部动作
	 *
	 *  设置模型下部动作
	 *
	 *  \param LPSTR UpperState 模型下部动作
	 *	
	 *  \remarks 动作由一个字符串指定。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual void SetLowerState( LPSTR LowerState ) = 0;

	/*! \fn LPSTR GetUpperState( void ) = 0
	 *  \brief 查询模型上部动作
	 *
	 *  查询模型上部动作
	 *
	 *  \param 本函数没有任何参数
	 *	
	 *  \remarks 动作由一个字符串指定。
	 *
	 *  \return 如果函数调用成功，返回一个动作字符串指针；如果函数调用失败，返回空指针 NULL。
	 */
	virtual LPSTR GetUpperState( void ) = 0;

	/*! \fn LPSTR GetLowerState( void ) = 0
	 *  \brief 查询模型下部动作
	 *
	 *  查询模型下部动作
	 *
	 *  \param 本函数没有任何参数
	 *	
	 *  \remarks 动作由一个字符串指定。
	 *
	 *  \return 如果函数调用成功，返回一个动作字符串指针；如果函数调用失败，返回空指针 NULL。
	 */
	virtual LPSTR GetLowerState( void ) = 0;

	/*! \fn void Render( void ) = 0
	 *  \brief 渲染模型
	 *
	 *  将模型渲染到屏幕或窗口
	 *
	 *  \param 本函数没有参数。
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void Render( void ) = 0;

	/*! \fn void RenderShadow( void ) = 0
	 *  \brief 	渲染模型阴影
	 *
	 *  将模型阴影渲染到屏幕或窗口
	 *
	 *  \param 本函数没有参数。
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void RenderShadow( void ) = 0;

	/*! \fn void Adjust( float x, float y, float z ) = 0
	 *  \brief 校准模型位置
	 *
	 *  移动模型位置，使其处于正确的中心位置。
	 *
	 *  \param float x 校准量的 x 分量
	 *	
	 *  \param float y 校准量的 y 分量
	 *	
	 *  \param float z 校准量的 z 分量
	 *	
	 *  \remarks 下一次调用该函数前一直有效。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void Adjust( float x, float y, float z ) = 0;

	/*! \fn void SetPos( float x, float y, float z ) = 0
	 *  \brief 设置模型位置
	 *
	 *  设置模型在场景中的位置坐标。
	 *
	 *  \param float x 模型位置的 x 坐标
	 *	
	 *  \param float y 模型位置的 y 坐标
	 *	
	 *  \param float z 模型位置的 z 坐标
	 *	
	 *  \remarks 直接将模型的位置设置为 （x, y, z），不进行碰撞检测的计算。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual void SetPos( float x, float y, float z ) = 0;

	/*! \fn void Goto( float x, float y, float z ) = 0
	 *  \brief 移动到指定位置
	 *
	 *  将模型移动到指定位置
	 *
	 *  \param float x 目标位置的 x 坐标
	 *	
	 *  \param float y 目标位置的 y 坐标
	 *	
	 *  \param float z 目标位置的 z 坐标
	 *	
	 *  \remarks 如果模型在新位置与场景没有发生碰撞，则位置设置成功，否则模型位置被设置为碰撞后位置。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual void Goto( float x, float y, float z ) = 0;

	/*! \fn void SetRotate( float angle, float x, float y, float z ) = 0
	 *  \brief 设置模型旋转角度
	 *
	 *  设置模型在场景中的旋转角度。
	 *
	 *  \param float angle 模型的旋转角度
	 *	
	 *  \param float x 旋转轴向量 x 分量
	 *	
	 *  \param float y 旋转轴向量 y 分量
	 *	
	 *  \param float z 旋转轴向量 z 分量
	 *	
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。如果模型在新角度与场景没有发生碰撞，则旋转角度位置设置成功，
	 *  否则模型角度被设置为碰撞后旋转角度。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
    virtual void SetRotate( float angle, float x, float y, float z ) = 0;

	/*! \fn void GetPos( vec3_t pos ) = 0
	 *  \brief 查询模型位置
	 *
	 *  查询模型在场景中的位置坐标。
	 *
	 *  \param vec3_t pos 模型位置结构指针
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值，模型位置已经通过参数指针返回。
	 */
	virtual void GetPos( vec3_t pos ) = 0;

	/*! \fn bool IsOnGround() = 0
	 *  \brief 查询模型是否与地面接触
	 *
	 *  查询模型是否与地面接触
	 *
	 *  \param 本函数没有参数。
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果模型与地面接触返回 TRUE，否则返回 FALSE。
	 */
	virtual bool IsOnGround() = 0;

	/*! \fn bool CrossRay( vec3_t a, vec3_t b, vec3_t cross ) = 0
	 *  \brief 检测指定线段与模型是否相交
	 *
	 *  检测指定线段与模型是否相交（如果相交，返回交点）。
	 *
	 *  \param  vec3_t a 线段起始顶点坐标
	 *	
	 *  \param  vec3_t b 线段结束顶点坐标
	 *	
	 *  \param  vec3_t cross 线段与模型的交点坐标
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果线段与模型相交，返回 TRUE，同时在 cross 中返回交点坐标，否则返回 FALSE；
	 */
	virtual bool CrossRay( vec3_t a, vec3_t b, vec3_t cross ) = 0;

	/*! \fn bool CrossSphere( vec3_t start, vec3_t end, float radius, vec3_t cross ) = 0
	 *  \brief 检测指定球体与模型是否发生碰撞
	 *
	 *  检测指定球体与模型是否发生碰撞（如果发生碰撞，返回交点）。
	 *
	 *  \param vec3_t start 球体运动起始点
	 *
	 *  \param vec3_t end 球体运动结束点
	 *	 
	 *  \param  float radius 球体半径
	 *	
	 *  \param  vec3_t cross 球体与模型的交点坐标
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果球体与模型相交，返回 TRUE，同时在 cross 中返回交点坐标，否则返回 FALSE；
	 */
	virtual bool CrossSphere( vec3_t start, vec3_t end, float radius, vec3_t cross ) = 0;

	/*! \fn bool CrossBox( vec3_t start, vec3_t end, vec3_t min, vec3_t max, vec3_t cross ) = 0
	 *  \brief 检测指定包围盒与模型是否发生碰撞
	 *
	 *  检测指定包围盒（AABB）与模型是否发生碰撞（如果发生碰撞，返回交点）。
	 *
	 *  \param vec3_t start 包围盒运动起始点
	 *
	 *  \param vec3_t end 包围盒运动结束点
	 *	 
	 *  \param  vec3_t min 包围盒对角线最小顶点
	 *	
	 *  \param  vec3_t max 包围盒对角线最大顶点
	 *	
	 *  \param  vec3_t cross 包围盒与模型的交点坐标
	 *	
	 *  \remarks  本函数没有相关信息。
	 *
	 *  \return  如果包围盒与模型相交，返回 TRUE，同时在 cross 中返回交点坐标，否则返回 FALSE；
	 */
	virtual bool CrossBox( vec3_t start, vec3_t end, vec3_t min, vec3_t max, vec3_t cross ) = 0;

};