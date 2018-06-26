

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ����ӳ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine   *engine;
	LightCamera   *camera;
	LightMesh     *mesh;
	LightText     *text;	
	LightSky      *sky;
	LightTexture  *texture;
	LightTextureDesc textureDesc;
	char          string[100];
	float         rotate = 0;
	DWORD         lasttime = 0;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );
	
	// ���ùؼ�ɫ
	engine->enable( LIGHT_KEY_COLOR );
	
	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );
	
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

	// ����̬�����ļ������ڴ�
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\mesh\\digger\\digger.3ds" );

	// ��������������	
	texture = engine->createTexture( textureDesc );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_X );
	texture->load( "..\\resource\\image\\camera\\cm_left.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_X );
	texture->load( "..\\resource\\image\\camera\\cm_right.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Y );
	texture->load( "..\\resource\\image\\camera\\cm_top.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Y );
	texture->load( "..\\resource\\image\\camera\\cm_bottom.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Z );
	texture->load( "..\\resource\\image\\camera\\cm_back.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Z );
	texture->load( "..\\resource\\image\\camera\\cm_front.tga" );

	// ���������
	camera->lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ��պ�
		//sky->render();

		// ��ʾ��̬����		
		mesh->setGlobalOrientationAngleAxis( rotate, 0, 1, 0 );
		texture->active();
		engine->enable( LIGHT_CUBE_MAP );
		mesh->render();
		engine->disable( LIGHT_CUBE_MAP );

		// ��ʾ��ʾ��Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 220 );		

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// ��ת���
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			rotate -= ( time - lasttime ) * 0.005f;
			if( rotate < -360 )
				rotate = 0;
			lasttime = time;
		}
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseTexture( texture );  // �ͷ�����������
	engine->releaseMesh ( mesh );       // �ͷž�̬�������
	engine->releaseSky( sky );	        // �ͷ���ն���
	engine->releaseText( text );        // �ͷ����ֶ���
	engine->releaseCamera( camera );    // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}