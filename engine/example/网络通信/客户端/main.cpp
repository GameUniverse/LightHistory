

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\lightnet.h"
#pragma comment( lib, "..\\..\\..\\lib\\lightnet.lib" )


// ������Ϣ������
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

HWND          hwnd ;
MSG           msg ;
LightNetwork  *network;
LightSocket   *client;
char name[]       = "�ͻ���";
char message1[50] = "�����ܲ���ǰ�淢�ֵ��ˣ�";

// �ͻ�����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ע��һ��������
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

	// ����һ������
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

	// ��ʾ����
    ShowWindow (hwnd, SW_SHOW) ;
    UpdateWindow (hwnd) ;

	 //����������������ʵ��
	LightNetworkDesc networkDesc;
	memset( &networkDesc, 0, sizeof(networkDesc) );
	networkDesc.hwnd = hwnd;
	network = LightNetworkCreate( networkDesc );	

	// ע����Ϣ������
	network->registerMessageProc( SocketProc );

	// ����һ���׽���
	LightSocketDesc socketDesc;
	memset( &socketDesc, 0, sizeof(socketDesc) );
	client = network->createSocket( socketDesc );
	
	// ���ӵ��ͻ���
	client->socket( LIGHT_SOCK_STREAM, 0 );
	client->connect( "127.0.0.1", 6000 );

	_sleep( 2000 );
	client->send( message1, 50 );

	// ��Ϣѭ��
	while( GetMessage (&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		network->receiveMessage( msg.hwnd, msg.message, msg.wParam, msg.lParam );		
	};
	
	// �ͷ������׽���
	network->releaseSocket( client );

	// �ͷŹ�����������ʵ��
	LightNetworkRelease( network );

	return 0;
}

// ������Ϣ������
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( message == LIGHT_WM_SOCKET )
	{
		switch( lParam )
		{
		// �����ӳɹ��������¼�
		case LIGHT_FD_CONNECT:
			//MessageBox( 0, "����r��ͬ�����ӣ����ӳɹ���", "�ͻ���", MB_OK );
			break;
		// ����ȡ���ݡ������¼�
		case LIGHT_FD_READ:
			char buffer[256];
			char str[256];			
			client->recv( buffer, 256 );
			sprintf( str, "�������˷�����Ϣ����%s��", buffer );
			MessageBox( 0, str, "�ͻ���", MB_OK );

			// �Ͽ���ǰ����
			//client->shutdown( 2 );
			//client->closeSocket();
			/*network->releaseSocket( client );

			// ������������
			_sleep( 200 );
			LightSocketDesc socketDesc;
			memset( &socketDesc, 0, sizeof(socketDesc) );
			client = network->createSocket( socketDesc );
			client->socket( LIGHT_SOCK_STREAM, 0 );
			client->connect( "127.0.0.1", 6000 );
			_sleep( 200 );
			client->send( message1, 50 );*/
			break;
		// ������д�롱�����¼������¼�һ�㲻��
		case LIGHT_FD_WRITE:
			break;
		// �����ӹرա������¼�
		case LIGHT_FD_CLOSE:
			// �ͷŷ������������׽���
			//network->releaseSocket( client );
			//MessageBox( 0, "�������˹ر�������!", "�ͻ���", MB_OK );
			break;
		}
	}

	return 0;
}
