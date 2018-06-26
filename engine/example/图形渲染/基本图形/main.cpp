

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ����ͼ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine   *engine;
	LightTexture  *ground;
	LightBrush    *brush;
	LightCamera   *camera;
	LightText     *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 400;                // ���ڿ��
	engineDesc.displayMode.window.height  = 300;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// �������ʶ���
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	// �����������
	LightTextureDesc textureDesc;
	ground = engine->createTexture( textureDesc );
	ground->load( "..\\resource\\image\\wood.dds" );

	// �������������
	camera->lookAt( 0, 6.8, 3.8,  0, 0, 0.5,  0, 0, 1 );
			
	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦһ�������
		vertex_t vertex[4];
		VEC3( vertex[0].position, -2.5,  2.5, 0 ); // ��������
		VEC3( vertex[1].position, -2.5, -2.5, 0 );
		VEC3( vertex[2].position,  2.5, -2.5, 0 );
		VEC3( vertex[3].position,  2.5,  2.5, 0 );
		VEC3( vertex[0].normal, 0, 0, 1 ); // ����
		VEC3( vertex[1].normal, 0, 0, 1 );
		VEC3( vertex[2].normal, 0, 0, 1 );
		VEC3( vertex[3].normal, 0, 0, 1 );
		VEC2( vertex[0].texcoord, 0, 0 ); // ��������
		VEC2( vertex[1].texcoord, 0, 1 );
		VEC2( vertex[2].texcoord, 1, 1 );
		VEC2( vertex[3].texcoord, 1, 0 );
		ground->active(); // ������������
		brush->polygon( vertex, 4 ); // ��Ⱦ�����

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 245 );
		text->drawText( fps );
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���	
	engine->releaseTexture( ground );  // �ͷ��������	
	engine->releaseBrush( brush );     // �ͷŻ��ʶ���	
	engine->releaseText( text );       // �ͷ����ֶ���	 
	engine->releaseCamera( camera );   // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;	
}