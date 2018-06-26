

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 光源演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightScene  *scene;
	LightMesh   *mesh;
	LightLight  *point_light;
	LightLight  *orientation_light;
	LightLight  *spotlight;
	LightInput  *input;
	LightText   *text;
	char string[100];
	float rotate = 0;
	DWORD lasttime = 0;
	bool light1 = TRUE, light2 = FALSE, light3 = FALSE;

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
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\mesh\\digger\\digger.3ds" );

	// 创建场景对象
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建一个点光源，设置灯光参数，打开灯光
	LightLightDesc lightDesc;
	memset( &lightDesc, 0, sizeof(lightDesc) );
	lightDesc.type = LIGHT_POINT_LIGHTING;
	VEC4( lightDesc.position, -100, 100, 100, 1 );	    // 光源位置
	VEC4( lightDesc.diffuse, 1.0f, 1.0f, 1.0f, 1.0f );  // 光源漫反射颜色
	VEC4( lightDesc.specular, 0.3f, 0.3f, 0.3f, 1.0f ); // 光源高光颜色
	VEC4( lightDesc.ambient, 0.3f, 0.3f, 0.3f, 1.0f );  // 光源环境光颜色
	lightDesc.enable = TRUE;
	point_light = engine->createLight( lightDesc );
	point_light->setPosition( -100, 100, 100, 1 );                   // 设置光源位置
	point_light->setColor( LIGHT_DIFFUSE, 1.0f, 1.0f, 1.0f, 1.0f );  // 光源漫反射颜色
	point_light->setColor( LIGHT_SPECULAR, 0.3f, 0.3f, 0.3f, 1.0f ); // 光源高光颜色
	point_light->setColor( LIGHT_AMBIENT, 0.3f, 0.3f, 0.3f, 1.0f );  // 光源环境光颜色
	point_light->setAttenuation( LIGHT_CONSTANT, 0.0000 );
	point_light->setAttenuation( LIGHT_LINEAR, 0.0000 );
	point_light->setAttenuation( LIGHT_QUADRATIC, 0.000001f );
	point_light->enable(); // 打开灯光

	// 创建一个方向光，设置灯光参数，打开灯光
	orientation_light = engine->createLight( lightDesc );
	orientation_light->setPosition( -50, 200, 50, 0 ); // 设置光源位置
	orientation_light->setColor( LIGHT_DIFFUSE, 1.0f, 1.0f, 1.0f, 1.0f );  // 光源漫反射颜色
	orientation_light->setColor( LIGHT_SPECULAR, 0.3f, 0.3f, 0.3f, 1.0f ); // 光源高光颜色
	orientation_light->setColor( LIGHT_AMBIENT, 0.3f, 0.3f, 0.3f, 1.0f );  // 光源环境光颜色
	orientation_light->enable(); // 打开灯光	

	// 创建一个点光源，设置灯光参数，打开灯光
	spotlight = engine->createLight( lightDesc );
	spotlight->setPosition( 0, 50, 250, 1 ); // 设置光源位置
	spotlight->setColor( LIGHT_DIFFUSE, 1.0f, 1.0f, 1.0f, 1.0f );  // 光源漫反射颜色
	spotlight->setColor( LIGHT_SPECULAR, 0.3f, 0.3f, 0.3f, 1.0f ); // 光源高光颜色
	spotlight->setColor( LIGHT_AMBIENT, 0.3f, 0.3f, 0.3f, 1.0f );  // 光源环境光颜色
	spotlight->setSpotlight( 0, -50, -250, 1, 30 );
	spotlight->enable(); // 打开灯光

	// 设置摄像机
	camera->lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );	

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 打开灯光
		engine->enable( LIGHT_LIGHTING );

		// 显示静态网格
		mesh->setGlobalOrientationAngleAxis( rotate, 0, 1, 0 );
		mesh->render();

		// 关闭灯光
		engine->disable( LIGHT_LIGHTING );

		// 旋转静态网格
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			rotate -= ( time - lasttime ) * 0.02f;
			if( rotate < -360 )
				rotate = 0;
			lasttime = time;
		}
        
		// 处理输入按键
		unsigned int key = input->getKey();
		// 根据按键，切换灯光状态
		if( key == KEY_1 )
			light1 = !light1;
		if( key == KEY_2 )
			light2 = !light2;
		if( key == KEY_3 )
			light3 = !light3;
		
		// 更新灯光状态
		if( light1 )
			point_light->enable();
		else
			point_light->disable();
		if( light2 )
			orientation_light->enable();
		else
			orientation_light->disable();
		if( light3 )
			spotlight->enable();
		else
			spotlight->disable();

		// 显示提示信息
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 20 );
		if( light1 )
			text->drawText( "1 = 关闭点光源" );
		else
			text->drawText( "1 = 打开点光源" );
		text->setTextPos( 20, 40 );
		if( light2 )
			text->drawText( "2 = 关闭方向光" );
		else
			text->drawText( "2 = 打开方向光" );
		text->setTextPos( 20, 60 );
		if( light3 )
			text->drawText( "3 = 关闭聚光灯" );
		else
			text->drawText( "3 = 打开聚光灯" );

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
	engine->releaseLight( point_light );        // 释放灯光对象
	engine->releaseLight( orientation_light );
	engine->releaseLight( spotlight );
	engine->releaseScene( scene );             // 释放场景对象	
	engine->releaseMesh ( mesh );              // 释放静态网格对象	
	engine->releaseInput( input );             // 释放输入接口	
	engine->releaseText( text );               // 释放文字对象	
	engine->releaseCamera( camera );           // 释放摄像机对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}