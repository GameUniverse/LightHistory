/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   video.h
 *  内容:   视频(音频)函数
 *
 ****************************************************************************/


/*! \file video.h
 * 视频(音频)函数.
 * 此文件是视频(音频)函数头文件.
 */

/* 重复播放，直到明确停止 */
#define LIGHT_REPEAT_INFINITE  0x7FFFFFFF

/* 播放状态 */
#define LIGHT_STATE_STOPPED   0
#define LIGHT_STATE_PAUSED    1
#define LIGHT_STATE_PLAYING   2


/** 视频描述符类 */
class LightVideoDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightVideoDesc()
	{
		memset( this, 0, sizeof(LightVideoDesc) );
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


/*! \class LightVideo
 *  \brief 视频/音频类 
 *
 *  本类负责视频/音频文件的播放，支持 MPEG2、AVI、MP3、WAV、MIDI等大部分常见的
 *  视频、音频文件。每个 LightVideo 实例都必须通过 LightEngine 类的 NewVideo 方法分配。 
 */

class LightVideo
{

public:

	/*! \brief 查询父引擎
	 *
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 打开视频文件
	 *
	 *  支持 MPEG2、AVI、MP3、WAV、MIDI等大部分常见的视频、音频文件。
	 *
	 *  \param filename[in] 视频文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see close, play, stop
	 */
	virtual int open ( const char *filename ) = 0;

	/*! \brief 设置播放窗口(全局有效)
	 *	 
	 *  \param left[in] 窗口左边框坐标
	 *
	 *  \param top[in] 窗口上边框坐标
	 *
	 *  \param right[in] 窗口右边框坐标
	 *
	 *  \param bottom[in] 窗口下边框坐标
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setWindow ( int left, int top, int right, int bottom ) = 0;

	/*! \brief 设置播放位置
	 *	 
	 *  \param position[in] 播放位置
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int seek ( double position ) = 0;

	/*! \brief 设置重复播放次数
	 *	 
	 *  \param repeats[in] 重复播放的次数。如果要一直重复播放，直到明确停止，可以设为 LIGHT_REPEAT_INFINITE 。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setRepeats ( int repeats ) = 0;

	/*! \brief 播放
	 *
	 *  播放视频文件。
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int play ( void ) = 0;

	/*! \brief 暂停
	 *
	 *  暂停播放视频文件。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int pause ( void ) = 0;

	/*! \brief 停止
	 *
	 *  停止播放视频文件。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int stop ( void ) = 0;

	/*! \brief 查询播放状态
	 *
	 *  查询视频文件播放状态。
	 *
	 *  \return  返回当前播放状态。返回下面的其中一种播放状态：
	 *           \li LIGHT_STATE_STOPPED   停止状态
	 *           \li LIGHT_STATE_PAUSED    暂停状态
	 *           \li LIGHT_STATE_PLAYING   正在播放
	 */
	virtual int getState ( void ) = 0;

	/*! \brief 关闭视频(音频)文件
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int close ( void ) = 0;

};