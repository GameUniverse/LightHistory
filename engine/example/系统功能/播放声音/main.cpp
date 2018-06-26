

#include "windows.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 播放声音演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightSound  *s1, *s2;
	LightText   *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 400;                // 窗口宽度
	engineDesc.displayMode.window.height  = 300;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 创建文字实例
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建声音对象
	LightSoundDesc soundDesc;
	s1 = engine->createSound( soundDesc );
	s2 = engine->createSound( soundDesc );

	// 将声音文件读取到内存中
	s1->load( "..\\resource\\sound\\start.wav" );
	s2->load( "..\\resource\\sound\\destory.wav" );
	// 可以同时播放多个声音（支持混音）
	s1->play();
	s2->play();

	// 显示提示信息
	text->color( 0, 255, 0 );
	text->setTextPos( 138, 122 );
	text->drawText( "同时播放多个声音......" );
	engine->swapBuffers();

	_sleep( 6000 );

	// 停止播放
	s1->stop();
	s2->stop();

	// 释放分配的对象
	engine->releaseText( text );  // 释放文字实例
	engine->releaseSound( s1 );   // 释放声音对象
	engine->releaseSound( s2 );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return(0);
}