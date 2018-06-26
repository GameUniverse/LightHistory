

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 显示模式演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage  *image;
	LightInput  *input;
	LightText   *text;
	LightDisplaymodeDesc displaymodeDesc;
	unsigned long key;
	int display_mode = 0;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度

	/*engineDesc.displayMode.mode                  = LIGHT_FULLSCREEN_MODE;  // 全屏显示模式
	engineDesc.displayMode.fullscreen.width      = 800;                    // 屏幕水平分辨率
	engineDesc.displayMode.fullscreen.height     = 600;                    // 屏幕垂直分辨率
	engineDesc.displayMode.fullscreen.color      = 16;                     // 屏幕颜色深度
	engineDesc.displayMode.fullscreen.refurbish  = 0;                      // 屏幕刷新率*/

	engine = LightEngineCreate( engineDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 关闭垂直同步（默认开启）
	engine->disable( LIGHT_SWAP_INTERVAL );
		
	// 创建图像对象
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
	image->load( "..\\resource\\image\\sweet_flower.bmp" );
	
	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示图像		
		image->render( 0, 0 );
		
		// 显示提示信息
		text->color( 255, 0, 0 );
		text->setTextPos( 270, 205 );
		text->drawText("请按空格键切换显示模式......");
		
		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 255, 255, 0 );
		text->setTextPos( 30, 413 );
		text->drawText( fps );
        
		// 更新显示
		engine->swapBuffers();

		// 查询用户按键
		key = input->getKey();
		if( key == KEY_SPACE )
		{
			display_mode++;
			if( display_mode > 2 )
				display_mode = 0;
			if( display_mode == 0 )
			{
				// 创建光线引擎实例
				displaymodeDesc.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
				displaymodeDesc.window.x       = 200;                // 窗口左上角 x 坐标
				displaymodeDesc.window.y       = 150;                // 窗口左上角 y 坐标
				displaymodeDesc.window.width   = 640;                // 窗口宽度
				displaymodeDesc.window.height  = 480;                // 窗口高度
				engine->changeDisplaySettings( displaymodeDesc );
			}
			else
			if( display_mode == 1 )
			{
				displaymodeDesc.mode = LIGHT_HALFSCREEN_MODE;  // 假全屏显示模式
				engine->changeDisplaySettings( displaymodeDesc );
			}
			else
			if( display_mode == 2 )
			{
				displaymodeDesc.mode                  = LIGHT_FULLSCREEN_MODE;  // 全屏显示模式
				displaymodeDesc.fullscreen.width      = 800;                    // 屏幕水平分辨率
				displaymodeDesc.fullscreen.height     = 600;                    // 屏幕垂直分辨率
				displaymodeDesc.fullscreen.color      = 16;                     // 屏幕颜色深度
				displaymodeDesc.fullscreen.refurbish  = 0;                      // 屏幕刷新率
				engine->changeDisplaySettings( displaymodeDesc );
			}
		}
	}
	// 配送消息
	while( engine->dispatchMessage() && key != KEY_ESCAPE );

	// 释放分配的对象
	engine->releaseImage( image );  // 释放图像对象
	engine->releaseInput( input );  // 释放输入接口
	engine->releaseText( text ); // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}