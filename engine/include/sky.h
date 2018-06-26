/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   sky.h
 *  内容:   天空函数
 *
 ****************************************************************************/


/*! \file sky.h
 * 天空函数.
 * 此文件是天空函数头文件.
 */


class LightEngine;


// 天空类型
#define LIGHT_SKY_BOX       0    // 天空盒
#define LIGHT_SKY_DOME      1    // 天空顶
#define LIGHT_SKY_PLANE     2    // 天空面


/** 天空描述符类 */
class LightSkyDesc
{
public:

	/** 天空类型 */
	int    type;

#ifdef LIGHT_CORPORATION_EDITION

	/** 天空旋转速度（以度/秒为单位） */
	float  rotate_velocity;

	/** 天空旋转轴，通过一个向量来指定 */
	vec3_t rotate_axis;

	/** 云层盒大小 */
	vec3_t cloud_size;

	/** 云层移动速度 */
	vec3_t cloud_velocity;

	/** 云层纹理缩放比例 */
	float  cloud_scale;

#endif

	/** 天空盒顶面纹理，天空顶和天空面也用的是此纹理 */
	LightTexture * top;

	/** 天空盒前面纹理 */
	LightTexture * front;

	/** 天空盒后面纹理 */
	LightTexture * back;

	/** 天空盒左面纹理 */
	LightTexture * left;

	/** 天空盒右面纹理 */
	LightTexture * right;

	/** 天空盒底面纹理 */
	LightTexture * bottom;

#ifdef LIGHT_CORPORATION_EDITION

	/** 天空盒云层纹理 */
	LightTexture * cloud;

#endif

	/** 天空盒长、宽、高 */
	struct { vec3_t size;   } box;

	struct { float  radius;
	         float  dtheta;
			 float  dphi;
			 float  hTile;
			 float  vTile;  } dome;   // 球体的半径

	struct { float  radius;
			 int    divisions;
			 float  PlanetRadius;
			 float  AtmosphereRadius;
			 float  hTile;
			 float  vTile;  } plane; // 圆柱体的半径和高

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightSkyDesc()
	{
		memset( this, 0, sizeof(LightSkyDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */
	LIGHT_INLINE void setToDefault()
	{
		type = LIGHT_SKY_BOX;

#ifdef LIGHT_CORPORATION_EDITION

		rotate_velocity = 0.0f;
		VEC3( rotate_axis, 0.0f, 0.0f, 1.0f );
		VEC3( cloud_size, 64.0f, 64.0f, 64.0f );
		VEC3( cloud_velocity, 0.0f, 0.0f, 0.0f );
		cloud_scale = 1.0f;
		cloud = NULL;

#endif

		top = NULL;
		front = NULL;
		back = NULL;
		left = NULL;
		right = NULL;
		bottom = NULL;

		VEC3( box.size, 64.0f, 64.0f, 64.0f );

	/*struct { float  radius;
	         float  dtheta;
			 float  dphi;
			 float  hTile;
			 float  vTile;  } dome;   // 球体的半径

	struct { float  radius;
			 int    divisions;
			 float  PlanetRadius;
			 float  AtmosphereRadius;
			 float  hTile;
			 float  vTile;  } plane; // 圆柱体的半径和高*/

		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightSky
 *  \brief 天空类 
 *
 *  本类负责天空的构建、显示，支持天空盒、天空顶、天空面三种类型的天空。
 *  每个 LightSky 实例都必须通过 LightEngine 类的 createSky 方法分配， releaseSky 释放。
 */

class LightSky
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回引擎指针
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 渲染天空
	 *		 
	 *  \see 
	 */
	virtual void render ( void ) = 0;

};