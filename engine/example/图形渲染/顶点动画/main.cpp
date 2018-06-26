

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// MD2 ���㶯����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char string[100];
	LightEngine *engine;
	LightAnimation *animation;
	LightTexture *texture;
	LightCamera *camera;
	LightText   *text;

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

	// ��������������ò���
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// �������㶯������
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\animation\\knight\\knight.pcx" );

	// �������㶯������
	LightAnimationDesc animationDesc;
	animation = engine->createAnimation( animationDesc );
	animation->Load( "..\\resource\\animation\\knight\\knight.md2" );	

	// ���õ�ǰ����
	animation->SetState( 0 );
	
	camera->lookAt( 100, 0, 0,  0, 0, 0,  0, 1, 0 );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ����㶯������
		texture->active();

		// ��Ⱦ���㶯��
		animation->Render();

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( string );
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���	
	engine->releaseAnimation( animation );  // �ͷŶ��㶯������	
	engine->releaseTexture( texture );      // �ͷŶ��㶯������	
	engine->releaseText( text );            // �ͷ����ֶ���	
	engine->releaseCamera( camera );        // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}