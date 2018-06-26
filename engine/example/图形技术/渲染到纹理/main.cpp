

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ��Ⱦ��������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;	
	LightImage *image, *dynamic_image;
	LightText   *text;
	char fps[100];
	int x, y;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ��ͼ���ļ������ڴ�
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
	image->load( "..\\resource\\image\\a.bmp" );

	// ������̬����
	dynamic_image = engine->createImage( imageDesc );
	dynamic_image->create( 256, 256, 1 );

	do
	{
		// ��Ⱦ������
		dynamic_image->renderToTexture( TRUE );
		
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		// ������ʾͼ��
		image->render( 0, 0 );		
		// ��ʾ֡�٣�FPS��
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 150 );
		text->drawText( fps );
		
		// ��Ⱦ������
		dynamic_image->renderToTexture( FALSE );
     
		
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// ������ʾͼ��
		for( y=40; y<400; y+=200 )
			for( x=50; x<600; x+=200 )
				dynamic_image->render( x, y );

        // ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseImage( image );          // �ͷ�ͼ�����
	engine->releaseImage( dynamic_image );
	engine->releaseText( text );            // �ͷ����ֶ���

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}