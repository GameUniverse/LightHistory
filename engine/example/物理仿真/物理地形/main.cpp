

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// 物理地形演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;
	LightScene   *scene;
	LightCamera  *camera;
	LightTerrain *terrain;
	LightTexture *texture[3];
	LightSky     *sky;
	LightPhysicsMaterial  *physicsMaterial;
	LightActor   *actor;
	LightActor   *physicsTerrain;
	LightTexture *wood;
	LightInput   *input;
	LightText    *text;
	LightTextureDesc textureDesc;
	char string[100];
	float angle = 0;
	DWORD lasttime = 0;
	int i;

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

	// 创建输入接口
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// 创建摄像机对象
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// 创建文字对象
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// 创建一个场景
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// 读入地形
	terrain = engine->NewTerrain();
	for( i=0; i<3; i++ )
		texture[i] = engine->createTexture( textureDesc );
	// 将地形纹理读入内存	
	texture[0]->load( "..\\resource\\terrain\\grass.bmp" );  // 第一层地形纹理，不含通道
	texture[1]->load( "..\\resource\\terrain\\stone.bmp" );  // 第二层地形纹理，不含通道
	texture[2]->load( "..\\resource\\terrain\\shadow.tga" ); // 地形阴影贴图（32位TGA格式，含通道，通道值为第一层纹理所占比例，第二层纹理所占比例 = 1-第一层纹理所点比例）
	for( i=0; i<3; i++ )
		terrain->SetTexture( i, texture[i] );
	// 设置地形瓷砖大小（宽度和高度）
	terrain->setTile( 32, 32 );
	// 将地形数据读入内存
	//terrain->load( "..\\resource\\terrain\\map1024.raw", 0, 1025, 1025, 8 );
	terrain->load( "..\\resource\\terrain\\height.raw", 0, 1025, 1025, 16 );
	// 设置地形显示品质
	//terrain->SetLODFactor( 2.5, 25 ); // 高速度
	terrain->SetLODFactor( 5, 50 ); // 高品质

	// 创建天空盒
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // 天空类型
	VEC3( skyDesc.box.size, 64, 64, 64 );            // 天空盒大小	
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

	// 创建物理材质
	LightPhysicsMaterialDesc  physicsMaterialDesc;
	memset( &physicsMaterialDesc, 0, sizeof( physicsMaterialDesc ) );	
	physicsMaterialDesc.restitution      = 0.8f; // 弹力系数（缺省值为 0.5）
	physicsMaterialDesc.staticFriction   = 35;  // 静态磨擦力系数（缺省值为 0.5）
	physicsMaterialDesc.dynamicFriction  = 1;   // 动态磨擦力系数（缺省值为 0.5）
	physicsMaterial = scene->createPhysicsMaterial( physicsMaterialDesc );

	LightActorDesc desc;

	// 创建长方体	
	wood = engine->createTexture( textureDesc );
	wood->load( "..\\resource\\image\\wood.jpg" );	
	memset( &desc, 0, sizeof(desc) );
	desc.type = LIGHT_SHAPE_SPHERE;
	desc.dynamic = TRUE;
	VEC3( desc.pos, 80, 250, 150 );
	desc.sphere.radius = 2;
	desc.quality_slices = 15;
	desc.quality_stacks = 15;
	VEC3( desc.rotate, 0.0f, 0.0f, 1.0f );
	desc.angle = 0;
	desc.mass = 1;
	desc.hide = FALSE;
	// 设置几何体表面物理参数
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	actor = scene->createActor( desc );

	// 创建物理地形	
	desc.type = LIGHT_SHAPE_HEIGHTFIELD;
	desc.dynamic = FALSE;
	VEC3( desc.pos, 0, 0, 0 );
	VEC3( desc.rotate, 0.0f, 0.0f, 1.0f );
	desc.angle = 0;
	desc.mass = 0;
	vec3_t position, box;
	VEC3( position, 0, 0, 0 ); // 此参数目前不使用
	VEC3( box, 1025, 1025, 64 ); // 物理地形大小，第三个目前参数不使用（注意：物理地形的大小必须要和高度图的大小相符合）
	desc.height_field.heightField = terrain->createHeightField( position, box );
	// 设置几何体表面物理参数
	desc.physicsMaterialIndex = physicsMaterial->getMaterialIndex();
	physicsTerrain = scene->createActor( desc );

	// 设置摄像机位置和方向
	camera->lookAt( 0, 0, 150,  256, 256, 25,  0, 0, 1 );

	do
	{
		// 更新物理引擎状态
		engine->updatePhysics();

		// 清除屏幕内容
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// 设置摄像机位置和方向
		float x, y, z;
		actor->getGlobalPosition( &x, &y, &z );
		camera->lookAt( 0, 100, 150,  x, y, z,  0, 0, 1 );

		// 渲染天空盒
		sky->render();

		//渲染地形
		//terrain->RenderMode( 0 );
		terrain->render();

		// 显示长方体（首先激活长方体纹理）
		wood->active();
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
	//scene->releaseActor( physicsScene );               // 释放物理角色
	scene->releaseActor( actor );
	scene->releasePhysicsMaterial( physicsMaterial );  // 释放物理材质
	//sceneMesh->releaseTriangleMesh( triangleMesh );    // 释放物理网格
	engine->releaseScene( scene );                     // 释放物理场景所占内存
	//engine->releaseMesh( sceneMesh );                  // 释放静态网格对象
	//engine->releaseTexture( texture );                 // 释放纹理
	engine->releaseSky( sky );	                       // 释放天空盒对象
	engine->releaseInput( input );                     // 释放输入接口
	engine->releaseCamera( camera );                   // 释放摄像机对象
	engine->releaseText( text );                       // 释放文字对象

	// 释放光线引擎对象
	LightEngineRelease( engine );

	return 0;
}