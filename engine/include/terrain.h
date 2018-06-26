/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   terrain.h
 *  内容:   地形函数
 *
 ****************************************************************************/


/*! \file terrain.h
 * 地形函数.
 * 此文件是地形函数头文件.
 */


/*! \class LightTerrain
 *  \brief 地形类 
 *
 *  本类负责地形文件的读取，渲染，支持高度图格式的地形。
 *  每个 LightTerrain 实例都必须通过 LightEngine 类的 NewTerrain 方法分配。
 */

class LightTerrain
{

public:

	/*! \brief 将地形文件读入内存
	 *
	 *  支持高度图格式的地图。
	 *
	 *  \param filename 地形文件名
	 *
	 *  \param format 地形文件名格式
	 *
	 *  \param width 地形文件宽度
	 *
	 *  \param height 地形文件高度
	 *
	 *  \param bits 地形文件通道位数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int load( const char *filename, int format, int width, int height, int bits ) = 0;

	/*! \brief 设置地形大小
	 *	 
	 *  \param width 地形宽度，指 x 轴方向的大小，必须为 2 的 n 次幂 + 1
	 *
	 *  \param height 地形高度，指 y 轴方向的大小，必须为 2 的 n 次幂 + 1
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int SetSize ( int width, int height ) = 0;

	/*! \brief 查询地形大小
	 *	 
	 *  \param LPSIZE lpSize 返回地形大小的数据结构指针，其中 LPSIZE 的成员 cx 和 cy 分别为地形的宽度和高度
	 *	
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int GetSize ( LPSIZE lpSize ) = 0;

	/*! \fn int SetTexture ( int name, LightTexture * texture ) = 0
	 *  \brief 设置地形纹理
	 *
	 *  设置地形纹理。
	 *
	 *  \param int name 要设置的地形纹理层
	 *
	 *  \param LightTexture * texture 要设置的地形纹理
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int SetTexture ( int name, LightTexture * texture ) = 0;

	/*! \brief 设置地形瓷砖大小
	 *	 
	 *  \param width 地形瓷砖宽度，指 x 轴方向的大小，必须为 2 的 n 次幂，<b>取值范围:</b> [32,地形宽度-1]
	 *
	 *  \param height 地形瓷砖高度，指 y 轴方向的大小，必须为 2 的 n 次幂，<b>取值范围:</b> [32,地形高度-1]
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int setTile( int width, int height ) = 0;

	/*! \brief 查询地形瓷砖大小
	 *	 
	 *  \param LPSIZE lpSize 返回地形瓷砖大小的数据结构指针，其中 LPSIZE 的成员 cx 和 cy 分别为地形瓷砖的宽度和高度
	 *	
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int getTile( LPSIZE lpSize ) = 0;

	/*! \fn void BuildLODData( void ) = 0
	 *  \brief 生成 LOD 所需要的数据
	 *
	 *  生成 LOD 所需要的数据，当地形
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void BuildLODData( void ) = 0;

	/*! \fn virtual void SetLODFactor( float distance, float fluctuant ) = 0
	 *  \brief 设置地形显示 LOD 因子
	 *
	 *  设置地形显示 LOD 因子，此函数用来调节地形显示品质和速度。
	 *
	 *  \param float distance LOD 的距离因子，取值范围为 2.5 ~ 5，此值越大，地形显示品质越高，但显示速度会下降
	 *
	 *  \param float fluctuant LOD 的起伏程度因子，取值范围为 25 ~ 50，此值越大，地形显示品质越高，但显示速度会下降
	 *
	 *  \return 本函数没有返回值。
	 *
	 *  \see 
	 */
	virtual void SetLODFactor( float distance, float fluctuant ) = 0;

    #define LIGHT_RENDER_LOD  5  // 使用 LOD

	/*! \fn int RenderMode ( int mode ) = 0
	 *  \brief 设置地形渲染模式
	 *
	 *  设置地形渲染模式。
	 *
	 *  \param int mode 地形渲染模式
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int RenderMode ( int mode ) = 0;

	/*! \brief 渲染地形
	 *		 
	 */
	virtual void render() = 0;

	/*! \fn float GetHeight ( float x, float y ) = 0
	 *  \brief 查询地形指定位置的高度值
	 *
	 *  查询地形指定位置的高度值。
	 *
	 *  \param float x 位置的 x 坐标
	 *
	 *  \param float y 位置的 y 坐标，实际上是 z 坐标
	 *
	 *  \return 返回地形指定位置的高度值。
	 */
	virtual float GetHeight ( float x, float y ) = 0;

	/*! \fn int SetHeight ( float x, float y, float height ) = 0
	 *  \brief 设置地形指定位置的高度值
	 *
	 *  设置地形指定位置的高度值。
	 *
	 *  \param float x 位置的 x 坐标
	 *
	 *  \param float y 位置的 y 坐标，实际上是 z 坐标
	 *
	 *  \param float height 指定位置 ( x, y ) 的高度值
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int SetHeight ( float x, float y, float height ) = 0;

	/*! \fn int GetTrianglesCount( void ) = 0
	 *  \brief 查询显示的三角形数
	 *
	 *  查询显示的三角形数。
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \return 返回地形类显示的三角形数。
	 */
	virtual int GetTrianglesCount( void ) = 0;

	/*! \brief 创建一个高度场对象
	 *	 
	 *  \return 创建的高度场对象
	 *
	 *  \see 
	 */	
	virtual LightHeightField * createHeightField( vec3_t position, vec3_t box ) = 0;

	/*! \fn int Load ( const char *filename ) = 0
	 *  \brief 将地形保存到文件中
	 *
	 *  支持高度图格式的地图。
	 *
	 *  \param const char *filename 地形文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int Save ( const char *filename ) = 0;

	/*! \fn int Unload ( void ) = 0
	 *  \brief 将地形文件从内存中清除
	 *
	 *  将地形文件从内存中清除。
	 *
	 *  \param 本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int Unload ( void ) = 0;

};