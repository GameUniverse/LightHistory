

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 角色控制演示程序
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
	// 碰撞标志位
	DWORD collisionFlags = 0;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 使用 3DSMAX 坐标系统(Z->UP）
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// 启用关键色（默认禁用）
	engine->enable( LIGHT_KEY_COLOR );
	// 设置关键色（透明色，默认值为黑色 0，0，0 ）
	engine->setKeyColor( 255, 0, 0 );

	// 关闭垂直同步（默认开启）
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );	

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建静态网格对象
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// 创建物理网格对象
	physicsSceneMesh = engine->createMesh( meshDesc );
	physicsSceneMesh->load( "..\\resource\\scene\\hill\\hill_physics.3DS" );
	triangleMesh = physicsSceneMesh->createTriangleMesh();

	// 创建物理场景
	LightActorDesc actorDesc;	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // 角色类型
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0; // 使用缺省材质
	physicsScene = scene->createActor( actorDesc );

	// 创建物理材质
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // 弹力（缺省值为 0.5）
	physicsMaterialDesc.staticFriction   = 35;  // 静态磨擦力（缺省值为 0.5）
	physicsMaterialDesc.dynamicFriction  = 1;   // 动态磨擦力（缺省值为 0.5）
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// 创建球体
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_SPHERE; // 角色类型
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.pos, 8, -24, 50 );     // 角色位置
	actorDesc.sphere.radius = 0.8;         // 球体半径
	actorDesc.quality_slices = 15;       // 球体显示品质
	actorDesc.quality_stacks = 15;
	VEC3( actorDesc.rotate, 1.0f, 1.0f, 0.0f ); // 旋转参数（旋转轴）
	actorDesc.angle = 45;                // 旋转参数（旋转角度）
	actorDesc.mass = 1.0;                // 角色质量
	actorDesc.hide = FALSE;              // 隐藏标志	
	actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	actor = scene->createActor( actorDesc );

	// 创建一个角色控制器
	LightCharacterDesc characterDesc;
	memset( &characterDesc, 0, sizeof(characterDesc) );
	characterDesc.type = LIGHT_CHARACTER_CAPSULE; // 角色控制器类型（胶囊）
	VEC3( characterDesc.position, 0, 13, 25 );     // 角色控制器位置
	characterDesc.capsule.radius = 0.65;             // 胶囊半径
	characterDesc.capsule.height = 2.5;             // 胶囊高度
	character = scene->createCharacter( characterDesc );

	// 创建天空盒
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // 天空类型
	VEC3( skyDesc.box.size, 64, 64, 64 );            // 天空盒大小	
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

	// 设置摄像机位置和方向
	camera->lookAt( -23, 8, 5,  48, 40, 5,  0, 0, 1 );

	// 设置最后更新时间
	lasttime = engine->getTickCount();

	do
	{
		// 更新物理引擎状态
		engine->updatePhysics();

		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染天空盒
		sky->render();

		// 渲染场景（首先激活长方体纹理）
		texture->active();
		actor->render();

		// 渲染场景网格
		sceneMesh->render();

		// 显示角色控制器
		texture->active();
		character->render();

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// 显示碰撞标志
		text->setTextPos( 40, 350 );
		//LIGHT_CHARACTER_COLLISION_SIDES = (1<<0), // 角色侧面发生了碰撞
		//LIGHT_CHARACTER_COLLISION_UP    = (1<<1), // 角色上面发生了碰撞
		//LIGHT_CHARACTER_COLLISION_DOWN  = (1<<2), // 角色下面发生了碰撞
		if( collisionFlags & 4 )
			text->drawText( "角色落地" );
		else
			text->drawText( "角色悬空" );

		// 更新显示
		engine->swapBuffers();

		// 处理玩家输入指令
		float mouseAgility = 500; // 鼠标指针移动速度
        POINT point;
		int cx, cy;		
		vec3_t upright;
		RECT rect;
		DWORD time;
		unsigned int key;

		// 查询当前系统时间
		time = engine->getTickCount();

		// 防止时间计数器溢出
		if( time < lasttime )
			lasttime = time;

		// 根据光标位置计算摄像机旋转角度，
		// 并将光标位置设置为窗口中心
		input->getCursorPos( &point );
		GetClientRect( engine->getWindowHandle(), &rect );
		cx = (rect.right - rect.left) / 2;
		cy = (rect.bottom - rect.top) / 2;
		//input->SetCursorPos( cx, cy );
		rotate[0] += (float)(point.x - cx) / mouseAgility;
		rotate[1] -= (float)(point.y - cy) / mouseAgility;
		rotate[2] = 0;

		// 限制摄像机旋转角度
		if( rotate[0] > 2 * LIGHT_PI )
			rotate[0] -= 2 * LIGHT_PI;
		if( rotate[0] < 0 )
			rotate[0] += 2 * LIGHT_PI;
		if( rotate[1] > 0.375 * LIGHT_PI )
			rotate[1] = 0.375f * LIGHT_PI;
		if( rotate[1] < -0.425 * LIGHT_PI )
			rotate[1] = -0.425f * LIGHT_PI;

		// 移动角色控制对象
		float velocity = 12; // 移动速度
		float gravity = -9.8f; // 重力
		float elapsedTime;   // 从最后一次更新以来消逝的时间
		float forward = 0, left = 0;

		if( input->getKeyState( KEY_UP ) || input->getKeyState( KEY_W ) )
			forward = 1;
		if( input->getKeyState( KEY_DOWN ) || input->getKeyState( KEY_S ) )
			forward = -1;
		if( input->getKeyState( KEY_LEFT ) || input->getKeyState( KEY_A ) )
			left = 1;
		if( input->getKeyState( KEY_RIGHT ) || input->getKeyState( KEY_D ) )
			left = -1;

		// 以千分之一秒为单位进行更新
		elapsedTime = time - lasttime;
		elapsedTime /= 1000;

		// 查询角色控制器位置
		//pos = character->getPosition();

		// 计算摄像机参数
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
	// 配送消息
	while( engine->dispatchMessage() && !input->getKeyState( KEY_ESCAPE ) );

	// 释放分配的对象
	scene->releaseActor( physicsScene );               // 释放物理角色
	scene->releaseActor( actor );
	scene->releasePhysicsMaterial( physicsMaterial );  // 释放物理材质
	sceneMesh->releaseTriangleMesh( triangleMesh );    // 释放物理网格
	engine->releaseScene( scene );                     // 释放物理场景所占内存
	engine->releaseMesh( sceneMesh );                  // 释放静态网格对象
	engine->releaseMesh( physicsSceneMesh );
	engine->releaseTexture( texture );                 // 释放纹理
	engine->releaseSky( sky );	                       // 释放天空盒对象
	engine->releaseInput( input );                     // 释放输入接口
	engine->releaseCamera( camera );                   // 释放摄像机对象
	engine->releaseText( text );                       // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}