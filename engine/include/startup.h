/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   startup.h
 *  内容:   引擎启动函数
 *
 ****************************************************************************/


/** \file startup.h
 * 引擎创建函数
 * 此文件是引擎创建函数头文件.
 */


/*! \fn LightEngine * LightEngineCreate( LightEngineDesc & engineDesc )
 *  \brief 创建光线引擎实例
 *
 *  创建光线引擎的一个实例，并返回一个 LightEngine 指针。目前在同一个应用程序中该函数只能调用一次（也就是说只能创建引擎的一个实例），
 *  不同程序同时使用光线引擎相互没有影响。
 *
 *  \param engineDesc 引擎描述符，用来指定引擎使用的特性。
 *
 *  \remarks 这是在使用引擎前必须要调用的第一个函数，引擎的大部分功能都需要通过调用 LightEngine 来完成。
 *
 *  \return 如果函数调用成功，返回一个 LightEngine 指针，否则返回 NULL 。
 */
LightEngine * LightEngineCreate( LightEngineDesc & engineDesc );

/*! \fn LightEngine * LightEngineCreate( LightEngineDesc * desc )
 *  \brief 释放光线引擎实例
 *
 *  释放光线引擎的实例。
 *
 *  \param 要释放的光线引擎实例指针，目前在同一个程序中只能创建一个实例。
 *
 *  \remarks 这是在引擎使用结束后，必须要调用的一个函数。
 *
 *  \return 如果函数调用成功，返回一个 LightEngine 指针，否则返回 NULL 。
 */
void LightEngineRelease( LightEngine * engine );

/*! \fn LightEngine * LightEngineSingle( void )
 *  \brief 查询光线引擎全局指针
 *
 *  查询光线引擎全局指针，该函数必须在 LightEngineCreate 函数之后调用，在整个程序运行期间，只存在引擎的一个维一实例。
 *
 *  \param 本函数没有参数。
 *
 *  \remarks 引擎的大部分功能都需要通过调用 LightEngine 来完成，当第一次创建引擎实例后，以后随时可以通过调用该函数来获取引擎的全局指针。
 *
 *  \return 如果函数调用成功，返回一个 LightEngine 指针，否则返回 NULL 。
 */
LightEngine * LightEngineGet( void );
