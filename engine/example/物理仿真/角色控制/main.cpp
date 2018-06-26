

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��ɫ������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine           *engine;
	LightScene            *scene;
	LightCamera           *camera;
	LightCharacter        *character;
	LightMesh             *sceneMesh;
	LightMesh             *physicsSceneMesh;
	LightSky              *sky;
	LightPhysicsMaterial  *physicsMaterial;
	LightTriangleMesh     *triangleMesh;
	LightActor            *physicsScene;
	LightActor            *actor;
	LightTexture          *texture;
	LightInput            *input;
	LightText             *text;
	LightTextureDesc  textureDesc;
	char string[150];
	vec3_t rotate = { 0, 0, 0 };
	vec3_t *pos, move, eye, center, up;
	DWORD lasttime = 0;
	// ��ײ��־λ
	DWORD collisionFlags = 0;

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

	// ����һ������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// ������̬�������
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// ���������������
	physicsSceneMesh = engine->createMesh( meshDesc );
	physicsSceneMesh->load( "..\\resource\\scene\\hill\\hill_physics.3DS" );
	triangleMesh = physicsSceneMesh->createTriangleMesh();

	// ����������
	LightActorDesc actorDesc;	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // ��ɫ����
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0; // ʹ��ȱʡ����
	physicsScene = scene->createActor( actorDesc );

	// �����������
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // ������ȱʡֵΪ 0.5��
	physicsMaterialDesc.staticFriction   = 35;  // ��̬ĥ������ȱʡֵΪ 0.5��
	physicsMaterialDesc.dynamicFriction  = 1;   // ��̬ĥ������ȱʡֵΪ 0.5��
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// ��������
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_SPHERE; // ��ɫ����
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.pos, 8, -24, 50 );     // ��ɫλ��
	actorDesc.sphere.radius = 0.8;         // ����뾶
	actorDesc.quality_slices = 15;       // ������ʾƷ��
	actorDesc.quality_stacks = 15;
	VEC3( actorDesc.rotate, 1.0f, 1.0f, 0.0f ); // ��ת��������ת�ᣩ
	actorDesc.angle = 45;                // ��ת��������ת�Ƕȣ�
	actorDesc.mass = 1.0;                // ��ɫ����
	actorDesc.hide = FALSE;              // ���ر�־	
	actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	actor = scene->createActor( actorDesc );

	// ����һ����ɫ������
	LightCharacterDesc characterDesc;
	memset( &characterDesc, 0, sizeof(characterDesc) );
	characterDesc.type = LIGHT_CHARACTER_CAPSULE; // ��ɫ���������ͣ����ң�
	VEC3( characterDesc.position, 0, 13, 25 );     // ��ɫ������λ��
	characterDesc.capsule.radius = 0.65;             // ���Ұ뾶
	characterDesc.capsule.height = 2.5;             // ���Ҹ߶�
	character = scene->createCharacter( characterDesc );

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

	// ���������λ�úͷ���
	camera->lookAt( -23, 8, 5,  48, 40, 5,  0, 0, 1 );

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

		// ��Ⱦ���������ȼ����������
		texture->active();
		actor->render();

		// ��Ⱦ��������
		sceneMesh->render();

		// ��ʾ��ɫ������
		texture->active();
		character->render();

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// ��ʾ��ײ��־
		text->setTextPos( 40, 350 );
		//LIGHT_CHARACTER_COLLISION_SIDES = (1<<0), // ��ɫ���淢������ײ
		//LIGHT_CHARACTER_COLLISION_UP    = (1<<1), // ��ɫ���淢������ײ
		//LIGHT_CHARACTER_COLLISION_DOWN  = (1<<2), // ��ɫ���淢������ײ
		if( collisionFlags & 4 )
			text->drawText( "��ɫ���" );
		else
			text->drawText( "��ɫ����" );

		// ������ʾ
		engine->swapBuffers();

		// �����������ָ��
		float mouseAgility = 500; // ���ָ���ƶ��ٶ�
        POINT point;
		int cx, cy;		
		vec3_t upright;
		RECT rect;
		DWORD time;
		unsigned int key;

		// ��ѯ��ǰϵͳʱ��
		time = engine->getTickCount();

		// ��ֹʱ����������
		if( time < lasttime )
			lasttime = time;

		// ���ݹ��λ�ü����������ת�Ƕȣ�
		// �������λ������Ϊ��������
		input->getCursorPos( &point );
		GetClientRect( engine->getWindowHandle(), &rect );
		cx = (rect.right - rect.left) / 2;
		cy = (rect.bottom - rect.top) / 2;
		//input->SetCursorPos( cx, cy );
		rotate[0] += (float)(point.x - cx) / mouseAgility;
		rotate[1] -= (float)(point.y - cy) / mouseAgility;
		rotate[2] = 0;

		// �����������ת�Ƕ�
		if( rotate[0] > 2 * LIGHT_PI )
			rotate[0] -= 2 * LIGHT_PI;
		if( rotate[0] < 0 )
			rotate[0] += 2 * LIGHT_PI;
		if( rotate[1] > 0.375 * LIGHT_PI )
			rotate[1] = 0.375f * LIGHT_PI;
		if( rotate[1] < -0.425 * LIGHT_PI )
			rotate[1] = -0.425f * LIGHT_PI;

		// �ƶ���ɫ���ƶ���
		float velocity = 12; // �ƶ��ٶ�
		float gravity = -9.8f; // ����
		float elapsedTime;   // �����һ�θ����������ŵ�ʱ��
		float forward = 0, left = 0;

		if( input->getKeyState( KEY_UP ) || input->getKeyState( KEY_W ) )
			forward = 1;
		if( input->getKeyState( KEY_DOWN ) || input->getKeyState( KEY_S ) )
			forward = -1;
		if( input->getKeyState( KEY_LEFT ) || input->getKeyState( KEY_A ) )
			left = 1;
		if( input->getKeyState( KEY_RIGHT ) || input->getKeyState( KEY_D ) )
			left = -1;

		// ��ǧ��֮һ��Ϊ��λ���и���
		elapsedTime = time - lasttime;
		elapsedTime /= 1000;

		// ��ѯ��ɫ������λ��
		//pos = character->getPosition();

		// �������������
		vec3_t vector;
		vector[0] = forward * velocity * elapsedTime;			
		vector[1] = left * velocity * 0.4f * elapsedTime;
		vector[2] = gravity * elapsedTime;
		/*camera->Rotate( pos, rotate, 230, move, FALSE, player.direction, player.eyes, player.up );*/

		//vec3_t move;
		//float s1 = (float)player.velocity * ( time - player.lasttime ) * 0.001f;
		//move[1] = s1 * player.forward;
		//move[0] = s1 * 0.4 * player.right;
		//move[2] = g_vVelocity.y;
		//camera->Rotate( player.pos, rotate, 230, move, FALSE, player.direction, player.eyes, player.up );

		if( elapsedTime > 0 )
		{
			
			character->move( vector, 0.5, &collisionFlags, 1 );
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