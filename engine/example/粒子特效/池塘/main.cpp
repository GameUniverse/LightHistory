

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 池塘演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightWater *water;
	LightTerrain *terrain;
	LightTexture *texture[3];
	LightTextureDesc textureDesc;
	LightScene *scene;
	LightActor *plane;
	LightActor *box;
	LightTexture *wood;
	LightSky *sky;	
	LightText *text;

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

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	terrain = engine->NewTerrain();

	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建地面（一个平面）
	LightActorDesc desc;
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_PLANE;
	VEC3( desc.plane.normal, 0.0f, 1.0f, 0.0f );
	desc.plane.distance = 0.0f;
	plane = scene->createActor( desc );

	// 创建一个盒子
	wood = engine->createTexture( textureDesc );
	wood->load( "..\\resource\\image\\wood.dds" );
	desc.type = LIGHT_SHAPE_BOX;
	VEC3( desc.box.size, 20, 20, 40 );
	VEC3( desc.pos, 312, 212, 130 );
	VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
	desc.angle = 0.0f;
	desc.mass = 5;
	desc.hide = FALSE;	
	box = scene->createActor( desc );

	// 读入地形
	terrain = engine->NewTerrain();
	// 将地形纹理读入内存	
	for( int i=0; i<3; i++ )
		texture[i] = engine->createTexture( textureDesc );	
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
	terrain->SetLODFactor( 2.5, 25 ); // 高速度
	//terrain->SetLODFactor( 5, 50 ); // 高品质

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

	// 构建水面
	LightWaterDesc waterDesc;
	waterDesc.type = LIGHT_WATER_RECTANGLE;	
	VEC3( waterDesc.pos, 0, 0, 129 );
	waterDesc.rectangle.width = 1024;
	waterDesc.rectangle.height = 1024;
	waterDesc.normal = engine->createTexture( textureDesc );
	waterDesc.normal->load( "..\\resource\\image\\wavesbump.dds" );
	water = engine->createWater( waterDesc );

	// 设置摄像机参数
	camera->lookAt( 150, 150, 180,  512, 412, 0,  0, 0, 1 );

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示游戏场景

		// 显示天空盒
		sky->render();
		//显示地形		
		terrain->render();
		// 显示长方体
		wood->active();
		box->render();

		// 渲染反射图		
		water->begin( LIGHT_REFLECTION_MAP );
		    sky->render();
			terrain->render();
			wood->active();
			box->render();
		water->end();

		// 渲染折射图
		water->begin( LIGHT_REFRACTION_MAP );
 		    //sky->Render(); // 折射图不需要渲染天空盒
			terrain->render();
			wood->active();
			box->render();
		water->end();

		// 渲染水面
		water->render();

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 420 );
		text->drawText( fps );

		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseSky( sky );        // 释放天空盒对象
	engine->releaseText( text );      // 释放文字对象
	engine->releaseCamera( camera );  // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}