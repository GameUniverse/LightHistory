

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine *engine;
LightCamera *camera;
LightText *text;
LightTexture *texture;
LightPhysicsMaterial *physicsMaterial;
LightScene  *scene;
LightActor *actor[40];
LightActor *plane;

// ����������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int i;

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

	// �����������
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );

	// ����һ������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// �����������
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.staticFriction   = 35;  // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.dynamicFriction  = 1;   // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// ����������
	texture->load( "..\\resource\\image\\wood.jpg" );
	LightActorDesc actorDesc;
	for( i=0; i<40; i++)
	{
		if( i < 30 )
			actorDesc.type = LIGHT_SHAPE_BOX;
		else
		if( i > 29 && i < 35)
		{
			actorDesc.type = LIGHT_SHAPE_SPHERE;
			actorDesc.sphere.radius = ( (float)rand() / ( RAND_MAX ) ) + 1;
		}
		else
		if( i > 34 && i< 40 )
		{
			actorDesc.type = LIGHT_SHAPE_CAPSULE;
			actorDesc.capsule.radius = 1;
			actorDesc.capsule.height = 2;
		}
		else
		if( i > 20 && i< 25 )
		{
			
		}

		actorDesc.dynamic = TRUE;
		actorDesc.quality_slices = 10;
		actorDesc.quality_stacks = 10;
		VEC3( actorDesc.box.size, ( (float)rand() / ( RAND_MAX / 2 ) )+1,( (float)rand() / ( RAND_MAX / 2 ) )+1, ( (float)rand() / ( RAND_MAX / 2 ) )+1 );
		VEC3( actorDesc.pos, ( (float)rand() / ( RAND_MAX / 8 ) )-4, ( (float)rand() / ( RAND_MAX / 80 ) )+20, ( (float)rand() / ( RAND_MAX / 8 ) )-4 );
		VEC3( actorDesc.rotate, ( (float)rand() / ( RAND_MAX / 4 ) )-2.0f, ( (float)rand() / ( RAND_MAX / 4 ) )-2.0f, ( (float)rand() / ( RAND_MAX / 4 ) )-2.0f );
		actorDesc.angle = ( (float)rand() / ( RAND_MAX / 90 ) )-5.0f;
		actorDesc.mass = 0.00000001f;
		actorDesc.hide = FALSE;
		// ���ü������������
		actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
		actor[i] = scene->createActor( actorDesc );
	}

	// �������棨һ��ƽ�棩	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_PLANE;
	VEC3( actorDesc.plane.normal, 0.0f, 1.0f, 0.0f );
	actorDesc.plane.distance = 0.0f;
	plane = scene->createActor( actorDesc );

	// ���������
	camera->lookAt( 0, 10, 20,  0, 2, 0,  0, 1, 0 );

	// ���ǰ����
	texture->active();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// ��������״̬
		engine->updatePhysics();
		
		// ��ʾ������
		for( i=0; i<40; i++)
			actor[i]->render();		

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
	scene->releaseActor( plane );                      // �ͷ������ɫ
	for( i=0; i<40; i++ )
		scene->releaseActor( actor[i] );	
	scene->releasePhysicsMaterial( physicsMaterial );  // �ͷ��������
	engine->releaseScene( scene );                     // �ͷ���������ռ�ڴ�
	engine->releaseTexture( texture );                 // �ͷ��������
	engine->releaseCamera( camera );                   // �ͷ����������
	engine->releaseText( text );                       // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}