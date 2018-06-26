

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ����ͼ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *image, *dynamic_image;	
	LightInput *input;
	LightText   *text;
	unsigned long time, lasttime;
	float rotate;
	char fps[100];

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 400;                // ���ڿ��
	engineDesc.displayMode.window.height  = 300;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����һ��ͼ��
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
	image->load( "..\\resource\\image\\b.bmp" );

	// ������̬ͼ��
	dynamic_image = engine->createImage( imageDesc );	
	dynamic_image->create( 256, 256, 1 );

	// ��ʼ��ʱ�����
	rotate = 0.0;
	lasttime = engine->getTickCount();

	do
	{
		// ��Ⱦ������
		dynamic_image->renderToTexture( TRUE );
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// ��ʾ��תͼ��
		LightImageRenderDesc renderDesc;
		renderDesc.flags = LIGHT_IMAGE_ROTATE;
		renderDesc.rotate = rotate;		
		image->renderDesc( 65, 60, renderDesc );

		// ��ʾ֡�٣�FPS��
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 50, 180 );
		text->drawText( fps );

		// ��Ⱦ������
		dynamic_image->renderToTexture( FALSE );
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		// ������ʾͼ��
		dynamic_image->render( 72, 16 );		
		// ��ʾ��ʾ��Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 80, 235 );
		text->drawText( "�밴 Enter ����ͼ�񱣴�Ϊ shot.bmp �ļ�" );

		if( input->getKey() == KEY_RETURN )
		{
			// ����ͼ���ļ�
			remove( "shot.bmp" );
			dynamic_image->save( "shot.bmp", LIGHT_BMP, 0 );
		}

		// ����ͼ����ת�Ƕ�
		time = engine->getTickCount();
		rotate += ( time - lasttime ) * 0.025f;
		lasttime = time;
		if( rotate > 360 )
			rotate -= 360;

        // ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseImage( dynamic_image );  // �ͷŶ�̬ͼ��
	engine->releaseImage( image );          // �ͷ�һ��ͼ��
	engine->releaseInput( input );          // �ͷ�����ӿ�
	engine->releaseText( text );            // �ͷ����ֶ���

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}