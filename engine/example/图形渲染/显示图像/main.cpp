

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 显示图像演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *desktop;
	LightImage *image[7];
	LightImage *mask;
	LightText *text;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );

    // 设置显示模式为窗口模式
	//engine->SetWindowMode(200, 150, 400, 300, 0);

	// 开启垂直同步（系统默认）
	//engine->Enable( LIGHT_SWAP_INTERVAL );
	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 关键色又叫透明色，有关键色的像素，渲染的时候是完全透明的，看不见。
	// 包含关键色的图像和纹理文件，加载之前必须启用并设置关键色，加载完之后必须关闭关键色，
	// 以防其他图像和纹理发生不希望的透明。
	// 每个图像和纹理可以设置不同的关键色。

	// 启用关键色（系统默为禁用关键色）
	engine->enable( LIGHT_KEY_COLOR );
	// 设置关键色（默认值为黑色 0，0，0 ）	
	engine->setKeyColor( 255, 0, 0 );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建图像对象
	LightImageDesc imageDesc;
	desktop = engine->createImage( imageDesc );
	image[0] = engine->createImage( imageDesc );
	image[1] = engine->createImage( imageDesc );
	image[2] = engine->createImage( imageDesc );
	image[3] = engine->createImage( imageDesc );
	image[4] = engine->createImage( imageDesc );
	image[5] = engine->createImage( imageDesc );
	image[6] = engine->createImage( imageDesc );
	mask = engine->createImage( imageDesc );

	// 把使用关键色的图像文件读入内存
	image[4]->load("..\\resource\\image\\keycolor.bmp");

	// 禁止关键色
	engine->enable( LIGHT_KEY_COLOR );

	// 将图像文件读入内存
	desktop->load("..\\resource\\image\\sweet_flower.bmp");
	image[0]->load("..\\resource\\image\\a.bmp");
	image[1]->load("..\\resource\\image\\d.bmp");
	image[2]->load("..\\resource\\image\\b.bmp");
	image[3]->load("..\\resource\\image\\c.bmp");	
	image[5]->load("..\\resource\\image\\l.bmp");
	image[6]->load("..\\resource\\image\\g.bmp");
	mask->load("..\\resource\\image\\mask.tga");

	/// 初始化技能冷却条
	float rotate = 0;
	int lasttime = engine->getTickCount();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 显示桌面
		desktop->render( 0, 0 );

		// 正常显示图像
		image[0]->render( 25, 25 );

		// 翻转图像
		LightImageRenderDesc desc;
		desc.flags = LIGHT_IMAGE_REVERSALX | LIGHT_IMAGE_REVERSALY;
		image[1]->renderDesc( 331, 25, desc );
		
		// 缩放图像
		desc.flags = LIGHT_IMAGE_DESTRECT;		
		desc.dest_rect.left = 54;
		desc.dest_rect.top = 240;
		desc.dest_rect.right = 150;
		desc.dest_rect.bottom = 336;		
		image[3]->renderDesc( 0, 0, desc );

		// 混合带有关键色（透明色）的图像
        desc.flags = LIGHT_IMAGE_BLEND;
		desc.blend = 0.6f;		
		image[2]->renderDesc( 178, 25, desc );
		
		// 显示指定区域的图像
		desc.flags = LIGHT_IMAGE_SOURRECT;		
		desc.sour_rect.left = 30;
		desc.sour_rect.top = 30;
		desc.sour_rect.right = 90;
		desc.sour_rect.bottom = 90;		
		image[3]->renderDesc( 25, 208, desc );

		// 按指定亮度显示图像
		desc.flags = LIGHT_IMAGE_LIGHTENESS;
		desc.lighteness = 0.5f;		
		image[3]->renderDesc( 484, 25, desc );

		// 旋转图像
		desc.flags = LIGHT_IMAGE_ROTATE;
		desc.rotate = -16;
		image[5]->renderDesc( 400, 190, desc );

		// 关键色（透明色）
		// 启用关键色
		engine->enable( LIGHT_KEY_COLOR );
		// 渲染关键色图像		
		image[4]->render( 320, 120 );

		// 禁止关键色
		engine->disable( LIGHT_KEY_COLOR );

#ifdef LIGHT_CORPORATION_EDITION

		// 图像掩码
		desc.flags = LIGHT_IMAGE_MASK;
		desc.mask.image = mask;
		image[6]->renderDesc( 180, 190, desc );

		// 图像掩码区域
		desc.flags = LIGHT_IMAGE_MASK | LIGHT_IMAGE_MASKRECT;
		desc.mask.image = mask;
		desc.mask.rect.left = 0;
		desc.mask.rect.top = 0;
		desc.mask.rect.right = 64;
		desc.mask.rect.bottom = 64;
		image[6]->renderDesc( 90, 125, desc );

		// 扇形阴影
		desc.flags = LIGHT_IMAGE_SECTOR;
		desc.sector.angle = rotate;
		VEC3( desc.sector.shadow_color, 128, 150, 128 );		
		image[1]->renderDesc( 355, 295, desc );

		// 更新技能冷却条
		int time = engine->getTickCount();
		if( (time - lasttime) > 16 )
		{
			rotate += ( time - lasttime ) * 0.005f;
			if( rotate > 360.0f )
				rotate = 0.0f;
			lasttime = time;
		}

#endif

		// 显示提示信息
		text->color( 255, 0, 0 );
		text->setTextPos( 69, 80 );
		text->drawText( "正常显示" );
		text->setTextPos( 385, 80 );
		text->drawText( "翻转" );
		text->setTextPos( 92, 280 );
		text->drawText( "缩放" );
		text->setTextPos( 490, 255 );
		text->drawText( "旋转" );
		text->setTextPos( 233, 80 );
		text->drawText( "混合" );
		text->setTextPos( 45, 232 );
		text->drawText( "区域" );
		text->setTextPos( 535, 80 );
		text->drawText( "亮度" );
		text->setTextPos( 365, 175 );
		text->drawText( "关键色" );

#ifdef LIGHT_CORPORATION_EDITION

		text->setTextPos( 185, 205 );
		text->drawText( "掩码区域" );
		text->setTextPos( 290, 265 );
		text->drawText( "图像掩码" );		
		text->setTextPos( 398, 352 );
		text->drawText( "扇形阴影" );

#endif

		// 显示帧速（FPS）
		char fps[100];
		sprintf( fps, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 255, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );
        
		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象
	engine->releaseText( text );      // 释放文字实例
	engine->releaseImage( desktop );  // 释放图像文件
	engine->releaseImage( image[0] );
	engine->releaseImage( image[1] );
	engine->releaseImage( image[2] );
	engine->releaseImage( image[3] );
	engine->releaseImage( image[4] );
	engine->releaseImage( image[5] );
	engine->releaseImage( image[6] );
	engine->releaseImage( mask );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}
