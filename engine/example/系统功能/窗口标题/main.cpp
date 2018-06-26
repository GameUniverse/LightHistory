

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ���ڱ�����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightInput  *input;
	LightText   *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 400;                // ���ڿ��
	engineDesc.displayMode.window.height  = 300;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );
			
	// ��ʾ��ʾ��Ϣ
	text->color( 0, 255, 0 );
	text->setTextPos( 115, 122 );
	text->drawText("�밴�ո���ı䴰�ڱ���......");
	engine->swapBuffers();

	// �ȴ��û�����������
	do
	{
	} while( input->getKey() != KEY_SPACE && engine->dispatchMessage() );

	// �ı䴰�ڱ���
	engine->setString( LIGHT_WINDOW_CAPTION, "��ӭʹ�ù������� LightEngine !" );
	   
	// ��ʾ��ʾ��Ϣ
	engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
	text->setTextPos( 145, 122 );
	text->drawText("�밴 ENTER ���أ�");
	engine->swapBuffers();

	// �ȴ��û����� ENTER ��
	do
	{
	} while( !input->getKeyState(KEY_RETURN) && engine->dispatchMessage() );
		
	// �ͷŷ���Ķ���
	engine->releaseInput( input );  // �ͷ�����ӿ�
	engine->releaseText( text );  // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}