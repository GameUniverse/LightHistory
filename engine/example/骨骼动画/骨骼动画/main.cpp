

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine *engine;
LightCamera *camera;
LightText *text;
LightSkeleton *skeleton;
LightInput *input;

// ����������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int seq = 0;
	char string[100];

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

	// ��������ʵ��
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );
	
	camera->lookAt( 0, 3.5, 11,  0, 3.5, 0,  0, 1, 0 );

	// �����������ļ������ڴ�
	LightSkeletonDesc skeletonDesc;
	skeleton = engine->createSkeleton( skeletonDesc );
	//skeleton->load( "..\\resource\\skeleton\\fighter\\fighter.cfg" );
	skeleton->load( "..\\resource\\skeleton\\knight-errant\\knight-errant.actor" );
	// ���ù�������ϸ�ڵȼ�
	skeleton->setLodLevel( 0.8f );
	// ���ù�������ģ�Ͷ���״̬
	skeleton->animation( 0 );

	do
	{
		// �����Ļ����
		engine->clearColor( 0, 0, 0, 0 );
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ��������
		skeleton->render();
		
		// ��ʾ��ʾ��Ϣ
		/*sprintf( string, "�� <������> �л�������%d", seq );
		text->color( 0, 255, 0 );
		text->setTextPos( 400, 400 );
		text->drawText( string );*/

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// ������ʾ
		engine->swapBuffers();

		// �任ģ�Ͷ���
		DWORD key = input->getKey();
		if( key == KEY_MOUSE_BUTTON0 )
		{
			seq++;
			if( seq > 0 )
				seq = 0;
			// ���ù�������
			skeleton->animation( seq );
		}			
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseSkeleton( skeleton );  // ���ڴ����ͷŹ��������ļ�
	engine->releaseInput( input );        // �ͷ�����ӿ�
	engine->releaseCamera( camera );      // �ͷ����������
	engine->releaseText( text );          // �ͷ�����ʵ��

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );
	
	return 0;
}