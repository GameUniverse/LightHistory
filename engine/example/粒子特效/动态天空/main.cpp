

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��̬�����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;
	LightCamera  *camera;
	LightMesh    *scene;
	LightSky     *sky;	
	LightInput   *input;
	LightText    *text;
	char string[100];
	float angle = 0;
	DWORD lasttime = 0;

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

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����̬�����ļ������ڴ�
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	scene = engine->createMesh( meshDesc );
	scene->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// ������պ�
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // �������
	VEC3( skyDesc.box.size, 64, 64, 64 );            // ��պд�С	
	skyDesc.rotate_velocity = 0;                     // ����
	VEC3( skyDesc.rotate_axis, 0, 0, 1 );            // ����
	VEC3( skyDesc.cloud_size, 128, 128, 10 );        // �Ʋ�д�С
	VEC3( skyDesc.cloud_velocity, 0.01f, 0.01f, 0 ); // �Ʋ��ƶ��ٶ�
	skyDesc.cloud_scale = 0.2f;                      // �Ʋ��������ű���
	LightTextureDesc textureDesc;
	skyDesc.top = engine->createTexture( textureDesc ); // ��ȡ��պ�����
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
	skyDesc.cloud = engine->createTexture( textureDesc ); // ��ȡ�Ʋ�����
	skyDesc.cloud->load( "..\\resource\\sky\\cloud.tga" );
	sky = engine->createSky( skyDesc );

	// ���������λ�úͷ���
	camera->lookAt( 0, 0, 5,  -10, -6, 8,  0, 0, 1 );

	do
	{
		// ������������״̬
		engine->updatePhysics();

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

	// �ͷ���ն���
	engine->releaseSky( sky );

	// �ͷž�̬������ռ�ڴ�
	engine->releaseMesh ( scene );

	// �ͷ�����ӿ�
	engine->releaseInput( input );

	// �ͷ����ֶ���
	engine->releaseText( text );

	// �ͷ����������
	engine->releaseCamera( camera );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}