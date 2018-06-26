

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 游戏摇杆演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightInput  *input;
	LightText   *text;
	LightBrush  *brush;

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

	// 创建画笔对象
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	unsigned long key;
	POINT point;
	char str[100];

	// 等待用户按下游戏杆 A 键（立即模式）
	do
	{
		// 查询并显示游戏杆位置
		point.x = input->getKeyState( KEY_JOYSTICK_X );
		point.y = input->getKeyState( KEY_JOYSTICK_Y );
		sprintf(str, "游戏杆位置: %d, %d", point.x, point.y);
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		text->color( 255, 0, 0 );
		text->setTextPos( 130, 107 );
		text->drawText( str );
		int x, y;
		x = point.x / 164;
		y = point.y / 218;
		brush->color( 255, 255, 0 );
		brush->line2D( x - 10, y, x + 10, y );
		brush->line2D( x , y - 10, x, y + 10 );

		// 显示提示信息
		text->color( 0, 255, 0 );
		text->setTextPos( 135, 137 );
		text->drawText("请按游戏杆 A 键......");
		text->setTextPos( 80, 160 );
		text->drawText("（如果没有安装游戏杆，请按 ESC 键退出）");

		engine->swapBuffers();

		// 配送消息
		engine->dispatchMessage();
	} while( !input->getKeyState( KEY_JOYSTICK_BUTTON0 ) && !input->getKeyState( KEY_ESCAPE ) ); // 检查键 A 的状态（立即模式）
	   
	// 显示提示信息
	engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
	text->setTextPos( 140, 123 );
	text->drawText("请按游戏杆 B 键退出！");
	engine->swapBuffers();

	// 等待用户按下游戏杆 B 键（缓冲模式）
	do
	{
		// 获取按键
		key = input->getKey();

		// 配送消息
		engine->dispatchMessage();
	} while( key != KEY_JOYSTICK_BUTTON1 && key != KEY_ESCAPE ); // 检查键 A 的状态（缓冲模式）

	// 释放分配的对象
	engine->releaseBrush( brush );  // 释放画笔对象
	engine->releaseInput( input );  // 释放输入接口
	engine->releaseText( text );    // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}