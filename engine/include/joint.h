/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   joint.h
 *  内容:   关节函数
 *
 ****************************************************************************/


/*! \file joint.h
 * 关节函数.
 * 此文件是关节函数头文件.
 */


/** 关节类型 */
enum LightJointType
{
	/** 长方体活塞关节，两个角色仅能做相对平移运动，不能旋转 */
	LIGHT_JOINT_PRISMATIC,

	/** 合页（铰链）关节，两个角色仅能绕共同的轴做旋转运动 */
	LIGHT_JOINT_REVOLUTE,

	/** 圆柱体活塞关节，两个角色不仅能绕轴做相对平移运动，也能绕轴做相对旋转运动 */
	LIGHT_JOINT_CYLINDRICAL,

	/** 球窝关节，也称万向节 */	
	LIGHT_JOINT_SPHERICAL,

	/** 点在线关节 */
	LIGHT_JOINT_POINT_ON_LINE,

    /** 点在面关节 */
	LIGHT_JOINT_POINT_IN_PLANE,

	/** 距离关节，一个角色上的一点和另一个角色上的一点始终保持一个不变的距离 */	
	LIGHT_JOINT_DISTANCE,

	/** 一个滑轮关节 */	
	LIGHT_JOINT_PULLEY,

	/** 一个固定连接，两个角色之间没有相对运动，就好像用胶水粘住了一样 */	
	LIGHT_JOINT_FIXED,

	
	LIGHT_JOINT_D6,

	/* 通常用来统计有效的枚举个数，不是一个关节类型 */
	LIGHT_JOINT_COUNT,
	LIGHT_JOINT_FORCE_DWORD = 0x7fffffff
};

/** 关节标志位 */
enum LightJointFlag
{
	/** 如果绑定到关节的刚体之间碰撞检测激活，此标志位为真。缺省情况下由关节联接的一对刚体不发生碰撞约束 */
    LIGHT_JF_COLLISION_ENABLED	= (1<<0),

	/** 为这个关节打开调试渲染器 */
    LIGHT_JF_VISUALIZATION		= (1<<1),
};

/** 弹性描述符结构 */
typedef struct
{
	/** 弹力系数 */
    float spring;
	
	/** 抑制系数 */
	float damper;
	
	/** 目前必须为 0 */
	float targetValue;

} LightSpringDesc;

/** 描述一个关节限制 */
typedef struct
{
	/** 角度/位置激活的最远限制 */
	float value;

	/** 弹性限制 */
	float restitution;

	/* [还没有实现!] 设置此值小于 1 可以制造柔软的效果 */
	float hardness;

} LightJointLimitDesc;

/** 描述一双关节限制 */
typedef struct
{
	/** 低的限制（小的值） */
	LightJointLimitDesc low;

	/** 高的限制（大的值） */
	LightJointLimitDesc high;

} LightJointLimitPairDesc;

/** 控制球窝关节行为的标志位 */
enum LightSphericalJointFlag
{
	/** 如果扭动限制有效，此标志位为真 */
	LIGHT_SJF_TWIST_LIMIT_ENABLED  = 1 << 0,
	
	/** 如果摆动限制有效，此标志位为真 */
	LIGHT_SJF_SWING_LIMIT_ENABLED  = 1 << 1,
	
	/** 如果扭动弹性有效，此标志位为真 */
	LIGHT_SJF_TWIST_SPRING_ENABLED = 1 << 2,
	
	/** 如果摆动弹性有效，此标志位为真 */
	LIGHT_SJF_SWING_SPRING_ENABLED = 1 << 3,
	
	/** 如果关节弹性有效，此标志位为真 */
	LIGHT_SJF_JOINT_SPRING_ENABLED = 1 << 4,

	/** 给线性运动增加另外约束 */
    LIGHT_SJF_PERPENDICULAR_DIR_CONSTRAINTS	= 1 << 5,
};

