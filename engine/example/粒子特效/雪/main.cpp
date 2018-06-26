

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ѩ��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;	
	LightCamera  *camera;
	LightMesh    *mesh;
	LightSky     *sky;	
	LightTexture *snowflake;
	LightWeather *weather;
	LightInput   *input;
	LightText    *text;
	LightTextureDesc textureDesc;
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

	// ���ùؼ�ɫ��Ĭ�Ͻ��ã�
	engine->enable( LIGHT_KEY_COLOR );
	// ���ùؼ�ɫ��͸��ɫ��Ĭ��ֵΪ��ɫ 0��0��0 ��
	engine->setKeyColor( 255, 0, 0 );

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

	// ������̬�������
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// ������պ�
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // �������
	VEC3( skyDesc.box.size, 64, 64, 64 );            // ��պд�С	
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

	// ����ѩ������
	snowflake = engine->createTexture( textureDesc );
	snowflake->load( "..\\resource\\particle\\snowflake.bmp" );

	// ����ѩ����
	LightWeatherDesc weatherDesc;
	memset( &weatherDesc, 0, sizeof(weatherDesc) );
	weatherDesc.type = LIGHT_WEATHER_SNOW;
	weatherDesc.numparticle = 2010;
	VEC3( weatherDesc.box, 200, 200, 200 );
	VEC3( weatherDesc.position, 0.0f, -30.0f, -150.0f );
	weatherDesc.drop_velocity_min = 0.02f;
	weatherDesc.drop_velocity_max = 0.52f;
	VEC3( weatherDesc.wind, 0, 0, 0 );
	weather = engine->createWeather( weatherDesc );

	// ���������λ�úͷ���
	camera->lookAt( 0, 0, 5,  -10, -5, 8,  0, 0, 1 );

	do
	{
		// ������������״̬
		engine->updatePhysics();

		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ��պ�
		sky->render();

		// ��Ⱦ��̬����
		mesh->render();

		// ��Ⱦѩ����
		snowflake->active();
		weather->render();

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
	engine->releaseTexture( snowflake );  // �ͷ�ѩ������
	engine->releaseWeather( weather );    // �ͷ�ѩ����
	engine->releaseSky( sky );            // �ͷ���ն���
	engine->releaseMesh ( mesh );         // �ͷž�̬�������
	engine->releaseInput( input );        // �ͷ�����ӿ�	
	engine->releaseText( text );          // �ͷ����ֶ���
	engine->releaseCamera( camera );      // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}