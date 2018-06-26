

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 基本图形演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine   *engine;
	LightTexture  *ground;
	LightBrush    *brush;
	LightCamera   *camera;
	LightText     *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 400;                // 窗口宽度
	engineDesc.displayMode.window.height  = 300;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建画笔对象
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	// 创建纹理对象
	LightTextureDesc textureDesc;
	ground = engine->createTexture( textureDesc );
	ground->load( "..\\resource\\image\\wood.dds" );

	// 设置摄像机参数
	camera->lookAt( 0, 6.8, 3.8,  0, 0, 0.5,  0, 0, 1 );
			
	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染一个多边形
		vertex_t vertex[4];
		VEC3( vertex[0].position, -2.5,  2.5, 0 ); // 顶点坐标
		VEC3( vertex[1].position, -2.5, -2.5, 0 );
		VEC3( vertex[2].position,  2.5, -2.5, 0 );
		VEC3( vertex[3].position,  2.5,  2.5, 0 );
		VEC3( vertex[0].normal, 0, 0, 1 ); // 法线
		VEC3( vertex[1].normal, 0, 0, 1 );
		VEC3( vertex[2].normal, 0, 0, 1 );
		VEC3( vertex[3].normal, 0, 0, 1 );
		VEC2( vertex[0].texcoord, 0, 0 ); // 纹理坐标
		VEC2( vertex[1].texcoord, 0, 1 );
		VEC2( vertex[2].texcoord, 1, 1 );
		VEC2( vertex[3].texcoord, 1, 0 );
		ground->active(); // 激活多边形纹理
		brush->polygon( vertex, 4 ); // 渲染多边形

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 245 );
		text->drawText( fps );
        
		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象	
	engine->releaseTexture( ground );  // 释放纹理对象	
	engine->releaseBrush( brush );     // 释放画笔对象	
	engine->releaseText( text );       // 释放文字对象	 
	engine->releaseCamera( camera );   // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;	
}