/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   fluid.h
 *  内容:   流体函数
 *
 ****************************************************************************/


/*! \file fluid.h
 * 流体函数.
 * 此文件是流体函数头文件.
 */


/*// 角色控制器类型
enum LightCharacterType
{
	LIGHT_CHARACTER_BOX,     // 长方体
	LIGHT_CHARACTER_CAPSULE  // 胶囊  
};

// 角色控制器描述符标志位
#define	LIGHT_CHARACTER_SLOPELIMIT  0x0001
#define	LIGHT_CHARACTER_SKINWIDTH   0x0002
#define	LIGHT_CHARACTER_STEPOFFSET  0x0004*/

/** 流体描述符结构 */
typedef struct
{
	///**	粒子最初被加到流体时的属性 */
	//LightParticleData	initialParticleData;

	/**	流体使用的最大粒子数 */
	int 	maxParticles;

	/**	创建时的备用粒子数 */
	int 	numReserveParticles;

	/** 粒子布告板大小（仅用于显示，与物理属性无关） */
	float   particleBillboardWidth;

	/** 含义同上 */
	float   particleBillboardHeight;

	///**	The particle resolution given as particles per linear meter measured when the fluid is in its rest state (relaxed). */	
	float 	restParticlesPerMeter;
	
	/** 流体密度（水大约是 1000） */
	float 	restDensity;
	
	/** 粒子相互作用范围半径 */
	float 	kernelRadiusMultiplier;
	
	/** 单个粒子在一个时间步内允许前进的最大距离 */
	float 	motionLimitMultiplier;
	
	/** 定义粒子和碰撞几何体之间的距离，该值在引擎运行期间一直有效 */
	float 	collisionDistanceMultiplier;
	
	/** 这个参数控制流体的平放 */
	int 	packetSizeMultiplier;
	
	/** 粒子的硬度，相互作用涉及到压力 */
	float 	stiffness;
	
	/** 流体的粘性定义它有粘性的行为 */
	float 	viscosity;

	/** 流体的表面张力定义一个粒子间的吸引力 */
	float 	surfaceTension;
	
	/** 速度衰减速常量，这是全局常量将应用到每一个粒子 */
	float 	damping;
	
	/** 定义一个粒子“淡入”时间长度 */
	float 	fadeInTime;
	
	/** 加速度（m/s^2）在所有的时间步应用到所有的粒子 */
	vec3_t	externalAcceleration;
		
	/** 定义流体粒子和静态几何体碰撞的弹力系数 */
	float 	restitutionForStaticShapes;
		
	/** 定义流体关于静态几何体表面的动态磨擦力系数 */
	float 	dynamicFrictionForStaticShapes;
		
	/** 定义流体关于静态几何体表面的静态磨擦力系数 */
	float 	staticFrictionForStaticShapes;
	
	/** 定义粒子和静态刚体之间碰撞时的吸引力 */
	float 	attractionForStaticShapes;
	
	/** 定义流体粒子和动态几何体碰撞的弹力系数 */
	float 	restitutionForDynamicShapes;
		
	/** 定义流体关于动态几何体表面的动态磨擦力系数 */
	float 	dynamicFrictionForDynamicShapes;
	
	/** 定义流体关于动态几何体表面的静态磨擦力系数 */
	float 	staticFrictionForDynamicShapes;
	
	/** 定义粒子和动态刚体之间碰撞时的吸引力 */
	float 	attractionForDynamicShapes;
	
	/** 定义一个推动力系数，从流体到碰撞的刚体 */
	float 	collisionResponseCoefficient;

} LightFluidDesc;


/*! \class LightFluid
 *  \brief 流体类
 *
 *  本类负责一个流体的创建，管理和渲染等功能。
 *  每个 LightFluid 实例都必须通过 LightScene 类的 createFluid 函数分配，通过 releaseFluid 函数释放。 
 */

class LightFluid
{

public:

	/*enum LightCharacterFlag
	{
		LIGHT_CHARACTER_COLLISION_SIDES = (1<<0), // 角色侧面发生了碰撞
		LIGHT_CHARACTER_COLLISION_UP    = (1<<1), // 角色上面发生了碰撞
		LIGHT_CHARACTER_COLLISION_DOWN  = (1<<2), // 角色下面发生了碰撞
	};*/

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

	/*! \fn LightFluidEmitter * createEmitter( const LightFluidEmitterDesc * fluidEmitterDesc ) = 0
	 *  \brief 创建一个流体发射器
	 *
	 *  创建一个流体发射器
	 *
	 *  \param const LightFluidEmitterDesc * fluidEmitterDesc 流体发射器描述符指针，用于说明要创建流体发射器的特征。
	 *	 
	 *  \return 返回已创建的流体发射器指针
	 *
	 *  \see 
	 */
	virtual LightFluidEmitter * createEmitter( const LightFluidEmitterDesc * fluidEmitterDesc ) = 0;

	/*! \fn void releaseEmitter( LightFluidEmitter * fluidEmitter ) = 0
	 *  \brief 释放一个流体发射器
	 *
	 *  释放一个流体发射器
	 *
	 *  \param LightFluidEmitter * fluidEmitter 要释放流体发射器的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseEmitter( LightFluidEmitter * fluidEmitter ) = 0;

	/*! \fn void render() = 0
	 *  \brief 渲染流体
	 *
	 *  渲染流体
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void render() = 0;

};