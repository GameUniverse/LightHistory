

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine        *engine;
	LightScene         *scene;
	LightCamera        *camera;
	LightMesh          *sceneMesh;
	LightMesh          *physicsSceneMesh;
	LightSky           *sky;
	LightTriangleMesh  *triangleMesh;
	LightActor         *actor;
	LightActor         *physicsScene;
	LightTexture       *texture;
	LightInput         *input;
	LightText          *text;
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

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����̬�����ļ������ڴ�
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// ����һ������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// ���������������
	physicsSceneMesh = engine->createMesh( meshDesc );
	physicsSceneMesh->load( "..\\resource\\scene\\hill\\hill_physics.3DS" );
	triangleMesh = physicsSceneMesh->createTriangleMesh();

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

	// ��������
	LightActorDesc desc;
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );	
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_SPHERE;
	desc.dynamic = TRUE;
	VEC3( desc.pos, 0, 13, 25 );
	desc.sphere.radius = 1;
	desc.quality_slices = 15;
	desc.quality_stacks = 15;
	VEC3( desc.rotate, 1.0f, 1.0f, 0.0f );
	desc.angle = 45;
	desc.mass = 0.00000001f;
	desc.hide = FALSE;
	// ���ü���������������
	actor = scene->createActor( desc );

	// ����������
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_MESH;
	desc.mesh.triangleMesh = triangleMesh;
	// ���ü���������������
	physicsScene = scene->createActor( desc );

	// ���������λ�úͷ���
	camera->lookAt( -23, 8, 5,  48, 40, 5,  0, 0, 1 );

	do
	{
		// ������������״̬
		engine->updatePhysics();

		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ��պ�
		sky->render();

		// ��Ⱦ��������
		sceneMesh->render();

		// ��ʾ�����壨���ȼ����������
		texture->active();
		actor->render();

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
	scene->releaseActor( physicsScene );               // �ͷ������ɫ
	scene->releaseActor( actor );
	sceneMesh->releaseTriangleMesh( triangleMesh );    // �ͷ���������
	engine->releaseScene( scene );                     // �ͷ���������ռ�ڴ�
	engine->releaseMesh( sceneMesh );                  // �ͷž�̬�������
	engine->releaseMesh( physicsSceneMesh );
	engine->releaseTexture( texture );                 // �ͷ�����
	engine->releaseSky( sky );	                       // �ͷ���պж���
	engine->releaseInput( input );                     // �ͷ�����ӿ�
	engine->releaseCamera( camera );                   // �ͷ����������
	engine->releaseText( text );                       // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}