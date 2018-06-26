

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 渲染地形演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine      *engine;
	LightCamera      *camera;
	LightTerrain     *terrain;
	LightTexture     *texture[3];
	LightSky         *sky;	
	LightText        *text;
	LightTextureDesc textureDesc;
	vec3_t start = { 100, 100, 50 };
	vec3_t end   = { 1000, 1000, 50  };
	float x, y, z, step = 0.05f;
	unsigned long time, lasttime;
	float rotate;
	int i;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 使用 3DSMAX 坐标系
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 读入地形
	terrain = engine->NewTerrain();
	for( i=0; i<3; i++ )
		texture[i] = engine->createTexture( textureDesc );
	// 将地形纹理读入内存	
	texture[0]->load( "..\\resource\\terrain\\grass.bmp" );
	texture[1]->load( "..\\resource\\terrain\\stone.bmp" );
	texture[2]->load( "..\\resource\\terrain\\shadow.tga" );	
	for( i=0; i<3; i++ )
		terrain->SetTexture( i, texture[i] );
	// 设置地形瓷砖大小（宽度和高度）
	terrain->setTile( 32, 32 );
	// 将地形数据读入内存
	//terrain->load( "..\\resource\\terrain\\map1024.raw", 0, 1025, 1025, 8 );
	terrain->load( "..\\resource\\terrain\\height.raw", 0, 1025, 1025, 16 );
	// 设置地形显示品质
	//terrain->SetLODFactor( 2.5, 25 ); // 高速度
	terrain->SetLODFactor( 5, 50 ); // 高品质

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
	
	// 初始化时间变量
	rotate = 0.0;
	lasttime = engine->getTickCount();

	// 初始化摄像机位置
	x = start[0];
	y = start[1];
	z = start[2];
	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// 设置摄像机
		z = terrain->GetHeight( x, y ) + 25;
		camera->lookAt( x, y, z, end[0], end[1], end[2], 0, 0, 1 );
		
		// 显示天空盒
		sky->render();

		//显示地形
		//terrain->RenderMode( 0 );
		terrain->render();

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );

		// 显示提示信息
		sprintf( fps, "三角形数: %d", terrain->GetTrianglesCount() );
		text->setTextPos( 40, 380 );
		text->drawText( fps );
		
		// 计算图像旋转角度
		time = engine->getTickCount();
		rotate += ( time - lasttime ) * 0.025f;
		lasttime = time;
		if( rotate > 360 )
			rotate -= 360;

		// 计算摄像机路径
		if( x < end[0]-100 )
			x += step;
		else
			x = start[0];
		if( z < end[2]-100 )
			z += step;
		else
			z = start[2];

        // 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseSky( sky );        // 释放天空对象
	//terrain = engine->NewTerrain(); // 释放地形对象
	for( i=0; i<3; i++ )              // 释放地形纹理
		engine->releaseTexture( texture[i] );
	engine->releaseText( text );      // 释放文字对象
	engine->releaseCamera( camera );  // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}