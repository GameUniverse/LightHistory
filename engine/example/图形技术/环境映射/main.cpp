

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 环境映射演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine   *engine;
	LightCamera   *camera;
	LightMesh     *mesh;
	LightText     *text;	
	LightSky      *sky;
	LightTexture  *texture;
	LightTextureDesc textureDesc;
	char          string[100];
	float         rotate = 0;
	DWORD         lasttime = 0;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );
	
	// 启用关键色
	engine->enable( LIGHT_KEY_COLOR );
	
	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );
	
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

	// 将静态网格文件读入内存
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\mesh\\digger\\digger.3ds" );

	// 创建立方体纹理	
	texture = engine->createTexture( textureDesc );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_X );
	texture->load( "..\\resource\\image\\camera\\cm_left.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_X );
	texture->load( "..\\resource\\image\\camera\\cm_right.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Y );
	texture->load( "..\\resource\\image\\camera\\cm_top.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Y );
	texture->load( "..\\resource\\image\\camera\\cm_bottom.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Z );
	texture->load( "..\\resource\\image\\camera\\cm_back.tga" );
	texture->channel( LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Z );
	texture->load( "..\\resource\\image\\camera\\cm_front.tga" );

	// 设置摄像机
	camera->lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示天空盒
		//sky->render();

		// 显示静态网格		
		mesh->setGlobalOrientationAngleAxis( rotate, 0, 1, 0 );
		texture->active();
		engine->enable( LIGHT_CUBE_MAP );
		mesh->render();
		engine->disable( LIGHT_CUBE_MAP );

		// 显示提示信息
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 220 );		

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// 旋转茶壶
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			rotate -= ( time - lasttime ) * 0.005f;
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
	engine->releaseTexture( texture );  // 释放立方体纹理
	engine->releaseMesh ( mesh );       // 释放静态网格对象
	engine->releaseSky( sky );	        // 释放天空对象
	engine->releaseText( text );        // 释放文字对象
	engine->releaseCamera( camera );    // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}