

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine *engine;
LightScene  *scene;
LightCamera *camera;
LightText *text;
LightTexture *texture;
LightActor *box;
LightActor *plane;
LightPhysicsMaterial  *physicsMaterial;

// 盒子演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
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
	scene = engine->createScene( sceneDesc );

	// 读取盒子纹理
	texture->load( "..\\resource\\image\\wood.jpg" );

	// 创建物理材质
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8; // 弹力系数（缺省值为 0.5）
	physicsMaterialDesc.staticFriction   = 35;  // 静态磨擦力系数（缺省值为 0.5）
	physicsMaterialDesc.dynamicFriction  = 1;   // 动态磨擦力系数（缺省值为 0.5）
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	// 创建一个盒子
	LightActorDesc desc;
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_BOX;
	desc.dynamic = TRUE;
	VEC3( desc.pos, 0.0f, 20.0f, 0.0f );
	VEC3( desc.box.size, 2.5, 2.5, 2.5 );
	VEC3( desc.rotate, 1.0f, 1.0f, 0.0f );
	desc.angle = 45;
	desc.mass = 0.00000001;
	desc.hide = FALSE;	
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex(); // 设置盒子物理材质
	box = scene->createActor( desc );

	// 创建地面（一个平面）
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_PLANE;
	desc.dynamic = FALSE;
	VEC3( desc.plane.normal, 0.0f, 1.0f, 0.0f );
	desc.plane.distance = 0.0f;
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex(); // 设置地面物理材质
	plane = scene->createActor( desc );

	// 设置摄像机
	camera->lookAt( 0, 10, 15,  0, 4, 0,  0, 1, 0 );

	// 激活当前纹理
	texture->active();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// 更新物理状态
		engine->updatePhysics();
		
		// 显示长方体
		box->render();
				
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
	scene->releaseActor( box );         // 释放盒子、地面和物理材质
	scene->releaseActor( plane );
	scene->releasePhysicsMaterial( physicsMaterial );	
	engine->releaseScene( scene );      // 释放物理场景对象	
	engine->releaseTexture( texture );  // 释放纹理对象	
	engine->releaseCamera( camera );    // 释放摄像机对象	
	engine->releaseText( text );        // 释放文字对象	

	// 释放光线引擎实例
	LightEngineRelease( engine );
	
	return 0;
}