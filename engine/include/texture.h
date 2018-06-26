/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   texture.h
 *  内容:   纹理函数，现在能读取 25 种 .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal, .pbm, .pcd, .pcx, .pgm, .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga 和 .tif .hdr 文件。
            支持保存的格式有 15 种： .bmp, .dds, .h, .jpg, .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga 和 .tif. 

 *
 ****************************************************************************/


/*! \file texture.h
 * 纹理函数.
 * 此文件是纹理函数头文件.
 */

// 指定纹理原点
#define LIGHT_ORIGIN_UPPER_LEFT  0
#define LIGHT_ORIGIN_LOWER_LEFT  1

// 纹理通道
#define LIGHT_TEXTURE_CHANNEL_2D   0
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_X   3
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_X   4
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Y   5
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Y   6
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Z   7
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Z   8

// 纹理层
#define LIGHT_TEXTURE_LAYER_0   0
#define LIGHT_TEXTURE_LAYER_1   1
#define LIGHT_TEXTURE_LAYER_2   2
#define LIGHT_TEXTURE_LAYER_3   3
#define LIGHT_TEXTURE_LAYER_4   4
#define LIGHT_TEXTURE_LAYER_5   5
#define LIGHT_TEXTURE_LAYER_6   6
#define LIGHT_TEXTURE_LAYER_7   7

// 图像文件格式
#define LIGHT_AUTO         0x0000
#define LIGHT_BMP          0x0420
#define LIGHT_CUT          0x0421
#define LIGHT_DOOM         0x0422
#define LIGHT_DOOM_FLAT    0x0423
#define LIGHT_ICO          0x0424
#define LIGHT_JPG          0x0425
#define LIGHT_JFIF         0x0425
#define LIGHT_LBM          0x0426
#define LIGHT_PCD          0x0427
#define LIGHT_PCX          0x0428
#define LIGHT_PIC          0x0429
#define LIGHT_PNG          0x042A
#define LIGHT_PNM          0x042B
#define LIGHT_SGI          0x042C
#define LIGHT_TGA          0x042D
#define LIGHT_TIF          0x042E
#define LIGHT_CHEAD        0x042F
#define LIGHT_RAW          0x0430
#define LIGHT_MDL          0x0431
#define LIGHT_WAL          0x0432
#define LIGHT_LIF          0x0434
#define LIGHT_MNG          0x0435
#define LIGHT_JNG          0x0435
#define LIGHT_GIF          0x0436
#define LIGHT_DDS          0x0437
#define LIGHT_DCX          0x0438
#define LIGHT_PSD          0x0439
#define LIGHT_EXIF         0x043A
#define LIGHT_PSP          0x043B
#define LIGHT_PIX          0x043C
#define LIGHT_PXR          0x043D
#define LIGHT_XPM          0x043E
#define LIGHT_HDR          0x043F

#define LIGHT_JASC_PAL     0x0475


class LightEngine;


/** 纹理描述符类 */
class LightTextureDesc
{
public:

	/** 纹理名称 */
	char name[17];

