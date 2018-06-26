

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine *engine;
LightCamera *camera;
LightText *text;
LightSkeleton *skeleton;
LightInput *input;

// 骨骼动画演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int seq = 0;
	char string[100];

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

	// 创建文字实例
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );
	
	camera->lookAt( 0, 3.5, 11,  0, 3.5, 0,  0, 1, 0 );

	// 将骨骼动画文件读入内存
	LightSkeletonDesc skeletonDesc;
	skeleton = engine->createSkeleton( skeletonDesc );
	//skeleton->load( "..\\resource\\skeleton\\fighter\\fighter.cfg" );
	skeleton->load( "..\\resource\\skeleton\\knight-errant\\knight-errant.actor" );
	// 设置骨骼动画细节等级
	skeleton->setLodLevel( 0.8f );
	// 设置骨骼动画模型动画状态
	skeleton->animation( 0 );

	do
	{
		// 清除屏幕内容
		engine->clearColor( 0, 0, 0, 0 );
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染骨骼动画
		skeleton->render();
		
		// 显示提示信息
		/*sprintf( string, "按 <鼠标左键> 切换动作：%d", seq );
		text->color( 0, 255, 0 );
		text->setTextPos( 400, 400 );
		text->drawText( string );*/

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// 更新显示
		engine->swapBuffers();

		// 变换模型动作
		DWORD key = input->getKey();
		if( key == KEY_MOUSE_BUTTON0 )
		{
			seq++;
			if( seq > 0 )
				seq = 0;
			// 设置骨骼动画
			skeleton->animation( seq );
		}			
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseSkeleton( skeleton );  // 从内存中释放骨骼动画文件
	engine->releaseInput( input );        // 释放输入接口
	engine->releaseCamera( camera );      // 释放摄像机对象
	engine->releaseText( text );          // 释放文字实例

	// 释放光线引擎实例
	LightEngineRelease( engine );
	
	return 0;
}