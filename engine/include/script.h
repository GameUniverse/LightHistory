/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   script.h
 *  内容:   脚本函数
 *
 ****************************************************************************/


/*! \file script.h
 * 脚本函数.
 * 此文件是脚本函数头文件.
 */


/** 脚本描述符类 */
class LightScriptDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightScriptDesc()
	{
		memset( this, 0, sizeof(LightScriptDesc) );
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


/*! \class LightScript
 *  \brief 脚本类
 *
 *  本类负责 c/c++ 脚本文件的读取，解释，执行，支持引擎绝大部分功能。
 *  每个 LightScript 实例都必须通过 LightEngine 类的 createScript 方法分配， releaseScript 释放。
 */

class LightScript
{

public:

	/*! \brief 查询父引擎
	 *
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 读入脚本文件
     *
	 *  将脚本文件读入内存中
	 *
     *  \param filename[in] 脚本文件名.
     *
	 *  \remarks 支持 lua 脚本文件。
	 *
     *  \return 如果函数调用成功，返回 0；如果函数调用失败，返回错误代码。
     */
	virtual int load ( const char *filename ) = 0;

	/*! \brief 编译脚本
	 *
	 *  编译读入内存的脚本
	 *	 
	 *  \remarks 
	 *
	 *  \return 如果函数调用成功，返回 0；如果函数调用失败，返回错误代码。
	 */
	virtual int build( const char *module ) = 0;

	/*! \brief 根据函数索引查询函数句柄
	 *
	 *  执行编译后的脚本
	 *	 
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int getFunctionIDByIndex( const char *module, int index ) = 0;

	/*! \brief 根据函数名称查询函数句柄
	 *
	 *  执行编译后的脚本
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int getFunctionIDByName( const char *module, const char *name ) = 0;

	/*! \brief 根据函数说明查询函数句柄
	 *
	 *  执行编译后的脚本
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int getFunctionIDByDecl(const char *module, const char *decl) = 0;

	/*! \brief 准备执行指定的函数
	 *	 
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int prepare( int funcId ) = 0;

	/*! \brief 执行脚本
	 *
	 *  执行编译后的脚本
	 *	 
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int execute() = 0;

	/*! \brief 中止脚本
	 *
	 *  执行编译后的脚本
	 *	 
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int abort() = 0;

	/*! \brief 暂停脚本
	 *	 
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int suspend() = 0;

	/*! \brief 执行指定的脚本字符串
	 *	 
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 可以解释执行脚本。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual int executeString(const char *module, const char *script ) = 0;

	/*! \brief 查询脚本执行状态
	 *	 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 返回脚本的执行状态。
	 */
	virtual int getState( void ) = 0;

	/*! \brief 释放脚本文件所占内存
	 *	 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void unload ( void ) = 0;	

};