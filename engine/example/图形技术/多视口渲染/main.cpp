

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ���ӿ���Ⱦ��ʾ����
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

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ʹ�� 3DSMAX ����ϵͳ(Z->UP��
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// ���ùؼ�ɫ��Ĭ�Ͻ��ã�
	engine->enable( LIGHT_KEY_COLOR );
	// ���ùؼ�ɫ��͸��ɫ��Ĭ��ֵΪ��ɫ 0��0��0 ��
	engine->setKeyColor( 255, 0, 0 );

	// �رմ�ֱͬ����Ĭ�Ͽ�����
	engine->disable( LIGHT_SWAP_INTERVAL );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// �������ʶ���
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	// ����̬�����ļ������ڴ�
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	scene = engine->createMesh( meshDesc );
	scene->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// ������պ�
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // �������
	VEC3( skyDesc.box.size, 64, 64, 64 );            // ��պд�С
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

	// �������������
	LightCameraDesc cameraDesc;
	// �����������
	camera = engine->createCamera( cameraDesc );
	// �����������
	camera_top = engine->createCamera( cameraDesc );
	camera_top->viewport( 495, 30, 100, 75 );
	camera_top->lookAt( 0, 0, 100,  0, 0, 0,  0, -1, 0 );
	// ����������ת�����
	camera_reverse = engine->createCamera( cameraDesc );
	camera_reverse->viewport( 30, 30, 100, 75 );	

	vec3_t pos, rotate, translation, eye, center, up;

	do
	{
		for( int i=0; i<3; i++ )
		{
			// �����Ļ����
			if( i == 0 )
				engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
			else
				engine->clear( LIGHT_DEPTH_BUFFER_BIT );
            
			if( i == 0 )
			{
				// ���������λ�úͷ���				
				VEC3( pos, 0, 0, 5 );                // ��תԭ��
				VEC3( rotate, angle, -ANGLE_TO_RADIAN(5), 0 ); // ��ת�Ƕ�
				VEC3( translation, 0, 0, 0 );           // ƽ��ʸ��
				camera->rotate( pos, rotate, 15, translation, TRUE, eye, center, up );
				gVectorAdd( pos, eye, eye );
				gVectorAdd( pos, center, center );
				gVectorAdd( pos, up, up );
				camera->lookAt( center[0], center[1], center[2],  eye[0], eye[1], eye[2],  up[0], up[1], up[2] );
				// ����һ���������Ϊ��ǰ�����
				camera->active();
			}
			else
			{
				if( i == 1 )
				{
					// �����ӿڱ߿�ͱ���
					brush->color( 0, 0, 255 );
					brush->rectangle2D( 492, 27, 598, 108 );
					brush->color( 0, 0, 0 );
					brush->rectangle2D( 495, 30, 595, 105 );
					// �����ӿڱ���
					brush->color( 0, 0, 255 );
					brush->rectangle2D( 27, 27, 133, 108 );
					brush->color( 0, 0, 0 );
					brush->rectangle2D( 30, 30, 100, 75 );
					// ���ڶ����������Ϊ��ǰ�����					
					camera_top->active();
				}
				else
				{
					// ���������������Ϊ��ǰ�����
					camera_reverse->lookAt( center[0], center[1], center[2],  eye[0], eye[1], eye[2],  up[0], up[1], up[2] );
					camera_reverse->active();					
				}
			}

			if( i != 1 )
				// ��Ⱦ��պ�
				sky->render();

			// ��Ⱦ��̬����
			scene->render();

			if( i == 0 )
			{
				// ��ʾ֡�٣�FPS��
				sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
				text->color( 0, 255, 0 );
				text->setTextPos( 40, 400 );
				text->drawText( string );
			}
		}

		// ��ת�����
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
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���	
	engine->releaseCamera( camera_reverse );  // �ͷ����������
	engine->releaseCamera( camera_top );
	engine->releaseCamera( camera );	
	engine->releaseSky( sky );                // �ͷ���ն���	
	engine->releaseMesh ( scene );            // �ͷž�̬������ռ�ڴ�	
	engine->releaseBrush( brush );            // �ͷŻ��ʶ���	
	engine->releaseInput( input );            // �ͷ�����ӿ�	
	engine->releaseText( text );	          // �ͷ����ֶ���

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}