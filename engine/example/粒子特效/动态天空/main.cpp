

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 动态天空演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;
	LightCamera  *camera;
	LightMesh    *scene;
	LightSky     *sky;	
	LightInput   *input;
	LightText    *text;
	char string[100];
	float angle = 0;
	DWORD lasttime = 0;

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

	// 将静态网格文件读入内存
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	scene = engine->createMesh( meshDesc );
	scene->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// 创建天空盒
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // 天空类型
	VEC3( skyDesc.box.size, 64, 64, 64 );            // 天空盒大小	
	skyDesc.rotate_velocity = 0;                     // 无用
	VEC3( skyDesc.rotate_axis, 0, 0, 1 );            // 无用
	VEC3( skyDesc.cloud_size, 128, 128, 10 );        // 云层盒大小
	VEC3( skyDesc.cloud_velocity, 0.01f, 0.01f, 0 ); // 云层移动速度
	skyDesc.cloud_scale = 0.2f;                      // 云层纹理缩放比例
	LightTextureDesc textureDesc;
	skyDesc.top = engine->createTexture( textureDesc ); // 读取天空盒纹理
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
	skyDesc.cloud = engine->createTexture( textureDesc ); // 读取云层纹理
	skyDesc.cloud->load( "..\\resource\\sky\\cloud.tga" );
	sky = engine->createSky( skyDesc );

	// 设置摄像机位置和方向
	camera->lookAt( 0, 0, 5,  -10, -6, 8,  0, 0, 1 );

	do
	{
		// 更新物理引擎状态
		engine->updatePhysics();

		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染天空盒
		sky->render();

		// 渲染场景网格
		scene->render();

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

	// 释放天空对象
	engine->releaseSky( sky );

	// 释放静态网格所占内存
	engine->releaseMesh ( scene );

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