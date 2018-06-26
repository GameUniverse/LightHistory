

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


LightEngine  *engine;
LightImage   *desktop;
LightImage   *image;	
LightText    *text;
bool         work; // 线程工作标志

// 渲染线程函数
DWORD WINAPI ThreadProc( LPVOID lpParameter )
{
	// 绑定渲染目标
	engine->attachRender();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示桌面
		desktop->render( 0, 0 );

		// 正常显示图像
		image->render( 25, 25 );		

		// 显示提示信息
		text->color( 255, 0, 0 );
		text->setTextPos( 295, 350 );
		text->drawText( "正在线程中渲染......" );

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 255, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );
        
		// 更新显示
		engine->swapBuffers();
	}
	// 渲染循环
	while( work );

	return 0;
}

// 线程中渲染演示程序
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
	
	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建图像对象
	LightImageDesc imageDesc;
	desktop = engine->createImage( imageDesc );
	desktop->load("..\\resource\\image\\sweet_flower.bmp");
	image = engine->createImage( imageDesc );
	image->load("..\\resource\\image\\a.bmp");

	// 分离渲染目标
	engine->detachRender();

	// 创建渲染线程
	HANDLE thread;
	DWORD  threadId;
	work = TRUE;
	thread = CreateThread( NULL, 0, ThreadProc, NULL, 0, &threadId );
	//WaitForSingleObject( thread, 5000 );

	do
	{		
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 结束渲染线程
	work = FALSE;
	_sleep( 100 );
	CloseHandle( thread );

	// 释放分配的对象	
	engine->releaseText( text );      // 释放文字对象
	engine->releaseImage( desktop );  // 释放图像对象
	engine->releaseImage( image );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}
