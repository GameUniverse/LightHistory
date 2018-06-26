/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   engine.h
 *  内容:   引擎类
 *
 ****************************************************************************/


/*! \file engine.h
 * 引擎函数.
 * 此文件是引擎函数头文件.
 */

/* 属性掩码 */
#define LIGHT_DEPTH_BUFFER_BIT               0x00000100
#define LIGHT_COLOR_BUFFER_BIT               0x00004000


/** 渲染内容标志 */
enum LightRenderFlag
{
	/** 颜色渲染标志位（当 LIGHT_RENDER_TEXTURE 位为 1 时，该位被忽略） */
	LIGHT_RENDER_COLOR     = 0x00000001,

	/** 渲染纹理标志位 */
	LIGHT_RENDER_TEXTURE   = 0x00000002,

	/** 渲染光照贴图标志位 */
	LIGHT_RENDER_LIGHTMAP  = 0x00000004,

	/** 渲染线框标志位 */
	LIGHT_RENDER_LINE      = 0x00000008,

	/** 渲染阴影标志位 */
	LIGHT_RENDER_SHADOW    = 0x00000010,

	/** 渲染选择框标志位 */
	LIGHT_RENDER_SELECT    = 0x00000020

};

/** 光线引擎枚举类型 */
enum LightEnum
{
	/** OpenGL 图形渲染器 */
	LIGHT_OPENGL_RENDER,

	/** D3D9 图形渲染器 */
	LIGHT_D3D9_RENDER,

	/** D3D10 图形渲染器 */
	LIGHT_D3D10_RENDER,

	/** 软件图形渲染器 */
	LIGHT_SOFTWARE_RENDER,

	/** 窗口显示模式 */
	LIGHT_WINDOW_MODE,

	/** 全屏显示模式 */
	LIGHT_FULLSCREEN_MODE,

	/** 假全屏显示模式 */
	LIGHT_HALFSCREEN_MODE,

	/** 绑定窗口显示模式 */
	LIGHT_ATTACH_MODE

};


/** 显示模式描述符类 */
class LightDisplaymodeDesc
{
public:

	/** 窗口句柄 */
	HWND hwnd;

	/** 图形渲染器 */
	LightEnum render;

	/** 显示模式 */
	LightEnum mode;

	/** 窗口模式参数 */
	struct
	{ 
		/** 窗口左上角 x 坐标 */
		int x;

		/** 窗口左上角 y 坐标 */
		int y;

		/** 窗口宽度 */
		int width;

		/** 窗口高度 */
		int height;

	} window;

	/** 全屏模式参数 */
	struct
	{ 
		/** 屏幕水平分辨率 */
		int width;

		/** 屏幕垂直分辨率 */
		int height;

		/** 屏幕颜色深度 */
		int color;