	/** 纹理文件名称 */
	char file[33];

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightTextureDesc()
	{
		memset( this, 0, sizeof(LightTextureDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "" );
		strcpy( file, "" );
		VEC3( position, 0, 0, 0 );		
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightTexture
 * \brief 纹理类
 *
 *  本类负责纹理的读取、创建和管理。支持 25 种图像文件 .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal,
 *  .pbm, .pcd, .pcx, .pgm, .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga, .tif 和 .hdr 的读取，支持 15 种图像文件 .bmp,
 *  .dds, .h, .jpg, .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga 和 .tif 的保存。每个 LightTexture 实例都必
 *  须通过 LightEngine 类的 createTexture 方法分配， releaseTexture 释放。
 */

class LightTexture
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 设置纹理原点
	 *
	 *  当读取纹理时使用。
	 *
	 *  \param mode[in] 原点位置
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void setOrigin( int mode ) = 0;

	/*! \brief 查询纹理原点
	 *	
	 *  \return 返回纹理原点
	 *
	 *  \see 
	 */
	virtual int getOrigin( void ) = 0;

	/*! \brief 纹理 2 次幂大小设置
	 *	 
	 *  \param power2[in] TRUE = 2 次幂大小，FALSE = 非 2 次幂大小
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int power2( bool power2 ) = 0;

	/*! \brief 设置当前纹理通道，当读取纹理时使用
	 *	 
	 *  \param channel[in] 当前纹理通道
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int channel( int channel ) = 0;

	/*! \brief 设置当前纹理层，当激活纹理时使用
	 *	 
	 *  \param layer[in] 当前纹理层
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int layer( int layer ) = 0;

	/*! \brief 设置纹理名称
	 *
	 *  缺省纹理名称为空。当纹理名称为空时，调用 load 函数后，纹理名称会改变为纹理文件名，否则，纹理名称不会改变。
	 *
	 *  \param name[in] 纹理名称，当超出长度时，只取前 16 个字符（字节）。
	 *	 
	 *  \see 
	 */
	virtual void setName( const char * name ) = 0;

	/*! \brief 查询纹理名称
	 *
	 *  纹理名称一般为纹理文件名，缺省纹理名称为空。
	 *
	 *  \param name[out] 返回纹理名称，缓冲区不得小于 17 字节（16 个字符（字节）＋'\0'）。
	 *	
	 *  \see 
	 */
	virtual void getName( char * name ) = 0;

	/*! \brief 将纹理文件读入内存
	 *
	 *  将纹理文件读入内存，现在能读取 25 种 .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal, .pbm, .pcd, .pcx, .pgm, .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga 和 .tif .hdr 文件。
	 *
	 *  \param filename[in] 文件纹理名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int load( const char *filename ) = 0;

	/*! \brief 从内存中创建纹理
	 *	 
	 *  \param width[in] 纹理宽度
	 *
	 *  \param height[in] 纹理高度
	 *
	 *  \param rgba[in] 纹理数据（RGBA）
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int build( int width, int height, unsigned char *rgba ) = 0;

	/*! \brief 创建新纹理
	 *	 
	 *  \param width[in] 纹理宽度
	 *
	 *  \param height[in] 纹理高度
	 *
	 *  \param type[in] 纹理类型， 0 = 普通纹理， 1 = 可渲染纹理
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int create( int width, int height, int type ) = 0;

	/*! \brief 设置栅格动画
	 *
	 *  在现有纹理的基础上设置栅格动画。
	 *
	 *  \param width[in] 栅格动画的宽度
	 *
	 *  \param height[in] 栅格动画的高度
	 *
	 *  \param numframe[in] 动画帧数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int grid( int width, int height, int numframe ) = 0;

	/*! \brief 查询纹理原始的宽度和高度
	 *	 
	 *  \param size[in] 返回纹理大小
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int getSize( SIZE & size ) = 0;

	/*! \brief 查询纹理实际（二次幂）的宽度和高度
	 *	
	 *  \param size 返回纹理实际（二次幂）的大小
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int getSizePower2( SIZE & size ) = 0;

	/*! \brief 查询纹理是否有效
	 *
	 *  \return 如果纹理有效，返回 TRUE，否则返回 FALSE 。
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

	/*! \brief 将纹理激活为当前纹理
	 *
	 *  将纹理激活为当前纹理，如果是动画纹理，则自动播放动画。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int active( void ) = 0;

	/*! \brief 插入纹理帧
	 *
	 *  新插入的纹理帧将会设为当前纹理帧。
	 *
	 *  \param position[in] 插入位置。
	 *
	 *  \param order[in] 插入次序，0 = 前面，1 = 后面。
	 *
	 *  \return 如果函数调用成功，返回新纹理帧位置，否则，返回 -1。
	 *
	 *  \see 
	 */
	virtual int insertFrame( int position, int order = 0 ) = 0;

	/*! \brief 删除纹理帧
	 *
	 *  如果删除后当前帧无效，则当前帧将被设为 0。
	 *
	 *  \param frame[in] 当前纹理帧。
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回非零值。
	 *
	 *  \see 
	 */
	virtual int deleteFrame( int frame ) = 0;

	/*! \brief 选择当前纹理帧
	 *
	 *  指定当前要渲染和操作的帧，在调用 load 和 save 前必须指定要读取和保存的目标帧（只对帧动画纹理有效）。
	 *
	 *  \param frame[in] 当前纹理帧。
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回非零值。
	 *
	 *  \see 
	 */
	virtual int selectFrame( int frame ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \brief 渲染到纹理
	 *	 
	 *  \param texture[in] 渲染目标（TRUE = 渲染到纹理，FALSE = 渲染到窗口）
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int renderToTexture( bool texture ) = 0;

	/*! \brief 将纹理颜色数据保存到指定的图像文件中。
	 *
	 *  将纹理颜色数据保存到指定的图像文件中。如果是动画纹理，则保存活动帧。
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

	/*! \brief 从内存中释放纹理
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int unload( void ) = 0;

};