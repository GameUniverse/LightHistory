

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ����ͼ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *image;
	LightText *text;
	unsigned long lasttime;
	float rotate;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 400;                // ���ڿ��
	engineDesc.displayMode.window.height  = 300;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����ͼ�����
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
		
	// ��ͼ���ļ������ڴ�
	image->speed( 100 );	
	image->load("..\\resource\\image\\flame\\flame1.tga");
	image->insertFrame( 0, 1 );	
	image->load("..\\resource\\image\\flame\\flame2.tga");
	image->insertFrame( 1, 1 );	
	image->load("..\\resource\\image\\flame\\flame3.tga");
	image->insertFrame( 2, 1 );
	image->load("..\\resource\\image\\flame\\flame4.tga");
	image->insertFrame( 3, 1 );
	image->load("..\\resource\\image\\flame\\flame5.tga");
	image->insertFrame( 4, 1 );
	image->load("..\\resource\\image\\flame\\flame6.tga");
	image->insertFrame( 5, 1 );
	image->load("..\\resource\\image\\flame\\flame7.tga");
	image->insertFrame( 6, 1 );
	image->load("..\\resource\\image\\flame\\flame8.tga");

	// ��ʼ��ʱ�����
	rotate = 0.0;
	lasttime = engine->getTickCount();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ����ͼ��		
		image->render( 135, 0 );

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 245 );
		text->drawText( fps );

		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���	
	engine->releaseImage( image );  // �ͷ�ͼ���ļ�	
	engine->releaseText( text );    // �ͷ�����ʵ��

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}