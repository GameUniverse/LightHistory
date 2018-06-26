/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   image.h
 *  内容:   图像类
 *
 ****************************************************************************/


/*! \file image.h
 * 图像函数.
 * 此文件是图像函数头文件.
 */


class LightImage;


/* 图像显示特效标志 */
#define LIGHT_IMAGE_SOURRECT    0x00000001
#define LIGHT_IMAGE_DESTRECT    0x00000002
#define LIGHT_IMAGE_ROTATE      0x00000004
#define LIGHT_IMAGE_BLEND       0x00000008
#define LIGHT_IMAGE_LIGHTENESS  0x00000010
#define LIGHT_IMAGE_REVERSALX   0x00000020
#define LIGHT_IMAGE_REVERSALY   0x00000040

#ifdef LIGHT_CORPORATION_EDITION

#define LIGHT_IMAGE_MASK        0x00000080
#define LIGHT_IMAGE_MASKRECT    0x00000100
#define LIGHT_IMAGE_SECTOR      0x00000200
#define LIGHT_IMAGE_LAYER       0x00000400

#endif

/** 图像渲染描述符类 */
class LightImageRenderDesc
{
public:

	/** 标志       */
	DWORD flags;

	/** 渲染层     */
	short layer;

	/** 源区域     */
	RECT  sour_rect;

	/** 目标区域   */
	RECT  dest_rect;

	/** 图像掩码 */
	struct
	{
		/** 掩码图像 */
		LightImage * image;

		/** 掩码区域   */
		RECT  rect;

	} mask;

	/** 扇形阴影 */
	struct
	{
		/** 扇形角度 */
		float angle;

		/** 阴影颜色 */
		int shadow_color[3];

	} sector;

	/** 旋转角度   */
	float rotate;

	/** 透明度     */
	float blend;

	/** 亮度       */
	float lighteness;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightImageRenderDesc()
	{
		memset( this, 0, sizeof(LightImageRenderDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */
	LIGHT_INLINE void setToDefault()
	{
		flags = 0;
		layer = 0;
		sour_rect.left = 0;
		sour_rect.top = 0;
		sour_rect.right = 128;
		sour_rect.bottom = 128;
		dest_rect.left = 0;
		dest_rect.top = 0;
		dest_rect.right = 128;
		dest_rect.bottom = 128;
		mask.image = NULL;
		mask.rect.left = 0;
		mask.rect.top = 0;
		mask.rect.right = 128;
		mask.rect.bottom = 128;
		rotate = 0.0f;
		blend = 1.0f;
		lighteness = 1.0f;
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


class LightEngine;


/** 图像描述符类 */
class LightImageDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */
	LIGHT_INLINE LightImageDesc()
	{
		memset( this, 0, sizeof(LightImageDesc) );
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


/*! \class LightImage
 * \brief 图像类
 *
 *  本类负责图像文件的读取和显示，支持渲染到图像。
 *  支持 25 种图像文件 .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal, .pbm, .pcd, .pcx, .pgm,
 *  .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga, .tif 和 .hdr 的读取，支持 15 种图像文件 .bmp, .dds, .h, .jpg,
 *  .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga 和 .tif 的保存。
 *  每个 LightImage 实例都必须通过 LightEngine 类的 createImage 方法分配， releaseImage 释放。
 */

class LightImage
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 将图像文件读入内存
	 *	 
	 *  \param filename[in] 图像文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int load ( const char *filename ) = 0;

	/*! \brief 从内存中创建图像
	 *	 
	 *  \param width[in] 图像宽度
	 *
	 *  \param height[in] 图像高度
	 *
	 *  \param rgba[in] 图像颜色数据指针
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int build( int width, int height, unsigned char *rgba ) = 0;
    
	/*! \brief 创建新图像
	 *	 
	 *  \param width[in] 图像宽度
	 *
	 *  \param height[in] 图像高度
	 *
	 *  \param type[in] 图像类型
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int create( int width, int height, int type ) = 0;

	/*! \brief 查询图像是否有效
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual bool isValid( void ) = 0;

	/*! \brief 设置动画播放速度
	 *	 
	 *  \param speed[in] 动画播放的速度，用每帧持续的时间表示，以千分之一秒为单位。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int speed( int speed ) = 0;

	/*! \brief 在指定位置显示图像
	 *	 
	 *  \param x 图像左上角在屏幕上 x 坐标
	 *
	 *  \param y 图像左上角在屏幕上 y 坐标
	 *	 
	 *  \see 
	 */
	virtual void render( int x, int y ) = 0;

	/*! \brief 在指定位置显示图像特效
	 *	 
	 *  \param x 图像左上角在屏幕上 x 坐标
	 *
	 *  \param y 图像左上角在屏幕上 y 坐标
	 *	 
	 *  \param desc 图像显示特效描述符，具体结构见头文件的定义。
	 *		 
	 *  \see 
	 */
	virtual void renderDesc( int x, int y, LightImageRenderDesc & desc ) = 0;

	/*! \brief 插入图像帧
	 *
	 *  新插入的图像帧将会设为当前图像帧。
	 *
	 *  \param position[in] 插入位置。
	 *
	 *  \param order[in] 插入次序，0 = 前面，1 = 后面。
	 *
	 *  \return 如果函数调用成功，返回新图像帧位置，否则，返回 -1。
	 *
	 *  \see 
	 */
	virtual int insertFrame( int position, int order = 0 ) = 0;

	/*! \brief 删除图像帧
	 *
	 *  如果删除后当前帧无效，则当前帧将被设为 0。
	 *
	 *  \param frame[in] 当前图像帧。
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回非零值。
	 *
	 *  \see 
	 */
	virtual int deleteFrame( int frame ) = 0;

	/*! \brief 选择当前图像帧
	 *
	 *  指定当前要渲染和操作的帧，在调用 load 和 save 前必须指定要读取和保存的目标帧（只对帧动画图像有效）。
	 *
	 *  \param int frame 当前图像帧。
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回非零值。
	 *
	 *  \see 
	 */
	virtual int selectFrame( int frame ) = 0;

	/*! \brief 查询图像的宽度和高度
	 *	 
	 *  \param size[out] 返回图像大小
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int getSize ( SIZE & size ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \brief 渲染到图像
	 *	 
	 *  \param texture[in] 渲染目标（TRUE = 渲染到图像，FALSE = 渲染到窗口）
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int renderToTexture( bool texture ) = 0;

	/*! \brief 将图像颜色数据保存到指定的图像文件中。
	 *
	 *  将图像颜色数据保存到指定的图像文件中。如果是动画图像，则保存活动帧。
	 *  支持 15 种图像文件 .bmp, .dds, .h, .jpg, .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga 和 .tif 的保存
	 *
	 *  \param filename[in]  要保存颜色数据的图像文件名
	 *	 
	 *  \param format[in]  图像文件的格式，如果是 LIGHT_AUTO 则根据文件扩展名确定。
	 *	 
	 *  \param color[in]  图像文件的颜色模式
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int save( const char *filename, int format, int color ) = 0;

#endif

	/*! \brief 从内存中释放图像
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int unload ( void ) = 0;

};