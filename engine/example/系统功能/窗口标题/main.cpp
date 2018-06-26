

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 窗口标题演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightInput  *input;
	LightText   *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 400;                // 窗口宽度
	engineDesc.displayMode.window.height  = 300;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );
			
	// 显示提示信息
	text->color( 0, 255, 0 );
	text->setTextPos( 115, 122 );
	text->drawText("请按空格键改变窗口标题......");
	engine->swapBuffers();

	// 等待用户按下鼠标左键
	do
	{
	} while( input->getKey() != KEY_SPACE && engine->dispatchMessage() );

	// 改变窗口标题
	engine->setString( LIGHT_WINDOW_CAPTION, "欢迎使用光线引擎 LightEngine !" );
	   
	// 显示提示信息
	engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
	text->setTextPos( 145, 122 );
	text->drawText("请按 ENTER 返回！");
	engine->swapBuffers();

	// 等待用户按下 ENTER 键
	do
	{
	} while( !input->getKeyState(KEY_RETURN) && engine->dispatchMessage() );
		
	// 释放分配的对象
	engine->releaseInput( input );  // 释放输入接口
	engine->releaseText( text );  // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}