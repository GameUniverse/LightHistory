

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 雪演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;	
	LightCamera  *camera;
	LightMesh    *mesh;
	LightSky     *sky;	
	LightTexture *snowflake;
	LightWeather *weather;
	LightInput   *input;
	LightText    *text;
	LightTextureDesc textureDesc;
	char string[100];
	float angle = 0;
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

	// 启用关键色（默认禁用）
	engine->enable( LIGHT_KEY_COLOR );
	// 设置关键色（透明色，默认值为黑色 0，0，0 ）
	engine->setKeyColor( 255, 0, 0 );

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
	mesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

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

	// 创建雪花纹理
	snowflake = engine->createTexture( textureDesc );
	snowflake->load( "..\\resource\\particle\\snowflake.bmp" );

	// 创建雪天气
	LightWeatherDesc weatherDesc;
	memset( &weatherDesc, 0, sizeof(weatherDesc) );
	weatherDesc.type = LIGHT_WEATHER_SNOW;
	weatherDesc.numparticle = 2010;
	VEC3( weatherDesc.box, 200, 200, 200 );
	VEC3( weatherDesc.position, 0.0f, -30.0f, -150.0f );
	weatherDesc.drop_velocity_min = 0.02f;
	weatherDesc.drop_velocity_max = 0.52f;
	VEC3( weatherDesc.wind, 0, 0, 0 );
	weather = engine->createWeather( weatherDesc );

	// 设置摄像机位置和方向
	camera->lookAt( 0, 0, 5,  -10, -5, 8,  0, 0, 1 );

	do
	{
		// 更新物理引擎状态
		engine->updatePhysics();

		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染天空盒
		sky->render();

		// 渲染静态网格
		mesh->render();

		// 渲染雪天气
		snowflake->active();
		weather->render();

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
	engine->releaseTexture( snowflake );  // 释放雪花纹理
	engine->releaseWeather( weather );    // 释放雪天气
	engine->releaseSky( sky );            // 释放天空对象
	engine->releaseMesh ( mesh );         // 释放静态网格对象
	engine->releaseInput( input );        // 释放输入接口	
	engine->releaseText( text );          // 释放文字对象
	engine->releaseCamera( camera );      // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}