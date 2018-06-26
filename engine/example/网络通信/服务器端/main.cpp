

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\lightnet.h"
#pragma comment( lib, "..\\..\\..\\lib\\lightnet.lib" )


// ������Ϣ������
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

HWND          hwnd ;
MSG           msg ;
LightNetwork  *network;
LightSocket   *server;
LightSocket   *connect1;
char name[] = "��������";

char message1[50] = "������죬ע�����Σ��������";

// ����������ʾ����
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

	// ����һ�������׽���
	LightSocketDesc socketDesc;
	memset( &socketDesc, 0, sizeof(socketDesc) );
	server = network->createSocket( socketDesc );

	// ��ʼ�����ͻ�����������
	server->socket( LIGHT_SOCK_STREAM, 0 );
	server->bind( "0.0.0.0", 6000 );
	server->listen();

	// ��Ϣѭ��
	while( GetMessage (&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		network->receiveMessage( msg.hwnd, msg.message, msg.wParam, msg.lParam );		
	};

	// �ͷ������׽���
	network->releaseSocket( connect1 );
	network->releaseSocket( server );	

	// �ͷŹ�����������ʵ��
	LightNetworkRelease( network );	

    return msg.wParam ;	
}

// ������Ϣ������
long FAR PASCAL SocketProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	// ֻ���������׽�����Ϣ
	if( message == LIGHT_WM_SOCKET )
	{
		switch( lParam )
		{
		// ���������ӡ������¼�
		case LIGHT_FD_ACCEPT:			
			connect1 = server->accept();
			//MessageBox( 0, "�ͻ����������ӣ�ͬ�⽨�����ӡ�", "��������", MB_OK );
            break;
		// ����ȡ���ݡ������¼�
		case LIGHT_FD_READ:
			char buffer[256];
			char str[256];			
			connect1->recv( buffer, 256 );
			sprintf( str, "�ͻ��˷�����Ϣ����%s��", buffer );
			MessageBox( 0, str, "��������", MB_OK );
			connect1->send( message1, 50 );
			break;
		// ������д�롱�����¼������¼�һ�㲻��
		case LIGHT_FD_WRITE:
			break;
        // �����ӹرա������¼�
		case LIGHT_FD_CLOSE:
			// �ͷſͻ��������׽���
			network->releaseSocket( connect1 );
			//MessageBox( 0, "�ͻ��˹ر�������!", "��������", MB_OK );
		}
	}

	return 0;
}
