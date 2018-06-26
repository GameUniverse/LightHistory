

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ���������ʾ����
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

	// ���ô��ڱ���
	engine->setString( LIGHT_WINDOW_CAPTION, "�������" );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ��������
	// KEY_MOUSE_BUTTON0  ������
	// KEY_MOUSE_BUTTON1  ����Ҽ�
	// KEY_MOUSE_BUTTON2  ����м�
	// KEY_MOUSE_X  ���ˮƽ����
	// KEY_MOUSE_Y  ��괹ֱ����
	// KEY_MOUSE_Z  ����������

	unsigned long key;
	POINT point;
	int wheel = 0;
	int step = 0;
	char str[100];

	// �ȴ��û�����������������ģʽ��
	do
	{
		// ��ʾ���λ��
		input->getCursorPos( &point);
		if( step != 3 )
			sprintf( str, "���λ��: %d, %d", point.x, point.y );
		else
			sprintf( str, "����λ�� %d", wheel );
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		text->color( 255, 0, 0 );
		text->setTextPos( 135, 107 );
		text->drawText( str );

		// ��ʾ��ʾ��Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 130, 137 );
		if( step == 0 )
			text->drawText("�밴����������......");
		else
			if( step == 1 )
				text->drawText("�밴����Ҽ�����......");
			else
				if( step == 2 )
				{
					text->drawText("�밴����м�����......");
					text->setTextPos( 110, 165 );
					text->drawText("(������û���м����밴 ESC ��)");
				}
				else
					if( step == 3 )
					{
						text->setTextPos( 70, 137 );
						text->drawText("����������֣�ʹ����λ�ô��� 2000 ......");
						text->setTextPos( 100, 165 );
						text->drawText("(������û�й��֣��밴 ESC ��)");
					}

		engine->swapBuffers();

		// ��ȡһ������ֵ
		key = input->getKey();
		if( step == 0 && key == KEY_MOUSE_BUTTON0 )
			step++;
		else
			if( step == 1 && key == KEY_MOUSE_BUTTON1 )
				step++;
			else
				if( step == 2 && (key == KEY_MOUSE_BUTTON2 || key == KEY_ESCAPE) )
				{
					step++;
					wheel = 0;
				}
				else
					if( step == 3 && key == KEY_ESCAPE )
						step++;

		// ��ȡ������λ��
		// �������ֳ�����Ļ���������ʱ��input->GetKeyState(KEY_MOUSE_Z) ����һ����ֵ��
		// �������ֱ�����Ļ���������ʱ��input->GetKeyState(KEY_MOUSE_Z) ����һ����ֵ��
		// ��������ֹͣ������ʱ��input->GetKeyState(KEY_MOUSE_Z) ���� 0
		wheel += input->getKeyState( KEY_MOUSE_Z );
		if( wheel > 2000 )
			step++;

		// ������Ϣ
		engine->dispatchMessage();
	} while( step <= 3 );
	   
	// ��ʾ��ʾ��Ϣ
	engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
	text->setTextPos( 145, 123 );
	text->drawText("�밴 ENTER ���أ�");
	engine->swapBuffers();

	// �ȴ��û����� ENTER ��������ģʽ��
	do
	{
		// ������Ϣ
		engine->dispatchMessage();
	} while( !input->getKeyState(KEY_RETURN) );

	// �ͷŷ���Ķ���
	engine->releaseInput( input );  // �ͷ�����ӿ�
	engine->releaseText( text );  // �ͷ����ֶ���

	// �ͷŹ����������
	LightEngineRelease( engine );

	return 0;
}