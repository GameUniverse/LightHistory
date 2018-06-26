

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// �����ٶ���ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine           *engine;
	LightScene            *scene;
	LightCamera           *camera;
	LightMesh             *sceneMesh;
	LightSky              *sky;
	LightPhysicsMaterial  *physicsMaterial;
	LightTriangleMesh     *triangleMesh;
	LightActor            *actor;
	LightActor            *physicsScene;
	LightTexture          *texture;
	LightInput            *input;
	LightText             *text;
	char string[100];
	int  mode = 0;        // ����ģʽ
	float velocity = 300; // �ƶ��ٶ�
	vec3_t rotate = { 0, 0, 0 };
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

	// ������̬�������
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\ground\\ground.3ds" );

	// ������������	
	triangleMesh = sceneMesh->createTriangleMesh();

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

	// �����������
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.staticFriction   = 35;  // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterialDesc.dynamicFriction  = 1;   // ��̬ĥ����ϵ����ȱʡֵΪ 0.5��
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// ����ľͷ����	
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );

	// ��������
	LightActorDesc actorDesc;
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_SPHERE; // ��ɫ����
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.pos, 0, 0, 20 );     // ��ɫλ��
	actorDesc.sphere.radius = 2;         // ����뾶
	actorDesc.quality_slices = 15;       // ������ʾƷ��
	actorDesc.quality_stacks = 15;
	VEC3( actorDesc.rotate, 1.0f, 1.0f, 0.0f ); // ��ת��������ת�ᣩ
	actorDesc.angle = 45;                // ��ת��������ת�Ƕȣ�
	actorDesc.mass = 1.0;                // ��ɫ����
	actorDesc.hide = FALSE;              // ���ر�־
	// ���ü������������	
	actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	actor = scene->createActor( actorDesc );

	// ����������
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // ��ɫ����	
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0; // ʹ��ȱʡ����
	physicsScene = scene->createActor( actorDesc );

	// ���������λ�úͷ���	
	camera->lookAt( 0, -100, 50,  0, 0, 0,  0, 0, 1 );

	// ����������ʱ��
	lasttime = engine->getTickCount();

	do
	{
		// ������������״̬
		engine->updatePhysics();

		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ��պ�
		sky->render();

		// ��Ⱦ����
		texture->active(); // �����ȼ����������
		//scene->Render();
		actor->render();

		// ��Ⱦ��������
		sceneMesh->render();

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

		// ��ʾ��ʾ��Ϣ		
		text->setTextPos( 300, 370 );
		if( mode == 0 )
			text->drawText( "����ģʽ��ʩ����( addForce )" );
		else
		if( mode == 1 )
			text->drawText( "����ģʽ���������ٶ�( setLinearVelocity )" );
		else
		if( mode == 2 )
			text->drawText( "����ģʽ�����ý��ٶ�( setAngularVelocity )" );
		text->setTextPos( 300, 400 );
		text->drawText( "W S A D = �������򣬿ո� = ��Ծ��M = �л�����ģʽ" );

		// ������ʾ
		engine->swapBuffers();

		// �����������ָ��		
		DWORD time;
		unsigned int key;

		// ��ѯ��ǰϵͳʱ��
		time = engine->getTickCount();

		// ��ֹʱ����������
		if( time < lasttime )
			lasttime = time;

		// �ƶ���ɫ���ƶ���
		float gravity = -9.8f; // ����
		float elapsedTime;    // �����һ�θ����������ŵ�ʱ��
		float forward = 0, left = 0;

		// ��������˶�����
		if( input->getKeyState( KEY_UP ) || input->getKeyState( KEY_W ) )
			forward = 1;
		if( input->getKeyState( KEY_DOWN ) || input->getKeyState( KEY_S ) )
			forward = -1;
		if( input->getKeyState( KEY_LEFT ) || input->getKeyState( KEY_A ) )
			left = -1;
		if( input->getKeyState( KEY_RIGHT ) || input->getKeyState( KEY_D ) )
			left = 1;

		key = input->getKey();
		// ������� M �������л�����ģʽ
		if( key == KEY_M )
		{
			mode++;
			if( mode > 2 )
				mode = 0;
		}
		// ������¿ո����������
		if( key == KEY_SPACE )
			actor->addForce( 0, 0, 10000, 0 );

		// ��ǧ��֮һ��Ϊ��λ���и���
		elapsedTime = (float)(time - lasttime);
		elapsedTime /= 1000;

		// ����������
		vec3_t vector, linearVelocity, angularVelocity;
		vector[0] = left * velocity;
		vector[1] = forward * velocity;
		vector[2] = gravity * elapsedTime;
		VEC3( linearVelocity, vector[0] * 0.05f, vector[1] * 0.05f, vector[2] * 0.05f );
		VEC3( angularVelocity, -vector[1], vector[0], vector[2] );

		if( elapsedTime > 0 )
		{
			if( mode == 0 )
				// ʩ����
				actor->addForce( vector[0], vector[1], vector[2] );
			else
			if( mode == 1 )
				// �������ٶ�
				actor->setLinearVelocity( linearVelocity );
			else
			if( mode == 2 )
				// ���ý��ٶ�
				actor->setAngularVelocity( angularVelocity );
			lasttime = time;
		}
	}
	// ������Ϣ
	while( engine->dispatchMessage() && !input->getKeyState( KEY_ESCAPE ) );

	// �ͷŷ���Ķ���
	scene->releaseActor( physicsScene );               // �ͷ������ɫ
	scene->releaseActor( actor );
	scene->releasePhysicsMaterial( physicsMaterial );  // �ͷ��������
	sceneMesh->releaseTriangleMesh( triangleMesh );    // �ͷ���������
	engine->releaseScene( scene );                     // �ͷ���������ռ�ڴ�
	engine->releaseMesh( sceneMesh );                  // �ͷž�̬�������
	engine->releaseTexture( texture );                 // �ͷ�����
	engine->releaseSky( sky );	                       // �ͷ���պж���
	engine->releaseInput( input );                     // �ͷ�����ӿ�
	engine->releaseCamera( camera );                   // �ͷ����������
	engine->releaseText( text );                       // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}