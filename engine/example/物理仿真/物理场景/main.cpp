

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 物理场景演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine        *engine;
	LightScene         *scene;
	LightCamera        *camera;
	LightMesh          *sceneMesh;
	LightMesh          *physicsSceneMesh;
	LightSky           *sky;
	LightTriangleMesh  *triangleMesh;
	LightActor         *actor;
	LightActor         *physicsScene;
	LightTexture       *texture;
	LightInput         *input;
	LightText          *text;
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

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 将静态网格文件读入内存
	LightMeshDesc meshDesc;
	sceneMesh = engine->createMesh( meshDesc );
	sceneMesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 创建物理网格对象
	physicsSceneMesh = engine->createMesh( meshDesc );
	physicsSceneMesh->load( "..\\resource\\scene\\hill\\hill_physics.3DS" );
	triangleMesh = physicsSceneMesh->createTriangleMesh();

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

	// 创建球体
	LightActorDesc desc;
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );	
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_SPHERE;
	desc.dynamic = TRUE;
	VEC3( desc.pos, 0, 13, 25 );
	desc.sphere.radius = 1;
	desc.quality_slices = 15;
	desc.quality_stacks = 15;
	VEC3( desc.rotate, 1.0f, 1.0f, 0.0f );
	desc.angle = 45;
	desc.mass = 0.00000001f;
	desc.hide = FALSE;
	// 设置几何体表面物理参数
	actor = scene->createActor( desc );

	// 创建物理场景
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_MESH;
	desc.mesh.triangleMesh = triangleMesh;
	// 设置几何体表面物理参数
	physicsScene = scene->createActor( desc );

	// 设置摄像机位置和方向
	camera->lookAt( -23, 8, 5,  48, 40, 5,  0, 0, 1 );

	do
	{
		// 更新物理引擎状态
		engine->updatePhysics();

		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 渲染天空盒
		sky->render();

		// 渲染场景网格
		sceneMesh->render();

		// 显示长方体（首先激活长方体纹理）
		texture->active();
		actor->render();

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
	scene->releaseActor( physicsScene );               // 释放物理角色
	scene->releaseActor( actor );
	sceneMesh->releaseTriangleMesh( triangleMesh );    // 释放物理网格
	engine->releaseScene( scene );                     // 释放物理场景所占内存
	engine->releaseMesh( sceneMesh );                  // 释放静态网格对象
	engine->releaseMesh( physicsSceneMesh );
	engine->releaseTexture( texture );                 // 释放纹理
	engine->releaseSky( sky );	                       // 释放天空盒对象
	engine->releaseInput( input );                     // 释放输入接口
	engine->releaseCamera( camera );                   // 释放摄像机对象
	engine->releaseText( text );                       // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}