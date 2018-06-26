

#include "windows.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��ʾ������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightText   *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ��������ʵ��
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ȱʡ����
	// ����������ɫ
	text->color( 0, 255, 0 );
	// ���ù��λ��
	text->setTextPos( 20, 20 );
	// ��ʾ����
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// ���ֱ���
	/* �������� */
	text->setFont( "���Ĳ���",     // ָ������
		         24,          // ָ������߶�
			     0,           // ָ��������
				 0,           // ָ�����������(FW_BOLD=700)
				 0,           // ָ���Ƕ�(1/10��)				 
				 0,           // ָ���Ƿ�б��
				 0,           // ָ���Ƿ����»���
				 0,           // ָ���Ƿ���StrikeOut����
				 0            // ָ���������
				 );
	text->color( 255, 255, 0 );
	// �������ֱ���ɫ
	text->backColor( 0, 0, 255 );
	// �������ֱ���ģʽΪ��͸��
	text->setBackMode( LIGHT_OPAQUE );
	text->setTextPos( 20, 55 );
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// б��
	text->setFont( "����", 28, 0, 0, 0, 1, 0, 0, 0 );				 
	text->color( 255, 0, 0 );
	text->setBackMode( LIGHT_TRANSPARENT );
	text->setTextPos( 20, 90 );
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// �»���
	text->setFont( "����", 28, 0, 0, 0, 0, 1, 0, 0 );				 
	text->color( 255, 255, 0 );
	text->setTextPos( 20, 128 );
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// ɾ����
	text->setFont( "����Ҧ��", 28, 0, 0, 0, 0, 0, 1, 0 );				 
	text->color( 0, 0, 255 );
	text->setTextPos( 20, 170 );
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// ��ת
	text->setFont( "��������", 28, 0, 0, 0, 1, 0, 0, 0 );				 
	text->color( 255, 0, 255 );
	text->setTextPos( 20, 210 );
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// �ּ��
	text->setFont( "����", 24, 0, 0, 0, 0, 0, 0, 0 );				 
	text->color( 255, 255, 255 );
	// �����ּ��
	text->setCharSpace( 10 );
	text->setTextPos( 20, 245 );
	text->drawText("��ӭʹ�ù�����Ϸ����");

	// ������ʾ
	engine->swapBuffers();

	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷ����ֶ���
	engine->releaseText( text );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}