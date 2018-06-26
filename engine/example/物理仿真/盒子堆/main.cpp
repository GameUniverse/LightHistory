

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine *engine;
LightCamera *camera;
LightText *text;
LightTexture *texture;
LightPhysicsMaterial *physicsMaterial;
LightScene  *scene;
LightActor *actor[40];
LightActor *plane;

// 物理引擎演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int i;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );
	
	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建纹理对象
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建物理材质
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // 弹力系数（缺省值为 0.5）
	physicsMaterialDesc.staticFriction   = 35;  // 静态磨擦力系数（缺省值为 0.5）
	physicsMaterialDesc.dynamicFriction  = 1;   // 动态磨擦力系数（缺省值为 0.5）
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// 创建几何体
	texture->load( "..\\resource\\image\\wood.jpg" );
	LightActorDesc actorDesc;
	for( i=0; i<40; i++)
	{
		if( i < 30 )
			actorDesc.type = LIGHT_SHAPE_BOX;
		else
		if( i > 29 && i < 35)
		{
			actorDesc.type = LIGHT_SHAPE_SPHERE;
			actorDesc.sphere.radius = ( (float)rand() / ( RAND_MAX ) ) + 1;
		}
		else
		if( i > 34 && i< 40 )
		{
			actorDesc.type = LIGHT_SHAPE_CAPSULE;
			actorDesc.capsule.radius = 1;
			actorDesc.capsule.height = 2;
		}
		else
		if( i > 20 && i< 25 )
		{
			
		}

		actorDesc.dynamic = TRUE;
		actorDesc.quality_slices = 10;
		actorDesc.quality_stacks = 10;
		VEC3( actorDesc.box.size, ( (float)rand() / ( RAND_MAX / 2 ) )+1,( (float)rand() / ( RAND_MAX / 2 ) )+1, ( (float)rand() / ( RAND_MAX / 2 ) )+1 );
		VEC3( actorDesc.pos, ( (float)rand() / ( RAND_MAX / 8 ) )-4, ( (float)rand() / ( RAND_MAX / 80 ) )+20, ( (float)rand() / ( RAND_MAX / 8 ) )-4 );
		VEC3( actorDesc.rotate, ( (float)rand() / ( RAND_MAX / 4 ) )-2.0f, ( (float)rand() / ( RAND_MAX / 4 ) )-2.0f, ( (float)rand() / ( RAND_MAX / 4 ) )-2.0f );
		actorDesc.angle = ( (float)rand() / ( RAND_MAX / 90 ) )-5.0f;
		actorDesc.mass = 0.00000001f;
		actorDesc.hide = FALSE;
		// 设置几何体物理材质
		actorDesc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
		actor[i] = scene->createActor( actorDesc );
	}

	// 创建地面（一个平面）	
	memset( &actorDesc, 0, sizeof(actorDesc) );
	actorDesc.type = LIGHT_SHAPE_PLANE;
	VEC3( actorDesc.plane.normal, 0.0f, 1.0f, 0.0f );
	actorDesc.plane.distance = 0.0f;
	plane = scene->createActor( actorDesc );

	// 设置摄像机
	camera->lookAt( 0, 10, 20,  0, 2, 0,  0, 1, 0 );

	// 激活当前纹理
	texture->active();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// 更新物理状态
		engine->updatePhysics();
		
		// 显示长方体
		for( i=0; i<40; i++)
			actor[i]->render();		

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );
        
		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象	
	scene->releaseActor( plane );                      // 释放物理角色
	for( i=0; i<40; i++ )
		scene->releaseActor( actor[i] );	
	scene->releasePhysicsMaterial( physicsMaterial );  // 释放物理材质
	engine->releaseScene( scene );                     // 释放物理场景所占内存
	engine->releaseTexture( texture );                 // 释放纹理对象
	engine->releaseCamera( camera );                   // 释放摄像机对象
	engine->releaseText( text );                       // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}