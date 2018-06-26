

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��Ϸҡ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightInput  *input;
	LightText   *text;
	LightBrush  *brush;

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

	// �������ʶ���
	LightBrushDesc brushDesc;
	brush = engine->createBrush( brushDesc );

	unsigned long key;
	POINT point;
	char str[100];

	// �ȴ��û�������Ϸ�� A ��������ģʽ��
	do
	{
		// ��ѯ����ʾ��Ϸ��λ��
		point.x = input->getKeyState( KEY_JOYSTICK_X );
		point.y = input->getKeyState( KEY_JOYSTICK_Y );
		sprintf(str, "��Ϸ��λ��: %d, %d", point.x, point.y);
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		text->color( 255, 0, 0 );
		text->setTextPos( 130, 107 );
		text->drawText( str );
		int x, y;
		x = point.x / 164;
		y = point.y / 218;
		brush->color( 255, 255, 0 );
		brush->line2D( x - 10, y, x + 10, y );
		brush->line2D( x , y - 10, x, y + 10 );

		// ��ʾ��ʾ��Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 135, 137 );
		text->drawText("�밴��Ϸ�� A ��......");
		text->setTextPos( 80, 160 );
		text->drawText("�����û�а�װ��Ϸ�ˣ��밴 ESC ���˳���");

		engine->swapBuffers();

		// ������Ϣ
		engine->dispatchMessage();
	} while( !input->getKeyState( KEY_JOYSTICK_BUTTON0 ) && !input->getKeyState( KEY_ESCAPE ) ); // ���� A ��״̬������ģʽ��
	   
	// ��ʾ��ʾ��Ϣ
	engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
	text->setTextPos( 140, 123 );
	text->drawText("�밴��Ϸ�� B ���˳���");
	engine->swapBuffers();

	// �ȴ��û�������Ϸ�� B ��������ģʽ��
	do
	{
		// ��ȡ����
		key = input->getKey();

		// ������Ϣ
		engine->dispatchMessage();
	} while( key != KEY_JOYSTICK_BUTTON1 && key != KEY_ESCAPE ); // ���� A ��״̬������ģʽ��

	// �ͷŷ���Ķ���
	engine->releaseBrush( brush );  // �ͷŻ��ʶ���
	engine->releaseInput( input );  // �ͷ�����ӿ�
	engine->releaseText( text );    // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}