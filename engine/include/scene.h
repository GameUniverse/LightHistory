/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   scene.h
 *  内容:   场景函数
 *
 ****************************************************************************/


/*! \file scene.h
 * 场景函数
 * 此文件是场景函数头文件.
 */


class LightEngine;


/** 光线结构 */
typedef struct
{
	/** 光线原点 */
	vec3_t  orig;

	/** 规格化的方向 */
	vec3_t  dir;

} LightRay;

/** 角色类型（静态或动态的）*/
enum LightShapesType
{
	/** 投射静态角色 */
	LIGHT_STATIC_SHAPES		= (1<<0),

	/** 投射动态角色 */
	LIGHT_DYNAMIC_SHAPES	= (1<<1),

	/** 同时投射静态和动态角色 */
	LIGHT_ALL_SHAPES		= LIGHT_STATIC_SHAPES|LIGHT_DYNAMIC_SHAPES
};

/** 指定 LightRaycastHit 哪些成员应该产生（当作为 raycasting 方法提示标志使用时），或者判别哪些成员已经产生，当检查 LightRaycastHit 的 flags 成员时。*/
enum LightRaycastBit
{
	LIGHT_RAYCAST_SHAPE		    = (1<<0),								// "shape" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_IMPACT		= (1<<1),								// "worldImpact" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_NORMAL		= (1<<2),								// "worldNormal" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_FACE_INDEX	= (1<<3),								// "faceID" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_DISTANCE		= (1<<4),								// "distance" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_UV			= (1<<5),								// "u" and "v" members of #NxRaycastHit are valid
	LIGHT_RAYCAST_FACE_NORMAL	= (1<<6),								// Same as NX_RAYCAST_NORMAL but computes a non-smoothed normal
	LIGHT_RAYCAST_MATERIAL		= (1<<7),								// "material" member of #NxRaycastHit is valid
};

/** 这个结构获取单次光线投射结果 */
struct LightRaycastHit
{
	/** 被碰撞的形状（关联的标志：LIGHT_RAYCAST_SHAPE）*/	
	LightActor * 	shape;

	/** 在世界空间中的碰撞点（关联的标志：LIGHT_RAYCAST_IMPACT) */
	vec3_t			worldImpact;
					
	/** 在世界空间中的碰撞法线（关联的标志：LIGHT_RAYCAST_NORMAL / LIGHT_RAYCAST_FACE_NORMAL）*/
	vec3_t			worldNormal;

	/** 被碰撞面的索引（关联的标志：LIGHT_RAYCAST_FACE_INDEX）*/
	unsigned long 	faceID;

	/** 含义同上 */
	unsigned long	internalFaceID;	

	/** 从光线起点到碰撞点的距离（关联的标志：LIGHT_RAYCAST_DISTANCE）*/
	float 			distance;

	/** 碰撞中心坐标（关联的标志：LIGHT_RAYCAST_UV）*/
	float 			u,

	/** 含义同上 */
		            v;

	/** 被碰撞物理材质的索引（关联的标志：LIGHT_RAYCAST_MATERIAL）*/
	unsigned short 	materialIndex;

	/** LightRaycastBit 联合标志字段，当一个标志位设置后，那么相应的成员是有效的。
	
	LightRaycastBit 标志能传递给 raycasting 函数，告诉引擎仅产生这个结构的指定成员，从而起到优化程序运行速度的作用。*/	
	unsigned long 	flags;
};

/** 接触通报消息 */
enum LightContactPairFlag
{
	/** 两个角色开始接触时发送此报告 */
	LIGHT_NOTIFY_ON_START_TOUCH					    = (1<<1),

	/** 两个角色停止接触时发送此报告 */
	LIGHT_NOTIFY_ON_END_TOUCH						= (1<<2),

	/** 两个角色持续接触时发送此报告 */
	LIGHT_NOTIFY_ON_TOUCH							= (1<<3),
};

// 用户角色接触报告函数原型
typedef void LightUserContactReport( LightActor * a, LightActor * b, unsigned long events );

/** 场景描述符结构 */
typedef struct
{
	/** 场景类型 */
	int    type;

} LightSceneDesc;


/*! \class LightScene
 * \brief 场景类
 *
 *  本类负责场景文件的读取、显示和管理，目前支持 3ds 格式的静态网格场景文件。 
 *  每个 LightScene 实例都必须通过 LightEngine 类的 createScene 方法分配。 
 */

class LightScene
{

public:

	/*! \brief 查询父引擎 
	 *	 
	 *  \return 返回引擎指针
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn LightActor * createActor( const LightActorDesc * desc ) = 0
	 *  \brief 创建一个角色
	 *
	 *  创建一个角色
	 *
	 *  \param const LightActorDesc * desc 角色描述符指针，用于说明要创建角色的特征。
	 *	 
	 *  \return 返回已创建的角色指针
	 *
	 *  \see 
	 */
	virtual LightActor * createActor( const LightActorDesc & actorDesc ) = 0;

