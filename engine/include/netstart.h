/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   netstart.h
 *  内容:   网络引擎启动函数
 *
 ****************************************************************************/


/** \file netstart.h
 * 网络引擎启动函数
 * 此文件是网络引擎启动函数头文件.
 */


/*! \brief 创建一个光线网络引擎实例
 *
 *  创建一个光线网络引擎实例，并返回 LightNetwork 指针。
 *
 *  \param 本函数没有参数。
 *
 *  \remarks 这是在使用网络引擎前必须要调用的第一个函数，网络引擎的大部分功能都需要通过调用 LightNetwork 来完成。
 *
 *  \return 如果函数调用成功，返回一个 LightNetwork 指针，否则返回 NULL 。
 */
LightNetwork * LightNetworkCreate( LightNetworkDesc & desc );

/*! \brief 释放光线网络引擎实例
 *
 *  \param 要释放的光线网络引擎实例指针，目前在同一个程序中只能创建一个实例。
 *
 *  \remarks 这是在引擎使用结束后，必须要调用的一个函数。
 *
 *  \return 如果函数调用成功，返回一个 LightNetwork 指针，否则返回 NULL 。
 */
void LightNetworkRelease( LightNetwork * network );

/*! \brief 查询光线网络引擎全局指针
 *
 *  查询光线网络引擎全局指针，该函数必须在 LightNetworkCreate 函数之后调用，在整个程序运行期间，只存在引擎的一个维一实例。
 *
 *  \param 本函数没有参数。
 *
 *  \remarks 引擎的大部分功能都需要通过调用 LightNetwork 来完成，当第一次创建引擎实例后，以后随时可以通过调用该函数来获取引擎的全局指针。
 *
 *  \return 如果函数调用成功，返回一个 LightNetwork 指针，否则返回 NULL 。
 */
LightNetwork * LightNetworkGet( void );