/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   text.h
 *  内容:   文字类
 *
 ****************************************************************************/


/*! \file text.h
 * 文字函数.
 * 此文件是文字函数头文件.
 */

/* 文字背景混合模式 */
#define LIGHT_TRANSPARENT    0  // 透明的
#define LIGHT_OPAQUE         1  // 不透明的


/** 文字描述符类 */
class LightTextDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightTextDesc()
	{
		memset( this, 0, sizeof(LightTextDesc) );
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


/*! \class LightText
 * \brief 文字类
 *
 *  本类负责文字的高速显示，支持中文显示。同时支持各种字体、大小、间隔、旋转、斜体、下划线、各种质量的文字显示。
 *  每个 LightText 实例都必须通过 LightEngine 类的 createText 方法分配， releaseText 释放。
 */

class LightText
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 显示指定的文字（支持中文）
	 *	 
	 *  \param string[in] 要显示的字符串，以 0 结束，支持中文
	 *
	 *  \remarks 这里是相关的备注信息。
	 */
	virtual void drawText( const char *string ) = 0;

	/*! \brief 查询字符串的宽度和高度
	 *	 
	 *  \param string[in] 要查询的字符串，以 0 结束，支持中文	 
	 *
	 *  \param size[out] 返回字符串宽度和高度数据的指针
	 *
	 *  \remarks 这里是相关的备注信息。
	 */
	virtual int getTextSize( const char *string, SIZE *size ) = 0;

	/*! \brief 设置当前文字颜色
	 *	 
	 *  \param red[in] 颜色的红色分量
	 *
	 *  \param green[in] 颜色的绿色分量
	 *
	 *  \param blue[in] 颜色的蓝色分量
	 *
	 *  \remarks 红、绿、蓝三种颜色分量的有效范围均为 0~255 ， 0 为最暗， 255 为最亮。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void color( int red, int green, int blue ) = 0;
    
	/*! \brief 设置文字背景混合模式
	 *	 
	 *  \param mode[in] 文字背景混合模式， LIGHT_TRANSPARENT 为透明的， LIGHT_OPAQUE 为不透明的。
	 *
	 *  \remarks 缺省情况下为 LIGHT_TRANSPARENT，透明的。
	 *
	 *  \return 返回原来的文字背景混合模式。
	 */
	virtual int setBackMode( int mode ) = 0;

	/*! \brief 设置当前文字背景色
	 *	 
	 *  \param red[in] 颜色的红色分量
	 *
	 *  \param green[in] 颜色的绿色分量
	 *
	 *  \param blue[in] 颜色的蓝色分量
	 *
	 *  \remarks 红、绿、蓝三种颜色分量的有效范围均为 0~255 ， 0 为最暗， 255 为最亮。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void backColor( int red, int green, int blue ) = 0;
    
	/*! \brief 设置文字显示位置
	 *
	 *  设置文字在屏幕上（全屏方式下）或窗口中（窗口方式下）的显示位置。
	 *
	 *  \param x[in] 文字位置的 x 坐标
	 *
	 *  \param y[in] 文字位置的 y 坐标
	 *	
	 *  \remarks 文字应位于屏幕内（全屏方式下）或窗口中（窗口方式下），否则会无法显示。
	 */
	virtual void setTextPos( int x, int y ) = 0;

	/*! \brief 设置字符间距
	 *
	 *  设置两个字符之间的距离
	 *
	 *  \param space[in] 两个字符之间的距离，以像素为单位
	 *
	 *  \remarks 一般不用设置此间距值，缺省的值即可满足大部分需要。
	 *
	 *  \return 返回原来的字符间距值。
	 */
	virtual int setCharSpace( int space ) = 0;

	/*! \brief 设置字体
	 *
	 *  注意：不可过于地频繁调用此函数，否则会由于内存碎片导致程序运行变慢。
	 *
	 *  \param FontName[in] 指定字体
	 *
	 *  \param Height[in] 指定字体高度
	 *
	 *  \param Width[in] 指定字体宽度
	 *
	 *  \param Weight[in] 指定字体的重量(FW_BOLD=700)
	 *
	 *  \param Escapement[in] 指定角度(1/10度)
	 *
	 *  \param Italic[in] 指定是否斜体
	 *
	 *  \param Underline[in] 指定是否有下划线
	 *
	 *  \param StrikeOut[in] 指定是否是StrikeOut字体
	 *
	 *  \param Quality[in] 指定输出质量
	 *
	 *  \remarks 缺省字为宋体，12号字。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int setFont( const char *FontName, int Height, int Width, int Weight, int Escapement, bool Italic, bool Underline, bool StrikeOut, int Quality ) = 0;

};