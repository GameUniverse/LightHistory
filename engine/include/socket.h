/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   socket.h
 *  内容:   网络函数
 *
 ****************************************************************************/


/*! \file socket.h
 * 网络函数.
 * 此文件是网络函数头文件.
 */


/** 网络事件定义 */
#define LIGHT_FD_READ_BIT      0
#define LIGHT_FD_READ          (1 << LIGHT_FD_READ_BIT)

#define LIGHT_FD_WRITE_BIT     1
#define LIGHT_FD_WRITE         (1 << LIGHT_FD_WRITE_BIT)

#define LIGHT_FD_OOB_BIT       2
#define LIGHT_FD_OOB           (1 << LIGHT_FD_OOB_BIT)

#define LIGHT_FD_ACCEPT_BIT    3
#define LIGHT_FD_ACCEPT        (1 << LIGHT_FD_ACCEPT_BIT)

#define LIGHT_FD_CONNECT_BIT   4
#define LIGHT_FD_CONNECT       (1 << LIGHT_FD_CONNECT_BIT)

#define LIGHT_FD_CLOSE_BIT     5
#define LIGHT_FD_CLOSE         (1 << LIGHT_FD_CLOSE_BIT)

#define LIGHT_FD_QOS_BIT       6
#define LIGHT_FD_QOS           (1 << LIGHT_FD_QOS_BIT)

#define LIGHT_FD_GROUP_QOS_BIT 7
#define LIGHT_FD_GROUP_QOS     (1 << LIGHT_FD_GROUP_QOS_BIT)

#define LIGHT_FD_ROUTING_INTERFACE_CHANGE_BIT 8
#define LIGHT_FD_ROUTING_INTERFACE_CHANGE     (1 << LIGHT_FD_ROUTING_INTERFACE_CHANGE_BIT)

#define LIGHT_FD_ADDRESS_LIST_CHANGE_BIT 9
#define LIGHT_FD_ADDRESS_LIST_CHANGE     (1 << LIGHT_FD_ADDRESS_LIST_CHANGE_BIT)

#define LIGHT_FD_MAX_EVENTS    10
#define LIGHT_FD_ALL_EVENTS    ((1 << LIGHT_FD_MAX_EVENTS) - 1)

// 自定义 SOCKET 消息
#define LIGHT_WM_SOCKET  WM_USER + 1000

// 套接字地址结构
struct socketaddr
{
	unsigned short port;    // 端口号
	unsigned long  address; // IP 地址
};

/** 描述网络套接字特性 */
typedef struct
{
	/** 因为网络引擎通过窗口传递消息，所以必须要将网络引擎绑定到一个窗口 */
	HWND hwnd;

} LightSocketDesc;


/*! \class LightSocket
 *  \brief 网络套接字类
 *
 *  本类负责最基本的网络通讯，支持客户端和服务器端两种方式。
 *  每个 LightSocket 实例都必须通过 LightEngine 类的 NewSocket 方法分配。
 */

class LightSocket
{

public:

	// SOCKET 类型
    #define LIGHT_SOCK_STREAM   1  // 流
    #define LIGHT_SOCK_DGRAM    2  // 数据报

	// 通讯协议
    #define LIGHT_IPPROTO_TCP   6  // TCP/IP 协议
    #define LIGHT_IPPROTO_UDP   17 // UDP 协议

