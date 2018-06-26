

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 动画纹理演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine           *engine;
	LightCamera           *camera;
	LightMesh             *scene;
	LightSky              *sky;	
	LightTexture          *texture;
	LightText             *text;
	char string[100];
	int id;

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

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 将静态网格文件读入内存
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	scene = engine->createMesh( meshDesc );
	scene->load( "..\\resource\\scene\\pond\\pond.3ds" );

	// 获取动画纹理
	id = engine->getTextureID( "water00.tga" );
	texture = engine->getTexture( id );

	// 读取动画纹理
	texture->speed( 100 );
	texture->insertFrame( 0, 1 );
	texture->load("..\\resource\\image\\water\\water01.tga");
	texture->insertFrame( 1, 1 );
	texture->load("..\\resource\\image\\water\\water02.tga");
	texture->insertFrame( 2, 1 );
	texture->load("..\\resource\\image\\water\\water03.tga");
	texture->insertFrame( 3, 1 );
	texture->load("..\\resource\\image\\water\\water04.tga");
	texture->insertFrame( 4, 1 );
	texture->load("..\\resource\\image\\water\\water05.tga");
	texture->insertFrame( 5, 1 );
	texture->load("..\\resource\\image\\water\\water06.tga");
	texture->insertFrame( 6, 1 );
	texture->load("..\\resource\\image\\water\\water07.tga");

	texture->insertFrame( 7, 1 );
	texture->load("..\\resource\\image\\water\\water08.tga");
	texture->insertFrame( 8, 1 );
	texture->load("..\\resource\\image\\water\\water09.tga");
	texture->insertFrame( 9, 1 );
	texture->load("..\\resource\\image\\water\\water10.tga");
	texture->insertFrame( 10, 1 );
	texture->load("..\\resource\\image\\water\\water11.tga");
	texture->insertFrame( 11, 1 );
	texture->load("..\\resource\\image\\water\\water12.tga");
	texture->insertFrame( 12, 1 );
	texture->load("..\\resource\\image\\water\\water13.tga");
	texture->insertFrame( 13, 1 );
	texture->load("..\\resource\\image\\water\\water14.tga");
	texture->insertFrame( 14, 1 );
	texture->load("..\\resource\\image\\water\\water15.tga");

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

	// 设置摄像机位置和方向	
	camera->lookAt( 0, -130, 80,  0, 0, 0,  0, 0, 1 );

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染天空盒
		sky->render();

		// 渲染场景网格
		scene->render();

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象	
	engine->releaseSky( sky );        // 释放天空
	engine->releaseMesh( scene );     // 释放网络场景所占内存
	engine->releaseText( text );      // 释放文字对象
	engine->releaseCamera( camera );  // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}