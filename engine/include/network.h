/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   network.h
 *  内容:   网络引擎函数
 *
 ****************************************************************************/


/** \file network.h
 * 网络引擎函数
 * 此文件是网络引擎函数头文件.
 */


/** 描述网络引擎特性 */
typedef struct
{
	/** 因为网络引擎通过窗口传递消息，所以必须要将网络引擎绑定到一个窗口 */
	HWND hwnd;

} LightNetworkDesc;


/*! \class LightNetwork
 * \brief 网络引擎类
 *
 *  本类负责大部分网络系统功能的调用和其它所有网络类的实例分配，是网络引擎最重要的一个类。
 *  此类的实例指针只能通过调用网络引擎创建函数 LightNetworkCreate 得到。举个例子：
 *  \n
 *  \n 
 *  \n  LightNetwork * network;
 *  \n  LightNetworkDesc desc;
 *  \n  
 *  \n  // 创建光线网络引擎实例	
 *  \n  memset( &desc, 0, sizeof(desc) );
 *  \n  desc.hwnd = hwnd;
 *  \n  network = LightNetworkCreate( desc );
 *  \n  
 *  \n  // 做一些事情...
 *  \n  
 *  \n  // 释放光线网络引擎实例
 *  \n  LightNetworkRelease( network );
 */

class LightNetwork
{

public:

	/*! \brief 通知网络引擎收到一个窗口消息
	 *	 
	 *  \return 如果消息已处理返回 TRUE, 否则返回 FALSE 值
	 *
	 *  \see 
	 */
	virtual bool receiveMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) = 0;

	/*! \brief 注册窗口消息监听函数
	 *
	 *  注册窗口消息监听函数，可以注册多个消息监听函数，这些函数都能收到窗口发来的所有消息。
	 *
	 *  \param lpfnWndProc 窗口消息监听函数
	 *	 
	 *  \return 如果成功返回 TRUE, 否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool registerMessageProc( WNDPROC lpfnWndProc ) = 0;

	/*! \brief 移除窗口消息监听函数
	 *
	 *  移除窗口消息监听函数，只能移除前面已注册的窗口消息监听函数。
	 *
	 *  \param lpfnWndProc 窗口消息监听函数
	 *	 
	 *  \return 如果成功返回 TRUE, 否则返回 FALSE
	 *
	 *  \see 
	 */
	virtual bool removeMessageProc( WNDPROC lpfnWndProc ) = 0;

	/*! \brief 创建一个网络套接字
	 *
	 *  \param socketDesc 网络套接字描述符指针，用于说明要创建套接字的特征。
	 *	 
	 *  \return 返回已创建的套接字指针
	 *
	 *  \see 
	 */
	virtual LightSocket * createSocket( const LightSocketDesc & socketDesc ) = 0;

	/*! \brief 释放一个网络套接字	 
	 *
	 *  \param socket 要释放网络套接字的指针
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual void releaseSocket( LightSocket * socket ) = 0;

};