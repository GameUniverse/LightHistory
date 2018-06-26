

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 键盘鼠标演示程序
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

	// 设置窗口标题
	engine->setString( LIGHT_WINDOW_CAPTION, "键盘鼠标" );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 按键定义
	// KEY_MOUSE_BUTTON0  鼠标左键
	// KEY_MOUSE_BUTTON1  鼠标右键
	// KEY_MOUSE_BUTTON2  鼠标中键
	// KEY_MOUSE_X  鼠标水平坐标
	// KEY_MOUSE_Y  鼠标垂直坐标
	// KEY_MOUSE_Z  鼠标滚轮坐标

	unsigned long key;
	POINT point;
	int wheel = 0;
	int step = 0;
	char str[100];

	// 等待用户按下鼠标左键（缓冲模式）
	do
	{
		// 显示光标位置
		input->getCursorPos( &point);
		if( step != 3 )
			sprintf( str, "光标位置: %d, %d", point.x, point.y );
		else
			sprintf( str, "滚轮位置 %d", wheel );
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		text->color( 255, 0, 0 );
		text->setTextPos( 135, 107 );
		text->drawText( str );

		// 显示提示信息
		text->color( 0, 255, 0 );
		text->setTextPos( 130, 137 );
		if( step == 0 )
			text->drawText("请按鼠标左键继续......");
		else
			if( step == 1 )
				text->drawText("请按鼠标右键继续......");
			else
				if( step == 2 )
				{
					text->drawText("请按鼠标中键继续......");
					text->setTextPos( 110, 165 );
					text->drawText("(如果鼠标没有中键，请按 ESC 键)");
				}
				else
					if( step == 3 )
					{
						text->setTextPos( 70, 137 );
						text->drawText("请调节鼠标滚轮，使滚轮位置大于 2000 ......");
						text->setTextPos( 100, 165 );
						text->drawText("(如果鼠标没有滚轮，请按 ESC 键)");
					}

		engine->swapBuffers();

		// 读取一个按键值
		key = input->getKey();
		if( step == 0 && key == KEY_MOUSE_BUTTON0 )
			step++;
		else
			if( step == 1 && key == KEY_MOUSE_BUTTON1 )
				step++;
			else
				if( step == 2 && (key == KEY_MOUSE_BUTTON2 || key == KEY_ESCAPE) )
				{
					step++;
					wheel = 0;
				}
				else
					if( step == 3 && key == KEY_ESCAPE )
						step++;

		// 读取鼠标滚轮位置
		// 当鼠标滚轮朝着屏幕方向滚动的时候，input->GetKeyState(KEY_MOUSE_Z) 返回一个正值，
		// 当鼠标滚轮背着屏幕方向滚动的时候，input->GetKeyState(KEY_MOUSE_Z) 返回一个负值，
		// 当鼠标滚轮停止滚动的时候，input->GetKeyState(KEY_MOUSE_Z) 返回 0
		wheel += input->getKeyState( KEY_MOUSE_Z );
		if( wheel > 2000 )
			step++;

		// 配送消息
		engine->dispatchMessage();
	} while( step <= 3 );
	   
	// 显示提示信息
	engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
	text->setTextPos( 145, 123 );
	text->drawText("请按 ENTER 返回！");
	engine->swapBuffers();

	// 等待用户按下 ENTER 键（立即模式）
	do
	{
		// 配送消息
		engine->dispatchMessage();
	} while( !input->getKeyState(KEY_RETURN) );

	// 释放分配的对象
	engine->releaseInput( input );  // 释放输入接口
	engine->releaseText( text );  // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}