

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ��Ⱦ������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine      *engine;
	LightCamera      *camera;
	LightTerrain     *terrain;
	LightTexture     *texture[3];
	LightSky         *sky;	
	LightText        *text;
	LightTextureDesc textureDesc;
	vec3_t start = { 100, 100, 50 };
	vec3_t end   = { 1000, 1000, 50  };
	float x, y, z, step = 0.05f;
	unsigned long time, lasttime;
	float rotate;
	int i;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ʹ�� 3DSMAX ����ϵ
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// �������
	terrain = engine->NewTerrain();
	for( i=0; i<3; i++ )
		texture[i] = engine->createTexture( textureDesc );
	// ��������������ڴ�	
	texture[0]->load( "..\\resource\\terrain\\grass.bmp" );
	texture[1]->load( "..\\resource\\terrain\\stone.bmp" );
	texture[2]->load( "..\\resource\\terrain\\shadow.tga" );	
	for( i=0; i<3; i++ )
		terrain->SetTexture( i, texture[i] );
	// ���õ��δ�ש��С����Ⱥ͸߶ȣ�
	terrain->setTile( 32, 32 );
	// ���������ݶ����ڴ�
	//terrain->load( "..\\resource\\terrain\\map1024.raw", 0, 1025, 1025, 8 );
	terrain->load( "..\\resource\\terrain\\height.raw", 0, 1025, 1025, 16 );
	// ���õ�����ʾƷ��
	//terrain->SetLODFactor( 2.5, 25 ); // ���ٶ�
	terrain->SetLODFactor( 5, 50 ); // ��Ʒ��

	// ������պ�
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // �������
	VEC3( skyDesc.box.size, 64, 64, 64 );            // ��պд�С
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
	
	// ��ʼ��ʱ�����
	rotate = 0.0;
	lasttime = engine->getTickCount();

	// ��ʼ�������λ��
	x = start[0];
	y = start[1];
	z = start[2];
	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// ���������
		z = terrain->GetHeight( x, y ) + 25;
		camera->lookAt( x, y, z, end[0], end[1], end[2], 0, 0, 1 );
		
		// ��ʾ��պ�
		sky->render();

		//��ʾ����
		//terrain->RenderMode( 0 );
		terrain->render();

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );

		// ��ʾ��ʾ��Ϣ
		sprintf( fps, "��������: %d", terrain->GetTrianglesCount() );
		text->setTextPos( 40, 380 );
		text->drawText( fps );
		
		// ����ͼ����ת�Ƕ�
		time = engine->getTickCount();
		rotate += ( time - lasttime ) * 0.025f;
		lasttime = time;
		if( rotate > 360 )
			rotate -= 360;

		// ���������·��
		if( x < end[0]-100 )
			x += step;
		else
			x = start[0];
		if( z < end[2]-100 )
			z += step;
		else
			z = start[2];

        // ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseSky( sky );        // �ͷ���ն���
	//terrain = engine->NewTerrain(); // �ͷŵ��ζ���
	for( i=0; i<3; i++ )              // �ͷŵ�������
		engine->releaseTexture( texture[i] );
	engine->releaseText( text );      // �ͷ����ֶ���
	engine->releaseCamera( camera );  // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}