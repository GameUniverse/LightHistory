

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// �����ļ���ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine    *engine;
	LightCamera    *camera;	
	LightParticle  *particle;
	LightText      *text;
	LightImage     *background;
	LightImageRenderDesc renderDesc;

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

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ���뱳��ͼƬ
	LightImageDesc imageDesc;
	background = engine->createImage( imageDesc );
	background->load( "..\\resource\\image\\grassland.jpg" );
	
	// ����һ�����ӷ�����
	LightParticleDesc particleDesc;
	particle = engine->createParticle( particleDesc );

	// �������ļ������ڴ�
	particle->load( "..\\resource\\particle\\smoke.particle" );

	camera->lookAt( 6, 0, 1,  0, 0, 1,  0, 0, 1 );

	do
	{
		// �����Ļ����		
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ����ͼƬ		
		renderDesc.dest_rect.left   = 0;
		renderDesc.dest_rect.top    = 0;
		renderDesc.dest_rect.right  = 660;
		renderDesc.dest_rect.bottom = 448;
		renderDesc.flags = LIGHT_IMAGE_DESTRECT;
		background->renderDesc( 0, 0, renderDesc );

		// ��ʾ����ϵͳ
		particle->render();

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );

		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���	
	engine->releaseParticle( particle ); // �ͷ����ӷ�����	
	engine->releaseImage( background );  // �ͷű���ͼƬ	
	engine->releaseText( text );         // �ͷ����ֶ���	
	engine->releaseCamera( camera );     // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}