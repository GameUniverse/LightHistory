

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ����������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine           *engine;
	LightCamera           *camera;
	LightMesh             *scene;
	LightSky              *sky;	
	LightTexture          *texture;
	LightText             *text;
	char string[100];
	int id;

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

	// �رմ�ֱͬ����Ĭ�Ͽ�����
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����̬�����ļ������ڴ�
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	scene = engine->createMesh( meshDesc );
	scene->load( "..\\resource\\scene\\pond\\pond.3ds" );

	// ��ȡ��������
	id = engine->getTextureID( "water00.tga" );
	texture = engine->getTexture( id );

	// ��ȡ��������
	texture->speed( 100 );
	texture->insertFrame( 0, 1 );
	texture->load("..\\resource\\image\\water\\water01.tga");
	texture->insertFrame( 1, 1 );
	texture->load("..\\resource\\image\\water\\water02.tga");
	texture->insertFrame( 2, 1 );
	texture->load("..\\resource\\image\\water\\water03.tga");
	texture->insertFrame( 3, 1 );
	texture->load("..\\resource\\image\\water\\water04.tga");
	texture->insertFrame( 4, 1 );
	texture->load("..\\resource\\image\\water\\water05.tga");
	texture->insertFrame( 5, 1 );
	texture->load("..\\resource\\image\\water\\water06.tga");
	texture->insertFrame( 6, 1 );
	texture->load("..\\resource\\image\\water\\water07.tga");

	texture->insertFrame( 7, 1 );
	texture->load("..\\resource\\image\\water\\water08.tga");
	texture->insertFrame( 8, 1 );
	texture->load("..\\resource\\image\\water\\water09.tga");
	texture->insertFrame( 9, 1 );
	texture->load("..\\resource\\image\\water\\water10.tga");
	texture->insertFrame( 10, 1 );
	texture->load("..\\resource\\image\\water\\water11.tga");
	texture->insertFrame( 11, 1 );
	texture->load("..\\resource\\image\\water\\water12.tga");
	texture->insertFrame( 12, 1 );
	texture->load("..\\resource\\image\\water\\water13.tga");
	texture->insertFrame( 13, 1 );
	texture->load("..\\resource\\image\\water\\water14.tga");
	texture->insertFrame( 14, 1 );
	texture->load("..\\resource\\image\\water\\water15.tga");

	// ������պ�
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // �������
	VEC3( skyDesc.box.size, 64, 64, 64 );            // ��պд�С
	LightTextureDesc textureDesc;
	skyDesc.top = engine->createTexture( textureDesc );
	skyDesc.top->load( "..\\resource\\sky\\fine_top.tga" );
	skyDesc.front = engine->createTexture( textureDesc );
	skyDesc.front->load( "..\\resource\\sky\\fine_front.tga" );
	skyDesc.back = engine->createTexture( textureDesc );
	skyDesc.back->load( "..\\resource\\sky\\fine_back.tga" );
	skyDesc.left = engine->createTexture( textureDesc );
	skyDesc.left->load( "..\\resource\\sky\\fine_left.tga" );
	skyDesc.right = engine->createTexture( textureDesc );
	skyDesc.right->load( "..\\resource\\sky\\fine_right.tga" );
	skyDesc.bottom = engine->createTexture( textureDesc );
	skyDesc.bottom->load( "..\\resource\\sky\\fine_bottom.tga" );
	sky = engine->createSky( skyDesc );

	// ���������λ�úͷ���	
	camera->lookAt( 0, -130, 80,  0, 0, 0,  0, 0, 1 );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ��պ�
		sky->render();

		// ��Ⱦ��������
		scene->render();

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���	
	engine->releaseSky( sky );        // �ͷ����
	engine->releaseMesh( scene );     // �ͷ����糡����ռ�ڴ�
	engine->releaseText( text );      // �ͷ����ֶ���
	engine->releaseCamera( camera );  // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}