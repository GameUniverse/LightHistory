

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\lightnet.h"
#pragma comment( lib, "..\\..\\..\\lib\\lightnet.lib" )


// 网络消息处理函数
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

HWND          hwnd ;
MSG           msg ;
LightNetwork  *network;
LightSocket   *server;
LightSocket   *connect1;
char name[] = "服务器端";

char message1[50] = "继续侦察，注意隐蔽，听候命令！";

// 服务器端演示程序
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

	// 创建一个监听套接字
	LightSocketDesc socketDesc;
	memset( &socketDesc, 0, sizeof(socketDesc) );
	server = network->createSocket( socketDesc );

	// 开始监听客户端连接请求
	server->socket( LIGHT_SOCK_STREAM, 0 );
	server->bind( "0.0.0.0", 6000 );
	server->listen();

	// 消息循环
	while( GetMessage (&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		network->receiveMessage( msg.hwnd, msg.message, msg.wParam, msg.lParam );		
	};

	// 释放网络套接字
	network->releaseSocket( connect1 );
	network->releaseSocket( server );	

	// 释放光线网络引擎实例
	LightNetworkRelease( network );	

    return msg.wParam ;	
}

// 网络消息处理函数
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	// 只处理网络套接字消息
	if( message == LIGHT_WM_SOCKET )
	{
		switch( lParam )
		{
		// “接受连接”网络事件
		case LIGHT_FD_ACCEPT:			
			connect1 = server->accept();
			//MessageBox( 0, "客户端请求连接，同意建立连接。", "服务器端", MB_OK );
            break;
		// “读取数据”网络事件
		case LIGHT_FD_READ:
			char buffer[256];
			char str[256];			
			connect1->recv( buffer, 256 );
			sprintf( str, "客户端发来消息：“%s”", buffer );
			MessageBox( 0, str, "服务器端", MB_OK );
			connect1->send( message1, 50 );
			break;
		// “数据写入”网络事件，此事件一般不用
		case LIGHT_FD_WRITE:
			break;
        // “连接关闭”网络事件
		case LIGHT_FD_CLOSE:
			// 释放客户端连接套接字
			network->releaseSocket( connect1 );
			//MessageBox( 0, "客户端关闭了连接!", "服务器端", MB_OK );
		}
	}

	return 0;
}
