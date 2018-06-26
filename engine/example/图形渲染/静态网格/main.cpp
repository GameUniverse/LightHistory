

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 静态网格演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightMesh   *mesh;
	LightInput  *input;
	LightText   *text;
	char string[100];
	float rotate = 0;
	DWORD lasttime = 0;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 关闭垂直同步（默认开启）
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建静态网格对象
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	mesh->load( "..\\resource\\mesh\\digger\\digger.3ds" );
	
	camera->lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );
	//camera->LookAt(  0, 200, 1000,  0, 200, 0,  0, 1, 0 );

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示静态网格
		mesh->setGlobalOrientationAngleAxis( rotate, 0, 1, 0 );
		mesh->render();

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

		// 旋转静态网格
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			rotate -= ( time - lasttime ) * 0.02f;
			if( rotate < -360 )
				rotate = 0;
			lasttime = time;
		}

		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseMesh ( mesh );     // 释放静态网格对象
	engine->releaseInput( input );    // 释放输入接口
	engine->releaseText( text );      // 释放文字对象
	engine->releaseCamera( camera );  // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}