

#include "windows.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 播放视频演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightVideo  *video;
	LightText   *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 创建文字实例
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建视频(音频)对象
	LightVideoDesc videoDesc;
	video = engine->createVideo( videoDesc );

	// 打开视频(音频)文件
	video->open("..\\resource\\video\\lake.mpg");

	// 播放
	video->play();

	// 等待视频播放完毕
	do
	{
	} while( video->getState() && engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseVideo( video );  // 释放视频(音频)对象
	engine->releaseText( text );    // 释放文字实例

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return(0);
}