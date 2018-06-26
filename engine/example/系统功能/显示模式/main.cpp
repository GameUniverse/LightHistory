

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��ʾģʽ��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage  *image;
	LightInput  *input;
	LightText   *text;
	LightDisplaymodeDesc displaymodeDesc;
	unsigned long key;
	int display_mode = 0;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�

	/*engineDesc.displayMode.mode                  = LIGHT_FULLSCREEN_MODE;  // ȫ����ʾģʽ
	engineDesc.displayMode.fullscreen.width      = 800;                    // ��Ļˮƽ�ֱ���
	engineDesc.displayMode.fullscreen.height     = 600;                    // ��Ļ��ֱ�ֱ���
	engineDesc.displayMode.fullscreen.color      = 16;                     // ��Ļ��ɫ���
	engineDesc.displayMode.fullscreen.refurbish  = 0;                      // ��Ļˢ����*/

	engine = LightEngineCreate( engineDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �رմ�ֱͬ����Ĭ�Ͽ�����
	engine->disable( LIGHT_SWAP_INTERVAL );
		
	// ����ͼ�����
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
	image->load( "..\\resource\\image\\sweet_flower.bmp" );
	
	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾͼ��		
		image->render( 0, 0 );
		
		// ��ʾ��ʾ��Ϣ
		text->color( 255, 0, 0 );
		text->setTextPos( 270, 205 );
		text->drawText("�밴�ո���л���ʾģʽ......");
		
		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 255, 255, 0 );
		text->setTextPos( 30, 413 );
		text->drawText( fps );
        
		// ������ʾ
		engine->swapBuffers();

		// ��ѯ�û�����
		key = input->getKey();
		if( key == KEY_SPACE )
		{
			display_mode++;
			if( display_mode > 2 )
				display_mode = 0;
			if( display_mode == 0 )
			{
				// ������������ʵ��
				displaymodeDesc.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
				displaymodeDesc.window.x       = 200;                // �������Ͻ� x ����
				displaymodeDesc.window.y       = 150;                // �������Ͻ� y ����
				displaymodeDesc.window.width   = 640;                // ���ڿ��
				displaymodeDesc.window.height  = 480;                // ���ڸ߶�
				engine->changeDisplaySettings( displaymodeDesc );
			}
			else
			if( display_mode == 1 )
			{
				displaymodeDesc.mode = LIGHT_HALFSCREEN_MODE;  // ��ȫ����ʾģʽ
				engine->changeDisplaySettings( displaymodeDesc );
			}
			else
			if( display_mode == 2 )
			{
				displaymodeDesc.mode                  = LIGHT_FULLSCREEN_MODE;  // ȫ����ʾģʽ
				displaymodeDesc.fullscreen.width      = 800;                    // ��Ļˮƽ�ֱ���
				displaymodeDesc.fullscreen.height     = 600;                    // ��Ļ��ֱ�ֱ���
				displaymodeDesc.fullscreen.color      = 16;                     // ��Ļ��ɫ���
				displaymodeDesc.fullscreen.refurbish  = 0;                      // ��Ļˢ����
				engine->changeDisplaySettings( displaymodeDesc );
			}
		}
	}
	// ������Ϣ
	while( engine->dispatchMessage() && key != KEY_ESCAPE );

	// �ͷŷ���Ķ���
	engine->releaseImage( image );  // �ͷ�ͼ�����
	engine->releaseInput( input );  // �ͷ�����ӿ�
	engine->releaseText( text ); // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}