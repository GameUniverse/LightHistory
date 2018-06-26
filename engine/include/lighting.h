/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   lighting.h
 *  内容:   灯光函数
 *
 ****************************************************************************/


/*! \file lighting.h
 * 灯光函数.
 * 此文件是灯光函数头文件.
 */

class LightEngine;


/* 灯光类型 */
#define LIGHT_POINT_LIGHTING          0   /* 点光源     */
#define LIGHT_ORIENTATION_LIGHTING    1   /* 方向光     */
#define LIGHT_SPOTLIGHT_LIGHTING      2   /* 聚光灯     */

/* 灯光的颜色 */
#define LIGHT_AMBIENT    1259   /* 环境光     */
#define LIGHT_DIFFUSE    1260   /* 漫反射     */
#define LIGHT_SPECULAR   1261   /* 镜面反射光 */

/* 灯光的衰减因子 */
#define LIGHT_CONSTANT   1262   /* 恒定衰减因子 */
#define LIGHT_LINEAR     1263   /* 线性衰减因子 */
#define LIGHT_QUADRATIC  1264   /* 二次衰减因子 */

/** 灯光描述符 */
typedef struct
{
	/** 灯光类型 */
	int    type;

	/** 灯光位置 */
	float  position[4];

	/** 环境光颜色 */
	float  ambient[4];

	/** 漫反射光颜色 */
	float  diffuse[4];

	/** 高光颜色 */
	float  specular[4];

	/** 常数衰减因子 */
	float  constant;

	/** 线性衰减因子 */
	float  linear;

	/** 二次衰减因子 */
	float  quadratic;

	/** 聚光灯参数 */
	struct
	{
		/** 灯光聚集目标位置 */
		vec3_t target;

		/** 聚光指数 */
		float  exponent;

		/** 聚光角度 */
		float angle;

	} spotlight;

	/** 立即开启灯光 */
	bool   enable;

} LightLightDesc;


/*! \brief 灯光类
 *
 *  本类负责动态灯光的管理。
 *  每个 LightLight 实例都必须通过 LightEngine 类的 createLight 方法分配，分配实例的同时，也就创建了一个动态灯光。 
 */

class LightLight
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 设置灯光的位置
	 *	 
	 *  \param x[in] 灯光位置的 x 坐标
	 *
	 *  \param y[in] 灯光位置的 y 坐标
	 *
	 *  \param z[in] 灯光位置的 z 坐标
	 *
	 *  \param w[in] 灯光位置的 w 坐标
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int setPosition( float x, float y, float z, float w ) = 0;

	/*! \brief 设置灯光的颜色值
	 *	 
	 *  \param name[in]  要设置的灯光颜色。可以选择下面的其中一个值：
	 *                   \li LIGHT_AMBIENT   环境光
	 *                   \li LIGHT_DIFFUSE   漫反射
	 *                   \li LIGHT_SPECULAR  镜面反射光
	 *
	 *  \param red[in] 灯光颜色的红色成分
	 *
	 *  \param green[in] 灯光颜色的绿色成分
	 *
	 *  \param blue[in] 灯光颜色的蓝色成分
	 *
	 *  \param alpha[in] 灯光颜色的 Alpha 色成分
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int setColor( int name, float red, float green, float blue, float alpha ) = 0;

	/*! \brief 设置灯光的聚光参数
	 *	 
	 *  \param x[in]  聚光方向的 x 坐标
	 *
	 *  \param y[in] 聚光方向的 y 坐标
	 *
	 *  \param z[in] 聚光方向的 z 坐标
	 *
	 *  \param exponent[in] 灯光的聚光指数
	 *
	 *  \param angle[in] 灯光的聚光角度
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int setSpotlight( float x, float y, float z, float exponent, float angle ) = 0;

	/*! \brief 设置灯光的衰减因子
	 *	 
	 *  \param name[in] 要设置的衰减因子。可以选择下面的其中一个值：
	 *                  \li LIGHT_CONSTANT   恒定衰减因子
	 *                  \li LIGHT_LINEAR     线性衰减因子
	 *                  \li LIGHT_QUADRATIC  二次衰减因子
	 *
	 *  \param attenuation[in] 衰减因子的值
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int setAttenuation( int name, float attenuation ) = 0;

	/*! \brief 打开灯光
	 *	 
	 *  \see 
	 */
	virtual void enable() = 0;

	/*! \brief 关闭灯光
	 *	 
	 *  \see 
	 */
	virtual void disable() = 0;

};