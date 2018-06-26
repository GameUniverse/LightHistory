

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ��ʾ��ɫ���Գ���
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *image[5];
	LightShader *shader;
	LightText *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 400;                // ���ڿ��
	engineDesc.displayMode.window.height  = 300;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����ͼ�����
	LightImageDesc imageDesc;	
	image[0] = engine->createImage( imageDesc );
	image[1] = engine->createImage( imageDesc );
	image[2] = engine->createImage( imageDesc );
	image[3] = engine->createImage( imageDesc );
	image[4] = engine->createImage( imageDesc );	

	// ��ʹ�ùؼ�ɫ��ͼ���ļ������ڴ�
	image[4]->load("..\\resource\\image\\keycolor.bmp");

	// ��ֹ�ؼ�ɫ
	engine->enable( LIGHT_KEY_COLOR );

	// ��ͼ���ļ������ڴ�	
	image[0]->load("..\\resource\\image\\a.bmp");
	image[1]->load("..\\resource\\image\\d.bmp");
	image[2]->load("..\\resource\\image\\b.bmp");
	image[3]->load("..\\resource\\image\\c.bmp");

	// ������ɫ���Զ���
	LightShaderDesc shaderDesc;
	shader = engine->createShader( shaderDesc );
	if( shader == NULL )
	{
		MessageBox( 0, "�Կ���֧�� OpenGL ��ɫ���� 1.0 �汾", "����", MB_OK );
		return 1;
	}	

	// ���� GLSL ��ɫ���Գ���
	shader->load( "..\\example\\ͼ�μ���\\��ɫ����\\vertex.vert", "..\\example\\ͼ�μ���\\��ɫ����\\fragment.frag" );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ������ɫ����
		shader->begin();

		// ������ʾͼ��
		image[0]->render( 69, 6 );

		// ��תͼ��
		LightImageRenderDesc renderDesc;		
		renderDesc.flags = LIGHT_IMAGE_REVERSALX | LIGHT_IMAGE_REVERSALY;
		image[1]->renderDesc( 203, 6, renderDesc );
		
		// ����ͼ��		
		renderDesc.dest_rect.left = 69;
		renderDesc.dest_rect.top = 140;
		renderDesc.dest_rect.right = 165;
		renderDesc.dest_rect.bottom = 236;
		renderDesc.flags = LIGHT_IMAGE_DESTRECT;
		image[2]->renderDesc( 40, 108, renderDesc );

		// ��ϴ��йؼ�ɫ��͸��ɫ����ͼ��        
		renderDesc.blend = 0.8f;
		renderDesc.flags = LIGHT_IMAGE_BLEND;
		image[4]->renderDesc( 135, 75, renderDesc );
		
		// ��ʾָ�������ͼ��		
		renderDesc.sour_rect.left = 30;
		renderDesc.sour_rect.top = 30;
		renderDesc.sour_rect.right = 90;
		renderDesc.sour_rect.bottom = 90;
		renderDesc.flags = LIGHT_IMAGE_SOURRECT;
		image[3]->renderDesc( 40, 108, renderDesc );

		// ��ָ��������ʾͼ��		
		renderDesc.lighteness = 0.5f;
		renderDesc.flags = LIGHT_IMAGE_LIGHTENESS;
		image[3]->renderDesc( 280, 75, renderDesc );

		// ��תͼ��
		renderDesc.rotate = 25;
		renderDesc.flags = LIGHT_IMAGE_ROTATE;
		image[3]->renderDesc( 203, 110, renderDesc );

		// ֹͣ������ɫ����
		shader->end();

		// ��ʾ��ʾ��Ϣ
		text->color( 255, 0, 0 );
		text->setTextPos( 105, 60 );
		text->drawText( "������ʾ" );
		text->setTextPos( 252, 60 );
		text->drawText( "��ת" );
		text->setTextPos( 102, 180 );
		text->drawText( "����" );
		text->setTextPos( 258, 165 );
		text->drawText( "��ת" );
		text->setTextPos( 182, 130 );
		text->drawText( "���" );
		text->setTextPos( 58, 130 );
		text->drawText( "����" );
		text->setTextPos( 335, 123 );
		text->drawText( "����" );

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
	engine->releaseShader( shader );   // �ͷ���ɫ���Զ���
	engine->releaseImage( image[0] );  // ���ڴ����ͷ�ͼ���ļ�
	engine->releaseImage( image[1] );
	engine->releaseImage( image[2] );
	engine->releaseImage( image[3] );
	engine->releaseImage( image[4] );	
	engine->releaseText( text );       // �ͷ�����ʵ��

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}