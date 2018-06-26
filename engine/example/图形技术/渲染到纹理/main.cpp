

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 渲染到纹理演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;	
	LightImage *image, *dynamic_image;
	LightText   *text;
	char fps[100];
	int x, y;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 将图像文件读入内存
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
	image->load( "..\\resource\\image\\a.bmp" );

	// 创建动态纹理
	dynamic_image = engine->createImage( imageDesc );
	dynamic_image->create( 256, 256, 1 );

	do
	{
		// 渲染到纹理
		dynamic_image->renderToTexture( TRUE );
		
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		// 正常显示图像
		image->render( 0, 0 );		
		// 显示帧速（FPS）
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 150 );
		text->drawText( fps );
		
		// 渲染到窗口
		dynamic_image->renderToTexture( FALSE );
     
		
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// 正常显示图像
		for( y=40; y<400; y+=200 )
			for( x=50; x<600; x+=200 )
				dynamic_image->render( x, y );

        // 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseImage( image );          // 释放图像对象
	engine->releaseImage( dynamic_image );
	engine->releaseText( text );            // 释放文字对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}