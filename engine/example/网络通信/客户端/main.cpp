

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\lightnet.h"
#pragma comment( lib, "..\\..\\..\\lib\\lightnet.lib" )


// 网络消息处理函数
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

HWND          hwnd ;
MSG           msg ;
LightNetwork  *network;
LightSocket   *client;
char name[]       = "客户端";
char message1[50] = "报告总部，前面发现敌人！";

// 客户端演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 注册一个窗口类
	WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = DefWindowProc;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = NULL;
    wndclass.hCursor       = NULL;
    wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = name;
    if( !RegisterClass(&wndclass) )
		return -1;

	// 创建一个窗口
    hwnd = CreateWindow( name,                       // window class name
                         name,                       // window caption
                         WS_OVERLAPPEDWINDOW,        // window style
                         CW_USEDEFAULT,              // initial x position
                         CW_USEDEFAULT,              // initial y position
                         CW_USEDEFAULT,              // initial x size
                         CW_USEDEFAULT,              // initial y size
                         NULL,                       // parent window handle
                         NULL,                       // window menu handle
                         hInstance,                  // program instance handle
                         NULL) ;                     // creation parameters
	if( hwnd == NULL )
		return -2;

	// 显示窗口
    ShowWindow (hwnd, SW_SHOW) ;
    UpdateWindow (hwnd) ;

	 //创建光线网络引擎实例
	LightNetworkDesc networkDesc;
	memset( &networkDesc, 0, sizeof(networkDesc) );
	networkDesc.hwnd = hwnd;
	network = LightNetworkCreate( networkDesc );	

	// 注册消息处理函数
	network->registerMessageProc( SocketProc );

	// 创建一个套接字
	LightSocketDesc socketDesc;
	memset( &socketDesc, 0, sizeof(socketDesc) );
	client = network->createSocket( socketDesc );
	
	// 连接到客户端
	client->socket( LIGHT_SOCK_STREAM, 0 );
	client->connect( "127.0.0.1", 6000 );

	_sleep( 2000 );
	client->send( message1, 50 );

	// 消息循环
	while( GetMessage (&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		network->receiveMessage( msg.hwnd, msg.message, msg.wParam, msg.lParam );		
	};
	
	// 释放网络套接字
	network->releaseSocket( client );

	// 释放光线网络引擎实例
	LightNetworkRelease( network );

	return 0;
}

// 网络消息处理函数
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( message == LIGHT_WM_SOCKET )
	{
		switch( lParam )
		{
		// “连接成功”网络事件
		case LIGHT_FD_CONNECT:
			//MessageBox( 0, "服务噐端同意连接，连接成功。", "客户端", MB_OK );
			break;
		// “读取数据”网络事件
		case LIGHT_FD_READ:
			char buffer[256];
			char str[256];			
			client->recv( buffer, 256 );
			sprintf( str, "服务器端发来消息：“%s”", buffer );
			MessageBox( 0, str, "客户端", MB_OK );

			// 断开当前连接
			//client->shutdown( 2 );
			//client->closeSocket();
			/*network->releaseSocket( client );

			// 重新请求连接
			_sleep( 200 );
			LightSocketDesc socketDesc;
			memset( &socketDesc, 0, sizeof(socketDesc) );
			client = network->createSocket( socketDesc );
			client->socket( LIGHT_SOCK_STREAM, 0 );
			client->connect( "127.0.0.1", 6000 );
			_sleep( 200 );
			client->send( message1, 50 );*/
			break;
		// “数据写入”网络事件，此事件一般不用
		case LIGHT_FD_WRITE:
			break;
		// “连接关闭”网络事件
		case LIGHT_FD_CLOSE:
			// 释放服务器端连接套接字
			//network->releaseSocket( client );
			//MessageBox( 0, "服务器端关闭了连接!", "客户端", MB_OK );
			break;
		}
	}

	return 0;
}
