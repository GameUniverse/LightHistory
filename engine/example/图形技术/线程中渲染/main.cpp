

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


LightEngine  *engine;
LightImage   *desktop;
LightImage   *image;	
LightText    *text;
bool         work; // �̹߳�����־

// ��Ⱦ�̺߳���
DWORD WINAPI ThreadProc( LPVOID lpParameter )
{
	// ����ȾĿ��
	engine->attachRender();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ����
		desktop->render( 0, 0 );

		// ������ʾͼ��
		image->render( 25, 25 );		

		// ��ʾ��ʾ��Ϣ
		text->color( 255, 0, 0 );
		text->setTextPos( 295, 350 );
		text->drawText( "�����߳�����Ⱦ......" );

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 255, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ��Ⱦѭ��
	while( work );

	return 0;
}

// �߳�����Ⱦ��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );
	
	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����ͼ�����
	LightImageDesc imageDesc;
	desktop = engine->createImage( imageDesc );
	desktop->load("..\\resource\\image\\sweet_flower.bmp");
	image = engine->createImage( imageDesc );
	image->load("..\\resource\\image\\a.bmp");

	// ������ȾĿ��
	engine->detachRender();

	// ������Ⱦ�߳�
	HANDLE thread;
	DWORD  threadId;
	work = TRUE;
	thread = CreateThread( NULL, 0, ThreadProc, NULL, 0, &threadId );
	//WaitForSingleObject( thread, 5000 );

	do
	{		
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// ������Ⱦ�߳�
	work = FALSE;
	_sleep( 100 );
	CloseHandle( thread );

	// �ͷŷ���Ķ���	
	engine->releaseText( text );      // �ͷ����ֶ���
	engine->releaseImage( desktop );  // �ͷ�ͼ�����
	engine->releaseImage( image );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}
