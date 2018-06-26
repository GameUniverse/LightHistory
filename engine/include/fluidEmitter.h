/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   fluidEmitter.h
 *  内容:   流体发射器函数
 *
 ****************************************************************************/


/*! \file fluidEmitter.h
 * 流体发射器函数.
 * 此文件是流体发射器函数头文件.
 */


class LightFluid;


enum LightFluidEmitterFlag
{

	LIGHT_FEF_VISUALIZATION		= (1<<0),

	LIGHT_FEF_FORCE_ON_BODY		= (1<<2),
	
	LIGHT_FEF_ADD_BODY_VELOCITY	= (1<<3),
	
	LIGHT_FEF_ENABLED				= (1<<4),
	
};

enum LightEmitterShape
{
	LIGHT_FE_RECTANGULAR		= (1<<0),
	LIGHT_FE_ELLIPSE			= (1<<1)
};

enum LightEmitterType
{
	LIGHT_FE_CONSTANT_PRESSURE		= (1<<0),
	LIGHT_FE_CONSTANT_FLOW_RATE	= (1<<1)
};


/** 流体发射器描述符结构 */
typedef struct
{
	/** 相对于 frameShape（发射器形体）的发射器位置和方向 */
	mat34_t			relPose;

	/** 相对于 frameShape（发射器形体）的发射器位置 */
	vec3_t          relPosition;

	/** 相对于 frameShape（发射器形体）的发射器方向四元数 */
	quat_t          relOrientationQuat;

	/** 角色指针指向发射器要绑定的角色 */
	LightActor *	frameShape;

	/** 发射器运转模式 */
	int 	type;

	/** 从这个发射器发射出的最大粒子数 */
	int 	maxParticles;

	/** 发射器的形状可以指定为矩形或椭圆 */
	int 	shape;
	
	/** 发射器在第一、二轴方向的大小，此轴由它的方向（relPose 或 relOrientationQuat ）决定 */
	float 	dimensionX;

	/** 含义同上 */
	float 	dimensionY;

	/** 发射器方向的每一个轴方向的随机向量值（肯定是一个正值） */
    vec3_t	randomPos;

	/** 发射方向的随机角度偏差 */
	float 	randomAngle;

	/** 发射出去的流体粒子的速度大小 */
	float 	fluidVelocityMagnitude;

	/** 这个速度指定每秒钟发射多少个粒子 */
	float 	rate;
	
	/** 指定以秒为单位的发射粒子的生命周期 */
	float 	particleLifetime;

	float 	repulsionCoefficient;
	
	int 	flags;

} LightFluidEmitterDesc;


/*! \class LightFluidEmitter
 *  \brief 流体发射器类
 *
 *  本类负责一个流体发射器的创建，管理和渲染等功能。
 *  每个 LightFluidEmitter 实例都必须通过 LightFluid 类的 createEmitter 函数分配，通过 releaseEmitter 函数释放。 
 */

class LightFluidEmitter
{

public:

	/*! \fn LightFluid * getFluid() = 0
	 *  \brief 查询父流体
	 *
	 *  查询父流体
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return LightFluid * 返回父流体引用
	 *
	 *  \see 
	 */	
	virtual	LightFluid * getFluid() = 0;

};