	/*! \fn void releaseActor( LightActor * actor ) = 0
	 *  \brief 释放一个角色
	 *
	 *  释放一个角色
	 *
	 *  \param LightActor * actor 要释放角色的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseActor( LightActor * actor ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \fn LightJoint * createJoint( const LightJointDesc * jointDesc ) = 0
	 *  \brief 创建一个关节
	 *
	 *  创建一个关节
	 *
	 *  \param const LightJointDesc * jointDesc 关节描述符指针，用于说明要创建关节的特征。
	 *	 
	 *  \return 返回已创建的关节指针
	 *
	 *  \see 
	 */
	virtual LightJoint * createJoint( const LightJointDesc & jointDesc ) = 0;

	/*! \fn void releaseJoint( LightJoint * joint ) = 0
	 *  \brief 释放一个关节
	 *
	 *  释放一个关节
	 *
	 *  \param LightJoint * joint 要释放关节的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseJoint( LightJoint * joint ) = 0;

	/*! \fn LightFluid * createFluid( const LightFluidDesc * fluidDesc ) = 0
	 *  \brief 创建一个流体
	 *
	 *  创建一个流体
	 *
	 *  \param const LightFluidDesc * fluidDesc 流体描述符指针，用于说明要创建流体的特征。
	 *	 
	 *  \return 返回已创建的流体指针
	 *
	 *  \see 
	 */
	virtual LightFluid * createFluid( const LightFluidDesc & fluidDesc ) = 0;

	/*! \fn void releaseFluid( LightFluid * fluid ) = 0
	 *  \brief 释放一个流体
	 *
	 *  释放一个流体
	 *
	 *  \param LightFluid * fluid 要释放流体的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseFluid( LightFluid * fluid ) = 0;

#endif

	/*! \fn LightPhysicsMaterial * createPhysicsMaterial( const LightPhysicsMaterialDesc * physicsMaterialDesc ) = 0
	 *  \brief 创建一个物理材质
	 *
	 *  创建一个物理材质
	 *
	 *  \param const LightPhysicsMaterialDesc * physicsMaterialDesc 物理材质描述符指针，用于说明要创建物理材质的特征。
	 *	 
	 *  \return 返回已创建的物理材质指针
	 *
	 *  \see 
	 */
	virtual LightPhysicsMaterial * createPhysicsMaterial( const LightPhysicsMaterialDesc & physicsMaterialDesc ) = 0;

	/*! \fn void releasePhysicsMaterial( LightPhysicsMaterial * physicsMaterial ) = 0
	 *  \brief 释放一个物理材质
	 *
	 *  释放一个物理材质
	 *
	 *  \param LightPhysicsMaterial * physicsMaterial 要释放物理材质的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releasePhysicsMaterial( LightPhysicsMaterial * physicsMaterial ) = 0;

	/*! \fn LightCharacter * createCharacter( const LightCharacterDesc * characterDesc ) = 0
	 *  \brief 创建一个角色控制对象
	 *
	 *  创建一个角色控制对象
	 *
	 *  \param const LightCharacterDesc * characterDesc 角色控制器的描述结构指针。
	 *	 
	 *  \return 返回要创建的角色控制对象指针
	 *
	 *  \see 
	 */
	virtual LightCharacter * createCharacter( const LightCharacterDesc & characterDesc ) = 0;

	/*! \fn void releaseCharacter( LightCharacter * character ) = 0
	 *  \brief 释放一个角色控制对象
	 *
	 *  释放一个角色控制对象
	 *
	 *  \param LightCharacter * character 要释放的角色控制对象
	 *	 
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void releaseCharacter( LightCharacter * character ) = 0;

	/*! \brief 渲染场景
	 *
	 *  将场景渲染到屏幕或窗口
	 *
	 *  \param 本函数没有参数。
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void render( void ) = 0;

	/*! \brief 指定一对形状组是否执行碰撞检测
	 *
	 *  LightCollisionGroup 是一个 0~31 之间的整数。
	 *
	 *  \param[in] group1 第一组
	 *	
	 *  \param[in] group2 第二组
	 *	
	 *  \param[in] enable TRUE 开启（FALSE 关闭）两个组之间的碰撞检测。
	 *	
	 *  \see 
	 */
	virtual void setGroupCollisionFlag( LightCollisionGroup group1, LightCollisionGroup group2, bool enable ) = 0;

	/*! \brief 查询两个形状组之间是否执行碰撞检测
	 *	 
	 *  LightCollisionGroup 是一个 0~31 之间的整数。
	 *
	 *  \param[in] group1 第一组
	 *	
	 *  \param[in] group2 第二组
	 *	
	 *  \return 两个组之间的碰撞检测状态，TRUE 开启（FALSE 关闭）。
	 *
	 *  \see 
	 */
	virtual bool getGroupCollisionFlag( LightCollisionGroup group1, LightCollisionGroup group2 ) = 0;

