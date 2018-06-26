

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ���ӻ�����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine    *engine;
	LightCamera    *camera;	
	LightParticle  *particle;	
	LightSound     *sound;
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

	// ʹ�� 3DSMAX ����ϵͳ(Z->UP��
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// ���ùؼ�ɫ ��ϵͳĬ�ϣ�
	engine->disable( LIGHT_KEY_COLOR );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ���������뱳��ͼƬ
	LightImageDesc imageDesc;
	background = engine->createImage( imageDesc );	 
	background->load( "..\\resource\\image\\grassland.jpg" );

	/// ����һ�����ӷ�����
	LightParticleDesc particleDesc;
	particleDesc.track = LIGHT_TRACK_RADIAL;
	strcpy( particleDesc.texture, "..\\resource\\particle\\fire.bmp" ); /// ���������ļ�
	particleDesc.numparticle = 16;	
	particleDesc.grid_width = 64;
	particleDesc.grid_width = 64;
	particleDesc.num_grid = 16;
	particle = engine->createParticle( particleDesc );

	// �������Ӳ���
	particle->setVector( 0.0f, 0.0f, 1.0f );
	particle->speed( 2.5f );
	particle->life( 1000 );
	particle->size( 1, 1 );

	// ���벢���Ż���ȼ�յ�����	
	LightSoundDesc soundDesc;
	sound = engine->createSound( soundDesc );
	sound->load( "..\\resource\\sound\\burn.wav" );
	sound->setRepeats( 1000 );
	sound->play();

	camera->lookAt( 6, 0, 4,  0, 0, 1,  0, 0, 1 );

	do
	{
		// �����Ļ����		
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ����ͼƬ		
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
	engine->releaseParticle( particle );  // �ͷ����ӷ�����	
	engine->releaseImage( background );	  // �ͷű���ͼƬ	
	engine->releaseText( text );          // �ͷ����ֶ���		
	engine->releaseSound( sound );        // �ͷ���������	
	engine->releaseCamera( camera );	  // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}