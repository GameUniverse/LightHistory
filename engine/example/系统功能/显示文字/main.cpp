

#include "windows.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 显示文字演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
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

	// 缺省字体
	// 设置文字颜色
	text->color( 0, 255, 0 );
	// 设置光标位置
	text->setTextPos( 20, 20 );
	// 显示文字
	text->drawText("欢迎使用光线游戏引擎");

	// 文字背景
	/* 设置字体 */
	text->setFont( "华文彩云",     // 指定字体
		         24,          // 指定字体高度
			     0,           // 指定字体宽度
				 0,           // 指定字体的重量(FW_BOLD=700)
				 0,           // 指定角度(1/10度)				 
				 0,           // 指定是否斜体
				 0,           // 指定是否有下划线
				 0,           // 指定是否是StrikeOut字体
				 0            // 指定输出质量
				 );
	text->color( 255, 255, 0 );
	// 设置文字背景色
	text->backColor( 0, 0, 255 );
	// 设置文字背景模式为不透明
	text->setBackMode( LIGHT_OPAQUE );
	text->setTextPos( 20, 55 );
	text->drawText("欢迎使用光线游戏引擎");

	// 斜体
	text->setFont( "隶书", 28, 0, 0, 0, 1, 0, 0, 0 );				 
	text->color( 255, 0, 0 );
	text->setBackMode( LIGHT_TRANSPARENT );
	text->setTextPos( 20, 90 );
	text->drawText("欢迎使用光线游戏引擎");

	// 下划线
	text->setFont( "宋体", 28, 0, 0, 0, 0, 1, 0, 0 );				 
	text->color( 255, 255, 0 );
	text->setTextPos( 20, 128 );
	text->drawText("欢迎使用光线游戏引擎");

	// 删除线
	text->setFont( "方正姚体", 28, 0, 0, 0, 0, 0, 1, 0 );				 
	text->color( 0, 0, 255 );
	text->setTextPos( 20, 170 );
	text->drawText("欢迎使用光线游戏引擎");

	// 旋转
	text->setFont( "方正舒体", 28, 0, 0, 0, 1, 0, 0, 0 );				 
	text->color( 255, 0, 255 );
	text->setTextPos( 20, 210 );
	text->drawText("欢迎使用光线游戏引擎");

	// 字间距
	text->setFont( "黑体", 24, 0, 0, 0, 0, 0, 0, 0 );				 
	text->color( 255, 255, 255 );
	// 设置字间距
	text->setCharSpace( 10 );
	text->setTextPos( 20, 245 );
	text->drawText("欢迎使用光线游戏引擎");

	// 更新显示
	engine->swapBuffers();

	// 配送消息
	while( engine->dispatchMessage() );

	// 释放文字对象
	engine->releaseText( text );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}