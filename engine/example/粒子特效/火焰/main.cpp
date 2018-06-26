

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 粒子火焰演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine    *engine;
	LightCamera    *camera;	
	LightParticle  *particle;	
	LightSound     *sound;
	LightText      *text;
	LightImage     *background;	
	LightImageRenderDesc renderDesc;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

	// 使用 3DSMAX 坐标系统(Z->UP）
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// 禁用关键色 （系统默认）
	engine->disable( LIGHT_KEY_COLOR );

	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建并读入背景图片
	LightImageDesc imageDesc;
	background = engine->createImage( imageDesc );	 
	background->load( "..\\resource\\image\\grassland.jpg" );

	/// 创建一个粒子发射器
	LightParticleDesc particleDesc;
	particleDesc.track = LIGHT_TRACK_RADIAL;
	strcpy( particleDesc.texture, "..\\resource\\particle\\fire.bmp" ); /// 粒子纹理文件
	particleDesc.numparticle = 16;	
	particleDesc.grid_width = 64;
	particleDesc.grid_width = 64;
	particleDesc.num_grid = 16;
	particle = engine->createParticle( particleDesc );

	// 设置粒子参数
	particle->setVector( 0.0f, 0.0f, 1.0f );
	particle->speed( 2.5f );
	particle->life( 1000 );
	particle->size( 1, 1 );

	// 读入并播放火焰燃烧的声音	
	LightSoundDesc soundDesc;
	sound = engine->createSound( soundDesc );
	sound->load( "..\\resource\\sound\\burn.wav" );
	sound->setRepeats( 1000 );
	sound->play();

	camera->lookAt( 6, 0, 4,  0, 0, 1,  0, 0, 1 );

	do
	{
		// 清除屏幕内容		
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示背景图片		
		renderDesc.dest_rect.left   = 0;
		renderDesc.dest_rect.top    = 0;
		renderDesc.dest_rect.right  = 660;
		renderDesc.dest_rect.bottom = 448;
		renderDesc.flags = LIGHT_IMAGE_DESTRECT;
		background->renderDesc( 0, 0, renderDesc );

		// 显示粒子系统		
		particle->render();

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );

		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象	
	engine->releaseParticle( particle );  // 释放粒子发射器	
	engine->releaseImage( background );	  // 释放背景图片	
	engine->releaseText( text );          // 释放文字对象		
	engine->releaseSound( sound );        // 释放声音对象	
	engine->releaseCamera( camera );	  // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}