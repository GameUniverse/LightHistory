/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   particle.h
 *  内容:   粒子函数
 *
 ****************************************************************************/


/*! \file particle.h
 * 粒子函数.
 * 此文件是粒子函数头文件.
 */


/** 粒子数据结构 */
typedef struct
{
	
} LightParticleData;


/** 粒子类型 */
enum LightParticleType
{
	/** 标准粒子 */
	LIGHT_PARTICLE_NORMAL,

	/** 柱状流体 */
	LIGHT_PARTICLE_CURRENT,


	LIGHT_PARTICLE_COMPOUND,

	LIGHT_PARTICLE_COUNT,

	LIGHT_PARTICLE_FORCE_DWORD = 0x7fffffff
};


// 粒子运动轨迹

/** 静止不动（仅指轨迹） */
#define  LIGHT_TRACK_POINT       0
/** 射线 */
#define  LIGHT_TRACK_RADIAL      1

#ifdef LIGHT_CORPORATION_EDITION

/** 向外辐射 */
#define  LIGHT_TRACK_RADIATE     2
/** 向一点聚集 */
#define  LIGHT_TRACK_CONVERGE    3
/** 螺旋形 */
#define  LIGHT_TRACK_GYROIDAL    4
/** 环绕 */
#define  LIGHT_TRACK_CIRCLE      5

#endif


/** 粒子描述符类 */
class LightParticleDesc
{
public:

	/** 粒子名称 */
	char   name[17];

	/** 粒子类型 */
	LightParticleType  type;

	/** 粒子运动轨迹 */
	int    track;

	/** 粒子发射源中心位置 */
	vec3_t center;

	/** 粒子发射源世界位置 */
	vec3_t global_position;

	/** 粒子发射源世界方向 */
	quat_t global_orientation;

	/** 粒子发射源局部位置 */
	vec3_t local_position;

	/** 粒子发射源局部方向 */
	quat_t local_orientation;

	vec3_t vector;              // 粒子发射方向
	int    numparticle;         // 粒子数
	int    billboard_mode;      // 粒子布告板模式
	float  billboard_width;     // 单个粒子布告板的宽度
	float  billboard_height;    // 单个粒子布告板的高度
	float  rise;                // 上升力的大小（如烟、火等）   
	int    life;                // 粒子发射源寿命，以千分之一秒为单位
	int    particle_life;       // 粒子寿命，以千分之一秒为单位
	float  emission_rate;       // 粒子发射速度，以（个/秒）为单位
	vec3_t homeplace_box;       // 粒子出生盒大小
	bool   disable_texture;	    // 禁用（或使用）布告板纹理
	char   texture[170];        // 纹理文件名称
	int    grid_width;          // 栅格宽度
	int    grid_height;         // 栅格高度
	int    num_grid;            // 动画栅格数
	int    min_frame;           // 最小起始纹理帧数
	int    max_frame;           // 最大起始纹理帧数
	bool   flip_horizintal;     // 允许水平翻转粒子
	bool   flip_vertical;       // 允许垂直翻转粒子
	float  left_point;          // 左转折点（取值范围[0,1]）
	float  right_point;         // 右转折点（取值范围[0,1]）
	int    color[4][4];         // 颜色（RGBA，含透明度）插值列表[开始，左中，右中，结束]
	vec3_t scale[4];            // 缩放插值列表[开始，左中，右中，结束]
	quat_t rotate[4];           // 旋转插值列表[开始，左中，右中，结束]
	vec3_t gyroidal[4];         // 螺旋（半径，旋转角度，高度，此为路径插值）插值列表[开始，左中，右中，结束]
	//int    material[4];         // 贴图插值列表[开始，左中，右中，结束]

	/** 柱状流体参数 */
	struct
	{
		/** 端点 1 （流动方向为 p1->p2） */
		vec3_t p1;

		/** 端点 2 */
		vec3_t p2;

