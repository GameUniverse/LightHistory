

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��Ⱦ���񳡾���ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightMesh   *scene;
	LightSky    *sky;	
	LightText   *text;
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

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ������̬�������
	LightMeshDesc meshDesc;
	scene = engine->createMesh( meshDesc );
	scene->load( "..\\resource\\scene\\hill\\hill.3DS" );

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

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ���������λ�úͷ���
		vec3_t pos, rotate, translation, eye, center, up;
		VEC3( pos, 0.0f, 0.0f, 5.0f );                // ��תԭ��
		VEC3( rotate, angle, -ANGLE_TO_RADIAN(5), 0 ); // ��ת�Ƕ�
		VEC3( translation, 0, 0, 0 );           // ƽ��ʸ��
		camera->rotate( pos, rotate, 15, translation, TRUE, eye, center, up );
		gVectorAdd( pos, eye, eye );
		gVectorAdd( pos, center, center );
		gVectorAdd( pos, up, up );
		camera->lookAt( center[0], center[1], center[2],  eye[0], eye[1], eye[2],  up[0], up[1], up[2] );

		// ��Ⱦ��պ�
		sky->render();

		// ��Ⱦ��̬����		
		scene->render();

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// ��ת��̬����
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			angle -= ( time - lasttime ) * 0.0002f;			
			if( angle < -360 )
				angle = 0;
			lasttime = time;
		}
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseSky( sky );        // �ͷ���ն���
	engine->releaseMesh ( scene );    // �ͷž�̬�������
	engine->releaseText( text );      // �ͷ����ֶ���
	engine->releaseCamera( camera );  // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}