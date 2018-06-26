

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ����ͼ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightBrush  *brush;
	LightText   *text;

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

	// �������ʶ���
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );	

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ���û�ͼ��ɫ
	    brush->color( 255, 0, 0 );
		// ����
		brush->point2D( 150, 75 );
		// ���߶�
		brush->color( 0, 255, 0 );
		brush->line2D( 200, 50, 250, 100 );
		// ������
		brush->color( 0, 0, 255 );
		brush->rectangle2D( 125, 125, 275, 225 );

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
	engine->releaseText( text );    // �ͷ����ֶ���
	engine->releaseBrush( brush );  // �ͷŻ��ʶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;	
}