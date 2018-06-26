

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ������Ч��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine    *engine;
	LightCamera    *camera;	
	LightParticle  *particle;	
	LightTexture   *texture;	
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

	// ���뱳��ͼƬ
	LightImageDesc imageDesc;
	background = engine->createImage( imageDesc );
	background->load( "..\\resource\\image\\grassland.jpg" );	

	// ��������������ڴ�
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );
	texture->setOrigin( LIGHT_ORIGIN_LOWER_LEFT );
	//texture->Load("..\\resource\\particle\\smoke.bmp");
	//texture->Grid( 64, 64, 16 );
	texture->load("..\\resource\\particle\\round.bmp");
	texture->grid( 128, 128, 1 );

	// ����һ�����ӷ�����
	LightParticleDesc particleDesc;		
	particleDesc.track = LIGHT_TRACK_POINT; // ���ӹ켣	
	particleDesc.billboard_mode = LIGHT_BILLBOARD_FIX_XY; // �����ģʽ
	particleDesc.billboard_width = 2.0f;
	particleDesc.billboard_height = 2.0f;
	particleDesc.numparticle = 10;
	VEC3( particleDesc.homeplace_box, 0.2f, 0.2f, 0.2f );
	particleDesc.disable_texture = FALSE;          // ��ֹ����	
	particleDesc.emission_rate = 2;
	particleDesc.left_point = 0.25f;                  // ��������ת�۵�λ�ã������ֵ�ã�
	particleDesc.right_point = 0.75f;
	VEC4( particleDesc.color[0], 255, 128, 255, 0 );  // ������ɫ������͸���ȣ���ֵ��Ϣ
	VEC4( particleDesc.color[1], 255, 128, 255, 255 );
	VEC4( particleDesc.color[2], 255, 128, 255, 255 );
	VEC4( particleDesc.color[3], 255, 64, 255, 0 );
	VEC3( particleDesc.scale[0], 0.1f, 0.1f, 0.1f );     // �������ű�����ֵ��Ϣ
	VEC3( particleDesc.scale[1], 0.5, 0.5, 0.5 );
	VEC3( particleDesc.scale[2], 1.5, 1.5, 1.5 );
	VEC3( particleDesc.scale[3], 2, 2, 2 );	
	VEC4( particleDesc.rotate[0], 0, 0, 1,  0 );      // ������ת��ֵ��Ϣ
	VEC4( particleDesc.rotate[1], 0, 0, 1,  90  );
	VEC4( particleDesc.rotate[2], 0, 0, 1,  270 );
	VEC4( particleDesc.rotate[3], 0, 0, 1,  360 );	
	particle = engine->createParticle( particleDesc );

	// �������Ӳ���
	particle->setVector( 0.0f, 1.0f, 0.0f );
	particle->speed( 2.5f );
	particle->life( 3000 );
	//particle->Size( 1, 1 );	

	camera->lookAt( 6, 0, 4,  0, 0, 1,  0, 0, 1 );

	do
	{
		// �����Ļ����
		//engine->ClearColor( 255, 255, 255, 255 );
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ����ͼƬ		
		renderDesc.dest_rect.left   = 0;
		renderDesc.dest_rect.top    = 0;
		renderDesc.dest_rect.right  = 660;
		renderDesc.dest_rect.bottom = 448;
		renderDesc.flags = LIGHT_IMAGE_DESTRECT;
		background->renderDesc( 0, 0, renderDesc );

		// ��ʾ����ϵͳ
		texture->active();
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
	engine->releaseTexture( texture );    // �ͷ��������
	engine->releaseImage( background );	
	engine->releaseParticle( particle );  // �ͷ����ӷ�����	
	engine->releaseText( text );          // �ͷ����ֶ���	
	engine->releaseCamera( camera );      // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}
