

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 动画图像演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *image;
	LightText *text;
	unsigned long lasttime;
	float rotate;

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

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建图像对象
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
		
	// 将图像文件读入内存
	image->speed( 100 );	
	image->load("..\\resource\\image\\flame\\flame1.tga");
	image->insertFrame( 0, 1 );	
	image->load("..\\resource\\image\\flame\\flame2.tga");
	image->insertFrame( 1, 1 );	
	image->load("..\\resource\\image\\flame\\flame3.tga");
	image->insertFrame( 2, 1 );
	image->load("..\\resource\\image\\flame\\flame4.tga");
	image->insertFrame( 3, 1 );
	image->load("..\\resource\\image\\flame\\flame5.tga");
	image->insertFrame( 4, 1 );
	image->load("..\\resource\\image\\flame\\flame6.tga");
	image->insertFrame( 5, 1 );
	image->load("..\\resource\\image\\flame\\flame7.tga");
	image->insertFrame( 6, 1 );
	image->load("..\\resource\\image\\flame\\flame8.tga");

	// 初始化时间变量
	rotate = 0.0;
	lasttime = engine->getTickCount();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染动画图像		
		image->render( 135, 0 );

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
	engine->releaseImage( image );  // 释放图像文件	
	engine->releaseText( text );    // 释放文字实例

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}