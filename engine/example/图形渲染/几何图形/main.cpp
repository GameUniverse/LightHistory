

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 几何图形演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightBrush  *brush;
	LightText   *text;

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

	// 创建画笔对象
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );	

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 设置画图颜色
	    brush->color( 255, 0, 0 );
		// 画点
		brush->point2D( 150, 75 );
		// 画线段
		brush->color( 0, 255, 0 );
		brush->line2D( 200, 50, 250, 100 );
		// 画矩形
		brush->color( 0, 0, 255 );
		brush->rectangle2D( 125, 125, 275, 225 );

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
	engine->releaseText( text );    // 释放文字对象
	engine->releaseBrush( brush );  // 释放画笔对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;	
}