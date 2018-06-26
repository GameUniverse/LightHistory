/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   water.h
 *  内容:   水函数
 *
 ****************************************************************************/


/*! \file water.h
 * 水函数.
 * 此文件是水函数头文件.
 */


// 水类型
#define LIGHT_WATER_RECTANGLE       0    // 水矩形


/** 水描述符类 */
class LightWaterDesc
{
public:

	/** 水类型 */
	int    type;

	/** 水的初始位置 */
	vec3_t pos;

	/** 水面的法线贴图 */
	LightTexture * normal;

	/** GLSL 顶点 shader 文件名 */
	char vertex[64];

	/** GLSL 片断 shader 文件名 */
	char fragment[64];

	/** 水矩形长和宽 */
	struct { float width;
		     float height; } rectangle;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */
	LIGHT_INLINE LightWaterDesc()
	{
		memset( this, 0, sizeof(LightWaterDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */
	LIGHT_INLINE void setToDefault()
	{
		type = LIGHT_WATER_RECTANGLE;
		VEC3( pos, 0.0f, 0.0f, 0.0f );
		normal = NULL;
		strcpy( vertex, "" );
		strcpy( fragment, "" );
		rectangle.width = 64;
		rectangle.height = 64;
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightWater
 *  \brief 水类
 *
 *  本类负责水的构建、更新、显示，可以实现非常逼真的水面效果，支持水面的反射、折射、凹凸贴图、逐像素光照和涟漪效果。
 *  每个 LightWater 实例都必须通过 LightEngine 类的 createWater 方法分配， releaseWater 释放。
 */

class LightWater
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

    #define LIGHT_REFLECTION_MAP  1  // 反射图
	#define LIGHT_REFRACTION_MAP  2  // 折射图

	/*! \brief 开始渲染水面反射（折射）图
	 *	 
	 *  \param map[in] 指定要渲染反射图还是折射图
	 *	 
	 *  \see 
	 */
	virtual void begin( int map ) = 0;

	/*! \brief 停止渲染水面反射（折射）图
	 *	 
	 *  \see 
	 */
	virtual void end( void ) = 0;

	/*! \brief 渲染水
	 *
	 *  \see 
	 */
	virtual void render ( void ) = 0;

};