		/** 屏幕刷新率 */
		int refurbish;

	} fullscreen;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */
	LIGHT_INLINE LightDisplaymodeDesc()
	{
		memset( this, 0, sizeof(LightDisplaymodeDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		hwnd = NULL;
		render = LIGHT_OPENGL_RENDER;
		mode = LIGHT_WINDOW_MODE;
		window.x = 80;
		window.y = 60;
		window.width = 640;
		window.height = 480;
		fullscreen.width = 800;
		fullscreen.height = 600;
		fullscreen.color = 16;
		fullscreen.refurbish = 0;
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/** 光线引擎描述符类 */
class LightEngineDesc
{
public:

	/** 显示模式 */
	LightDisplaymodeDesc displayMode;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightEngineDesc()
	{
		//memset( this, 0, sizeof(LightEngineDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightEngine
 * \brief 引擎类
 *
 *  本类负责大部分系统功能的调用和其它所有类的实例分配，是引擎最重要的一个类。
 *  此类的实例指针只能通过调用函数 LightEngineCreate 得到，
 *  释放时调用函数 LightEngineRelease。中间可以随时调用 LightEngineGet 得到
 *  引擎实例全局指针。
 *  \n
 *  \n 用法示例：
 *  \n
 *  \n // 创建光线引擎实例
 *  \n LightEngine     *engine;
 *  \n LightEngineDesc  engineDesc;
 *  \n engineDesc.display_mode   = LIGHT_WINDOW_MODE;  // 窗口显示模式
 *  \n engineDesc.window.x       = 200;                // 窗口左上角 x 坐标
 *  \n engineDesc.window.y       = 150;                // 窗口左上角 y 坐标
 *  \n engineDesc.window.width   = 640;                // 窗口宽度
 *  \n engineDesc.window.height  = 480;                // 窗口高度
 *  \n engine = LightEngineCreate( engineDesc );
 *  \n 
 *  \n // 使用引擎...
 *  \n 
 *  \n // 释放光线引擎实例
 *  \n LightEngineRelease( engine );
 */

class LightEngine
{

public:

	/*! \brief 更新物理状态
	 *
	 *  用于物理状态的更新
	 *	 
	 *  \see updateLight
	 */
	virtual void updatePhysics( void ) = 0;

	/*! \brief 更新灯光设置
	 *
	 *  用于灯光的更新
	 *
	 *  \see updatePhysics
	 */
	virtual void updateLight() = 0;

	/*! \brief 绑定渲染目标
	 *		 
	 *  \param[in] render 渲染目标（此值保留，准备以后使用，现在必须设为 0）
	 *	 
	 *  \see 
	 */
	virtual void attachRender( int render=0 ) = 0;

	/*! \brief 分离渲染目标
	 *	 
	 *  \see 
	 */
	virtual void detachRender( void ) = 0;

	/*! \brief 设置当前颜色值
	 *	
	 *  该颜色值影响所有渲染内容，任何渲染到窗口点的颜色值都将乘以该值。
	 *
	 *  \param[in] red 颜色的红色成分（取值范围[0,1]，下同）
	 *  \param[in] green 颜色的绿色成分
	 *  \param[in] blue 颜色的蓝色成分
	 *  \param[in] alpha 颜色的 Alpha 成分
	 *	 
	 *  \see colorMask
	 */
	virtual void color( float red, float green, float blue, float alpha ) = 0;

	/*! \brief 允许（或禁止）写入"帧缓存器"的指定颜色成分
	 *	
	 *  任何渲染到窗口点的颜色值都将受该值影响。
	 *
	 *  \param[in] red 颜色的红色成分（取值范围[TRUE,FALSE]，TURE 为允许，FALSE 为禁止，下同）
	 *  \param[in] green 颜色的绿色成分
	 *  \param[in] blue 颜色的蓝色成分
	 *  \param[in] alpha 颜色的 Alpha 成分
	 *	 
	 *  \see color
	 */
	virtual void colorMask( bool red, bool green, bool blue, bool alpha ) = 0;

	/*! \brief 设置清除后的颜色值
	 *
	 *  用于设置清除后的颜色值
	 *
	 *  \param int red 颜色的红色成分
	 *  \param int green 颜色的绿色成分
	 *  \param int blue 颜色的蓝色成分
	 *  \param int alpha 颜色的 Alpha 成分
	 *	 
	 *  \see clearDepth
	 */
	virtual void clearColor( int red, int green, int blue, int alpha ) = 0;

	/*! \brief 设置清除后的深度值
	 *
	 *  用于设置清除后的深度值
	 *
	 *  \param float depth 清除后的深度值
	 *	 
	 *  \see clearColor
	 */
	virtual void clearDepth( float depth ) = 0;

	/*! \brief 清除指定缓存
	 *
	 *  用于清除指定缓存
	 *
	 *  \param int mask 要清除的缓存
	 *	 
	 *  \see clearColor, clearDepth
	 */
	virtual void clear( int mask ) = 0;


	// 选择

	/*! \brief 设置选择模式缓冲区
	 *	 
	 *  \param size 缓冲区大小
	 *	 
	 *  \param buffer 返回选择数据
	 *	 
	 *  \see 
	 */
	virtual void selectBuffer( int size, unsigned int * buffer ) = 0;

	/*! \brief 设置拾取矩形参数
	 *	 
	 *  \param x 拾取矩形中心位置
	 *	 
	 *  \param y 含义同上
	 *	 
	 *  \param width 拾取矩形大小
	 *	 
	 *  \param height 含义同上
	 *	 
	 *  \see 
	 */
	virtual void pickRectangle( double x, double y, double width, double height ) = 0;

    #define LIGHT_RENDER  0
    #define LIGHT_SELECT  1

	/*! \brief 设置引擎渲染模式
	 *	 
	 *  \param mode 引擎渲染模式，LIGHT_RENDER ＝ 正常渲染，LIGHT_SELECT ＝ 选择模式。
	 *	 
	 *  \return 如果当前渲染模式为 LIGHT_SELECT，使用参数 LIGHT_RENDER 调用时，返回选中的图元数；否则返回 0。
	 *
	 *  \see 
	 */
	virtual int renderMode( int mode ) = 0;

	/*! \brief 初始化名称堆栈
	 *	 
	 *  \see 
	 */
	virtual void initNames( void ) = 0;

	/*! \brief 压入名称堆栈
	 *	 
	 *  \param name 将要压入名称堆栈的名称
	 *	 	 
	 *  \see 
	 */
	virtual void pushName( unsigned int name ) = 0;

	/*! \brief 弹出名称堆栈
	 *	 
	 *  \see 
	 */
	virtual void popName( void ) = 0;

	/*! \brief 将一个名称加载到名称堆栈
	 *	 
	 *  \param name 将要替换名称堆栈顶部的一个名称
	 *	 	 
	 *  \see 
	 */
	virtual void loadName( unsigned int name ) = 0;


	// 渲染内容

	/*! \brief 设置指定的渲染内容标志
	 *	 
	 *  \param renderFlag[in] 渲染内容标志
	 *		 
	 *  \see 
	 */
	virtual void raiseRenderFlag( LightRenderFlag renderFlag ) = 0;

	/*! \brief 清除指定的渲染内容标志
	 *	 
	 *  \param renderFlag[in] 渲染内容标志
	 *		 
	 *  \see 
	 */
	virtual void clearRenderFlag( LightRenderFlag renderFlag ) = 0;

	/*! \brief 查询指定的渲染内容标志
	 *	 
	 *  \param renderFlag[in] 渲染内容标志
	 *		 
	 *  \see 
	 */
	virtual bool readRenderFlag( LightRenderFlag renderFlag ) = 0;


	/*! \brief 更新游戏窗口显示内容
	 *
	 *  更新游戏窗口显示内容
	 *
	 *  \param 无
	 *
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see clear, clearColor, clearDepth
	 */
	virtual bool swapBuffers( void ) = 0;

	/*! \brief 查询每秒钟显示的帧数
	 *	 
	 *  \return 返回每秒钟显示的帧数
	 *
	 *  \see swapBuffers
	 */
	virtual int getFramePerSecond( void ) = 0;

	/*! \brief 改变显示模式设置
	 *	 
	 *  \param displaymodeDesc[in] 显示模式描述符，用于说明要设置显示模式的特征。
	 *
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */
	virtual int changeDisplaySettings( LightDisplaymodeDesc & displaymodeDesc ) = 0;


    #define LIGHT_OPENGL_COORDINATE_SYSTEM  0  // 缺省设置
    #define LIGHT_3DSMAX_COORDINATE_SYSTEM  1

	/*! \brief 设置引擎坐标系统
	 *	 
	 *  \param int system 要设置的坐标系统
	 *	 
	 *  \return 函数返回原来的坐标系统
	 *
	 *  \see 
	 */
	virtual int coordinateSystem( int system ) = 0;

	/*! \brief 设置当前作图模式（2D/3D）
	 *	 
	 *  \param bool Ortho2D 作图模式，TRUE = 2D，FALSE = 3D	 
	 */
	virtual void ortho2D( bool Ortho2D ) = 0;

	/*! \brief 更新窗口状态
	 *	 
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */
	virtual int updateWindowState( void ) = 0;

	/*! \brief 设置关键色（透明色）
	 *	 
	 *  \param int red 红色分量（0~255）
	 *
	 *  \param int green 绿色分量（0~255）
	 *
	 *  \param int blue 蓝色分量（0~255）
	 *
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */
	virtual int setKeyColor( int red, int green, int blue ) = 0;

	// 混合因子
	// Parameter                             // (f (R) ,f (G) ,f (B) ,f (A) ) 
    #define LIGHT_ZERO 0                     // (0,0,0,0)
    #define LIGHT_ONE  1                     // (1,1,1,1)
    #define LIGHT_SRC_COLOR 0x0300           // (RS/kR,GS/kG,BS/kB,AS/kA)
    #define LIGHT_ONE_MINUS_SRC_COLOR 0x0301 // (1,1,1,1) - (RS/kR,GS/kG,BS/kB,AS/kA)
    #define LIGHT_DST_COLOR 0x0306           // (Rd/kR,Gd/kG,Bd/kB,Ad/kA)
    #define LIGHT_ONE_MINUS_DST_COLOR 0x0307 // (1,1,1,1) 
    #define LIGHT_SRC_ALPHA 0x0302           // AS/kA,AS/kA,AS/kA,AS/kA 
    #define LIGHT_ONE_MINUS_SRC_ALPHA 0x0303 // (1,1,1,1) - (AS/kA,AS/kA,AS/kA,AS/kA) 
    #define LIGHT_DST_ALPHA 0x0304           // (AD/kA,AD/kA,AD/kA,AD/kA) 
    #define LIGHT_ONE_MINUS_DST_ALPHA 0x0305 // (1,1,1,1) - (AD/kA,AD/kA,AD/kA,AD/kA) 
    #define LIGHT_SRC_ALPHA_SATURATE 0x0308  // (i,i,i,1)

	/*! \brief 指定混合的象素算法
	 *
	 *  指定混合的象素算法
	 *
	 *  \param sfactor 源混合因子，可以取值 LIGHT_ZERO, LIGHT_ONE, LIGHT_DST_COLOR, LIGHT_ONE_MINUS_DST_COLOR, LIGHT_SRC_ALPHA, LIGHT_ONE_MINUS_SRC_ALPHA, LIGHT_DST_ALPHA, LIGHT_ONE_MINUS_DST_ALPHA, 和 LIGHT_SRC_ALPHA_SATURATE。
	 *
	 *  \param dfactor 目标混合因子，可以取值 LIGHT_ZERO, LIGHT_ONE, LIGHT_SRC_COLOR, LIGHT_ONE_MINUS_SRC_COLOR, LIGHT_SRC_ALPHA, LIGHT_ONE_MINUS_SRC_ALPHA, LIGHT_DST_ALPHA, 和 LIGHT_ONE_MINUS_DST_ALPHA。
	 *	 
	 *  \see 
	 */
	virtual void blendFunc( int sfactor, int dfactor ) = 0;

	// 渲染剔除面
    #define LIGHT_FRONT             1
    #define LIGHT_BACK              2
    #define LIGHT_FRONT_AND_BACK    3

	/*! \brief 指定渲染时要剔除的面
	 *	 	 
	 *  \param mode 指定要剔除正面还是背面，可以取值 LIGHT_FRONT，LIGHT_BACK，并且 LIGHT_FRONT_AND_BACK 也是认可的；缺省值是 LIGHT_BACK。
	 *	 
	 *  \see 
	 */
	virtual void cullFace( int mode ) = 0;

	/*! \brief 查询音频设备的音量
	 *	 
	 *  \param int device 要查询的音频设备，通常情况下系统只有一个音频设备，则此值设为 0
	 *	 
	 *  \return 返回音频设备的音量值，低字（WORD）是左声道的音量，高字（WORD）是右声道
	 *          的音量，音量范围从 0x0000 到 0xFFFF，0x0000 = 静音，0xFFFF = 最大音量。
	 *
	 *  \see 
	 */	
	virtual DWORD getOutVolume( int device ) = 0;

	/*! \brief 设置音频设备的音量
	 *	 
	 *  \param int device 要设置的音频设备，通常情况下系统只有一个音频设备，则此值设为 0
	 *
	 *  \param int left 左声道的音量，音量范围从 0x0000 到 0xFFFF，0x0000 = 静音，0xFFFF = 最大音量。
	 *
	 *  \param int blue 左声道的音量，音量范围同上。
	 *
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */	
	virtual int setOutVolume( int device, int left, int right ) = 0;

	/*! \brief 转换窗口客户区坐标（2D）到场景世界坐标（3D）
	 *
	 *  需要注意的是此函数的执行结果取决于渲染图像，也就是说必须在要查询的目标对像渲染后立即调用此函数，才能得到正确的结果。
	 *
	 *  \param x 窗口客户区坐标（2D）x 分量
	 *
	 *  \param y 窗口客户区坐标（2D）y 分量
	 *
	 *  \param point 一个浮点数组指针，返回的是该窗口客户区坐标（2D）对应的场景世界坐标（3D）（x，y，z）
	 *	 
	 *  \see 
	 */	
	virtual void windowToWorld( int x, int y, vec3_t point ) = 0;

	/*! \brief 转换场景世界坐标（3D）到窗口客户区坐标（2D）
	 *
	 *  需要注意的是此函数的执行结果取决于渲染图像，也就是说必须在要查询的目标对像渲染后立即调用此函数，才能得到正确的结果。
	 *
	 *  \param x 场景世界坐标（3D）x 分量
	 *
	 *  \param y 场景世界坐标（3D）y 分量
	 *
	 *  \param z 场景世界坐标（3D）z 分量
	 *
	 *  \param point 一个浮点数组指针，返回的是该场景世界坐标（3D）对应的窗口客户区坐标（2D）（x，y，z）
	 *	 
	 *  \see 
	 */	
	virtual void worldToWindow( float x, float y, float z, vec3_t point ) = 0;

	/*! \brief 配送消息
	 *
	 *  配送消息
	 *
	 *  \param 无
	 *	 
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */
	virtual bool dispatchMessage( void ) = 0;

	/*! \brief 注册窗口消息监听函数
	 *
	 *  注册窗口消息监听函数，可以注册多个消息监听函数，这些函数都能收到窗口发来的所有消息。
	 *
	 *  \param WNDPROC lpfnWndProc 窗口消息监听函数
	 *	 
	 *  \return 如果成功返回 TRUE, 否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool registerMessageProc( WNDPROC lpfnWndProc ) = 0;

	/*! \brief 移除窗口消息监听函数
	 *
	 *  移除窗口消息监听函数，只能移除前面已注册的窗口消息监听函数。
	 *
	 *  \param WNDPROC lpfnWndProc 窗口消息监听函数
	 *	 
	 *  \return 如果成功返回 TRUE, 否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool removeMessageProc( WNDPROC lpfnWndProc ) = 0;


	// 光标

	/*! \brief 读取光标文件
	 *
	 *  必须是以 .CUR 或 .ANI  结尾的 windows 光标文件。
	 *
	 *  \param filename[in] 光标文件名称
	 *	 
	 *  \return 如果读取成功返回正值，表示光标的索引值，否则返回负值。
	 *
	 *  \see destroyCursor，setCursor，showCursor
	 */
	virtual int loadCursor( const char * filename ) = 0;

	/*! \brief 销毁光标
	 *
	 *  此函数释放指定光标占用的任何内存。
	 *
	 *  \param cursor[in] 光标索引，由 loadCursor 得到
	 *	 
	 *  \return 如果函数调用成功返回 TRUE, 否则返回 FALSE
	 *
	 *  \see loadCursor，setCursor，showCursor
	 */
	virtual bool destroyCursor( int cursor ) = 0;

	/*! \brief 设置当前光标
	 *	 
	 *  \param cursor[in] 光标索引，由 loadCursor 得到
	 *	 
	 *  \return 如果设置成功返回 TRUE, 否则返回 FALSE
	 *
	 *  \see loadCursor，destroyCursor，showCursor
	 */
	virtual bool setCursor( int cursor ) = 0;

	/*! \brief 显示（或隐藏）光标
	 *	 
	 *  \param show[in] 指定显示（或隐藏）光标，TRUE 显示光标，FALSE 隐藏光标。
	 *	 	 
	 *  \see loadCursor，destroyCursor，setCursor
	 */
	virtual void showCursor( bool show ) = 0;


	/*! \brief 查询系统启动以来经过的千分之一秒数
	 *
	 *  \return 返回系统启动以来经过的千分之一秒数
	 *
	 *  \see 
	 */
	virtual unsigned long getTickCount( void ) = 0;

	/*! \brief 设置全局环境光的颜色值
	 *	 
	 *  \param float red 红色分量
	 *
	 *  \param float green 绿色分量
	 *
	 *  \param float blue 蓝色分量
	 *
	 *  \param float alpha Alpha 分量
	 *
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */
	virtual int lightAmbient( float red, float green, float blue, float alpha ) = 0;

	/* 状态函数 */
	
	/*! \brief 查询窗口句柄
	 *
	 *  \return 返回窗口句柄
	 *
	 *  \see 
	 */
	virtual HWND getWindowHandle( void ) = 0;

    #define LIGHT_WINDOW_CAPTION       1
    #define LIGHT_WORK_DIRECTORY       2
    #define LIGHT_VIDEO_DIRECTORY      3
    #define LIGHT_MUSIC_DIRECTORY      4
    #define LIGHT_SOUND_DIRECTORY      5
    #define LIGHT_TEXTURE_DIRECTORY    6
    #define LIGHT_LEVEL_DIRECTORY      7
    #define LIGHT_MODEL_DIRECTORY      8
    #define LIGHT_IMAGE_DIRECTORY      9
    #define LIGHT_SCRIPT_DIRECTORY     10
	#define LIGHT_SKY_DIRECTORY        11
	#define LIGHT_PARTICLE_DIRECTORY   12

	/*! \brief 设置指定字符串
	 *	 
	 *  \param int name 要设置的字符串
	 *  \param const char *string 字符串指针
	 *
	 *  \return 如果成功返回 0, 否则返回非 0 值
	 *
	 *  \see 
	 */
	virtual bool setString( int name, const char *string ) = 0;

	/*! \brief 查询指定字符串
	 *	 
	 *  \param int name 要查询的字符串
	 *
	 *  \return 如果成功返回一个字符串指针（该字符串以 0 结尾）， 否则返回 NULL 。
	 *
	 *  \see 
	 */
	virtual const char * getString( int name ) = 0;

	#define LIGHT_ENABLE         1    /* 开启     */
	#define LIGHT_DISABLE        0    /* 禁止     */
	#define LIGHT_AUTOMATIC      2    /* 自动     */

    #define LIGHT_KEY_COLOR      12   /* 关键色   */
    #define LIGHT_BLEND          13   /* 混合     */
    #define LIGHT_TEXTURE        14   /* 纹理     */
    #define LIGHT_SWAP_INTERVAL  15   /* 垂直同步 */
    #define LIGHT_PROJECTION     16   /* 投影纹理 */
    #define LIGHT_LIGHTING       17   /* 光照     */
    #define LIGHT_LOCAL_VIEWER   18   /* 局部视点 */
    #define LIGHT_TWO_SIDE       19   /* 双面光照 */
    #define LIGHT_FOG            20   /* 雾       */
    #define LIGHT_DEPTH_TEST     21   /* 深度测试 */
    #define LIGHT_SAMPLES        22   /* 多重采样 */
    #define LIGHT_CUBE_MAP       23   /* 立方映射 */
    #define	LIGHT_CULL_FACE      24   /* 剔除面   */

	/*! \brief 充许指定功能
	 *	 
	 *  \param int name 要充许的功能
	 *	 
	 *  \see 
	 */
	virtual void enable( int name ) = 0;

	/*! \brief 禁止指定功能
	 *	 
	 *  \param int name 要禁止的功能
	 *	 
	 *  \see 
	 */
	virtual void disable( int name ) = 0;

	/*! \brief 自动指定功能
	 *
	 *  调用该函数后，引擎将会根据需要自动开启或禁止指定的功能。
	 *
	 *  \param int name 要自动的功能
	 *	 
	 *  \see 
	 */
	virtual void automatic( int name ) = 0;

#define LIGHT_MAX_LIGHTS                 5
#define LIGHT_MAX_TEXTURE_SIZE           6
#define LIGHT_RENDERED_NUM_TRIANGLE      7
#define LIGHT_RENDERED_NUM_MESH          8
#define LIGHT_RENDERED_NUM_MODEL         9
#define LIGHT_RENDERED_NUM_LEAF          10

	/*! \brief 查询指定的整型数
	 *	 
	 *  \param int name 要查询的整型数
	 *	 
	 *  \return 返回要查询的整型数
	 *
	 *  \see 
	 */
	virtual int getInteger( int name ) = 0;

	/*! \brief 引擎内部函数
	 * 
	 *  保留函数，请勿调用，否则可能会导致内存错误。
	 *	 
	 *  \param name[in] 保留参数
	 *	 
	 *  \param ...[in] 保留参数
	 *	
	 *  \return 保留返回值
	 *
	 *  \see 
	 */
	virtual int debugging( int num, ... ) = 0;


	// 创建对象

	/*! \fn LightLensFlare * NewLensFlare( void )
	 *  \brief 创建一个镜头光晕
	 *
	 *  创建一个镜头光晕
	 *
	 *  \param 无
	 *	 
	 *  \return 返回要创建的镜头光晕类指针
	 *
	 *  \see 
	 */
	virtual LightLensFlare * NewLensFlare( void ) = 0;

	/*! \fn LightModelMD3 * NewModelMD3( void )
	 *  \brief 创建一个 MD3 模型
	 *
	 *  创建一个 MD3 模型
	 *
	 *  \param 无
	 *	 
	 *  \return 返回要创建的 MD3 模型类指针
	 *
	 *  \see 
	 */
	virtual LightModelMD3 * NewModelMD3( void ) = 0;

	/*! \fn LightFrustum * NewFrustum( void )
	 *  \brief 创建一个视锥体
	 *
	 *  创建一个视锥体
	 *
	 *  \param 无
	 *	 
	 *  \return 返回要创建的视锥体类指针
	 *
	 *  \see 
	 */
	virtual LightFrustum * NewFrustum( void ) = 0;

	/*! \fn LightCollide * NewCollide( void ) = 0
	 *  \brief 创建一个碰撞检测对象
	 *
	 *  创建一个碰撞检测对象
	 *
	 *  \param 无
	 *	 
	 *  \return 返回要创建的碰撞检测对象指针
	 *
	 *  \see 
	 */
	//virtual LightCollide * NewCollide( void ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \fn LightTerrain * NewTerrain ( void ) = 0
	 *  \brief 创建一个地形对象
	 *
	 *  创建一个地形对象
	 *
	 *  \param 无
	 *	 
	 *  \return 返回要创建的地形对象指针
	 *
	 *  \see 
	 */
	virtual LightTerrain * NewTerrain ( void ) = 0;

#endif

	/*! \brief 创建一个场景
	 *	 
	 *  \param sceneDesc 场景描述符指针，用于说明要创建场景的特征。
	 *	 
	 *  \return 返回创建场景的指针
	 *
	 *  \see 
	 */
	virtual LightScene * createScene( const LightSceneDesc & sceneDesc ) = 0;

	/*! \brief 释放一个场景
	 *	 
	 *  \param scene 要释放场景的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseScene( LightScene * scene ) = 0;

	/*! \brief 创建一个摄像机
	 *	 
	 *  \param cameraDesc 摄像机描述符指针，用于说明要创建摄像机的特征。
	 *	 
	 *  \return 返回要创建摄像机的指针
	 *
	 *  \see 
	 */
	virtual LightCamera * createCamera( const LightCameraDesc & cameraDesc ) = 0;

	/*! \brief 释放一个摄像机
	 *	 
	 *  \param camera 要释放摄像机的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseCamera( LightCamera * camera ) = 0;

	/*! \brief 创建一个天空
	 *	 
	 *  \param skyDesc 天空描述符，用于说明要创建天空的特征。
	 *	 
	 *  \return 返回已创建的天空指针
	 *
	 *  \see 
	 */
	virtual LightSky * createSky( const LightSkyDesc & skyDesc ) = 0;

	/*! \brief 释放一个天空
	 *	 
	 *  \param sky 要释放天空的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseSky( LightSky * sky ) = 0;

	/*! \brief 创建一个雾
	 *	 
	 *  \param fogDesc[in] 雾描述符，用于说明要创建雾的特征。
	 *	 
	 *  \return 返回已创建的雾指针
	 *
	 *  \see 
	 */
	virtual LightFog * createFog( const LightFogDesc & fogDesc ) = 0;

	/*! \brief 释放一个雾
	 *	 
	 *  \param fog[in] 要释放雾的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseFog( LightFog * fog ) = 0;

	/*! \fn LightBillboardPool * createBillboardPool( const LightBillboardPoolDesc * billboardPoolDesc ) = 0
	 *  \brief 创建一个布告板池
	 *
	 *  创建一个布告板池
	 *
	 *  \param const LightBillboardPoolDesc * billboardPoolDesc 布告板池描述符指针，用于说明要创建布告板池的特征。
	 *	 
	 *  \return 返回已创建的布告板池指针
	 *
	 *  \see 
	 */
	virtual LightBillboardPool * createBillboardPool( const LightBillboardPoolDesc & billboardPoolDesc ) = 0;

	/*! \fn void releaseBillboardPool(  LightBillboardPool * billboardPool ) = 0
	 *  \brief 释放一个布告板池
	 *
	 *  释放一个布告板池
	 *
	 *  \param LightBillboardPool * billboardPool 要释放布告板池的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseBillboardPool(  LightBillboardPool * billboardPool ) = 0;

	/*! \fn LightParticle * createParticle( const LightParticleDesc * particleDesc ) = 0
	 *  \brief 创建一个粒子
	 *
	 *  创建一个粒子
	 *
	 *  \param const LightParticleDesc * particleDesc 粒子描述符指针，用于说明要创建粒子的特征。
	 *	 
	 *  \return 返回已创建的粒子指针
	 *
	 *  \see 
	 */
	virtual LightParticle * createParticle( const LightParticleDesc & particleDesc ) = 0;

	/*! \fn void releaseParticle( LightParticle * particle ) = 0
	 *  \brief 释放一个粒子
	 *
	 *  释放一个粒子
	 *
	 *  \param LightParticle * particle 要释放粒子的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseParticle( LightParticle * particle ) = 0;

	/*! \brief 创建一个场景
	 *	 
	 *  \param levelDesc[in] 场景描述符，用于说明要创建场景的特征。
	 *	 
	 *  \return 返回已创建的场景指针
	 *
	 *  \see 
	 */
	virtual LightLevel * createLevel( const LightLevelDesc & levelDesc ) = 0;

	/*! \brief 释放一个场景
	 *	 
	 *  \param level[in] 要释放场景的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseLevel( LightLevel * level ) = 0;

	/*! \brief 创建一个骨骼动画
	 *	 
	 *  \param skeletonDesc[in] 骨骼动画描述符，用于说明要创建骨骼动画的特征。
	 *	 
	 *  \return 返回已创建的骨骼动画指针
	 *
	 *  \see 
	 */
	virtual LightSkeleton * createSkeleton( const LightSkeletonDesc & skeletonDesc ) = 0;

	/*! \brief 释放一个骨骼动画
	 *	 
	 *  \param skeleton[in] 要释放骨骼动画的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseSkeleton( LightSkeleton * skeleton ) = 0;

	/*! \brief 创建一个静态网格
	 *	 
	 *  \param meshDesc[in] 静态网格描述符，用于说明要创建静态网格的特征。
	 *	 
	 *  \return 返回已创建的静态网格指针
	 *
	 *  \see 
	 */
	virtual LightMesh * createMesh( const LightMeshDesc & meshDesc ) = 0;

	/*! \brief 释放一个静态网格
	 *	 
	 *  \param mesh[in] 要释放静态网格的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseMesh( LightMesh * mesh ) = 0;

	/*! \brief 创建一个纹理
	 *	 
	 *  \param textureDesc[in] 纹理描述符，用于说明要创建纹理的特征。
	 *	 
	 *  \return 返回已创建的纹理指针
	 *
	 *  \see 
	 */
	virtual LightTexture * createTexture( const LightTextureDesc & textureDesc ) = 0;

	/*! \brief 释放一个纹理
	 *	 
	 *  \param texture[in] 要释放纹理的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseTexture( LightTexture * texture ) = 0;

	/*! \brief 创建一个图像
	 *	 
	 *  \param imageDesc[in] 图像描述符，用于说明要创建图像的特征。
	 *	 
	 *  \return 返回已创建的图像指针
	 *
	 *  \see 
	 */
	virtual LightImage * createImage( const LightImageDesc & imageDesc ) = 0;

	/*! \brief 释放一个图像
	 *	 
	 *  \param image[in] 要释放图像的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseImage( LightImage * image ) = 0;

	/*! \brief 创建一个视频
	 *	 
	 *  \param videoDesc[in] 视频描述符，用于说明要创建视频的特征。
	 *	 
	 *  \return 返回已创建的视频指针
	 *
	 *  \see 
	 */
	virtual LightVideo * createVideo( const LightVideoDesc & videoDesc ) = 0;

	/*! \brief 释放一个视频
	 *	 
	 *  \param video[in] 要释放视频的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseVideo( LightVideo * video ) = 0;

	/*! \brief 创建一个文字
	 *	 
	 *  \param textDesc[in] 文字描述符，用于说明要创建文字的特征。
	 *	 
	 *  \return 返回已创建的文字指针
	 *
	 *  \see 
	 */
	virtual LightText * createText( const LightTextDesc & textDesc ) = 0;

	/*! \brief 释放一个文字
	 *	 
	 *  \param text[in] 要释放文字的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseText( LightText * text ) = 0;

	/*! \brief 创建一个日志
	 *	 
	 *  \param logDesc[in] 日志描述符，用于说明要创建日志的特征。
	 *	 
	 *  \return 返回已创建的日志指针
	 *
	 *  \see 
	 */
	virtual LightLog * createLog( const LightLogDesc & logDesc ) = 0;

	/*! \brief 释放一个日志
	 *	 
	 *  \param log[in] 要释放日志的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseLog( LightLog * log ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \brief 创建一个天气
	 *	 
	 *  \param weatherDesc[in] 天气描述符，用于说明要创建天气的特征。
	 *	 
	 *  \return 返回已创建的天气指针
	 *
	 *  \see 
	 */
	virtual LightWeather * createWeather( const LightWeatherDesc & weatherDesc ) = 0;

	/*! \brief 释放一个天气
	 *	 
	 *  \param weather[in] 要释放天气的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseWeather( LightWeather * weather ) = 0;

	/*! \brief 创建一个浏览器
	 *	
	 *  \param browserDesc[in] 浏览器描述符，用于说明要创建浏览器的特征。
	 *	 
	 *  \return 返回已创建的浏览器指针
	 *
	 *  \see 
	 */
	virtual LightBrowser * createBrowser( const LightBrowserDesc & browserDesc ) = 0;

	/*! \brief 释放一个浏览器
	 *	 
	 *  \param browser[in] 要释放浏览器的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseBrowser( LightBrowser * browser ) = 0;

	/*! \brief 创建一个着色器
	 *	
	 *  \param shaderDesc[in] 着色器描述符，用于说明要创建着色器的特征。
	 *	 
	 *  \return 返回已创建的着色器指针
	 *
	 *  \see 
	 */
	virtual LightShader * createShader( const LightShaderDesc & shaderDesc ) = 0;

	/*! \brief 释放一个着色器
	 *	 
	 *  \param shader[in] 要释放着色器的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseShader( LightShader * shader ) = 0;

	/*! \brief 创建一个水
	 *	
	 *  \param waterDesc[in] 水描述符，用于说明要创建水的特征。
	 *	 
	 *  \return 返回已创建的水指针
	 *
	 *  \see 
	 */
	virtual LightWater * createWater( const LightWaterDesc & waterDesc ) = 0;

	/*! \brief 释放一个水
	 *	 
	 *  \param water[in] 要释放水的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseWater( LightWater * water ) = 0;

#endif

	/*! \brief 创建一个脚本
	 *	
	 *  \param scriptDesc[in] 脚本描述符，用于说明要创建脚本的特征。
	 *	 
	 *  \return 返回已创建的脚本指针
	 *
	 *  \see 
	 */
	virtual LightScript * createScript( const LightScriptDesc & scriptDesc ) = 0;

	/*! \brief 释放一个脚本
	 *	 
	 *  \param script[in] 要释放脚本的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseScript( LightScript * script ) = 0;

	/*! \brief 创建一个画笔
	 *	
	 *  \param brushDesc[in] 画笔描述符，用于说明要创建画笔的特征。
	 *	 
	 *  \return 返回已创建的画笔指针
	 *
	 *  \see 
	 */
	virtual LightBrush * createBrush( const LightBrushDesc & brushDesc ) = 0;

	/*! \brief 释放一个画笔
	 *	 
	 *  \param brush[in] 要释放画笔的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseBrush( LightBrush * brush ) = 0;

	/*! \brief 创建一个输入接口
	 *	
	 *  \param inputDesc[in] 输入接口描述符，用于说明要创建输入接口的特征。
	 *	 
	 *  \return 返回已创建的输入接口指针
	 *
	 *  \see 
	 */
	virtual LightInput * createInput( const LightInputDesc & inputDesc ) = 0;

	/*! \brief 释放一个输入接口
	 *	 
	 *  \param input[in] 要释放输入接口的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseInput( LightInput * input ) = 0;

	/*! \brief 创建一个声音
	 *	
	 *  \param soundDesc[in] 声音描述符，用于说明要创建声音的特征。
	 *	 
	 *  \return 返回已创建的声音指针
	 *
	 *  \see 
	 */
	virtual LightSound * createSound( const LightSoundDesc & soundDesc ) = 0;

	/*! \brief 释放一个声音
	 *	 
	 *  \param sound[in] 要释放声音的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseSound( LightSound * sound ) = 0;

	/*! \brief 创建一个顶点动画
	 *	
	 *  \param animationDesc[in] 顶点动画描述符，用于说明要创建顶点动画的特征。
	 *	 
	 *  \return 返回已创建的顶点动画指针
	 *
	 *  \see 
	 */
	virtual LightAnimation * createAnimation( const LightAnimationDesc & animationDesc ) = 0;

	/*! \brief 释放一个顶点动画
	 *	 
	 *  \param animation[in] 要释放顶点动画的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseAnimation( LightAnimation * animation ) = 0;

	/*! \brief 创建一个二叉树
	 *	
	 *  \param bsptreeDesc[in] 二叉树描述符，用于说明要创建二叉树的特征。
	 *	 
	 *  \return 返回已创建的二叉树指针
	 *
	 *  \see 
	 */
	virtual LightBSPTree * createBSPTree( const LightBSPTreeDesc & bsptreeDesc ) = 0;

	/*! \brief 释放一个二叉树
	 *	 
	 *  \param bsptree[in] 要释放二叉树的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseBSPTree( LightBSPTree * bsptree ) = 0;

	/*! \brief 创建一个灯光
	 *	 
	 *  \param lightDesc[in] 灯光描述符，用于说明要创建灯光的特征。
	 *	 
	 *  \return 返回已创建的灯光指针
	 *
	 *  \see 
	 */
	virtual LightLight * createLight( const LightLightDesc & lightDesc ) = 0;

	/*! \brief 释放一个灯光
	 *	 
	 *  \param light[in] 要释放灯光的指针
	 *	 	 
	 *  \see 
	 */
	virtual void releaseLight( LightLight * light ) = 0;

	/*! \brief 查询纹理数量
	 *	 	 
	 *  \return 返回纹理数量
	 *
	 *  \see 
	 */
	virtual int getTextureNumber() = 0;

	/*! \brief 查询纹理 ID（根据纹理名称）
	 *	 
	 *  \param name[in] 纹理名称。
	 *	 
	 *  \return 返回纹理 ID
	 *
	 *  \see 
	 */
	virtual int getTextureID( const char * name ) = 0;

	/*! \brief 查询纹理（根据纹理 ID）
	 *	 
	 *  \param id[in] 纹理 ID。
	 *	 
	 *  \return 返回纹理指针
	 *
	 *  \see 
	 */
	virtual LightTexture * getTexture( int id ) = 0;

};