

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 碰撞组演示程序
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
	int  mode = 0;        // 控制模式
	float velocity = 300; // 移动速度
	vec3_t rotate = { 0, 0, 0 };
	DWORD lasttime = 0;

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

	// 将静态网格文件读入内存
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\ground\\ground.3ds" );

	// 创建天空盒
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // 天空类型
	VEC3( skyDesc.box.size, 64, 64, 64 );            // 天空盒大小
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

	// 创建物理材质
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // 弹力系数（缺省值为 0.5）
	physicsMaterialDesc.staticFriction   = 35;  // 静态磨擦力系数（缺省值为 0.5）
	physicsMaterialDesc.dynamicFriction  = 1;   // 动态磨擦力系数（缺省值为 0.5）
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// 读取角色纹理
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );

	// 创建球体1
	LightActorDesc actorDesc;	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_SPHERE; // 角色类型
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.pos, 0, -25, 20 );     // 角色位置
	actorDesc.sphere.radius = 2;         // 球体半径
	actorDesc.quality_slices = 15;       // 球体显示品质
	actorDesc.quality_stacks = 15;
	VEC3( actorDesc.rotate, 1.0f, 1.0f, 0.0f ); // 旋转参数（旋转轴）
	actorDesc.angle = 45;                // 旋转参数（旋转角度）
	actorDesc.mass = 1.0;                // 角色质量
	actorDesc.hide = FALSE;              // 隐藏标志
	// 设置几何体物理材质	
	actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	sphere1 = scene->createActor( actorDesc );
	// 创建球体2
	VEC3( actorDesc.pos, -10, -25, 20 );
	sphere2 = scene->createActor( actorDesc );
	// 创建球体3
	VEC3( actorDesc.pos, 10, -25, 20 );
	sphere3 = scene->createActor( actorDesc );

	// 创建盒子1
	actorDesc.type = LIGHT_SHAPE_BOX;    // 角色类型	
	VEC3( actorDesc.pos, 0, -10, 20 );    // 角色位置
	VEC3( actorDesc.box.size, 4, 4, 4 ); // 盒子大小
	VEC3( actorDesc.rotate, 0.0f, 0.0f, 1.0f ); // 旋转参数（旋转轴）
	actorDesc.angle = 0;                // 旋转参数（旋转角度）	
	box1 = scene->createActor( actorDesc );
	// 创建盒子2
	VEC3( actorDesc.pos, -10, -10, 20 );
	box2 = scene->createActor( actorDesc );
	// 创建盒子3
	VEC3( actorDesc.pos, 10, -10, 20 );
	box3 = scene->createActor( actorDesc );

	// 创建物理场景
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // 角色类型
	actorDesc.mesh.triangleMesh = sceneMesh->createTriangleMesh();		
	actorDesc.physicsMaterialIndex = 0; // 使用缺省材质
	physicsScene = scene->createActor( actorDesc );

	// 设置角色碰撞组	
	physicsScene->setGroup( 0 ); // 地面 0 组
	sphere1->setGroup( 1 );      // 球体 1 组
	sphere2->setGroup( 1 );
	sphere3->setGroup( 1 );
	box1->setGroup( 2 );         // 盒子 2 组
	box2->setGroup( 2 );
	box3->setGroup( 2 );

	// 定义角色碰撞组开关
	bool switch1 = TRUE, // 1组（球体）和1组（球体）
		 switch2 = TRUE, // 1组（球体）和2组（盒子）
		 switch3 = TRUE, // 2组（盒子）和2组（盒子）
		 switch4 = TRUE, // 0组（地面）和1组（球体）
		 switch5 = TRUE; // 0组（地面）和2组（盒子）

	// 设置摄像机位置和方向	
	camera->lookAt( 0, -100, 50,  0, 0, 0,  0, 0, 1 );

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

		// 渲染角色
		texture->active(); // （首先激活角色纹理）		
		sphere1->render();
		sphere2->render();
		sphere3->render();
		box1->render();
		box2->render();
		box3->render();

		// 渲染场景网格
		sceneMesh->render();
		
		// 显示角色碰撞组开关信息
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 40 );		
		text->drawText( "数字键 1~5 控制碰撞组之间的开关" );
		text->setTextPos( 40, 65 );
		sprintf( string, "1组(球体) <----> 1组(球体) = %d", switch1 );
		text->drawText( string );
		text->setTextPos( 40, 90 );
		sprintf( string, "1组(球体) <----> 2组(盒子) = %d", switch2 );
		text->drawText( string );
		text->setTextPos( 40, 115 );
		sprintf( string, "2组(盒子) <----> 2组(盒子) = %d", switch3 );
		text->drawText( string );
		text->setTextPos( 40, 140 );
		sprintf( string, "0组(地面) <----> 1组(球体) = %d", switch4 );
		text->drawText( string );
		text->setTextPos( 40, 165 );
		sprintf( string, "0组(地面) <----> 2组(盒子) = %d", switch5 );
		text->drawText( string );

		// 显示操作提示信息
		text->setTextPos( 390, 400 );
		text->drawText( "W S A D = 滚动方向，空格 = 跳跃" );

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

		// 更新显示
		engine->swapBuffers();

		// 处理玩家输入指令
		DWORD time;
		unsigned int key;

		// 查询当前系统时间
		time = engine->getTickCount();

		// 防止时间计数器溢出
		if( time < lasttime )
			lasttime = time;

		// 移动角色控制对象
		float gravity = -9.8f; // 重力
		float elapsedTime;    // 从最后一次更新以来消逝的时间
		float forward = 0, left = 0;

		// 控制球的运动方向
		if( input->getKeyState( KEY_UP ) || input->getKeyState( KEY_W ) )
			forward = 1;
		if( input->getKeyState( KEY_DOWN ) || input->getKeyState( KEY_S ) )
			forward = -1;
		if( input->getKeyState( KEY_LEFT ) || input->getKeyState( KEY_A ) )
			left = -1;
		if( input->getKeyState( KEY_RIGHT ) || input->getKeyState( KEY_D ) )
			left = 1;

		// 读取当前按键值
		key = input->getKey();

		// 如果按下 1-5 键，则切换对应的碰撞检测开关
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

		// 如果按下空格键，则跳起
		if( key == KEY_SPACE )
			sphere1->addForce( 0, 0, 10000, 0 );

		// 以千分之一秒为单位进行更新
		elapsedTime = (float)(time - lasttime);
		elapsedTime /= 1000;

		// 计算力向量
		vec3_t vector;
		vector[0] = left * velocity;
		vector[1] = forward * velocity;
		vector[2] = gravity * elapsedTime;

		if( elapsedTime > 0 )
		{
			// 施加力
			sphere1->addForce( vector[0], vector[1], vector[2] );
			lasttime = time;
		}
	}
	// 配送消息
	while( engine->dispatchMessage() && !input->getKeyState( KEY_ESCAPE ) );

	// 释放分配的对象
	scene->releaseActor( physicsScene );               // 释放物理角色
	scene->releaseActor( sphere1 );
	scene->releaseActor( sphere2 );
	scene->releaseActor( sphere3 );
	scene->releaseActor( box1 );
	scene->releaseActor( box2 );
	scene->releaseActor( box3 );	
	scene->releasePhysicsMaterial( physicsMaterial );  // 释放物理材质	
	engine->releaseScene( scene );                     // 释放物理场景所占内存
	engine->releaseMesh( sceneMesh );                  // 释放静态网格对象
	engine->releaseTexture( texture );                 // 释放纹理
	engine->releaseSky( sky );	                       // 释放天空盒对象
	engine->releaseInput( input );                     // 释放输入接口
	engine->releaseCamera( camera );                   // 释放摄像机对象
	engine->releaseText( text );                       // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}