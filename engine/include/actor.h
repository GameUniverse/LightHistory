/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   actor.h
 *  内容:   角色函数
 *
 ****************************************************************************/


/*! \file actor.h
 * 角色函数
 * 此文件是角色函数头文件.
 */


class LightTriangleMesh;
class LightHeightField;
class LightScene;
class LightActor;


/** 睡眠间隔 */
#define LIGHT_SLEEP_INTERVAL (1.0f/60.0f*20.0f)		// Corresponds to 20 frames for the standard time step.

/** 碰撞检测组（必须< 32）*/
typedef unsigned short LightCollisionGroup;

/** 碰撞检测过滤使用的 128-bit 掩码 */
typedef struct
{
	unsigned long bits0, bits1, bits2, bits3;

} LightGroupsMask;

/** 确定一个特定的形状类型 */
enum LightShapeType
{
	/** 一个物理平面 */
	LIGHT_SHAPE_PLANE,

	/** 一个物理球体 */
	LIGHT_SHAPE_SPHERE,

	/** 一个物理盒子 (OBB) */
	LIGHT_SHAPE_BOX,

	/** 一个物理胶囊 (LSS) */
	LIGHT_SHAPE_CAPSULE,

	/* A wheel for raycast cars */
	LIGHT_SHAPE_WHEEL,

	/** 一个物理凸体网格 */
	LIGHT_SHAPE_CONVEX,

	/** 一个物理网格 */
	LIGHT_SHAPE_MESH,

	/** 一个物理地形（高度场）*/
	LIGHT_SHAPE_HEIGHTFIELD,

	/* 仅仅内部使用! */
	LIGHT_SHAPE_RAW_MESH,

	LIGHT_SHAPE_COMPOUND,

	LIGHT_SHAPE_COUNT,

	LIGHT_SHAPE_FORCE_DWORD = 0x7fffffff
};

/** 角色描述符类 */
class LightActorDesc
{
public:

	/** 角色类型 */
	LightShapeType    type;

	/** 是否动态角色 */
	bool   dynamic;

	/** 父角色，如果不为 NULL，则创建一个 parent 的子角色 */
	LightActor * parent;

	/** 有效数据标志位 */
	int    flag;

	/** 角色初始位置 */
	vec3_t pos;

	/** 角色的旋转角度 */
	float  angle;

	/** 通过原点的旋转轴上的一点 */
	vec3_t rotate;

	/** 角色所属的碰撞检测组（见 LightActor::setGroup() 说明）*/
	LightCollisionGroup  group;

	/** 角色的品质，圆柱侧面沿圆周方向的段数 */
	int    quality_slices;

	/** 角色的品质，圆柱侧面沿高度方向的段数 */
	int    quality_stacks;

	/** 角色质量，取值范围为 [0，+-无穷大]，缺省值为 -1.0，当 <= 0 时，根据密度计算质量。*/
	float  mass;

	/** 角色隐藏标志（TRUE = 隐藏，FALSE = 显示），在角色隐藏时，只是在窗口不显示，其物理模型继续存在。*/
	bool   hide;

	/** 物理材质索引 */
	int    physicsMaterialIndex;

	/** 长方体参数 */
	struct 
	{
		/** 长方体长、宽、高 */
		vec3_t size;
	
	} box;

	/** 球体参数 */
	struct
	{
		/** 球体半径 */
		float  radius;
	
	} sphere;

	/** 平面参数 */
	struct
	{ 
		/** 平面法线 */
		vec3_t normal;

		/** 平面到原点的距离 */
		float  distance;

	} plane;

    /** 胶囊体参数 */
	struct 
	{ 
		/** 胶囊体半径 */
		float  radius;
		/** 胶囊体高 */
		float  height;

	} capsule;

	 /** 三角形网格参数 */
	struct 
	{ 
		/** 三角形网格指针 */
		LightTriangleMesh * triangleMesh;

	} mesh;

	/** 高度场参数 */
	struct 
	{ 
		/** 高度场指针 */
		LightHeightField * heightField;

	} height_field;

