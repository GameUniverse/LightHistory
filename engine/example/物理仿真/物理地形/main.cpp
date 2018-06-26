

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ���������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;
	LightScene   *scene;
	LightCamera  *camera;
	LightTerrain *terrain;
	LightTexture *texture[3];
	LightSky     *sky;
	LightPhysicsMaterial  *physicsMaterial;
	LightActor   *actor;
	LightActor   *physicsTerrain;
	LightTexture *wood;
	LightInput   *input;
	LightText    *text;
	LightTextureDesc textureDesc;
	char string[100];
	float angle = 0;
	DWORD lasttime = 0;
	int i;

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

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����һ������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// �������
	terrain = engine->NewTerrain();
	for( i=0; i<3; i++ )
		texture[i] = engine->createTexture( textureDesc );
	// ��������������ڴ�	
	texture[0]->load( "..\\resource\\terrain\\grass.bmp" );  // ��һ�������������ͨ��
	texture[1]->load( "..\\resource\\terrain\\stone.bmp" );  // �ڶ��������������ͨ��
	texture[2]->load( "..\\resource\\terrain\\shadow.tga" ); // ������Ӱ��ͼ��32λTGA��ʽ����ͨ����ͨ��ֵΪ��һ��������ռ�������ڶ���������ռ���� = 1-��һ���������������
	for( i=0; i<3; i++ )
		terrain->SetTexture( i, texture[i] );
	// ���õ��δ�ש��С����Ⱥ͸߶ȣ�
	terrain->setTile( 32, 32 );
	// ���������ݶ����ڴ�
	//terrain->load( "..\\resource\\terrain\\map1024.raw", 0, 1025, 1025, 8 );
	terrain->load( "..\\resource\\terrain\\height.raw", 0, 1025, 1025, 16 );
	// ���õ�����ʾƷ��
	//terrain->SetLODFactor( 2.5, 25 ); // ���ٶ�
	terrain->SetLODFactor( 5, 50 ); // ��Ʒ��

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

	// �����������
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.staticFriction   = 35;  // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.dynamicFriction  = 1;   // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	LightActorDesc desc;

	// ����������	
	wood = engine->createTexture( textureDesc );
	wood->load( "..\\resource\\image\\wood.jpg" );	
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_SPHERE;
	desc.dynamic = TRUE;
	VEC3( desc.pos, 80, 250, 150 );
	desc.sphere.radius = 2;
	desc.quality_slices = 15;
	desc.quality_stacks = 15;
	VEC3( desc.rotate, 0.0f, 0.0f, 1.0f );
	desc.angle = 0;
	desc.mass = 1;
	desc.hide = FALSE;
	// ���ü���������������
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	actor = scene->createActor( desc );

	// �����������	
	desc.type = LIGHT_SHAPE_HEIGHTFIELD;
	desc.dynamic = FALSE;
	VEC3( desc.pos, 0, 0, 0 );
	VEC3( desc.rotate, 0.0f, 0.0f, 1.0f );
	desc.angle = 0;
	desc.mass = 0;
	vec3_t position, box;
	VEC3( position, 0, 0, 0 ); // �˲���Ŀǰ��ʹ��
	VEC3( box, 1025, 1025, 64 ); // ������δ�С��������Ŀǰ������ʹ�ã�ע�⣺������εĴ�С����Ҫ�͸߶�ͼ�Ĵ�С����ϣ�
	desc.height_field.heightField = terrain->createHeightField( position, box );
	// ���ü���������������
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	physicsTerrain = scene->createActor( desc );

	// ���������λ�úͷ���
	camera->lookAt( 0, 0, 150,  256, 256, 25,  0, 0, 1 );

	do
	{
		// ������������״̬
		engine->updatePhysics();

		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ���������λ�úͷ���
		float x, y, z;
		actor->getGlobalPosition( &x, &y, &z );
		camera->lookAt( 0, 100, 150,  x, y, z,  0, 0, 1 );

		// ��Ⱦ��պ�
		sky->render();

		//��Ⱦ����
		//terrain->RenderMode( 0 );
		terrain->render();

		// ��ʾ�����壨���ȼ����������
		wood->active();
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
	//scene->releaseActor( physicsScene );               // �ͷ������ɫ
	scene->releaseActor( actor );
	scene->releasePhysicsMaterial( physicsMaterial );  // �ͷ��������
	//sceneMesh->releaseTriangleMesh( triangleMesh );    // �ͷ���������
	engine->releaseScene( scene );                     // �ͷ���������ռ�ڴ�
	//engine->releaseMesh( sceneMesh );                  // �ͷž�̬�������
	//engine->releaseTexture( texture );                 // �ͷ�����
	engine->releaseSky( sky );	                       // �ͷ���պж���
	engine->releaseInput( input );                     // �ͷ�����ӿ�
	engine->releaseCamera( camera );                   // �ͷ����������
	engine->releaseText( text );                       // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}