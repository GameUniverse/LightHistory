/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   datastart.h
 *  内容:   数据库引擎启动函数
 *
 ****************************************************************************/


/** \file datastart.h
 * 数据库引擎启动函数
 * 此文件是数据库引擎启动函数头文件.
 */


/*! \brief 创建一个光线数据库引擎实例
 *
 *  创建一个光线数据库引擎实例，并返回 LightDatabase 指针。
 *
 *  \param 本函数没有参数。
 *
 *  \remarks 这是在使用数据库引擎前必须要调用的第一个函数，数据库引擎的大部分功能都需要通过调用 LightDatabase 来完成。
 *
 *  \return 如果函数调用成功，返回一个 LightDatabase 指针，否则返回 NULL 。
 */
LightDatabase * LightDatabaseCreate( LightDatabaseDesc & databaseDesc );

/*! \brief 释放光线数据库引擎实例
 *
 *  \param 要释放的光线数据库引擎实例指针，目前在同一个程序中只能创建一个实例。
 *
 *  \remarks 这是在引擎使用结束后，必须要调用的一个函数。
 *
 *  \return 如果函数调用成功，返回一个 LightDatabase 指针，否则返回 NULL 。
 */
void LightDatabaseRelease( LightDatabase * database );
