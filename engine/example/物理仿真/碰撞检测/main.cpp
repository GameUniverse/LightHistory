

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine   *engine;
LightScene    *scene;
LightCamera   *camera;
LightText     *text;
LightTexture  *texture;
LightActor    *a, *b;
LightActor    *plane;

bool collided = FALSE; // 碰撞标志

// 角色接触报告监听函数
void contactReportProc( LightActor * a1, LightActor * a2, unsigned long events )
{
	// 物体 a 和 b 发生碰撞，根据接触标志位执行相应的操作
	if( (a1 == a && a2 == b) || (a1 == b && a2 == a) )
	{
		// 当 a 和 b 开始接触（也即停止接触之前的第一次接触）
		if( events & LIGHT_NOTIFY_ON_START_TOUCH )
			collided = TRUE;
		else
			// 当 a 和 b 持续接触（保持接触状态）
			if( events & LIGHT_NOTIFY_ON_TOUCH )
				collided = TRUE;
			else
				// 当 a 和 b 停止接触（离开）
				if( events & LIGHT_NOTIFY_ON_END_TOUCH )
					collided = FALSE;
	}
}

// 碰撞检测演示程序
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

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建地面（一个平面）
	LightActorDesc desc;	
	desc.type = LIGHT_SHAPE_PLANE;
	VEC3( desc.plane.normal, 0.0f, 1.0f, 0.0f );
	desc.plane.distance = 0.0f;
	plane = scene->createActor( desc );

	// 创建长方体 a 和 b
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );	
	desc.type = LIGHT_SHAPE_BOX;
	desc.dynamic = TRUE;
	VEC3( desc.box.size, 2.0f, 2.0f, 2.0f );
	VEC3( desc.pos, 0.0f, 10.0f, 0.0f );
	VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
	desc.angle = 0.0f;
	desc.mass = 0.00001f;
	desc.hide = FALSE;	
	a = scene->createActor( desc );
	desc.type = LIGHT_SHAPE_BOX;
	desc.dynamic = TRUE;
	VEC3( desc.box.size, 2.0f, 2.0f, 2.0f );
	VEC3( desc.pos, 0.0f, 40.0f, 0.0f );
	VEC3( desc.rotate, 1.5f, 1.0f, 0.0f );
	desc.angle = 45.0f;	
	b = scene->createActor( desc );

	// 设置碰撞检测响应函数
	scene->setUserContactReport( contactReportProc );

	// 设置摄像机
	camera->lookAt( 0, 10, 15,  0, 2, 0,  0, 1, 0 );

	// 激活当前纹理
	texture->active();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// 碰撞标志复位
		//collided = FALSE;

		// 更新物理状态
		engine->updatePhysics();
		
		// 显示长方体 a 和 b
		a->render();
		b->render();

		// 显示提示信息
		text->setTextPos( 40, 368 );
		if( collided )
		{
			text->color( 255, 0, 0 );
			text->drawText( "A 和 B 发生碰撞" );
		}
		else
		{
			text->color( 0, 255, 0 );
			text->drawText( "A 和 B 没有碰撞" );
		}

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
	engine->releaseTexture( texture );  // 释放纹理对象
	scene->releaseActor( a );           // 释放物理对象
	scene->releaseActor( b );
	scene->releaseActor( plane );
	engine->releaseScene( scene );      // 释放物理场景对象
	engine->releaseText( text );        // 释放文字对象
	engine->releaseCamera( camera );    // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );
	
	return 0;
}