    /** 茶壶体参数 */
	struct
	{
		/** 茶壶体半径 */
		float  radius;
	
	} teapot;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightActorDesc()
	{
		memset( this, 0, sizeof(LightActorDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		//VEC3( position, 0, 0, 0 );	
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightActor
 * \brief 角色类
 *
 *  本类负责角色的创建、显示和控制，目前支持盒子、球体、胶囊、平面、静态网格和骨骼动画 6 种角色类型。 
 *  每个 LightActor 实例都必须通过 LightScene 类的 createActor 方法分配， releaseActor 释放。
 */

class LightActor
{
	protected:
	
	//inline  LightActor() : userData(NULL) {}

	//virtual	~LightActor() {}

    public:

	/*! \fn LightScene * getScene() = 0
	 *  \brief 查询父场景
	 *
	 *  查询父场景
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回父场景引用
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;


	// 全局状态控制

	/*! \brief 设置角色矩阵（矩阵包含位置和方向信息）
     *	 
     *  \param mat 要设置的角色矩阵     
     */
	virtual	void setGlobalPose( const mat34_t mat ) = 0;
	
	/*! \fn void setGlobalPosition( const vec3_t vec ) = 0
     *  \brief 设置角色位置
     *
	 *  设置角色位置
	 *
     *  \param const vec3_t vec 要设置的角色位置
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual	void setGlobalPosition( const vec3_t vec ) = 0;

	/*! \fn void setGlobalPosition( float x, float y, float z ) = 0
     *  \brief 设置角色位置
     *
	 *  设置角色位置
	 *
     *  \param float x 要设置角色位置的 x 坐标
     *
	 *  \param float y 要设置角色位置的 y 坐标
     *
	 *  \param float z 要设置角色位置的 z 坐标
     *
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual	void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \fn void setGlobalOrientation( const mat33_t mat ) = 0
     *  \brief 设置角色方向（使用矩阵）
     *
	 *  设置角色方向（使用矩阵）
	 *
     *  \param const mat33_t mat 要设置的角色方向矩阵
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual	void setGlobalOrientation( const mat33_t mat ) = 0;
	
	/*! \fn void setGlobalOrientationQuat( const quat_t mat ) = 0
     *  \brief 设置角色方向（使用四元数）
     *
	 *  设置角色方向（使用四元数）
	 *
     *  \param const mat33_t mat 要设置的角色方向四元数
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \fn void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0
     *  \brief 设置角色方向（使用绕轴旋转）
     *
	 *  设置角色方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param float angle 角色绕轴旋转角度
     *
     *  \param float x 旋转轴向量 x 分量
     *
	 *  \param float y 旋转轴向量 y 分量
     *
	 *  \param float z 旋转轴向量 z 分量
     *
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。
	 *
     *  \return 本函数没有返回值。
     */
	virtual	void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;
	
	/*! \fn void setGlobalPose( const mat34_t mat ) = 0
     *  \brief 查询角色矩阵（矩阵包含位置和方向信息）
     *
	 *  查询角色矩阵（矩阵包含位置和方向信息）
	 *
     *  \param const mat34_t mat 
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 返回要查询的角色矩阵指针 float matrix[3][4]。
     */
	virtual	mat34_t &getGlobalPose() const = 0;

	/*! \fn void setGlobalPosition( const vec3_t vec ) = 0
     *  \brief 查询角色位置
     *
	 *  查询角色位置
	 *
     *  \param 本函数没有参数
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 返回要查询的角色位置向量指针 float vector[3]。
     */
	virtual	vec3_t &getGlobalPosition() const = 0;

	/*! \fn void getGlobalPosition( float * x, float * y, float * z ) = 0
     *  \brief 查询角色位置
     *
	 *  查询角色位置
	 *
     *  \param float * x 角色位置的 x 坐标指针
     *
	 *  \param float * y 角色位置的 y 坐标指针
     *
	 *  \param float * z 角色位置的 z 坐标指针
     *
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值，角色位置已经通过参数的指针返回了。
     */
	virtual void getGlobalPosition( float * x, float * y, float * z ) = 0;
	
	/*! \fn void setGlobalOrientation( const mat33_t mat ) = 0
     *  \brief 查询角色方向（使用矩阵）
     *
	 *  查询角色方向（使用矩阵）
	 *
     *  \param 本函数没有参数
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 返回要查询的角色方向矩阵指针 float matrix[3][3]。
     */
	virtual	mat33_t &getGlobalOrientation() const = 0; 
	
	/*! \fn void setGlobalOrientationQuat( const quat_t mat ) = 0
     *  \brief 查询角色方向（使用四元数）
     *
	 *  查询角色方向（使用四元数）
	 *
     *  \param 本函数没有参数
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 返回要查询的角色方向四元数指针 float quat[4]。
     */
	virtual	quat_t &getGlobalOrientationQuat() const	= 0;


	// 局部状态控制（仅对子角色有效）

	/*! \brief setLocal*() 方法设置子角色在父角色空间中的状态，也就是相对于父角色自已的坐标
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \param mat[in] 子角色相对于父角色的新变换。<b>取值范围:</b> [刚体变换]
     */
	virtual	void setLocalPose( const mat34_t mat ) = 0;

	/*! \brief setLocal*() 方法设置子角色在父角色空间中的状态，也就是相对于父角色自已的坐标
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \param vec[in] 子角色相对于父角色的新位置。<b>取值范围:</b> [位置矢量]
     */
	virtual	void setLocalPosition( const vec3_t vec ) = 0;

	/*! \brief setLocal*() 方法设置子角色在父角色空间中的状态，也就是相对于父角色自已的坐标
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \param mat[in] 子角色相对于父角色的新方向。<b>取值范围:</b> [旋转矩阵]
     */
	virtual	void setLocalOrientation( const mat33_t mat ) = 0;

	/*! \brief getLocal*() 方法返回子角色在父角色空间中的状态，也就是相对于父角色自已的坐标
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \return 子角色相对于父角色的状态 float mat[3][4]。
     */
	virtual	mat34_t &getLocalPose() = 0;

	/*! \brief getLocal*() 方法返回子角色在父角色空间中的状态，也就是相对于父角色自已的坐标
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \return 子角色相对于父角色的位置。
     */
	virtual	vec3_t &getLocalPosition() = 0;

	/*! \brief getLocal*() 方法返回子角色在父角色空间中的状态，也就是相对于父角色自已的坐标
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \return 子角色相对于父角色的方向。
     */
	virtual	mat33_t &getLocalOrientation() = 0;


	// 移动

	/*! \brief moveGlobal*() 方法调用服务，去移动活动角色穿过游戏世界（此角色是运动受限制的）。
     *	 
	 *  这个变换缺省为单位矩阵
	 *
     *  \param mat[in] 运动角色希望的位置和方向（世界坐标）。<b>取值范围:</b> [刚体变换]
     */
	//virtual	void moveGlobalPose( const mat34_t & mat ) = 0;


	// 质量

	/*! \brief 设置动态角色质量
     *	 
	 *  质量必须是正数，角色必须是动态的。
	 *
     *  \param mass[in] 角色新质量值。<b>取值范围:</b> [0，正无穷]
     */
	virtual void setMass( float mass ) = 0;

	/*! \brief 查询角色质量
     *	
	 *  静态角色将总是返回 0。
	 *
     *  \return 这个角色的质量。
     */
	virtual float getMass() = 0;


	// 阻尼

	/*! \brief 设置线性阻尼系数
     *	 
	 *  零表示没有阻尼，阻尼系数必须是正数。角色必须是动态的。
	 *
	 *  <b>缺省值:</b> 0
	 *
     *  \param linDamp[in] 线性阻尼系数。<b>取值范围:</b> [0，正无穷]
     */
	virtual	void setLinearDamping( float linDamp ) = 0;

	/*! \brief 查询线性阻尼系数
     *	
	 *  角色必须是动态的，静态角色将总是返回 0。
	 *
     *  \return 这个角色的线性阻尼系数。
     */
	virtual	float getLinearDamping() = 0;

	/*! \brief 设置角度阻尼系数
     *	 
	 *  零表示没有阻尼，阻尼系数必须是正数。角色必须是动态的。
	 *
	 *  <b>缺省值:</b> 0.05
	 *
     *  \param linDamp[in] 角度阻尼系数。<b>取值范围:</b> [0，正无穷]
     */
	virtual	void setAngularDamping( float angDamp ) = 0;

	/*! \brief 查询角度阻尼系数
     *	
	 *  角色必须是动态的，静态角色将总是返回 0。
	 *
     *  \return 这个角色的角度阻尼系数。
     */
	virtual	float getAngularDamping() = 0;


	// 速度

	/*! \brief 设置角色线速度
     *	 
	 *  角色必须是动态的。
	 *
     *  \param linVel[in] 新的线速度。<b>取值范围:</b> [速度矢量]
     */
	virtual	void setLinearVelocity( const vec3_t & linVel ) = 0;

	/*! \brief 设置角色角速度
     *	 
	 *  角色必须是动态的。
	 *
     *  \param angVel[in] 新的角速度。<b>取值范围:</b> [角速度矢量]
     */
	virtual	void setAngularVelocity( const vec3_t & angVel ) = 0;

	/*! \brief 查询角色线速度
     *	 
	 *  角色必须是动态的。
	 *
     *  \param linVel[out] 返回角色线速度。
     */
	virtual	void getLinearVelocity( vec3_t & linVel ) = 0;

	/*! \brief 查询角色角速度
     *	 
	 *  角色必须是动态的。
	 *
     *  \param angVel[out] 返回角色角速度。
     */
	virtual	void getAngularVelocity( vec3_t & angVel ) = 0;

	/*! \brief 设置这个角色允许的最大角速度
     *	 
	 *  角色必须是动态的。
	 *
     *  \param maxAngVel[in] 这个角色允许的最大角速度。<b>取值范围:</b> [0，正无穷]
     */
	virtual	void setMaxAngularVelocity( float maxAngVel ) = 0;

	/*! \brief 查询这个角色允许的最大角速度
     *	 
	 *  角色必须是动态的。
	 *
     *  \return 这个角色允许的最大角速度。
     */
	virtual float getMaxAngularVelocity() = 0;


	// 动量

	/*! \brief 设置角色线动量
     *	 
	 *  角色必须是动态的。
	 *
     *  \param linMoment[in] 新的线动量。<b>取值范围:</b> [动量矢量]
     */
	virtual void setLinearMomentum( const vec3_t & linMoment ) = 0;

	/*! \brief 设置角色角动量
     *	 
	 *  角色必须是动态的。
	 *
     *  \param angMoment[in] 新的角动量。<b>取值范围:</b> [角动量矢量]
     */
	virtual void setAngularMomentum( const vec3_t & angMoment ) = 0;

	/*! \brief 查询角色线动量
     *	 
	 *  角色必须是动态的。
	 *
     *  \param linMoment[out] 返回角色线动量。
     */
	virtual void getLinearMomentum( vec3_t & linMoment ) = 0;

	/*! \brief 查询角色角动量
     *	 
	 *  角色必须是动态的。
	 *
     *  \param angMoment[out] 返回角色角动量。
     */
	virtual void getAngularMomentum( vec3_t & angMoment ) = 0;


	// 力

	/*! \fn void addForce( float x, float y, float z, int mode ) = 0
     *  \brief 对角色施加一个用世界坐标表示的力
     *
	 *  对角色施加一个用世界坐标表示的力
	 *
     *  \param float x 力向量的 x 分量
     *
	 *  \param float y 力向量的 y 分量
     *
	 *  \param float z 力向量的 z 分量
     *
	 *  \param int mode 施加力的模式，0 = 帧内有效，1 = 持续累加
     *
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual void addForce( float x, float y, float z, int mode = 0 ) = 0;

	/*! \fn void addLocalForce( float x, float y, float z, int mode ) = 0
     *  \brief 对角色施加一个用局部坐标表示的力
     *
	 *  对角色施加一个用局部坐标表示的力
	 *
     *  \param float x 力向量的 x 分量
     *
	 *  \param float y 力向量的 y 分量
     *
	 *  \param float z 力向量的 z 分量
     *
	 *  \param int mode 施加力的模式，0 = 帧内有效，1 = 持续累加
     *
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual void addLocalForce( float x, float y, float z, int mode = 0 ) = 0;

	/*! \brief 渲染角色
     *	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual void render( void ) = 0;


	// 碰撞检测组

    /*! \brief 设置这个形状是哪个碰撞检测组的一部分
 	 *	 
	 *  \param collisionGroup[in] 这个形状的碰撞检测组，<b>取值范围:</b> [0,31]
	 */
	virtual	void setGroup( LightCollisionGroup collisionGroup ) = 0;

	/*! \brief 查询 setGroup() 设置的值
	 *	 
	 *  \return 这个形状所属的碰撞检测组
	 */	
	virtual	LightCollisionGroup getGroup() = 0;

	/*! \brief 设置碰撞检测过滤使用的 128-bit 掩码（见 LightGroupsMask 的注释）
	 *	 
	 *  \param mask[in] 这个形状的碰撞检测组掩码
	 */
	virtual	void setGroupsMask( const LightGroupsMask & mask ) = 0;

	/*! \brief 查询碰撞检测过滤使用的 128-bit 掩码（见 LightGroupsMask 的注释）
	 *	
	 *  \return 这个形状的碰撞检测组掩码
	 */
	virtual	const LightGroupsMask & getGroupsMask() = 0;


	// 睡眠

	/*! \brief 如果角色处于睡眠状态，唤醒角色
     *	 
     *  \param wakeCounterValue[in] 新的睡眠计数器值。<b>取值范围:</b> [0,正无穷]
     *	 	 
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual	void wakeUp( float wakeCounterValue=LIGHT_SLEEP_INTERVAL ) = 0;


	/*! \brief 隐藏/显示角色
     *	 
     *  \param hide 隐藏/显示命令（TRUE = 隐藏，FALSE = 显示），角色隐藏时，角色的物理模型仍旧正常存在。
     *	 	 
	 *  \remarks 此函数通常在调试程序时使用，缺省情况下角色是隐藏的，当调试程序时可能需要显示角色。 
     */
	virtual void hide( bool hide ) = 0;

   /*! \brief 查询角色矩阵（矩阵包含位置和方向信息）
	*
	*  \return 返回要查询的角色矩阵引用 float matrix[4][4]。
	*/
	virtual	mat44_t &getGlobalPoseMatrix44() = 0;

   /*! \brief 查询角色方向（使用矩阵） 注：临时函数，提供一个 3x4 的矩阵
	*	
	*  \return 返回要查询的角色方向矩阵指针 float matrix[4][3]。
	*/
	virtual	mat34_t &getGlobalOrientationMatrix34() = 0;


	/*! \brief 在指位置施加力
     *	 
     *  \param float fx 力矢量的 x 分量
     *
	 *  \param float fy 力矢量的 y 分量
     *
	 *  \param float fz 力矢量的 z 分量
     *
	 *  \param float px 位置的 x 坐标
     *
	 *  \param float py 位置的 y 坐标
     *
	 *  \param float pz 位置的 z 坐标
     *
	 *  \remarks 本函数没有相关信息。
	 *
     *  \return 本函数没有返回值。
     */
	virtual void AddForceAtPos( float fx, float fy, float fz, float px, float py, float pz ) = 0;


	// 公共变量：

	/** 你能将它用于任何用途，通常用来和一个对象创建 1:1 对应的关系。*/
	void * userData;

};