

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// MD2 顶点动画演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char string[100];
	LightEngine *engine;
	LightAnimation *animation;
	LightTexture *texture;
	LightCamera *camera;
	LightText   *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 关闭垂直同步（默认开启）
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机并设置参数
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建顶点动画纹理
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\animation\\knight\\knight.pcx" );

	// 创建顶点动画对象
	LightAnimationDesc animationDesc;
	animation = engine->createAnimation( animationDesc );
	animation->Load( "..\\resource\\animation\\knight\\knight.md2" );	

	// 设置当前动画
	animation->SetState( 0 );
	
	camera->lookAt( 100, 0, 0,  0, 0, 0,  0, 1, 0 );

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 激活顶点动画纹理
		texture->active();

		// 渲染顶点动画
		animation->Render();

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );
        
		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象	
	engine->releaseAnimation( animation );  // 释放顶点动画对象	
	engine->releaseTexture( texture );      // 释放顶点动画纹理	
	engine->releaseText( text );            // 释放文字对象	
	engine->releaseCamera( camera );        // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}