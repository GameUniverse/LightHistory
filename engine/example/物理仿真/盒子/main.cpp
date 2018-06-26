

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine *engine;
LightScene  *scene;
LightCamera *camera;
LightText *text;
LightTexture *texture;
LightActor *box;
LightActor *plane;
LightPhysicsMaterial  *physicsMaterial;

// ������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
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
	scene = engine->createScene( sceneDesc );

	// ��ȡ��������
	texture->load( "..\\resource\\image\\wood.jpg" );

	// �����������
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8; // ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.staticFriction   = 35;  // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.dynamicFriction  = 1;   // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// ����һ������
	LightActorDesc desc;
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_BOX;
	desc.dynamic = TRUE;
	VEC3( desc.pos, 0.0f, 20.0f, 0.0f );
	VEC3( desc.box.size, 2.5, 2.5, 2.5 );
	VEC3( desc.rotate, 1.0f, 1.0f, 0.0f );
	desc.angle = 45;
	desc.mass = 0.00000001;
	desc.hide = FALSE;	
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex(); // ���ú����������
	box = scene->createActor( desc );

	// �������棨һ��ƽ�棩
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_PLANE;
	desc.dynamic = FALSE;
	VEC3( desc.plane.normal, 0.0f, 1.0f, 0.0f );
	desc.plane.distance = 0.0f;
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex(); // ���õ����������
	plane = scene->createActor( desc );

	// ���������
	camera->lookAt( 0, 10, 15,  0, 4, 0,  0, 1, 0 );

	// ���ǰ����
	texture->active();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// ��������״̬
		engine->updatePhysics();
		
		// ��ʾ������
		box->render();
				
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
	scene->releaseActor( box );         // �ͷź��ӡ�������������
	scene->releaseActor( plane );
	scene->releasePhysicsMaterial( physicsMaterial );	
	engine->releaseScene( scene );      // �ͷ�����������	
	engine->releaseTexture( texture );  // �ͷ��������	
	engine->releaseCamera( camera );    // �ͷ����������	
	engine->releaseText( text );        // �ͷ����ֶ���	

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );
	
	return 0;
}