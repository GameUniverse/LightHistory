/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   character.h
 *  内容:   角色控制函数
 *
 ****************************************************************************/


/*! \file character.h
 * 角色控制函数.
 * 此文件是角色控制函数头文件.
 */


// 角色控制器类型
enum LightCharacterType
{
	LIGHT_CHARACTER_BOX,     // 长方体
	LIGHT_CHARACTER_CAPSULE  // 胶囊  
};

// 角色控制器描述符标志位
#define	LIGHT_CHARACTER_SLOPELIMIT  0x0001
#define	LIGHT_CHARACTER_SKINWIDTH   0x0002
#define	LIGHT_CHARACTER_STEPOFFSET  0x0004

typedef struct
{
	LightCharacterType  type;        // 角色控制器类型
	int                 flags;       // 有效数据标志位
	vec3_t              position;    // 角色控制器位置
	float 			    slopeLimit;  // 角色控制器能爬的最大坡度（用角度的余弦表示，缺省值 0.707）
	float		        skinWidth;   // 角色控制器外壳宽度（缺省值 0.1）
	float		        stepOffset;  // 角色控制器能爬过的最大障碍物高度（缺省值 0.5）
	//NxUserControllerHitReport*	callback;
	//NxCCTInteractionFlag		interactionFlag;	

	struct { vec3_t size;   } box;      // 长方体长、宽、高

	struct { float  radius;
			 float  height; } capsule;  // 胶囊体的半径和高

} LightCharacterDesc;


/*! \class LightCharacter
 *  \brief 角色控制类 
 *
 *  本类负责一个角色在物理世界中的正确运算，包括行走、跳跃等绝大部分功能。
 *  每个 LightCharacter 实例都必须通过 LightEngine 类的 createCharacter 函数分配，通过 releaseCharacter 函数释放。 
 */

class LightCharacter
{

public:

	enum LightCharacterFlag
	{
		LIGHT_CHARACTER_COLLISION_SIDES = (1<<0), // 角色侧面发生了碰撞
		LIGHT_CHARACTER_COLLISION_UP    = (1<<1), // 角色上面发生了碰撞
		LIGHT_CHARACTER_COLLISION_DOWN  = (1<<2), // 角色下面发生了碰撞
	};

	/*! \brief 查询父场景
	 *	 
	 *  \return 返回父场景指针
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;

	/*! \fn void move( const vec3_t vector, float minDist, unsigned long * collisionFlags, float sharpness ) = 0
	 *  \brief 移动角色控制器
	 *
	 * 移动角色控制器
	 *
	 *  \param const vec3_t vector 是当前帧的位移向量。在一般情况下，当你的角色正在移动时，它是垂直向下的重力和水平移动量（均由此参数指定）的组合。
	 *                             注意这是一个位移向量（第一次序），它只对当前帧起作用，并且不会累加；它不是一个速度向量（第二次序）或力（第三次序）向量。
	 *
	 *  \param float minDist 是提前停止位移递归算法的最小距离值，缺省值是 1。
	 *
	 *  \param unsigned long * collisionFlags 是一个位掩码指针，返回在角色移动期间用户要查询的碰撞事件。这是 LightCharacterFlag 标志的组合，它能用来引发各种不同的角色动画。
	 *                                       例如，当此标志为 0 时，就可以播放一个落下的动画，当 LIGHT_CHARACTER_COLLISION_DOWN 标志反回时，就可以播放站立的动画。
	 * 
	 *  \param float sharpness 此参数保留，供以后使用，必须设置为 1.0f。
	 *
	 *  \remarks 
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void move( const vec3_t vector, float minDist, unsigned long * collisionFlags, float sharpness ) = 0;

	/*! \fn bool setPosition( const vec3_t position ) = 0
	 *  \brief 设置角色控制器的位置
	 *
	 *  设置角色控制器的位置
	 *
	 *  \param const vec3_t position 角色控制器新的位置
	 *
	 *  \remarks 
	 *
	 *  \return 目前总是返回 TRUE。
	 */
	virtual bool setPosition( const vec3_t position ) = 0;

	/*! \brief 查询角色控制器的位置
	 *	 
	 *  \remarks 
	 *
	 *  \return 返回角色控制器的全局世界坐标值。
	 */
	virtual const vec3_t * getPosition() = 0;

	/*! \brief 查询角色控制器过滤后的位置
	 *	 
	 *  \remarks 
	 *
	 *  \return 角色控制器过滤后的全局世界坐标值。
	 */
	virtual	const vec3_t& getFilteredPosition()	= 0;

	/*! \brief 设置步幅高度
	 *	 
	 *  \param offset[in] 角色控制器允许跨过的障碍物高度
	 */
	virtual	void setStepOffset( const float offset ) = 0;

	/*! \brief 允许/禁止这个角色控制器的碰撞检测
	 *	 
	 *  \param enabled[in] TRUE 开启角色控制器的碰撞检测
	 */
	virtual	void setCollision( bool enabled ) = 0;

	/*! \brief 渲染角色控制器
	 *	 	 
	 *  \remarks 	 
	 */
	virtual void render() = 0;

};