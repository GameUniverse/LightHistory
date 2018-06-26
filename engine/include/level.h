/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   level.h
 *  内容:   场景函数
 *
 ****************************************************************************/


/*! \file level.h
 * 场景函数.
 * 此文件是场景函数头文件.
 */


class LightEngine;


// 场景描述符
class LightLevelDesc
{
	int    type;                 // 场景类型
	vec3_t position;             // 场景位置

};


/*! \brief 场景类 
 *
 *  本类负责场景文件的读取，渲染、控制、保存，支持地形、网络、BSP格式的场景。
 *  每个 LightLevel 实例都必须通过 LightEngine 类的 createLevel 方法分配。
 */

class LightLevel
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回引擎指针
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 将场景文件读入内存
	 *	 
	 *  \param filename 场景文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int load( const char * filename ) = 0;

	/*! \brief 渲染场景
	 *	 	 
	 */
	virtual void render( void ) = 0;

	/*! \brief 查询显示的三角形数
	 *		 
	 *  \return 返回场景类显示的三角形数。
	 */
	virtual int getTrianglesCount( void ) = 0;

	/*! \brief 查询地形指针
	 *	 
	 *  \return 返回场景类的地形指针。
	 */
	//virtual LightTerrain * getTerrain( void ) = 0;

	/*! \brief 将指定的静态网格绑定到场景中
	 *
	 *  \param mesh[in] 要绑定的静态网格
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int attachMesh( LightMesh * mesh ) = 0;

	/*! \brief 将指定的静态网格从场景中分离
	 *
	 *  \param mesh[in] 要分离的静态网格
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int detachMesh( LightMesh * mesh ) = 0;

	/*! \brief 查询场景中静态网格的数量
	 *		 
	 *  \return 返回场景中静态网格的数量
	 */
	virtual int getMeshCount( void ) = 0;

	/*! \brief 查询静态网格指针
	 *
	 *  \param mesh 要查询的静态网格索引
	 *
	 *  \return 返回场景类的静态网格指针。
	 */
	virtual LightMesh * getMesh( int mesh ) = 0;

	/*! \brief 将场景保存到文件中
	 *	 
	 *  \param filename 场景文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int save( const char * filename ) = 0;

	/*! \brief 将场景文件从内存中清除
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int unload( void ) = 0;

};