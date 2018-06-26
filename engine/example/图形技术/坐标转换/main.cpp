

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine         *engine;
LightInput          *input;
LightCamera         *camera;
LightText           *text;
LightTexture        *texture;
LightMesh           *mesh;
LightTriangleMesh   *triangleMesh;
LightScene          *scene;
LightActor          *physicsScene;
LightActor          *a, *b;
LightActorDesc      actorDesc;


// 坐标转换演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
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

	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );
	
	// 创建纹理对象
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建长方体 a 和 b
	texture->load( "..\\resource\\image\\wood.jpg" );
	memset( &actorDesc, 0, sizeof(LightActorDesc) );
	actorDesc.type = LIGHT_SHAPE_BOX;
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.box.size, 3.0f, 3.0f, 3.0f );
	VEC3( actorDesc.pos, 0.0f, 0.0f, 15.0f );
	VEC3( actorDesc.rotate, 0.0f, 0.0f, 1.0f );
	actorDesc.angle = 0.0f;
	actorDesc.mass = 0.00001f;
	actorDesc.hide = FALSE;	
	a = scene->createActor( actorDesc );	
	actorDesc.type = LIGHT_SHAPE_BOX;
	actorDesc.dynamic = TRUE;
	VEC3( actorDesc.box.size, 3.0f, 3.0f, 3.0f );
	VEC3( actorDesc.pos, 0.0f, 0.0f, 25.0f );
	VEC3( actorDesc.rotate, 1.5f, 1.5f, 1.5f );
	actorDesc.angle = 45.0f;	
	b = scene->createActor( actorDesc );

	// 创建静态网格对象
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\scene\\ground\\ground.3ds" );

	// 创建物理网格	
	triangleMesh = mesh->createTriangleMesh();

	// 创建物理场景	
	memset( &actorDesc, 0, sizeof(LightActorDesc) );
	actorDesc.type = LIGHT_SHAPE_MESH; // 角色类型
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0; // 使用缺省材质
	physicsScene = scene->createActor( actorDesc );

	// 设置摄像机位置和方向
	vec3_t eye = { 0, -50, 25 };
	camera->lookAt( eye[0], eye[1], eye[2],  0, 25, 10,  0, 0, 1 );

	// 激活当前纹理
	texture->active();

	do
	{
		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 更新物理状态
		engine->updatePhysics();

		// 显示场景
		mesh->render();

		// 显示长方体 a 和 b
		texture->active();
		a->render();
		b->render();

		POINT point2d;
		vec3_t point3d, reverse2d;

		// 查询光标窗口坐标
		input->getCursorPos( &point2d );

		// 更新摄像机设置
		camera->updateCamera();

		// 注意：请在目标对象渲染之后立即调用坐标转换函数，否则得到的结果可能不正确

		// 将“窗口坐标”转换成“世界坐标”
		engine->windowToWorld( point2d.x, point2d.y, point3d );

		// 将“世界坐标”转换成“窗口坐标”
		engine->worldToWindow( point3d[0], point3d[1], point3d[2], reverse2d );

		// 显示坐标信息
		char string[100];
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 40 );
		sprintf( string, "窗口 2D (%d,%d) ----> 世界 3D (%.2f,%.2f,%.2f)", point2d.x, point2d.y, point3d[0], point3d[1], point3d[2] );
		text->drawText( string );
		text->setTextPos( 40, 65 );
		sprintf( string, "窗口 2D (%.0f,%.0f) <---- 世界 3D (%.2f,%.2f,%.2f)  ", reverse2d[0], reverse2d[1], point3d[0], point3d[1], point3d[2] );
		text->drawText( string );

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
	scene->releaseActor( a );                   // 释放物理角色
	scene->releaseActor( b );
	scene->releaseActor( physicsScene );
	mesh->releaseTriangleMesh( triangleMesh );  // 释放物理网格
	engine->releaseScene( scene );              // 释放物理场景所占内存
	engine->releaseMesh( mesh );                // 释放静态网格对象
	engine->releaseTexture( texture );          // 释放纹理
	engine->releaseInput( input );              // 释放输入接口
	engine->releaseCamera( camera );            // 释放摄像机对象
	engine->releaseText( text );                // 释放文字对象

	// 释放光线引擎实例
	LightEngineRelease( engine );
	
	return 0;
}