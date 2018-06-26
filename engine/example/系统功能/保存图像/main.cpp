

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 保存图像演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *image, *dynamic_image;	
	LightInput *input;
	LightText   *text;
	unsigned long time, lasttime;
	float rotate;
	char fps[100];

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

	// 创建一般图像
	LightImageDesc imageDesc;
	image = engine->createImage( imageDesc );
	image->load( "..\\resource\\image\\b.bmp" );

	// 创建动态图像
	dynamic_image = engine->createImage( imageDesc );	
	dynamic_image->create( 256, 256, 1 );

	// 初始化时间变量
	rotate = 0.0;
	lasttime = engine->getTickCount();

	do
	{
		// 渲染到纹理
		dynamic_image->renderToTexture( TRUE );
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// 显示旋转图像
		LightImageRenderDesc renderDesc;
		renderDesc.flags = LIGHT_IMAGE_ROTATE;
		renderDesc.rotate = rotate;		
		image->renderDesc( 65, 60, renderDesc );

		// 显示帧速（FPS）
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 50, 180 );
		text->drawText( fps );

		// 渲染到窗口
		dynamic_image->renderToTexture( FALSE );
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		// 正常显示图像
		dynamic_image->render( 72, 16 );		
		// 显示提示信息
		text->color( 0, 255, 0 );
		text->setTextPos( 80, 235 );
		text->drawText( "请按 Enter 键将图像保存为 shot.bmp 文件" );

		if( input->getKey() == KEY_RETURN )
		{
			// 保存图像文件
			remove( "shot.bmp" );
			dynamic_image->save( "shot.bmp", LIGHT_BMP, 0 );
		}

		// 计算图像旋转角度
		time = engine->getTickCount();
		rotate += ( time - lasttime ) * 0.025f;
		lasttime = time;
		if( rotate > 360 )
			rotate -= 360;

        // 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseImage( dynamic_image );  // 释放动态图像
	engine->releaseImage( image );          // 释放一般图像
	engine->releaseInput( input );          // 释放输入接口
	engine->releaseText( text );            // 释放文字对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}