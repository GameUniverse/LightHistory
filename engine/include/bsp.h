/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   LightBsp.h
 *  内容:   二叉树函数
 *
 ****************************************************************************/


/*! \file bsp.h
 * 二叉树函数.
 * 此文件是二叉树函数头文件.
 */


#define LIGHT_MAX_BSP_HOMEPLACE   256 // 最大玩家出生点数

// 玩家出生点结构
typedef struct homeplace_s
{
	vec3_t pos;   // 玩家位置
	float  angle; // 玩家角度
} homeplace_t;

// 场景数据结构
typedef struct bsp_data_s
{
	int    NumHomeplace;                             // 玩家出生点数
	homeplace_t Homeplaces[LIGHT_MAX_BSP_HOMEPLACE]; // 玩家出生点列表

} bsp_data_t;


/** 二叉树描述符类 */
class LightBSPTreeDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightBSPTreeDesc()
	{
		memset( this, 0, sizeof(LightBSPTreeDesc) );
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


/*! \class LightBSPTree
 * \brief 二叉树类
 *
 *  本类负责地图文件的读取和显示，二叉树场景管理，是引擎的核心部分。
 *  每个 LightBSPTree 实例都必须通过 LightEngine 类的 createBSPTree 方法分配， releaseBSPTree 释放。
 */

class LightBSPTree
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn void Lighteness( float lighteness ) = 0
	 *  \brief 设置地图亮度值（必须在读取地图之前设置才有效，缺省值为 10 ）
	 *
	 *  设置地图亮度值（必须在读取地图之前设置才有效，缺省值为 10 ）
	 *
	 *  \param float lighteness 地图亮度值
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void Lighteness( float lighteness ) = 0;

	/*! \fn bool Load(const char *strFileName) = 0
	 *  \brief 将指定的 .bsp 室内场景文件读入内存
	 *
	 *  将指定的 .bsp 室内场景文件读入内存
	 *
	 *  \param float lighteness 地图文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual bool Load(const char *strFileName) = 0;

	/*! \brief 创建一个三角形网格对象
	*	 
	*  \return 新的三角形网格
	*
	*  \see 
	*/	
	virtual LightTriangleMesh * createTriangleMesh() = 0;
	
	/*! \fn int FindLeaf( float x, float y, float z ) = 0
	 *  \brief 查询指定点所在的叶节点（返回索引）
	 *
	 *  查询指定点所在的叶节点（返回索引）
	 *
	 *  \param float x 该点的 x 坐标值
	 *
	 *  \param float y 该点的 y 坐标值
	 *
	 *  \param float z 该点的 z 坐标值
	 *
	 *  \return 该点所在叶节点的索引值
	 *
	 *  \see 
	 */
	virtual int FindLeaf( float x, float y, float z ) = 0;

	/*! \fn int AttachModel( LightModelMD3 *model ) = 0
	 *  \brief 将指定模型与地图绑定
	 *
	 *  将指定模型与地图绑定
	 *
	 *  \param LightModelMD3 *model 要绑定的模型
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int AttachModel( LightModelMD3 *model ) = 0;

	/*! \fn void Gravity( float gravity ) = 0
	 *  \brief 设置地图重力
	 *
	 *  设置地图重力
	 *
	 *  \param float gravity 重力值
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void Gravity( float gravity ) = 0;

	/*! \fn int GetData( bsp_data_t * bsp_data ) = 0
	 *  \brief 查询室内场景数据
	 *
	 *  查询室内场景数据，包括玩家出生点等数据
	 *
	 *  \param bsp_data_t * bsp_data 要返回数据的结构指针
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int GetData( bsp_data_t * bsp_data ) = 0;

	/*! \fn void Update( void ) = 0
	 *  \brief 更新场景状态
	 *
	 *  更新场景状态
	 *
	 *  \param 本函数没有参数
	 *	 
	 *
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void Update( void ) = 0;

	/*! \fn virtual void Render( void ) = 0
	 *  \brief 渲染场景
	 *
	 *  渲染场景
	 *
	 *  \param 本函数没有参数
	 *	 
	 *
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void Render( void ) = 0;

	/*! \fn void RenderSingle( void ) = 0
	 *  \brief 仅仅渲染场景（不渲染模型和阴影）
	 *
	 *  仅仅渲染场景（不渲染模型和阴影）
	 *
	 *  \param 本函数没有参数
	 *	 
	 *
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void RenderSingle( void ) = 0;

	/*! \fn void RenderProjection() = 0
	 *  \brief 以投影纹理模式渲染场景
	 *
	 *  以投影纹理模式渲染场景
	 *
	 *  \param 无
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void RenderProjection() = 0;

	/*! \fn  void RenderBlendFace() = 0
	 *  \brief 渲染场景中的透明面
	 *
	 *  渲染场景中的透明面
	 *
	 *  \param 无
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void RenderBlendFace() = 0;

	/*! \fn CVector3 TraceRay(CVector3 vStart, CVector3 vEnd) = 0
	 *  \brief 测试指定的线段与场景中的凸体是否发生碰撞
	 *
	 *  测试指定的线段与场景中的凸体是否发生碰撞
	 *
	 *  \param CVector3 vStart 线段起始点
	 *
	 *  \param CVector3 vEnd 线段结束点
	 *	 
	 *  \return CVector3 发生碰撞的点
	 *
	 *  \see 
	 */
	virtual CVector3 TraceRay(CVector3 vStart, CVector3 vEnd) = 0;

	/*! \fn  CVector3 TraceSphere(CVector3 vStart, CVector3 vEnd, float radius) = 0
	 *  \brief 测试指定的球体与场景中的凸体是否发生碰撞
	 *
	 *  测试指定的球体与场景中的凸体是否发生碰撞
	 *
	 *  \param CVector3 vStart 线段起始点
	 *
	 *  \param CVector3 vEnd 线段结束点
	 *	 
	 *  \param float radius 球体的半径
	 *	 
	 *  \return CVector3 发生碰撞的点
	 *
	 *  \see 
	 */
	virtual CVector3 TraceSphere(CVector3 vStart, CVector3 vEnd, float radius) = 0;

	/*! \fn  CVector3 TraceBox(CVector3 vStart, CVector3 vEnd, CVector3 vMin, CVector3 vMax) = 0
	 *  \brief 测试指定的包围盒（AABB）与场景中的凸体是否发生碰撞
	 *
	 *  测试指定的包围盒（AABB）与场景中的凸体是否发生碰撞
	 *
	 *  \param CVector3 vStart 线段起始点
	 *
	 *  \param CVector3 vEnd 线段结束点
	 *	 
	 *  \param CVector3 vMin 包围盒（AABB）对角线顶点
	 *	 
	 *  \param CVector3 vMax 包围盒（AABB）对角线另一个顶点
	 *	 
	 *  \return CVector3 发生碰撞的点
	 *
	 *  \see 
	 */
	virtual CVector3 TraceBox(CVector3 vStart, CVector3 vEnd, CVector3 vMin, CVector3 vMax) = 0;

	/*! \fn  bool IsOnGround() = 0
	 *  \brief 查询最后一次碰撞检测是否与地面发生碰撞
	 *
	 *  查询最后一次碰撞检测是否与地面发生碰撞
	 *
	 *  \param 无
	 *
	 *  \return 如果与地面发生碰撞，返回 TRUE ，否则返回 FALSE ；
	 *
	 *  \see 
	 */
	virtual bool IsOnGround() = 0;

	/*! \fn  bool Collided() = 0
	 *  \brief 查询最后一次碰撞检测是否发生碰撞
	 *
	 *  查询最后一次碰撞检测是否发生碰撞
	 *
	 *  \param 无
	 *
	 *  \return 如果发生碰撞，返回 TRUE ，否则返回 FALSE ；
	 *
	 *  \see 
	 */
	virtual bool Collided() = 0;

	/*! \fn  void Destroy() = 0
	 *  \brief 释放地图所占内存
	 *
	 *  释放地图所占内存
	 *
	 *  \param 无
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void Destroy() = 0;
};