/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   shader.h
 *  内容:   着色语言函数
 *
 ****************************************************************************/


/*! \file shader.h
 * 着色语言函数。
 * 此文件是着色语言函数头文件.
 */


/** 着色器描述符类 */
class LightShaderDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightShaderDesc()
	{
		memset( this, 0, sizeof(LightShaderDesc) );
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


/*! \class LightShader
 *  \brief 着色器类
 *
 *  本类负责 OpenGL 着色语言的读取、编译、连接和运行。
 *  每个 LightShader 实例都必须通过 LightEngine 类的 createShader 方法分配， releaseShader 释放。
 */

class LightShader
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 从文件读取 shader 程序
	 *
	 *  支持 OpenGL 着色语言。
	 *
	 *  \param vertex 顶点语言文件名
	 *
	 *  \param fragment 片段语言文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int load( const char *vertex, const char *fragment ) = 0;

	/*! \brief 从字符串读取 shader 程序
	 *
	 *  支持 OpenGL 着色语言。
	 *
	 *  \param vertex 顶点语言文件名
	 *
	 *  \param fragment 片段语言文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int loadString( const char *vertex, const char *fragment ) = 0;

	/*! \brief 编译 shader 程序
	 *
	 *  支持 OpenGL 着色语言。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual bool compile( void ) = 0;

	/*! \brief 链接 shader 程序
	 *
	 *  支持 OpenGL 着色语言。
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual bool link( void ) = 0;

	/*! \brief 查询变量句柄
	 *
	 *  根据变量名称查询变量句柄，此句柄可以用来设置变量的值。
	 *
	 *  \param name[in] 要查询变量的名称
	 *	 
	 *  \return 此函数返回一个整数，表示该变量的句柄。如果没有找到该变量，或者 name 以保留前缀 “gl_” 开始，则返回 -1 。
	 *
	 *  \see 
	 */
	virtual int getVariableHandle( const char * name ) = 0;

	/*! \fn void Variable{1|2|3|4}{f|i}( int handle, TYPE v ) = 0
	 *  \brief 设置变量的值
	 *	 
	 *  \param int handle 要设置变量的句柄
	 *	 
	 *  \param TYPE v 要设置变量的值
	 *	 
	 *  \return 此函数没有返回值
	 *
	 *  \see 
	 */
	virtual void variable1f( int handle, float value ) = 0;
	virtual void variable2f( int handle, float x, float y ) = 0;
	virtual void variable3f( int handle, float x, float y, float z ) = 0;
	virtual void variable4f( int handle, float x, float y, float z, float w ) = 0;
	virtual void variable1i( int handle, int value ) = 0;
	virtual void variable2i( int handle, int x, int y ) = 0;
	virtual void variable3i( int handle, int x, int y, int z ) = 0;
	virtual void variable4i( int handle, int x, int y, int z, int w ) = 0;

	/*! \brief 开始使用 shader 程序
	 *
	 *  支持 OpenGL 着色语言。
	 *	 
	 *  \see 
	 */
	virtual void begin( void ) = 0;

	/*! \brief 停止使用 shader 程序
	 *
	 *  支持 OpenGL 着色语言。
	 *	 
	 *  \see 
	 */
	virtual void end( void ) = 0;

	/*! \brief 查询信息日志
	 *
	 *  支持 OpenGL 着色语言。
	 *
	 *  \param string[out] 存放信息日志的字符串指针。
	 *	 
	 *  \param size[in] 存放信息日志的字符串大小。
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int getInfoLog( char *string, int size ) = 0;

	/*! \brief 释放 shader 程序所占内存
	 *
	 *  释放 shader 程序所占内存
	 */
	virtual void unload ( void ) = 0;

};