/** 球窝关节描述符 */
typedef struct
{
	/** 在 actor 0 关节空间定义的摇摆限制轴 */
	vec3_t swingAxis;
		
	/** 投影关节的投影距离 */
	float  projectionDistance;

	/** 围绕扭动轴旋转限制 */
	LightJointLimitPairDesc twistLimit;

	/** 扭动轴摆动限制 */
	LightJointLimitDesc swingLimit;
	
	/** 扭动反弹性 */
	LightSpringDesc	 twistSpring;

	/** 摆动反弹性 */
	LightSpringDesc	 swingSpring;

	/** 让关节拉开的弹性 */
	LightSpringDesc	 jointSpring;

	/** 这是一个由 LightSphericalJointFlag 定义的联合标志位 */
	unsigned long    flags;

	//NxJointProjectionMode projectionMode;

} LightSphericalJointDesc;

/** 控制距离关节行为的标志 */
enum LightDistanceJointFlag
{
	/** 如果该位为 1，关节执行最大分开距离 */
	LIGHT_DJF_MAX_DISTANCE_ENABLED = 1 << 0,

	/** 如果该位为 1，关节执行最小分开距离 */
	LIGHT_DJF_MIN_DISTANCE_ENABLED = 1 << 1,

	/** 如果该位为 1，弹性激活 */
	LIGHT_DJF_SPRING_ENABLED	   = 1 << 2,
};

/** 距离关节描述符 */
typedef struct
{
	/** 绳索或杆子两个定位点之间的最大拉伸距离 */
	float maxDistance;

	/** 绳索或杆子两个定位点之间的最小拉伸距离 */
	float minDistance;
	
	/** 制造关节弹性，spring.targetValue 字段不使用 */
	LightSpringDesc spring;

	/** 这是一个由 LightDistanceJointFlag 定义的联合位标志 */
	unsigned long   flags;

} LightDistanceJointDesc;

/** 描述一个关节发动机 */
typedef struct
{
	/** 发动机设法达到的相对速度 */
	float velTarget;

	/** 发动机能被施加的最大力（或转矩）*/
	float maxForce;

    /** 如果为真，当关节速度大于 velTarget 时，发动机将不会刹车 */	
	bool  freeSpin;
} LightMotorDesc;

/** 控制滑轮关节行为的标志位 */
enum LightPulleyJointFlag
{
	/** 如果该标志位为 1，关节同时维护一个最小距离，否则仅仅一个最大距离 */
	LIGHT_PJF_IS_RIGID = 1 << 0,

	/** 如果该标志位为 1，发动机激活 */
	LIGHT_PJF_MOTOR_ENABLED = 1 << 1
};

/** 滑轮关节描述符 */
typedef struct
{
	/** 在世界空间中悬挂两个刚体的两个滑轮的位置 */
	vec3_t pulley[2];

	/** 连接两个物体绳索的其余长度，此距离计算方法为 ||(pulley0 - anchor0)|| +  ||(pulley1 - anchor1)|| * ratio */
	float  distance;

	/** 约束有多硬，在 0 和 1（最硬） 之间 */
	float  stiffness;

	/** 传动比 */
	float  ratio;

	/** 这是一个由 LightPulleyJointFlag 定义的联合标志位 */
	unsigned long  flags;

	/** 可选择的关节发动机 */
	LightMotorDesc	motor;

} LightPulleyJointDesc;

/** 关节描述符结构 */
typedef struct
{
	/** 关节类型 */
	LightJointType type;
	
	/** 关节连接的两个角色 */
	LightActor * actor[2];

	/** 关节空间的 X 轴，在 actor[i] 的空间， 与 localAxis[i] 成直角 */
	vec3_t localNormal[2];

	/** 关节空间的 Z 轴，在 actor[i] 的空间。这是关节的主坐标轴。*/
	vec3_t localAxis[2];
	
	/** 在 actor[i] 空间的关节绑定点 */
	vec3_t localAnchor[2];

	/** 关节破坏之前能承受的最大角向力（扭矩），必须是正值 */
	float  maxForce;

	/** 含义同上 */
	float  maxTorque;

	/** 解决关节约束的推断因子 */
	float solverExtrapolationFactor;

	/** 切换到基于加速度的效果 */
	int   useAccelerationSpring;
	
	/** 将要复制到 LightJoint::userData */
	void * userData;

	/* 可能使用的调试名称。这个字符串引擎不复制，仅仅保存指针。*/
	const char * name;

	/* 这是一个 NxJointFlag 定义的联合二进制位 */
	unsigned long jointFlags;

	/** 距离关节参数 */
	LightDistanceJointDesc distanceJoint;

	/** 球窝关节参数 */
	LightSphericalJointDesc sphericalJoint;

	/** 滑轮关节参数 */
	LightPulleyJointDesc pulleyJointDesc;

} LightJointDesc;


