/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2007 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  文件:   lensflare.h
 *  内容:   透镜光晕函数
 *
 ****************************************************************************/


/*! \file lensflare.h
 *  透镜光晕函数.
 * 此文件是透镜光晕函数头文件.
 */

/*! \class LightLensFlare
 * \brief 透镜光晕类
 *
 *  本类负责透镜光晕的创建和显示。
 *  每个 LightLensFlare 实例都必须通过 LightEngine 类的 NewLensFlare 方法分配。 
 */

class LightLensFlare
{

public:

	/*! \fn void Release() = 0
	 *  \brief 清除透镜光晕
	 *
	 *  清除透镜光晕。
	 *
	 *  \param 无
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void Release() = 0;

	/*! \fn void SetPosition( float x, float y, float z ) = 0
	 *  \brief 设置透镜光晕位置
	 *
	 *  设置透镜光晕位置
	 *
	 *  \param float x 透镜光晕位置的 x 坐标
	 *
	 *  \param float y 透镜光晕位置的 y 坐标
	 *
	 *  \param float z 透镜光晕位置的 z 坐标
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void SetPosition( float x, float y, float z ) = 0;

	/*! \fn void AddSubNode( float size, float pos, LightTexture *texture ) = 0
	 *  \brief 增加一个透镜光晕子节点
	 *
	 *  增加一个透镜光晕子节点
	 *
	 *  \param float size 节点大小
	 *
	 *  \param float pos 节点位置
	 *
	 *  \param LightTexture *texture 节点纹理
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void AddSubNode( float size, float pos, LightTexture *texture ) = 0;

	/*! \fn void AddMainNode( float size, LightTexture *texture ) = 0
	 *  \brief 增加一个透镜光晕主节点
	 *
	 *  增加一个透镜光晕主节点
	 *
	 *  \param float size 节点大小
	 *
	 *  \param LightTexture *texture 节点纹理
	 *
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void AddMainNode( float size, LightTexture *texture ) = 0;

	/*! \fn void Draw() = 0
	 *  \brief 显示透镜光晕
	 *
	 *  显示透镜光晕
	 *
	 *  \param 无
	 *	 
	 *  \return 无
	 *
	 *  \see 
	 */
	virtual void Draw() = 0;
	
};