	/*! \brief 设置用户角色接触报告函数
	 *	 
	 *  \param callback 用户角色接触报告监听函数指针
	 *		 
	 *  \see 
	 */
	virtual void setUserContactReport( LightUserContactReport * callback ) = 0;

	// 光线投射

	/*! \brief 判断光线是否与角色 AABB（轴对齐包围盒）相交
	 *
	 *  \param[in] worldRay 在世界场景中投射的光线
	 *
	 *  \param[in] shapesType 选择要投射的角色类型（静态、动态、静态和动态）
	 *
	 *  \param[in] groups 角色过滤掩码
	 *
	 *  \param[in] maxDist 沿光线向前检测相交的最大距离
	 *
	 *  \param[in] groupsMask 可选的角色过滤掩码
	 *	 
	 *  \return 如果光线与任何一个角色 AABB（轴对齐包围盒）相交，函数返回 TRUE，否则返回 FALSE。
	 *
	 *  \see 
	 */
	virtual bool raycastAnyBounds( const LightRay & worldRay, LightShapesType shapesType, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, const LightGroupsMask * groupsMask=NULL ) = 0;

	/*! \brief 判断光线是否与角色相交
	 *
	 *  \param[in] worldRay 在世界场景中投射的光线
	 *
	 *  \param[in] shapesType 选择要投射的角色类型（静态、动态、静态和动态）
	 *
	 *  \param[in] groups 角色过滤掩码
	 *
	 *  \param[in] maxDist 沿光线向前检测相交的最大距离
	 *
	 *  \param[in] groupsMask 可选的角色过滤掩码
	 *
	 *  \param[in] cache 持久稳固的光线投射可能使用的缓存，由引擎填写。
	 *
	 *  \return 如果光线与任何一个角色 AABB（轴对齐包围盒）相交，函数返回 TRUE，否则返回 FALSE。
	 *
	 *  \see 
	 */	
	virtual bool raycastAnyShape( const LightRay & worldRay, LightShapesType shapesType, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, const LightGroupsMask * groupsMask=NULL, LightActor ** cache=NULL ) = 0;

	
	/*virtual NxU32						raycastAllBounds		(const NxRay& worldRay, NxUserRaycastReport& report, NxShapesType shapesType, NxU32 groups=0xffffffff, NxReal maxDist=NX_MAX_F32, NxU32 hintFlags=0xffffffff, const NxGroupsMask* groupsMask=NULL) const = 0;

	virtual NxU32						raycastAllShapes		(const NxRay& worldRay, NxUserRaycastReport& report, NxShapesType shapesType, NxU32 groups=0xffffffff, NxReal maxDist=NX_MAX_F32, NxU32 hintFlags=0xffffffff, const NxGroupsMask* groupsMask=NULL) const = 0;
*/
	
	/*! \brief 返回第一个与光线相交 AABB（轴对齐包围盒）包含的 shapeType 类型的形状
	 *
	 *  \param[in] worldRay 在世界场景中投射的光线
	 *
	 *  \param[in] shapesType 选择要投射的角色类型（静态、动态、静态和动态）
	 *
	 *  \param[out] hit 相交点描述
	 *
	 *  \param[in] groups 角色过滤掩码
	 *
	 *  \param[in] maxDist 沿光线向前检测相交的最大距离
	 *
     *  \param[in] hintFlags 允许用户指定他们对 LightRaycastHit 的哪个字段是感兴趣的
	 *
	 *  \param[in] groupsMask 可选的角色过滤掩码
	 *     
	 *  \return 返回与光线相交的 AABB（轴对齐包围盒）包含的形状
	 *
	 *  \see 
	 */	
	virtual LightActor * raycastClosestBounds( const LightRay & worldRay, LightShapesType shapesType, LightRaycastHit & hit, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, unsigned long hintFlags=0xffffffff, const LightGroupsMask* groupsMask=NULL ) = 0;
	
	/*! \brief 返回第一个与光线相交 shapeType 类型的形状
	 *
	 *  \param[in] worldRay 在世界场景中投射的光线
	 *
	 *  \param[in] shapesType 选择要投射的角色类型（静态、动态、静态和动态）
	 *
	 *  \param[out] hit 相交点描述
	 *
	 *  \param[in] groups 角色过滤掩码
	 *
	 *  \param[in] maxDist 沿光线向前检测相交的最大距离
	 *
     *  \param[in] hintFlags 允许用户指定他们对 LightRaycastHit 的哪个字段是感兴趣的
	 *
	 *  \param[in] groupsMask 可选的角色过滤掩码
	 *
     *  \param[in] cache 持久稳固的光线投射可能使用的缓存，由引擎填写。
	 *	 
	 *  \return 返回与光线相交的形状
	 *
	 *  \see 
	 */
	virtual LightActor * raycastClosestShape( const LightRay & worldRay, LightShapesType shapesType, LightRaycastHit & hit, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, unsigned long hintFlags=0xffffffff, const LightGroupsMask* groupsMask=NULL, LightActor ** cache=NULL ) = 0;

};