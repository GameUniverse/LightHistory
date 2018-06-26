

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 多视口渲染演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightCamera *camera_top;
	LightCamera *camera_reverse;
	LightMesh   *scene;
	LightBrush  *brush;
	LightSky    *sky;
	LightInput  *input;
	LightText   *text;
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

	// 启用关键色（默认禁用）
	engine->enable( LIGHT_KEY_COLOR );
	// 设置关键色（透明色，默认值为黑色 0，0，0 ）
	engine->setKeyColor( 255, 0, 0 );

	// 关闭垂直同步（默认开启）
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建画笔对象
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

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

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	// 创建主摄像机
	camera = engine->createCamera( cameraDesc );
	// 创建顶摄像机
	camera_top = engine->createCamera( cameraDesc );
	camera_top->viewport( 495, 30, 100, 75 );
	camera_top->lookAt( 0, 0, 100,  0, 0, 0,  0, -1, 0 );
	// 创建逆向旋转摄像机
	camera_reverse = engine->createCamera( cameraDesc );
	camera_reverse->viewport( 30, 30, 100, 75 );	

	vec3_t pos, rotate, translation, eye, center, up;

	do
	{
		for( int i=0; i<3; i++ )
		{
			// 清除屏幕内容
			if( i == 0 )
				engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
			else
				engine->clear( LIGHT_DEPTH_BUFFER_BIT );
            
			if( i == 0 )
			{
				// 设置摄像机位置和方向				
				VEC3( pos, 0, 0, 5 );                // 旋转原点
				VEC3( rotate, angle, -ANGLE_TO_RADIAN(5), 0 ); // 旋转角度
				VEC3( translation, 0, 0, 0 );           // 平移矢量
				camera->rotate( pos, rotate, 15, translation, TRUE, eye, center, up );
				gVectorAdd( pos, eye, eye );
				gVectorAdd( pos, center, center );
				gVectorAdd( pos, up, up );
				camera->lookAt( center[0], center[1], center[2],  eye[0], eye[1], eye[2],  up[0], up[1], up[2] );
				// 将第一个摄像机设为当前摄像机
				camera->active();
			}
			else
			{
				if( i == 1 )
				{
					// 绘制视口边框和背景
					brush->color( 0, 0, 255 );
					brush->rectangle2D( 492, 27, 598, 108 );
					brush->color( 0, 0, 0 );
					brush->rectangle2D( 495, 30, 595, 105 );
					// 绘制视口背景
					brush->color( 0, 0, 255 );
					brush->rectangle2D( 27, 27, 133, 108 );
					brush->color( 0, 0, 0 );
					brush->rectangle2D( 30, 30, 100, 75 );
					// 将第二个摄像机设为当前摄像机					
					camera_top->active();
				}
				else
				{
					// 将第三个摄像机设为当前摄像机
					camera_reverse->lookAt( center[0], center[1], center[2],  eye[0], eye[1], eye[2],  up[0], up[1], up[2] );
					camera_reverse->active();					
				}
			}

			if( i != 1 )
				// 渲染天空盒
				sky->render();

			// 渲染静态网格
			scene->render();

			if( i == 0 )
			{
				// 显示帧速（FPS）
				sprintf( string, "帧速: %d 帧/秒", engine->getFramePerSecond() );
				text->color( 0, 255, 0 );
				text->setTextPos( 40, 400 );
				text->drawText( string );
			}
		}

		// 旋转摄像机
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			angle -= ( time - lasttime ) * 0.0002f;
			if( angle < -360 )
				angle = 0;
			lasttime = time;
		}
        
		// 更新显示
		engine->swapBuffers();
	}
	// 配送消息
	while( engine->dispatchMessage() );

	// 释放分配的对象	
	engine->releaseCamera( camera_reverse );  // 释放摄像机对象
	engine->releaseCamera( camera_top );
	engine->releaseCamera( camera );	
	engine->releaseSky( sky );                // 释放天空对象	
	engine->releaseMesh ( scene );            // 释放静态网格所占内存	
	engine->releaseBrush( brush );            // 释放画笔对象	
	engine->releaseInput( input );            // 释放输入接口	
	engine->releaseText( text );	          // 释放文字对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}