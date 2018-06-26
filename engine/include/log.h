/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   log.h
 *  内容:   日志函数
 *
 ****************************************************************************/


/*! \file log.h
 * 日志函数.
 * 此文件是日志函数头文件.
 */


/** 日志描述符类 */
class LightLogDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightLogDesc()
	{
		memset( this, 0, sizeof(LightLogDesc) );
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


/*! \class LightLog
 *  \brief 日志类 
 *
 *  本类负责日志的信息的输出、控制和管理，目前支持输出到文件。
 *  每个 LightLog 实例都必须通过 LightEngine 类的 createLog 方法分配， releaseLog 释放。
 */

class LightLog
{

public:

	/*! \brief 打开日志输出设备
     *	
     *  \param device[in] 要打开的日志输出设备名称，目前只支持文件设备，应将此参数设为一个文件名（可以保含路径）。
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 如果函数调用成功，返回 0；如果函数调用失败，返回错误代码。
     */
	virtual int open ( const char *device ) = 0;

	/*! \brief 输出调试信息
     *	 
     *  \param string[in] 要输出调试的信息
     *	 	 
	 *  \remarks 本函数没有相关信息。     
     */
	virtual void debug ( const char *string ) = 0;

    /*! \brief 输出一般信息
     *	 
     *  \param string[in] 要输出的一般信息
     *	 	 
	 *  \remarks 本函数没有相关信息。     
     */
	virtual void message ( const char *string ) = 0;

	/*! \brief 输出警告信息
     *	 
     *  \param string[in] 要输出的警告信息
     *	 	 
	 *  \remarks 本函数没有相关信息。     
     */
	virtual void warning ( const char *string ) = 0;

	/*! \brief 输出错误信息
     *	 
     *  \param string[in] 要输出的错误信息
     *	 	 
	 *  \remarks 本函数没有相关信息。     
     */
	virtual void error ( const char *string ) = 0;

	/*! \brief 关闭日志输出设备
     *	 
     *  \param device[in] 要关闭的日志输出设备名称，目前只支持文件设备，应将此参数设为一个文件名（可以保含路径）。
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 如果函数调用成功，返回 0；如果函数调用失败，返回错误代码。
     */
	virtual int close ( const char *device ) = 0;

};