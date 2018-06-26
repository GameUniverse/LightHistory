

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine         *engine;
LightCamera         *camera;
LightInput          *input;
LightText           *text;
LightTexture        *texture;
LightMesh           *mesh;
LightScene          *scene;
LightTriangleMesh   *triangleMesh;
LightActor          *physicsMesh;
LightActor          *a, *b;
LightActor          *plane;
LightActorDesc      actorDesc;


// 鼠标拾取演示程序
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

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

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

	// 创建物理网格对象
	triangleMesh = mesh->createTriangleMesh();

	// 创建物理角色对象
	actorDesc.type = LIGHT_SHAPE_MESH; // 角色类型
	actorDesc.dynamic = FALSE;
	actorDesc.mesh.triangleMesh = triangleMesh;
	actorDesc.physicsMaterialIndex = 0;
	physicsMesh = scene->createActor( actorDesc );

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

		// 渲染场景
		mesh->render();

		// 显示长方体 a 和 b
		texture->active();
		a->render();
		b->render();

		// 小提示：如何让拾取更灵敏？
		// 可以在光标右下角（x+32，y+32）再进行一次拾取，将两次拾取的结果作为最后拾取的结果

		// 查询光标在场景世界中的坐标
		POINT point;
		vec3_t cursor;
		input->getCursorPos( &point );
		camera->updateCamera();
		engine->windowToWorld( point.x, point.y, cursor );

		// 对角色进行拾取
		LightRay ray;
		LightRaycastHit hit;
		gVectorCopy( eye, ray.orig );
		gVectorSubtract( cursor, ray.orig, ray.dir );
		gVectorNormalize( ray.dir );
		LightActor * hitActor = scene->raycastClosestShape( ray, LIGHT_ALL_SHAPES, hit, 0xffffffff, 500, 0 ); // LIGHT_DYNAMIC_SHAPES 为只拾取动态角色

		// 显示提示信息和拾取结果
		text->setTextPos( 40, 368 );
		if( hitActor == a )
		{
			text->color( 255, 0, 0 );
			text->drawText( "选中盒子 A" );
		}
		else
		if( hitActor == b )
		{
			text->color( 255, 0, 0 );
			text->drawText( "选中盒子 B" );
		}
		else
		if( hitActor == physicsMesh )
		{
			text->color( 255, 0, 0 );
			text->drawText( "选中地面" );
		}
		else
		{
			text->color( 0, 255, 0 );
			text->drawText( "请将光标移动到地面或盒子上面" );
		}		

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
	scene->releaseActor( a );                   // 释放物理角色对象
	scene->releaseActor( b );
	scene->releaseActor( physicsMesh );
	mesh->releaseTriangleMesh( triangleMesh );  // 释放物理网格
	engine->releaseScene( scene );              // 释放物理场景所占内存
	engine->releaseMesh( mesh );                // 释放静态网格对象
	engine->releaseTexture( texture );          // 释放纹理对象
	engine->releaseInput( input );              // 释放输入接口
	engine->releaseCamera( camera );            // 释放摄像机对象
	engine->releaseText( text );                // 释放文字对象

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}