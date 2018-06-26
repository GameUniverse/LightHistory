/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   billboard.h
 *  内容:   布告板池函数
 *
 ****************************************************************************/


/*! \file billboard.h
 * 布告板池函数.
 * 此文件是布告板函数头文件.
 */


/** 布告板模式 */
#define  LIGHT_BILLBOARD_POINT      0
#define  LIGHT_BILLBOARD_ROTATE_X   1
#define  LIGHT_BILLBOARD_ROTATE_Y   2
#define  LIGHT_BILLBOARD_ROTATE_Z   3
#define  LIGHT_BILLBOARD_FIX_YZ     4
#define  LIGHT_BILLBOARD_FIX_XZ     5
#define  LIGHT_BILLBOARD_FIX_XY     6


/** 布告板池描述符类 */
class LightBillboardPoolDesc
{
public:

	/** 布告板模式 */
	int mode;

	/** 布告板池中心位置 */
	vec3_t center;

	/** 布告板池世界位置 */
	vec3_t global_position;

	/** 布告板池世界方向 */
	quat_t global_orientation;

	/** 布告板池局部位置 */
	vec3_t local_position;

	/** 布告板池局部方向 */
	quat_t local_orientation;

	/** 布告板宽度 */
	float width;

	/** 布告板高度 */
	float height;

	/** 布告板颜色（RGBA，最后一个数组成员为透明度 */
	int color[4];

	/** 布告板缩放比例 */
	vec3_t scale;

	/** 布告板旋转角度 */
	quat_t rotate;

	/** 水平翻转纹理 */
	bool flip_horizintal;

	/** 垂直翻转纹理 */
	bool flip_vertical;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */
	LIGHT_INLINE LightBillboardPoolDesc()
	{
		memset( this, 0, sizeof(LightBillboardPoolDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */
	LIGHT_INLINE void setToDefault()
	{
		mode = LIGHT_BILLBOARD_POINT;
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		width = 1.0f;
		height = 1.0f;
		VEC4( color, 255, 255, 255, 255 );	     // 布告板颜色缺省为白色不透明
		VEC3( scale, 1.0f, 1.0f, 1.0f );         // 布告板缺省为不进行缩放
		VEC4( rotate, 0.0f, 0.0f, 1.0f, 0.0f );  // 布告板缺省为不进行旋转
		flip_horizintal = FALSE;                 // 缺省为禁止水平翻转纹理
		flip_vertical = FALSE;                   // 缺省为禁止垂直翻转纹理
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightBillboardPool
 *  \brief 布告板池类 
 *
 *  本类负责布告板的管理和显示，支持点和轴两种类型的布告板。
 *  每个 LightBillboardPool 实例都必须通过 LightScene 类的 NewBillboard 方法分配。
 */

class LightBillboardPool
{

public:

	/*! \brief 查询父引擎
	 *		 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 设置布告板模式
	 *	
	 *  \param mode[in] 布告板模式
	 *
	 *  \see 
	 */
	virtual void mode( int mode ) = 0;

	/*! \brief 设置布告板池中心位置
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

	/*! \brief 设置布告板池世界位置
	 *	 
	 *  \param x 布告板池世界位置的 x 坐标
	 *
	 *  \param y 布告板池世界位置的 y 坐标
	 *
	 *  \param z 布告板池世界位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置布告板池世界方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的布告板池世界方向四元数
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置布告板池世界方向（使用绕轴旋转）
     *
	 *  设置布告板池世界方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 布告板池绕轴旋转角度
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

	/*! \brief 设置布告板池局部位置
	 *	 
	 *  \param x 布告板池局部位置的 x 坐标
	 *
	 *  \param y 布告板池局部位置的 y 坐标
	 *
	 *  \param z 布告板池局部位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置布告板池局部方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的布告板池局部方向四元数
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置布告板池局部方向（使用绕轴旋转）
     *
	 *  设置布告板池局部方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 布告板池绕轴旋转角度
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

	/*! \brief 设置布告板大小
	 *	
	 *  \param width[in] 布告板宽度	 
	 *  \param height[in] 布告板高度
	 *	 
	 *  \see 
	 */
	virtual void size( float width, float height ) = 0;

	/*! \brief 设置布告板颜色值
	 *	
	 *  该颜色值只影响后面新加入的布告板，每个布告板拥有一个独立的颜色值。
	 *
	 *  \param[in] red 颜色的红色成分（取值范围[0,255]，下同）
	 *  \param[in] green 颜色的绿色成分
	 *  \param[in] blue 颜色的蓝色成分
	 *  \param[in] alpha 颜色的 Alpha 成分
	 *	 
	 *  \see 
	 */
	virtual void color( int red, int green, int blue, int alpha ) = 0;

	/*! \brief 设置布告板缩放比例
	 *	
	 *  该缩放比例只影响后面新加入的布告板，每个布告板拥有一个独立的缩放比例。
	 *
	 *  \param[in] x 沿 x 轴的缩放比例（取值范围[正无穷,负无穷]，下同）
	 *  \param[in] y 沿 y 轴的缩放比例
	 *  \param[in] z 沿 z 轴的缩放比例
	 *	 
	 *  \see 
	 */
	virtual void scale( float x, float y, float z ) = 0;

	/*! \brief 设置布告板旋转角度
	 *	
	 *  该旋转角度只影响后面新加入的布告板，每个布告板拥有一个独立的旋转角度。
	 *
	 *  \param[in] angle 沿指定轴旋转的角度（取值范围[正无穷,负无穷]）
	 *  \param[in] x 表示旋转轴向量的 x 分量（取值范围[正无穷,负无穷]，下同）
	 *  \param[in] y 表示旋转轴向量的 y 分量
	 *  \param[in] z 表示旋转轴向量的 z 分量
	 *	 
	 *  \see 
	 */
	virtual void rotate( float angle, float x, float y, float z ) = 0;

	/*! \brief 翻转布告板纹理
	 *	 
	 *  \param s[in] 水平翻转纹理
	 *
	 *  \param t[in] 垂直翻转纹理
	 *	 
	 *  \see 
	 */
	virtual void reversal( bool s, bool t ) = 0;

	/*! \brief 禁用（或使用）布告板纹理
	 *	 
	 *  \param disable[in] 禁用布告板纹理标志，TRUE = 禁用，FALSE = 使用
	 *	 
	 *  \see 
	 */
	virtual void disableTexture( bool disable ) = 0;

	/*! \brief 增加一个点布告板
	 *	 
	 *  \param x 布告板位置的 x 坐标
	 *
	 *  \param y 布告板位置的 y 坐标
	 *
	 *  \param z 布告板位置的 z 坐标
	 *	 
	 *  \param frame = 0 动画纹理的帧数，缺省为 0，也就第一帧
	 *
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void addPoint ( float x, float y, float z, int frame = 0 ) = 0;

	/*! \brief 增加一个轴布告板
	 *
	 *  增加一个轴布告板，该布告板始终垂直于地面。
	 *
	 *  \param float x 布告板位置的 x 坐标
	 *
	 *  \param float y 布告板位置的 y 坐标
	 *
	 *  \param float z 布告板位置的 z 坐标
	 *	 
	 *  \param int frame = 0 动画纹理的帧数，缺省为 0，也就第一帧
	 *
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void addAxis ( float x, float y, float z, int frame = 0 ) = 0;

	/*! \brief 渲染布告板
	 *
	 *  渲染所有加入布告池的布告板。
	 *
	 *  \see 
	 */
	virtual void render ( void ) = 0;

};