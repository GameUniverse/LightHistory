

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 法阵特效演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine    *engine;
	LightCamera    *camera;	
	LightParticle  *particle;	
	LightTexture   *texture;	
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

	// 读入背景图片
	LightImageDesc imageDesc;
	background = engine->createImage( imageDesc );
	background->load( "..\\resource\\image\\grassland.jpg" );	

	// 将粒子纹理读入内存
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );
	texture->setOrigin( LIGHT_ORIGIN_LOWER_LEFT );
	//texture->Load("..\\resource\\particle\\smoke.bmp");
	//texture->Grid( 64, 64, 16 );
	texture->load("..\\resource\\particle\\round.bmp");
	texture->grid( 128, 128, 1 );

	// 创建一个粒子发射器
	LightParticleDesc particleDesc;		
	particleDesc.track = LIGHT_TRACK_POINT; // 粒子轨迹	
	particleDesc.billboard_mode = LIGHT_BILLBOARD_FIX_XY; // 布告板模式
	particleDesc.billboard_width = 2.0f;
	particleDesc.billboard_height = 2.0f;
	particleDesc.numparticle = 10;
	VEC3( particleDesc.homeplace_box, 0.2f, 0.2f, 0.2f );
	particleDesc.disable_texture = FALSE;          // 禁止纹理	
	particleDesc.emission_rate = 2;
	particleDesc.left_point = 0.25f;                  // 设置左右转折点位置（计算插值用）
	particleDesc.right_point = 0.75f;
	VEC4( particleDesc.color[0], 255, 128, 255, 0 );  // 设置颜色（包括透明度）插值信息
	VEC4( particleDesc.color[1], 255, 128, 255, 255 );
	VEC4( particleDesc.color[2], 255, 128, 255, 255 );
	VEC4( particleDesc.color[3], 255, 64, 255, 0 );
	VEC3( particleDesc.scale[0], 0.1f, 0.1f, 0.1f );     // 设置缩放比例插值信息
	VEC3( particleDesc.scale[1], 0.5, 0.5, 0.5 );
	VEC3( particleDesc.scale[2], 1.5, 1.5, 1.5 );
	VEC3( particleDesc.scale[3], 2, 2, 2 );	
	VEC4( particleDesc.rotate[0], 0, 0, 1,  0 );      // 设置旋转插值信息
	VEC4( particleDesc.rotate[1], 0, 0, 1,  90  );
	VEC4( particleDesc.rotate[2], 0, 0, 1,  270 );
	VEC4( particleDesc.rotate[3], 0, 0, 1,  360 );	
	particle = engine->createParticle( particleDesc );

	// 设置粒子参数
	particle->setVector( 0.0f, 1.0f, 0.0f );
	particle->speed( 2.5f );
	particle->life( 3000 );
	//particle->Size( 1, 1 );	

	camera->lookAt( 6, 0, 4,  0, 0, 1,  0, 0, 1 );

	do
	{
		// 清除屏幕内容
		//engine->ClearColor( 255, 255, 255, 255 );
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示背景图片		
		renderDesc.dest_rect.left   = 0;
		renderDesc.dest_rect.top    = 0;
		renderDesc.dest_rect.right  = 660;
		renderDesc.dest_rect.bottom = 448;
		renderDesc.flags = LIGHT_IMAGE_DESTRECT;
		background->renderDesc( 0, 0, renderDesc );

		// 显示粒子系统
		texture->active();
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
	engine->releaseTexture( texture );    // 释放纹理对象
	engine->releaseImage( background );	
	engine->releaseParticle( particle );  // 释放粒子发射器	
	engine->releaseText( text );          // 释放文字对象	
	engine->releaseCamera( camera );      // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}
