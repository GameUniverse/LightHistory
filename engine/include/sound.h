/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   sound.h
 *  内容:   声音类
 *
 ****************************************************************************/


/*! \file sound.h
 * 声音函数.
 * 此文件是声音函数文件.
 */


/* 声音处理模式 */
#define LIGHT_S3DMODE_NORMAL         0x0000
#define LIGHT_S3DMODE_HEADRELATIVE   0x0001
#define LIGHT_S3DMODE_DISABLE        0x0002


/** 声音描述符类 */
class LightSoundDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightSoundDesc()
	{
		memset( this, 0, sizeof(LightSoundDesc) );
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


/*! \class LightSound
 *  \brief 声音类
 *
 *  声音在游戏中的重要性不言而喻，没有声音的游戏世界是无法想像的。本类负责声音文件
 *  的播放，支持 WAV 和 MIDI 格式的声音文件。每一个独立的声音称为声源。每个声源分配
 *  一个 LightSound 实例，每个实例都必须通过 LightEngine 类的 createSound 方法分配，
 *  releaseSound 释放。
 *  声音类提供了游戏开发者需要的两个重要特性：速度快和可控制性强。同时还支持以下特性：
 *
 *  \li 当硬件空闲时自动启用硬件加速。
 *  \li 不受数量限制的声源混合。
 *  \li 极短的声音重现延迟。
 *  \li 利用硬件的新特性而不改变函数。
 */

class LightSound
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 读入声音文件
     *
	 *  将声音文件读入内存中
	 *
     *  \param filename[in] 音乐文件名。
     *
	 *  \remarks 支持 WAV 和 MIDI 文件。
	 *
     *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
     */
	virtual int load ( const char *filename ) = 0;

	/*! \brief 设置重复播放次数
	 *
	 *  设置声音重复播放的次数
	 *
	 *  \param repeats[in] 复数次数
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int setRepeats ( int repeats ) = 0;

	/*! \brief 播放
	 *
	 *  播放读入内存的声音
	 *
	 *  \remarks 完全支持混音，支持多个声音同时播放，也支持同一个声音同时播放多次。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int play ( void ) = 0;

	/*! \brief 暂停
	 *
	 *  暂停正在播放的声音
	 *	 
	 *  \return 本函数没有返回值。
	 */
	virtual int pause ( void ) = 0;

	/*! \brief 停止
	 *
	 *  停止正在播放的声音
	 *	 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int stop ( void ) = 0;

	/*! \brief 查询声音播放状态
	 *	 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 返回声音的播放状态。
	 */
	virtual int getState( void ) = 0;

	/*! \brief 释放音乐(MIDI)和声音(WAV)文件所占内存
	 *	 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void unload ( void ) = 0;


	/*! \brief 设置听众位置
	 *
	 *  设置 3D 声场的听众位置
	 *
	 *  \param x[in] 听众位置的 x 坐标
	 *
	 *  \param y[in] 听众位置的 y 坐标
	 *
	 *  \param z[in] 听众位置的 z 坐标
	 *
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setListenerPosition( float x, float y, float z ) = 0;

	/*! \brief 设置听众方向
	 *
	 *  设置 3D 声场的听众方向
	 *
	 *  \param xFront[in] 听众前方的 x 坐标
	 *
	 *  \param yFront[in] 听众前方的 y 坐标
	 *
	 *  \param zFront[in] 听众前方的 z 坐标
	 *
	 *  \param xTop[in] 听众上方的 x 坐标
	 *
	 *  \param yTop[in] 听众上方的 y 坐标
	 *
	 *  \param zTop[in] 听众上方的 z 坐标
	 *
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setListenerOrientation( float xFront, float yFront, float zFront, float xTop, float yTop, float zTop ) = 0;

	/*! \brief 设置听众速度
	 *
	 *  设置 3D 声场的听众速度
	 *
	 *  \param x[in] 听众速度的 x 分量
	 *
	 *  \param y[in] 听众速度的 y 分量
	 *
	 *  \param z[in] 听众速度的 z 分量
	 *
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setListenerVelocity( float x, float y, float z ) = 0;

	/*! \brief 设置距离因子
	 *
	 *  设置 3D 声场的距离因子
	 *
	 *  \param DistanceFactor[in] 距离因子
	 *	 
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setDistanceFactor( float DistanceFactor ) = 0;

	/*! \brief 设置多普勒因子
	 *
	 *  设置 3D 声场的多普勒因子
	 *
	 *  \param DopplerFactor[in] 多普勒因子
	 *	 
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setDopplerFactor( float DopplerFactor ) = 0;

	/*! \brief 设置声波衰减因子
	 *
	 *  设置 3D 声场的声波衰减因子
	 *
	 *  \param RolloffFactor[in] 声波衰减因子
	 *	 
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setRolloffFactor( float RolloffFactor ) = 0;


	/*! \brief 设置声音处理模式
	 *
	 *  设置 3D 声场的声音处理模式
	 *
	 *  \param mode[in] 声音处理模式，分为正常、头部相关和禁用三种模式。
	 *	 
	 *  \remarks 一个声音设置后，对所有声音均有效。
	 *
	 *  \note LIGHT_S3DMODE_NORMAL 是正常模式，声源的位置和方向在空间里是不变的。通过用于声源不会相对于听者移动或转动
	 *  的情况。LIGHT_S3DMODE_HEADRELATIVE 是头部相关模式，声源的 3D 特性和听者的当前位置，速度和朝向都有关。当听者移
	 *  动旋转时，缓冲器自动地在空间中重新定位。头部相关模式可以用于处理如蜜蜂绕听者的头部嗡嗡叫的哪种声音。这是默认
	 *  模式。然而，大部分和听者一起移动的声音都不是 3D 声音。LIGHT_S3DMODE_DISABLE 是禁用模式，3D 声音处理是无效的，
	 *  声音好像是从听者的头部中心发出的。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setMode( int mode ) = 0;

	/*! \brief 设置声音位置
	 *
	 *  设置声音在 3D 声场中的位置
	 *
	 *  \param x[in] 声音位置的 x 坐标
	 *
	 *  \param y[in] 声音位置的 y 坐标
	 *
	 *  \param z[in] 声音位置的 z 坐标
	 *
	 *  \remarks 一次设置后，一直有效，直到重新设置为止。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setPosition ( float x, float y, float z ) = 0;

	/*! \brief 设置声音速度
	 *
	 *  设置声音在 3D 声场中的速度
	 *
	 *  \param x[in] 声音速度的 x 分量
	 *
	 *  \param y[in] 声音速度的 y 分量
	 *
	 *  \param z[in] 声音速度的 z 分量
	 *
	 *  \remarks 一次设置后，一直有效，直到重新设置为止。
	 *
	 *  \note 速度的单位是米/秒。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setVelocity ( float x, float y, float z ) = 0;

	/*! \brief 设置声音锥体角度
	 *	 
	 *  \param inncone[in] 内锥体角度
	 *
	 *  \param outcone[in] 外锥体角度
	 *	 
	 *  \remarks 一次设置后，一直有效，直到重新设置为止。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setConeAngles ( int inncone, int outcone ) = 0;

	/*! \brief 设置声音锥体方向
	 *	 
	 *  \param x[in] 声音锥体方向的 x 分量
	 *
	 *  \param y[in] 声音锥体方向的 y 分量
	 *
	 *  \param z[in] 声音锥体方向的 z 分量
	 *
	 *  \remarks 一次设置后，一直有效，直到重新设置为止。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setConeOrientation( float x, float y, float z ) = 0;

	/*! \brief 设置声音锥体外的音量
	 *	 
	 *  \param inncone[in] 声音锥体外的音量
	 *	 
	 *  \remarks 一次设置后，一直有效，直到重新设置为止。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setConeOutsideVolume( long ConeOutsideVolume ) = 0;

	/*! \brief 设置声音最大距离
	 *
	 *  设置声音最大距离。当一个声源离听者的距离达到某距离后，听者听到的音量不再减少，这个距离就是最大距离。
	 *
	 *  \param MaxDistance[in] 声音最大距离
	 *	 
	 *  \remarks 默认的最大距离是十亿，表示即使当声音已经远远超出听觉范围之外时，声音的衰减都还会被计算，所以对于软件
	 *  缓冲器来说，为了避免不必要的计算，应该设定一个合理的最大距离值；最大距离值也可以用于防止一个声音太远时听不见。
	 *  距离的数值默认用米（m）表示。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setMaxDistance( float MaxDistance ) = 0;

	/*! \brief 设置声音最小距离
	 *
	 *  设置声音最小距离。当一个声源离听者的距离在某个值之内时，听者听到的音量是最大值，不会发生衰减，这个距离就是最小距离。
	 *
	 *  \param MaxDistance[in] 声音最小距离
	 *	 
	 *  \remarks 对声音设置的最小距离决定了声音随着距离衰减的速度。举例来说，可能为一个喷气引擎将这一数值设定为 100km 而
	 *  为一只蜜蜂设定为 2cm 。在这样的设定下，当听者在远离 200km 处，听到的喷气引擎的音量是原来的一半；但是只要远离蜜蜂
	 *  4m 远，听到蜜蜂的声音就是原来的一半了。默认的最小距离是 1 个单位，如果用默认距离因子的话就是 1m 。在这个默认值下，
	 *  当声音远离听者 1m 时，听到的声音是它完整的音量，在 2m 时听到的是一半音量，在 4m 时听到的是四分之一音量。对大多数的
	 *  声音都可能要设定一个比较大的最小距离，以便当它移开的时候，声音不会衰减得那么快。距离的数值默认用米（m）表示。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setMinDistance( float MinDistance ) = 0;
};