/*! \class LightJoint
 *  \brief 关节类 
 *
 *  本类是物理引擎的一部分，负责各类关节的创建、绑定和设置。
 *  每个 LightJoint 实例都必须通过 LightScene 类的 createJoint 方法创建。 
 */

class LightJoint
{

public:

	/*! \brief 查询父场景	 
	 *	 
	 *  \return 返回父场景指针
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;

	/*! \brief 查询关节绑定的角色	 
	 *
	 *  \param actor1[out] 关节绑定的第一个角色
	 *	 
	 *  \param actor2[out] 关节绑定的第二个角色
	 *	 	 
	 *  \see 
	 */	
	virtual void getActors( LightActor ** actor1, LightActor ** actor2 ) = 0;

	/*! \brief 设置两个角色绑定点的位置（使用全局坐标）
	 *
	 *  \param vec[in] 角色绑定点的位置（使用全局坐标）
	 *	 	 
	 *  \see 
	 */	
	virtual void setGlobalAnchor( const vec3_t & vec ) = 0;

	/*! \brief 设置关节主坐标轴方向（使用全局坐标）
	 *
	 *  \param vec[in] 关节主坐标轴方向（使用全局坐标）
	 *	 	 
	 *  \see 
	 */	
	virtual void setGlobalAxis( const vec3_t & vec ) = 0;

	/*! \brief 查询关节绑定点位置
	 *
	 *  \param vec[out] 返回关节绑定点位置（使用全局坐标）
	 *	 	 
	 *  \see 
	 */	
	virtual	void getGlobalAnchor( vec3_t & vec ) = 0;

	/*! \brief 查询关节主坐标轴方向
	 *
	 *  \param vec[out] 返回关节主坐标轴方向（使用全局坐标）
	 *	 	 
	 *  \see 
	 */	
	virtual	void getGlobalAxis( vec3_t & vec ) = 0;

	/*! \brief 查询这个关节的类型
	 *	 
	 *  \return 关节类型
	 *
	 *  \see 
	 */	
	virtual LightJointType getType() = 0;

	/*! \brief 设置一个名称字符串，仅仅为了用 getName() 查询
	 *
	 *  \param name[in] 设置对象名称的字符串
	 *	 	 
	 *  \see 
	 */	
	virtual	void setName( const char * name ) = 0;

	/*! \brief 查询 setName() 设置的名称字符串
	 *	 
	 *  \return 这个对象的名称字符串
	 *
	 *  \see 
	 */	
	virtual	const char * getName() = 0;


	// 限制

	/*! \brief 设置限制点
	 *
	 *  \param point[in] 限制控制点（使用全局坐标）
	 *	 
	 *  \param pointIsOnActor2[in] 如果为真，point 绑定到第二个角色，否则绑定到第一个角色
	 *	 	 
	 *  \see 
	 */	
	virtual void setLimitPoint( const vec3_t & point, bool pointIsOnActor2 = true ) = 0;

	/*! \brief 查询全局空间限制点
	 *
	 *  \param worldLimitPoint[out] 用来存储全局空间限制点
	 *	 
	 *  \return 如果为真，限制点绑定到角色 2，否则绑定到角色 1。
	 *
	 *  \see 
	 */	
	virtual bool getLimitPoint( vec3_t & worldLimitPoint ) = 0;

	/*! \brief 增加一个限制平面
	 *
	 *  \param normal[in] 限制平面法线（使用全局坐标）
	 *	 
	 *  \param pointInPlane[in] 限制平面上的一点（使用全局坐标）
	 *	 
	 *  \param restitution[in] 限制平面弹性
	 *	 
	 *  \return 总是返回 TRUE。
	 *
	 *  \see 
	 */	
	virtual bool addLimitPlane( const vec3_t & normal, const vec3_t & pointInPlane, float restitution = 0.0f ) = 0;

	/*! \brief 删除所有增加到关节的限制平面
	 *	 
	 *  \see 
	 */	
	virtual void purgeLimitPlanes() = 0;


	// 公共变量：

	/** 你能将它用于任何用途，通常用来和一个对象创建 1:1 对应的关系。*/
	void * userData;

};