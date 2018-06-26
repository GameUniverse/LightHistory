

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine         *engine;
LightCamera         *camera;
LightInput          *input;
LightText           *text;
LightTexture        *texture;
LightMesh           *mesh;
LightScene          *scene;
LightTriangleMesh   *triangleMesh;
LightActor          *physicsMesh;
LightActor          *a, *b;
LightActor          *plane;
LightActorDesc      actorDesc;


// ���ʰȡ��ʾ����
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

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

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

	// ���������������
	triangleMesh = mesh->createTriangleMesh();

	// ���������ɫ����
	actorDesc.type = LIGHT_SHAPE_MESH; // ��ɫ����
	actorDesc.dynamic = FALSE;
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0;
	physicsMesh = scene->createActor( actorDesc );

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

		// ��Ⱦ����
		mesh->render();

		// ��ʾ������ a �� b
		texture->active();
		a->render();
		b->render();

		// С��ʾ�������ʰȡ��������
		// �����ڹ�����½ǣ�x+32��y+32���ٽ���һ��ʰȡ��������ʰȡ�Ľ����Ϊ���ʰȡ�Ľ��

		// ��ѯ����ڳ��������е�����
		POINT point;
		vec3_t cursor;
		input->getCursorPos( &point );
		camera->updateCamera();
		engine->windowToWorld( point.x, point.y, cursor );

		// �Խ�ɫ����ʰȡ
		LightRay ray;
		LightRaycastHit hit;
		gVectorCopy( eye, ray.orig );
		gVectorSubtract( cursor, ray.orig, ray.dir );
		gVectorNormalize( ray.dir );
		LightActor * hitActor = scene->raycastClosestShape( ray, LIGHT_ALL_SHAPES, hit, 0xffffffff, 500, 0 ); // LIGHT_DYNAMIC_SHAPES Ϊֻʰȡ��̬��ɫ

		// ��ʾ��ʾ��Ϣ��ʰȡ���
		text->setTextPos( 40, 368 );
		if( hitActor == a )
		{
			text->color( 255, 0, 0 );
			text->drawText( "ѡ�к��� A" );
		}
		else
		if( hitActor == b )
		{
			text->color( 255, 0, 0 );
			text->drawText( "ѡ�к��� B" );
		}
		else
		if( hitActor == physicsMesh )
		{
			text->color( 255, 0, 0 );
			text->drawText( "ѡ�е���" );
		}
		else
		{
			text->color( 0, 255, 0 );
			text->drawText( "�뽫����ƶ���������������" );
		}		

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
	scene->releaseActor( a );                   // �ͷ������ɫ����
	scene->releaseActor( b );
	scene->releaseActor( physicsMesh );
	mesh->releaseTriangleMesh( triangleMesh );  // �ͷ���������
	engine->releaseScene( scene );              // �ͷ���������ռ�ڴ�
	engine->releaseMesh( mesh );                // �ͷž�̬�������
	engine->releaseTexture( texture );          // �ͷ��������
	engine->releaseInput( input );              // �ͷ�����ӿ�
	engine->releaseCamera( camera );            // �ͷ����������
	engine->releaseText( text );                // �ͷ����ֶ���

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}