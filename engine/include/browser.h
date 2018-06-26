/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   browser.h
 *  内容:   浏览器函数
 *
 ****************************************************************************/


/*! \file browser.h
 * 浏览器函数.
 * 此文件是浏览器函数头文件.
 */

/* 重复播放，直到明确停止 */
#define LIGHT_REPEAT_INFINITE  0x7FFFFFFF

/* 播放状态 */
#define LIGHT_STATE_STOPPED   0
#define LIGHT_STATE_PAUSED    1
#define LIGHT_STATE_PLAYING   2


/** 浏览器描述符类 */
class LightBrowserDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightBrowserDesc()
	{
		memset( this, 0, sizeof(LightBrowserDesc) );
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


/*! \class LightBrowser
 *  \brief 浏览器类 
 *
 *  本类负责交互式文件的播放，支持 GIF、SWF、网页文件，支持本地和网络两种播放方式。
 *  每个 LightBrowser 实例都必须通过 LightEngine 类的 createBrowser 方法分配， releaseBrowser 释放。
 */

class LightBrowser
{

public:

	/*! \brief 打开交互式文件
	 *
	 *  支持 GIF、SWF、网页文件，支持本地和网络两种播放方式。
	 *
	 *  \param filename 交互式文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see close, play, stop
	 */
	virtual int open( const char *address ) = 0;

	/*! \brief 设置播放窗口位置和大小
	 *	 
	 *  \param x 窗口左上角 x 坐标
	 *
	 *  \param y 窗口左上角 y 坐标
	 *
	 *  \param width 窗口宽度
	 *
	 *  \param height 窗口高度
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setWindowPosition( int x, int y, int width, int height ) = 0;

	/*! \brief 设置播放位置
	 *	 
	 *  \param position 播放位置
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int seek( double position ) = 0;

	/*! \brief 设置重复播放次数
	 *	 
	 *  \param repeats 重复播放的次数。如果要一直重复播放，直到明确停止，可以设为 LIGHT_REPEAT_INFINITE 。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setRepeats( int repeats ) = 0;

	/*! \brief 播放
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int play( void ) = 0;

	/*! \brief 暂停
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int pause( void ) = 0;

	/*! \brief 停止
	 *		 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int stop( void ) = 0;

	/*! \brief 查询播放状态
	 *	 
	 *  \return  返回当前播放状态。返回下面的其中一种播放状态：
	 *           \li LIGHT_STATE_STOPPED   停止状态
	 *           \li LIGHT_STATE_PAUSED    暂停状态
	 *           \li LIGHT_STATE_PLAYING   正在播放
	 */
	virtual int getState( void ) = 0;

	/*! \brief 关闭交互式文件
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int close( void ) = 0;

};