	/*! \fn int Socket( int type, int protocol ) = 0
	 *  \brief 建立一个网络套接字（服务器端或客户端）
	 *
	 *  客户端需要向服务器端发送连接请求，一旦服务器端收到并响应了客户端的连接请求，
	 *  则建立了一个连接。
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int socket( int type, int protocol ) = 0;

	/*! \fn int Bind( const char* ip, unsigned short port ) = 0
	 *  \brief 建立一个网络服务器端（服务器端）
	 *
	 *  客户端需要向服务器端发送连接请求，一旦服务器端收到并响应了客户端的连接请求，
	 *  则建立了一个连接。
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int bind( const char* ip, unsigned short port ) = 0;

	/*! \fn int Listen( void ) = 0
	 *  \brief 监听客户端的连接请求（服务器端）
	 *
	 *  服务器端调用完 Listen() 函数后，如果此时客户端调用 Connect() 函数提出连接
	 *  申请的话，服务器端必须再调用 Accept() 函数，这样服务器端和客户端才算正式
	 *  完成通信程序的连接动作。
	 *
	 *  \param 本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int listen( void ) = 0;

	/*! \fn LightSocket* Accept( void ) = 0
	 *  \brief 接受客户端的连接请求（服务器端）
	 *
	 *  为了使服务器端接受客户端的连接请求，就要使用 Accept() 函数，该函数新建一个
	 *  SOCKET 与客户端相连，原先监听的 SOCKET 继续进入监听状态，等待其它的连接请求。
	 *
	 *  \param  无
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual LightSocket* accept( void ) = 0;

	/*! \fn int Connect( const char* ip, unsigned short port ) = 0
	 *  \brief 向服务器端发送连接请求（客户端）
	 *
	 *  客户端需要向服务器端发送连接请求，一旦服务器端收到并响应了客户端的连接请求，
	 *  则建立了一个连接。
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int connect( const char* ip, unsigned short port ) = 0;

	/*! \fn int Send( const char* buf, int len ) = 0
	 *  \brief 发送数据（服务器端或客户端）
	 *
	 *  客户端需要向服务器端发送连接请求，一旦服务器端收到并响应了客户端的连接请求，
	 *  则建立了一个连接。
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int send( const char* buf, int len ) = 0;

	/*! \fn int Recv( char* buf, int len ) = 0
	 *  \brief 接收数据（服务器端或客户端）
	 *
	 *  客户端需要向服务器端发送连接请求，一旦服务器端收到并响应了客户端的连接请求，
	 *  则建立了一个连接。
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int recv( char* buf, int len ) = 0;

	/*! \fn unsigned long GetSocket( void ) = 0
	 *  \brief 查询网络套接字的 SOCKET 句柄（服务器端或客户端）
	 *
	 *  当程序中存在多个连接的时候，SOCKET 句柄可以区分不同连接的消息。	 
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回该网络套接字的 SOCKET 句柄；如果函数调用失败，返回零。
	 */
	virtual unsigned long getSocket( void ) = 0;

	/*! \fn int GetPeerName( struct socketaddr* address ) = 0
	 *  \brief 查询对方的 IP 地址和端口号（服务器端或客户端）
	 *
	 *  查询对方的 IP 地址和端口号，这里的对方指的是与本网络套接字相连的另一方。
	 *
	 *  \param struct socketaddr* address 接收对方 IP 地址和端口号的结构指针
	 *	 
	 *  \return 如果函数调用成功，返回 0；如果函数调用失败，返回 -1。
	 */
	virtual int getPeerName( struct socketaddr* address ) = 0;

	/*! \fn int GetSockName( struct socketaddr* address ) = 0
	 *  \brief 查询本地的 IP 地址和端口号（服务器端或客户端）
	 *
	 *  查询本地的 IP 地址和端口号，这里的本地指的是本套接字。
	 *
	 *  \param struct socketaddr* address 接收本地 IP 地址和端口号的结构指针
	 *	 
	 *  \return 如果函数调用成功，返回 0；如果函数调用失败，返回 -1。
	 */
	virtual int getSockName( struct socketaddr* address ) = 0;

	/*! \brief 关闭已经建立的网络套接字（服务器端或客户端）
	 *
	 *  当断开连接或不在需要此套接字时调用此函数。	 
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int closeSocket( void ) = 0;

    #define LIGHT_SD_RECEIVE   0x00
    #define LIGHT_SD_SEND      0x01
    #define LIGHT_SD_BOTH      0x02

	/*! \brief 关闭已经建立的网络套接字（服务器端或客户端）
	 *
	 *  当断开连接或不在需要此套接字时调用此函数。	 
	 *
	 *  \param  本函数没有参数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int shutdown( int how ) = 0;

};