

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightWater *water;
	LightTerrain *terrain;
	LightTexture *texture[3];
	LightTextureDesc textureDesc;
	LightScene *scene;
	LightActor *plane;
	LightActor *box;
	LightTexture *wood;
	LightSky *sky;	
	LightText *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ʹ�� 3DSMAX ����ϵ
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	terrain = engine->NewTerrain();

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// ����һ������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// �������棨һ��ƽ�棩
	LightActorDesc desc;
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_PLANE;
	VEC3( desc.plane.normal, 0.0f, 1.0f, 0.0f );
	desc.plane.distance = 0.0f;
	plane = scene->createActor( desc );

	// ����һ������
	wood = engine->createTexture( textureDesc );
	wood->load( "..\\resource\\image\\wood.dds" );
	desc.type = LIGHT_SHAPE_BOX;
	VEC3( desc.box.size, 20, 20, 40 );
	VEC3( desc.pos, 312, 212, 130 );
	VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
	desc.angle = 0.0f;
	desc.mass = 5;
	desc.hide = FALSE;	
	box = scene->createActor( desc );

	// �������
	terrain = engine->NewTerrain();
	// ��������������ڴ�	
	for( int i=0; i<3; i++ )
		texture[i] = engine->createTexture( textureDesc );	
	texture[0]->load( "..\\resource\\terrain\\grass.bmp" );
	texture[1]->load( "..\\resource\\terrain\\stone.bmp" );
	texture[2]->load( "..\\resource\\terrain\\shadow.tga" );	
	for( i=0; i<3; i++ )
		terrain->SetTexture( i, texture[i] );
	// ���õ��δ�ש��С����Ⱥ͸߶ȣ�
	terrain->setTile( 32, 32 );
	// ���������ݶ����ڴ�
	//terrain->load( "..\\resource\\terrain\\map1024.raw", 0, 1025, 1025, 8 );
	terrain->load( "..\\resource\\terrain\\height.raw", 0, 1025, 1025, 16 );
	// ���õ�����ʾƷ��
	terrain->SetLODFactor( 2.5, 25 ); // ���ٶ�
	//terrain->SetLODFactor( 5, 50 ); // ��Ʒ��

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

	// ����ˮ��
	LightWaterDesc waterDesc;
	waterDesc.type = LIGHT_WATER_RECTANGLE;	
	VEC3( waterDesc.pos, 0, 0, 129 );
	waterDesc.rectangle.width = 1024;
	waterDesc.rectangle.height = 1024;
	waterDesc.normal = engine->createTexture( textureDesc );
	waterDesc.normal->load( "..\\resource\\image\\wavesbump.dds" );
	water = engine->createWater( waterDesc );

	// �������������
	camera->lookAt( 150, 150, 180,  512, 412, 0,  0, 0, 1 );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ��Ϸ����

		// ��ʾ��պ�
		sky->render();
		//��ʾ����		
		terrain->render();
		// ��ʾ������
		wood->active();
		box->render();

		// ��Ⱦ����ͼ		
		water->begin( LIGHT_REFLECTION_MAP );
		    sky->render();
			terrain->render();
			wood->active();
			box->render();
		water->end();

		// ��Ⱦ����ͼ
		water->begin( LIGHT_REFRACTION_MAP );
 		    //sky->Render(); // ����ͼ����Ҫ��Ⱦ��պ�
			terrain->render();
			wood->active();
			box->render();
		water->end();

		// ��Ⱦˮ��
		water->render();

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 420 );
		text->drawText( fps );

		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseSky( sky );        // �ͷ���պж���
	engine->releaseText( text );      // �ͷ����ֶ���
	engine->releaseCamera( camera );  // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}