		/** 半径 */
		float radius;

	} current;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */
	LIGHT_INLINE LightParticleDesc()
	{
		memset( this, 0, sizeof(LightParticleDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "particle" );
		type = LIGHT_PARTICLE_NORMAL;
		track = LIGHT_TRACK_POINT;
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( vector, 0.0f, 0.0f, 1.0f );
		numparticle = 16;
		//billboard_mode = LIGHT_BILLBOARD_POINT;
		billboard_mode = 0;
		billboard_width = 1.0f;
		billboard_height = 1.0f;
		rise = 1.5f;
		//life = 0;
		particle_life = 1000;
		emission_rate = 8;
		VEC3( homeplace_box, 0.1f, 0.1f, 0.1f );
		disable_texture = FALSE;
	    texture[0] = '\0';
		grid_width = 64;
		grid_height = 64;
		num_grid = 1;
		min_frame = 0;
		max_frame = 4;
		flip_horizintal = FALSE;
		flip_vertical = FALSE;
		left_point = 0.33f;
		right_point = 0.66f;
		VEC4( color[0], 255, 255, 255, 0 );
		VEC4( color[1], 255, 255, 255, 255 );
		VEC4( color[2], 255, 255, 255, 255 );
		VEC4( color[3], 255, 255, 255, 0 );
		VEC3( scale[0], 1.0f, 1.0f, 1.0f );
		VEC3( scale[1], 1.0f, 1.0f, 1.0f );
		VEC3( scale[2], 1.0f, 1.0f, 1.0f );
		VEC3( scale[3], 1.0f, 1.0f, 1.0f );
		VEC4( rotate[0], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC4( rotate[1], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC4( rotate[2], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC4( rotate[3], 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( gyroidal[0], 1.0f, 0.0f, 0.0f );
		VEC3( gyroidal[1], 1.0f, 120.0f, 1.0f );
		VEC3( gyroidal[2], 1.0f, 240.0f, 2.0f );
		VEC3( gyroidal[3], 1.0f, 360.0f, 3.0f );

		VEC3( current.p1, -1.0f, 0.0f, 0.0f );
		VEC3( current.p2,  1.0f, 0.0f, 0.0f );
		current.radius = 0.5f;

		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightParticle
 *  \brief 粒子类 
 *
 *  本类负责粒子的创建、管理和显示。每个 LightParticle 实例都必须通过 LightEngine 类的 NewParticle 方法分配。 
 */

class LightParticle
{

public:

	/*! \brief 查询父引擎
	 *	 	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 从文件中读取粒子数据
	 *	 
	 *  \param filename 要读取的粒子数据文件名称
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *	 
	 *  \see 
	 */
	virtual int load( const char *filename ) = 0;

	/*! \brief 保存粒子数据到文件中
	 *	 
	 *  \param filename 要保存的的粒子数据文件名称
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *	 
	 *  \see 
	 */
	virtual int save( const char *filename ) = 0;

	/*! \brief 从描述符中读取粒子数据
	 *	 
	 *  \param particleDesc 要读取的粒子数据描述符
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *	 
	 *  \see 
	 */
	virtual int loadFromDesc( LightParticleDesc &particleDesc ) = 0;

	/*! \brief 保存粒子数据到描述符中
	 *	 
	 *  \param particleDesc 要保存的粒子数据描述符
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *	 
	 *  \see 
	 */
	virtual int saveToDesc( LightParticleDesc &particleDesc ) = 0;

	/*! \brief 释放内存中的粒子数据
	 *		 
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *	 
	 *  \see 
	 */
	virtual int unload() = 0;

	/*! \brief 设置粒子发射源中心位置
	 *	 
	 *  \param x 中心位置的 x 坐标
	 *
	 *  \param y 中心位置的 y 坐标
	 *
	 *  \param z 中心位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setCenter( float x, float y, float z ) = 0;

	/*! \brief 把粒子绑定到骨骼动画骨头上
	 *	 
	 *  绑定后，粒子将跟随绑定的骨头进行运动（包括位置和方向），同一时刻，只有最后绑定的骨头有效。
	 *
	 *  \param skeleton[in] 要绑定的骨骼动画，当该参数为 NULL 时解除绑定
	 *
	 *  \param bone[in] 要绑定的骨头
	 *
	 *  \return 如果函数调用成功，返回 0；否则，返回错误代码。
	 *
	 *  \see 
	 */
	virtual int attach( LightSkeleton * skeleton, int bone ) = 0;

	/*! \brief 设置粒子发射源世界位置
	 *	 
	 *  \param x 发射源世界位置的 x 坐标
	 *
	 *  \param y 发射源世界位置的 y 坐标
	 *
	 *  \param z 发射源世界位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置粒子发射源世界方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的粒子发射源世界方向四元数
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置粒子发射源世界方向（使用绕轴旋转）
     *
	 *  设置粒子发射源世界方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 粒子发射源绕轴旋转角度
     *
     *  \param x[in] 旋转轴向量 x 分量
     *
	 *  \param y[in] 旋转轴向量 y 分量
     *
	 *  \param z[in] 旋转轴向量 z 分量
     *
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。
	 *
     */
	virtual	void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;

	/*! \brief 设置粒子发射源局部位置
	 *	 
	 *  \param x 发射源局部位置的 x 坐标
	 *
	 *  \param y 发射源局部位置的 y 坐标
	 *
	 *  \param z 发射源局部位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置粒子发射源局部方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的粒子发射源局部方向四元数
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置粒子发射源局部方向（使用绕轴旋转）
     *
	 *  设置粒子发射源局部方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 粒子发射源绕轴旋转角度
     *
     *  \param x[in] 旋转轴向量 x 分量
     *
	 *  \param y[in] 旋转轴向量 y 分量
     *
	 *  \param z[in] 旋转轴向量 z 分量
     *
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。
	 *
     */
	virtual	void setLocalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;

	/*! \brief 设置粒子发射方向
	 *
	 *  设置粒子发射方向。
	 *
	 *  \param float x 发射方向的 x 分量
	 *
	 *  \param float y 发射方向的 y 分量
	 *
	 *  \param float z 发射方向的 z 分量
	 *
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void setVector ( float x, float y, float z ) = 0;

	/*! \brief 设置粒子发射源开口角度
	 *
	 *  设置粒子发射源开口角度。
	 *
	 *  \param float angle 发射源开口角度
	 *	 
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void setAngle ( float angle ) = 0;

	/*! \brief 设置粒子初始速度
	 *
	 *  设置粒子初始速度
	 *
	 *  \param float speed 粒子初始速度
	 *	 
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void speed ( float speed ) = 0;

	/*! \brief 设置粒子寿命
	 *
	 *  设置粒子寿命
	 *
	 *  \param int life 每个粒子的存活时间（以千分之一秒为单位）
	 *	 
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void life ( int life ) = 0;

	/*! \brief 设置粒子追随因子
	 *
	 *  设置粒子追随因子。通常情况下，粒子离开发射源后，就不再受发射源位置的影响；但总的粒子数是有限的，有时为了更逼真地模拟快速移动的物体，
	 *  我们需要让粒子跟着发射源的位置移动，通过设置追随因子，我们就能模拟这种现象。
	 *
	 *  \param float factor 要设置的追随因子，取值范围（0~1），0 表示粒子离开发射源后就不再受发射源位置的影响，1 表示粒子的位置完全由发射源的位置确定。
	 *	 
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void follow ( float factor ) = 0;

	/*! \brief 设置存活粒子数
	 *
	 *  设置存活粒子数
	 *
	 *  \param int sum 所有存活粒子的总数
	 *	 
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void sum ( int sum ) = 0;

	/*! \brief 设置单个粒子大小
	 *
	 *  设置单个粒子大小
	 *
	 *  \param float width 单个粒子的宽度
	 *
	 *  \param float height 单个粒子的高度
	 *
	 *  \return 本函数无返回值。
	 *
	 *  \see 
	 */
	virtual void size ( float width, float height ) = 0;

	/*! \brief 渲染粒子
	 *
	 *  渲染粒子。
	 *
	 *  \param 本函数无参数。
	 *
	 *  \return 本函数无返回值。如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual void render ( void ) = 0;

	/*! \brief 重新激活粒子发射源
	 *
	 *  此函数用于重新激活生命周期结束的粒子发射源
	 *	 
	 *  \see 
	 */
	virtual void active( void ) = 0;

};