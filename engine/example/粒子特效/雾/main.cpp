

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 雾演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;
	LightCamera  *camera;
	LightInput   *input;
	LightText    *text;
	LightMesh    *mesh;
	LightSky     *sky;	
	LightFog     *fog;	
	char string[100];
	float angle = 0;
	DWORD lasttime = 0;
	bool fog_enable = TRUE;

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

	// 启用关键色（默认禁用）
	engine->enable( LIGHT_KEY_COLOR );
	// 设置关键色（透明色，默认值为黑色 0，0，0 ）
	engine->setKeyColor( 255, 0, 0 );

	// 关闭垂直同步（默认开启）
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建静态网格对象
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// 创建天空盒
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // 天空类型
	VEC3( skyDesc.box.size, 64, 64, 64 );            // 天空盒大小
	LightTextureDesc textureDesc;
	skyDesc.top = engine->createTexture( textureDesc );
	skyDesc.top->load( "..\\resource\\sky\\fine_top.tga" );
	skyDesc.front = engine->createTexture( textureDesc );
	skyDesc.front->load( "..\\resource\\sky\\fine_front.tga" );
	skyDesc.back = engine->createTexture( textureDesc );
	skyDesc.back->load( "..\\resource\\sky\\fine_back.tga" );
	skyDesc.left = engine->createTexture( textureDesc );
	skyDesc.left->load( "..\\resource\\sky\\fine_left.tga" );
	skyDesc.right = engine->createTexture( textureDesc );
	skyDesc.right->load( "..\\resource\\sky\\fine_right.tga" );
	skyDesc.bottom = engine->createTexture( textureDesc );
	skyDesc.bottom->load( "..\\resource\\sky\\fine_bottom.tga" );	
	sky = engine->createSky( skyDesc );

	// 创建雾对象
	LightFogDesc fogDesc;
	memset( &fogDesc, 0, sizeof(fogDesc) );
	fogDesc.type = 0;                         // 雾类型
	VEC3( fogDesc.color, 0.88f, 0.51f, 0.06f );  // 雾颜色
	fogDesc.color[3] = 1.0;
	fogDesc.density = 1;                      // 雾密度
	fogDesc.start = 50;                       // 雾起始距离
	fogDesc.end = 200;                        // 雾结束距离
	fogDesc.quality = 0;                      // 雾显示品质
	fogDesc.enable = TRUE;                    // 开启雾
	fog = engine->createFog( fogDesc );

	// 设置摄像机位置和方向
	camera->lookAt( 0, 0, 5,  10, 10, 8,  0, 0, 1 );

	do
	{
		// 更新物理引擎状态
		engine->updatePhysics();

		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染天空盒
		sky->render();

		// 渲染场景网格
		mesh->render();

		// 显示提示信息
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 20 );
		if( fog_enable )
			text->drawText( "空格 = 关闭雾效果" );
		else
			text->drawText( "空格 = 打开雾效果" );

		// 显示帧速（FPS）
		sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// 处理输入按键
		unsigned int key = input->getKey();
		// 如果按下空格键，则关闭/打开雾
		if( key == KEY_SPACE )
			fog_enable = !fog_enable;
		if( fog_enable )
			fog->enable();
		else
			fog->disable();

		// 更新显示
		engine->swapBuffers();		
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放雾对象	
	engine->releaseFog( fog );

	// 释放天空对象
	engine->releaseSky( sky );

	// 释放静态网格对象
	engine->releaseMesh ( mesh );

	// 释放输入接口
	engine->releaseInput( input );

	// 释放文字对象
	engine->releaseText( text );

	// 释放摄像机对象
	engine->releaseCamera( camera );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}