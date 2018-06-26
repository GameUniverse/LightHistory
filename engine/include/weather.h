/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   weather.h
 *  内容:   天气函数
 *
 ****************************************************************************/


/*! \file weather.h
 * 天气函数.
 * 此文件是天气函数头文件.
 */


class LightEngine;


// 天气类型
#define LIGHT_WEATHER_RAIN            0    // 雨
#define LIGHT_WEATHER_SNOW            1    // 雪
#define LIGHT_WEATHER_LIGHTNING       2    // 闪电


// 天气描述符
typedef struct
{
	int    type;                 // 天气类型
	int    numparticle;          // 粒子数
	vec3_t box;                  // 天气盒长、宽、高
	vec3_t position;             // 天气盒位置（相对于摄像机）
	float  drop_velocity_min;    // 粒子落下最小速度
	float  drop_velocity_max;    // 粒子落下最大速度
	vec3_t wind;                 // 风速
	
	//LightTexture * top;      // 天空盒顶面纹理，天空顶和天空面也用的是此纹理
	//LightTexture * front;    // 天空盒前面纹理	
	//LightTexture * cloud;    // 天空盒云层纹理

} LightWeatherDesc;


/*! \brief 天气类 
 *
 *  本类负责天气的构建、显示，支持雨、雪、闪电三种类型的天气。
 *  每个 LightWeather 实例都必须通过 LightEngine 类的 createWeather 方法分配。 
 */

class LightWeather
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回引擎指针
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 渲染天气
	 *		 
	 *  \see 
	 */
	virtual void render() = 0;

};