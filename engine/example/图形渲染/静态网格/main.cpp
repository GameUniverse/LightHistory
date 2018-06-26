

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��̬������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightMesh   *mesh;
	LightInput  *input;
	LightText   *text;
	char string[100];
	float rotate = 0;
	DWORD lasttime = 0;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// �رմ�ֱͬ����Ĭ�Ͽ�����
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ������̬�������
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	mesh->load( "..\\resource\\mesh\\digger\\digger.3ds" );
	
	camera->lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );
	//camera->LookAt(  0, 200, 1000,  0, 200, 0,  0, 1, 0 );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ��̬����
		mesh->setGlobalOrientationAngleAxis( rotate, 0, 1, 0 );
		mesh->render();

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );

		// ��ת��̬����
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

		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseMesh ( mesh );     // �ͷž�̬�������
	engine->releaseInput( input );    // �ͷ�����ӿ�
	engine->releaseText( text );      // �ͷ����ֶ���
	engine->releaseCamera( camera );  // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}