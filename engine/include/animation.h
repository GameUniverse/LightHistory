/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   animation.h
 *  内容:   顶点动画函数
 *
 ****************************************************************************/


/*! \file animation.h
 * 顶点动画函数.
 * 此文件是顶点动画函数头文件.
 */


/** 顶点动画描述符类 */
class LightAnimationDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightAnimationDesc()
	{
		memset( this, 0, sizeof(LightAnimationDesc) );
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


/*! \class LightAnimation
 *  \brief 顶点动画类 
 *
 *  本类负责顶点动画文件的读取，显示，目前支持 MD2 顶点动画文件。
 *  每个 LightAnimation 实例都必须通过 LightEngine 类的 createAnimation 方法分配， releaseAnimation 释放。
 */

class LightAnimation
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn int Load ( const char *filename ) = 0
     *  \brief 读入顶点动画文件
     *
	 *  将顶点动画文件读入内存中
	 *
     *  \param filename 顶点动画文件名.
     *
	 *  \remarks 目前支持 MD2 顶点动画文件。
	 *
     *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
     */
	virtual int Load ( const char *filename ) = 0;

	/*! \fn void SetPos( float x, float y, float z ) = 0
	 *  \brief 设置顶点动画位置
	 *
	 *  设置顶点动画位置
	 *
	 *  \param float x 顶点动画位置的 x 坐标
	 *	
	 *  \param float y 顶点动画位置的 y 坐标
	 *	
	 *  \param float z 顶点动画位置的 z 坐标
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void SetPos( float x, float y, float z ) = 0;

	/*! \fn void SetRotate( float angle, float x, float y, float z ) = 0
	 *  \brief 设置顶点动画旋转角度
	 *
	 *  设置顶点动画旋转角度，顶点动画沿一根轴旋转，而这根轴可以用一个向量表示。
	 *
	 *  \param float angle 顶点动画的旋转角度（以度为单位，比如从前面转到后面是 180 度）
	 *
	 *  \param float x 轴向量的 x 坐标
	 *
	 *  \param float y 轴向量的 y 坐标
	 *
	 *  \param float z 轴向量的 z 坐标
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void SetRotate( float angle, float x, float y, float z ) = 0;

	/*! \fn void SetRotateMatrix( const float * rotate ) = 0
 	 *  \brief 设置顶点动画旋转矩阵
	 *
	 *  设置顶点动画旋转矩阵。
	 *
	 *  \param const float * rotate 该指针指向一个 4x3 的旋转矩阵
	 *	 
	 *  \return  本函数没有返回值
	 */
    virtual void SetRotateMatrix( const float * rotate ) = 0;

	/*! \fn void Render( void ) = 0
	 *  \brief 渲染动画
	 *
	 *  将动画渲染到屏幕或窗口
	 *
	 *  \param 本函数没有参数。
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void Render( void ) = 0;

	/*! \fn int Play ( void ) = 0
	 *  \brief 播放
	 *
	 *  播放读入内存的顶点动画
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int Play ( void ) = 0;

	/*! \fn int Pause ( void ) = 0
	 *  \brief 暂停
	 *
	 *  暂停正在播放的顶点动画
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int Pause ( void ) = 0;

	/*! \fn int Stop ( void ) = 0
	 *  \brief 停止
	 *
	 *  停止正在播放的顶点动画
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int Stop ( void ) = 0;

	/*! \fn int Insert( int insert ) = 0
	 *  \brief 插入动画
	 *
	 *  插入动画
	 *
	 *  \param int insert 要插入的位置
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int Insert( int insert ) = 0;

	/*! \fn int Edit( int animation, int start, int end, const char *name ) = 0
	 *  \brief 编辑动画
	 *
	 *  编辑动画
	 *
	 *  \param int animation 要编辑的动画
	 *
	 *  \param int start 动画起始帧
	 *
	 *  \param int end 动画结束帧
	 *
	 *  \param const char *name 新的动画名称
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int Edit( int animation, int start, int end, const char *name ) = 0;

	/*! \fn int SetState( int state ) = 0
	 *  \brief 设置当前动画
	 *
	 *  设置当前动画
	 *
	 *  \param int state 当前动画
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int SetState( int state ) = 0;

	/*! \fn int SetType( int type ) = 0
	 *  \brief 设置顶点动画类型
	 *
	 *  设置顶点动画类型
	 *
	 *  \param int type 动画类型，当为 0 时，该动画循环播放时，最后一帧和第一帧间
	 *                  进行插值，用于首尾相接的动画，如人物跑的动作，这也是缺省的
	 *                  动画类型；当为 1 时，该动画循环播放时，最后一帧和第一帧间
	 *                  不进行插值，用于首尾不相接的动画，如人物攻击的动作。
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 返回脚本的执行状态。
	 */
	virtual int SetType( int type ) = 0;

	/*! \fn void Unload ( void ) = 0
	 *  \brief 释放顶点动画所占内存
	 *
	 *  释放顶点动画所占内存
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void Unload ( void ) = 0;	

};