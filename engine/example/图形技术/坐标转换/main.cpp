

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine         *engine;
LightInput          *input;
LightCamera         *camera;
LightText           *text;
LightTexture        *texture;
LightMesh           *mesh;
LightTriangleMesh   *triangleMesh;
LightScene          *scene;
LightActor          *physicsScene;
LightActor          *a, *b;
LightActorDesc      actorDesc;


// ����ת����ʾ����
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

	// ʹ�� 3DSMAX ����ϵͳ(Z->UP��
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

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

	// ���������� a �� b
	texture->load( "..\\resource\\image\\wood.jpg" );
	memset( &actorDesc, 0, sizeof(LightActorDesc) );
	actorDesc.type = LIGHT_SHAPE_BOX;
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.box.size, 3.0f, 3.0f, 3.0f );
	VEC3( actorDesc.pos, 0.0f, 0.0f, 15.0f );
	VEC3( actorDesc.rotate, 0.0f, 0.0f, 1.0f );
	actorDesc.angle = 0.0f;
	actorDesc.mass = 0.00001f;
	actorDesc.hide = FALSE;	
	a = scene->createActor( actorDesc );	
	actorDesc.type = LIGHT_SHAPE_BOX;
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.box.size, 3.0f, 3.0f, 3.0f );
	VEC3( actorDesc.pos, 0.0f, 0.0f, 25.0f );
	VEC3( actorDesc.rotate, 1.5f, 1.5f, 1.5f );
	actorDesc.angle = 45.0f;	
	b = scene->createActor( actorDesc );

	// ������̬�������
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\scene\\ground\\ground.3ds" );

	// ������������	
	triangleMesh = mesh->createTriangleMesh();

	// ����������	
	memset( &actorDesc, 0, sizeof(LightActorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // ��ɫ����
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0; // ʹ��ȱʡ����
	physicsScene = scene->createActor( actorDesc );

	// ���������λ�úͷ���
	vec3_t eye = { 0, -50, 25 };
	camera->lookAt( eye[0], eye[1], eye[2],  0, 25, 10,  0, 0, 1 );

	// ���ǰ����
	texture->active();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��������״̬
		engine->updatePhysics();

		// ��ʾ����
		mesh->render();

		// ��ʾ������ a �� b
		texture->active();
		a->render();
		b->render();

		POINT point2d;
		vec3_t point3d, reverse2d;

		// ��ѯ��괰������
		input->getCursorPos( &point2d );

		// �������������
		camera->updateCamera();

		// ע�⣺����Ŀ�������Ⱦ֮��������������ת������������õ��Ľ�����ܲ���ȷ

		// �����������ꡱת���ɡ��������ꡱ
		engine->windowToWorld( point2d.x, point2d.y, point3d );

		// �����������ꡱת���ɡ��������ꡱ
		engine->worldToWindow( point3d[0], point3d[1], point3d[2], reverse2d );

		// ��ʾ������Ϣ
		char string[100];
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 40 );
		sprintf( string, "���� 2D (%d,%d) ----> ���� 3D (%.2f,%.2f,%.2f)", point2d.x, point2d.y, point3d[0], point3d[1], point3d[2] );
		text->drawText( string );
		text->setTextPos( 40, 65 );
		sprintf( string, "���� 2D (%.0f,%.0f) <---- ���� 3D (%.2f,%.2f,%.2f)  ", reverse2d[0], reverse2d[1], point3d[0], point3d[1], point3d[2] );
		text->drawText( string );

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
	scene->releaseActor( a );                   // �ͷ������ɫ
	scene->releaseActor( b );
	scene->releaseActor( physicsScene );
	mesh->releaseTriangleMesh( triangleMesh );  // �ͷ���������
	engine->releaseScene( scene );              // �ͷ���������ռ�ڴ�
	engine->releaseMesh( mesh );                // �ͷž�̬�������
	engine->releaseTexture( texture );          // �ͷ�����
	engine->releaseInput( input );              // �ͷ�����ӿ�
	engine->releaseCamera( camera );            // �ͷ����������
	engine->releaseText( text );                // �ͷ����ֶ���

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );
	
	return 0;
}