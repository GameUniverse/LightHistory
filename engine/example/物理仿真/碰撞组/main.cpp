

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��ײ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine           *engine;
	LightScene            *scene;
	LightCamera           *camera;
	LightMesh             *sceneMesh;
	LightSky              *sky;
	LightPhysicsMaterial  *physicsMaterial;
	LightActor            *sphere1, *sphere2, *sphere3;
	LightActor            *box1, *box2, *box3;
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

	// ����̬�����ļ������ڴ�
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\ground\\ground.3ds" );

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

	// ��ȡ��ɫ����
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );

	// ��������1
	LightActorDesc actorDesc;	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_SPHERE; // ��ɫ����
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.pos, 0, -25, 20 );     // ��ɫλ��
	actorDesc.sphere.radius = 2;         // ����뾶
	actorDesc.quality_slices = 15;       // ������ʾƷ��
	actorDesc.quality_stacks = 15;
	VEC3( actorDesc.rotate, 1.0f, 1.0f, 0.0f ); // ��ת��������ת�ᣩ
	actorDesc.angle = 45;                // ��ת��������ת�Ƕȣ�
	actorDesc.mass = 1.0;                // ��ɫ����
	actorDesc.hide = FALSE;              // ���ر�־
	// ���ü������������	
	actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	sphere1 = scene->createActor( actorDesc );
	// ��������2
	VEC3( actorDesc.pos, -10, -25, 20 );
	sphere2 = scene->createActor( actorDesc );
	// ��������3
	VEC3( actorDesc.pos, 10, -25, 20 );
	sphere3 = scene->createActor( actorDesc );

	// ��������1
	actorDesc.type = LIGHT_SHAPE_BOX;    // ��ɫ����	
	VEC3( actorDesc.pos, 0, -10, 20 );    // ��ɫλ��
	VEC3( actorDesc.box.size, 4, 4, 4 ); // ���Ӵ�С
	VEC3( actorDesc.rotate, 0.0f, 0.0f, 1.0f ); // ��ת��������ת�ᣩ
	actorDesc.angle = 0;                // ��ת��������ת�Ƕȣ�	
	box1 = scene->createActor( actorDesc );
	// ��������2
	VEC3( actorDesc.pos, -10, -10, 20 );
	box2 = scene->createActor( actorDesc );
	// ��������3
	VEC3( actorDesc.pos, 10, -10, 20 );
	box3 = scene->createActor( actorDesc );

	// ����������
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // ��ɫ����
	actorDesc.mesh.triangleMesh = sceneMesh->createTriangleMesh();		
	actorDesc.physicsMaterialIndex = 0; // ʹ��ȱʡ����
	physicsScene = scene->createActor( actorDesc );

	// ���ý�ɫ��ײ��	
	physicsScene->setGroup( 0 ); // ���� 0 ��
	sphere1->setGroup( 1 );      // ���� 1 ��
	sphere2->setGroup( 1 );
	sphere3->setGroup( 1 );
	box1->setGroup( 2 );         // ���� 2 ��
	box2->setGroup( 2 );
	box3->setGroup( 2 );

	// �����ɫ��ײ�鿪��
	bool switch1 = TRUE, // 1�飨���壩��1�飨���壩
		 switch2 = TRUE, // 1�飨���壩��2�飨���ӣ�
		 switch3 = TRUE, // 2�飨���ӣ���2�飨���ӣ�
		 switch4 = TRUE, // 0�飨���棩��1�飨���壩
		 switch5 = TRUE; // 0�飨���棩��2�飨���ӣ�

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

		// ��Ⱦ��ɫ
		texture->active(); // �����ȼ����ɫ����		
		sphere1->render();
		sphere2->render();
		sphere3->render();
		box1->render();
		box2->render();
		box3->render();

		// ��Ⱦ��������
		sceneMesh->render();
		
		// ��ʾ��ɫ��ײ�鿪����Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 40 );		
		text->drawText( "���ּ� 1~5 ������ײ��֮��Ŀ���" );
		text->setTextPos( 40, 65 );
		sprintf( string, "1��(����) <----> 1��(����) = %d", switch1 );
		text->drawText( string );
		text->setTextPos( 40, 90 );
		sprintf( string, "1��(����) <----> 2��(����) = %d", switch2 );
		text->drawText( string );
		text->setTextPos( 40, 115 );
		sprintf( string, "2��(����) <----> 2��(����) = %d", switch3 );
		text->drawText( string );
		text->setTextPos( 40, 140 );
		sprintf( string, "0��(����) <----> 1��(����) = %d", switch4 );
		text->drawText( string );
		text->setTextPos( 40, 165 );
		sprintf( string, "0��(����) <----> 2��(����) = %d", switch5 );
		text->drawText( string );

		// ��ʾ������ʾ��Ϣ
		text->setTextPos( 390, 400 );
		text->drawText( "W S A D = �������򣬿ո� = ��Ծ" );

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

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

		// ��ȡ��ǰ����ֵ
		key = input->getKey();

		// ������� 1-5 �������л���Ӧ����ײ��⿪��
		if( key == KEY_1 )
		{
			switch1 = !switch1;
			scene->setGroupCollisionFlag( 1, 1, switch1 );
		}
		else
		if( key == KEY_2 )
		{
			switch2 = !switch2;
			scene->setGroupCollisionFlag( 1, 2, switch2 );
		}
		else
		if( key == KEY_3 )
		{
			switch3 = !switch3;
			scene->setGroupCollisionFlag( 2, 2, switch3 );
		}
		else
		if( key == KEY_4 )
		{
			switch4 = !switch4;
			scene->setGroupCollisionFlag( 0, 1, switch4 );
		}
		else
		if( key == KEY_5 )
		{
			switch5 = !switch5;
			scene->setGroupCollisionFlag( 0, 2, switch5 );
		}

		// ������¿ո����������
		if( key == KEY_SPACE )
			sphere1->addForce( 0, 0, 10000, 0 );

		// ��ǧ��֮һ��Ϊ��λ���и���
		elapsedTime = (float)(time - lasttime);
		elapsedTime /= 1000;

		// ����������
		vec3_t vector;
		vector[0] = left * velocity;
		vector[1] = forward * velocity;
		vector[2] = gravity * elapsedTime;

		if( elapsedTime > 0 )
		{
			// ʩ����
			sphere1->addForce( vector[0], vector[1], vector[2] );
			lasttime = time;
		}
	}
	// ������Ϣ
	while( engine->dispatchMessage() && !input->getKeyState( KEY_ESCAPE ) );

	// �ͷŷ���Ķ���
	scene->releaseActor( physicsScene );               // �ͷ������ɫ
	scene->releaseActor( sphere1 );
	scene->releaseActor( sphere2 );
	scene->releaseActor( sphere3 );
	scene->releaseActor( box1 );
	scene->releaseActor( box2 );
	scene->releaseActor( box3 );	
	scene->releasePhysicsMaterial( physicsMaterial );  // �ͷ��������	
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