/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   fog.h
 *  内容:   雾函数
 *
 ****************************************************************************/


/*! \file fog.h
 * 雾函数.
 * 此文件是雾函数头文件.
 */


class LightEngine;


// 雾类型
/*#define LIGHT_SKY_BOX       0    // 天空盒
#define LIGHT_SKY_DOME      1    // 天空顶
#define LIGHT_SKY_PLANE     2    // 天空面*/


/** 雾描述符 */
typedef struct
{
	/** 雾类型 */
	int    type;

	/** 雾颜色 */
	float  color[4];

	/** 雾密度 */
	float  density;

	/** 雾开始的位置 */
	float  start;

	/** 雾结束的位置 */
	float  end;

	/** 雾的显示品质 */
	int    quality;

	/** 立即开启雾 */
	bool   enable;

} LightFogDesc;


/*! \brief 雾类
 *
 *  本类负责雾的开启、关闭和参数设置。
 *  每个 LightFog 实例都必须通过 LightEngine 类的 createFog 方法分配。 
 */

class LightFog
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回引擎指针
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 设置雾的颜色
	 *	
	 *  \param red[in] 雾颜色的红色分量
     *	
	 *  \param green[in] 雾颜色的绿色分量
     *	
	 *  \param blue[in] 雾颜色的蓝色分量
     *	
	 *  \param alpha[in] 雾颜色的 ALPHA 分量
     *	
	 *  \see 
	 */
	virtual void color( float red, float green, float blue, float alpha ) = 0;

	/*! \brief 设置雾的密度
	 *	
	 *  \param density[in] 雾的密度
     *
	 *  \see 
	 */
	virtual void density( float density ) = 0;

	/*! \brief 设置雾的范围
	 *	
	 *  \param start[in] 从屏幕到雾开始平面的距离
     *
	 *  \param end[in] 从屏幕到雾结束平面的距离
     *
	 *  \see 
	 */
	virtual void bound( float start, float end ) = 0;

	/*! \brief 设置雾的显示品质
	 *	
	 *  \param quality[in] 雾的显示品质
     *
	 *  \see 
	 */
	virtual void quality( int quality ) = 0;

	/*! \brief 开启雾
	 *		 
	 *  \see 
	 */
	virtual void enable() = 0;

	/*! \brief 关闭雾
	 *		 
	 *  \see 
	 */
	virtual void disable() = 0;

};