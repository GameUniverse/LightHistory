

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 显示着色语言程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *image[5];
	LightShader *shader;
	LightText *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 400;                // 窗口宽度
	engineDesc.displayMode.window.height  = 300;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建图像对象
	LightImageDesc imageDesc;	
	image[0] = engine->createImage( imageDesc );
	image[1] = engine->createImage( imageDesc );
	image[2] = engine->createImage( imageDesc );
	image[3] = engine->createImage( imageDesc );
	image[4] = engine->createImage( imageDesc );	

	// 把使用关键色的图像文件读入内存
	image[4]->load("..\\resource\\image\\keycolor.bmp");

	// 禁止关键色
	engine->enable( LIGHT_KEY_COLOR );

	// 将图像文件读入内存	
	image[0]->load("..\\resource\\image\\a.bmp");
	image[1]->load("..\\resource\\image\\d.bmp");
	image[2]->load("..\\resource\\image\\b.bmp");
	image[3]->load("..\\resource\\image\\c.bmp");

	// 创建着色语言对象
	LightShaderDesc shaderDesc;
	shader = engine->createShader( shaderDesc );
	if( shader == NULL )
	{
		MessageBox( 0, "显卡不支持 OpenGL 着色语言 1.0 版本", "错误", MB_OK );
		return 1;
	}	

	// 读入 GLSL 着色语言程序
	shader->load( "..\\example\\图形技术\\着色语言\\vertex.vert", "..\\example\\图形技术\\着色语言\\fragment.frag" );

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 运行着色程序
		shader->begin();

		// 正常显示图像
		image[0]->render( 69, 6 );

		// 翻转图像
		LightImageRenderDesc renderDesc;		
		renderDesc.flags = LIGHT_IMAGE_REVERSALX | LIGHT_IMAGE_REVERSALY;
		image[1]->renderDesc( 203, 6, renderDesc );
		
		// 缩放图像		
		renderDesc.dest_rect.left = 69;
		renderDesc.dest_rect.top = 140;
		renderDesc.dest_rect.right = 165;
		renderDesc.dest_rect.bottom = 236;
		renderDesc.flags = LIGHT_IMAGE_DESTRECT;
		image[2]->renderDesc( 40, 108, renderDesc );

		// 混合带有关键色（透明色）的图像        
		renderDesc.blend = 0.8f;
		renderDesc.flags = LIGHT_IMAGE_BLEND;
		image[4]->renderDesc( 135, 75, renderDesc );
		
		// 显示指定区域的图像		
		renderDesc.sour_rect.left = 30;
		renderDesc.sour_rect.top = 30;
		renderDesc.sour_rect.right = 90;
		renderDesc.sour_rect.bottom = 90;
		renderDesc.flags = LIGHT_IMAGE_SOURRECT;
		image[3]->renderDesc( 40, 108, renderDesc );

		// 按指定亮度显示图像		
		renderDesc.lighteness = 0.5f;
		renderDesc.flags = LIGHT_IMAGE_LIGHTENESS;
		image[3]->renderDesc( 280, 75, renderDesc );

		// 旋转图像
		renderDesc.rotate = 25;
		renderDesc.flags = LIGHT_IMAGE_ROTATE;
		image[3]->renderDesc( 203, 110, renderDesc );

		// 停止运行着色程序
		shader->end();

		// 显示提示信息
		text->color( 255, 0, 0 );
		text->setTextPos( 105, 60 );
		text->drawText( "正常显示" );
		text->setTextPos( 252, 60 );
		text->drawText( "翻转" );
		text->setTextPos( 102, 180 );
		text->drawText( "缩放" );
		text->setTextPos( 258, 165 );
		text->drawText( "旋转" );
		text->setTextPos( 182, 130 );
		text->drawText( "混合" );
		text->setTextPos( 58, 130 );
		text->drawText( "区域" );
		text->setTextPos( 335, 123 );
		text->drawText( "亮度" );

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
	engine->releaseShader( shader );   // 释放着色语言对象
	engine->releaseImage( image[0] );  // 从内存中释放图像文件
	engine->releaseImage( image[1] );
	engine->releaseImage( image[2] );
	engine->releaseImage( image[3] );
	engine->releaseImage( image[4] );	
	engine->releaseText( text );       // 释放文字实例

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}