

#include "windows.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ����������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightSound  *s1, *s2;
	LightText   *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 400;                // ���ڿ��
	engineDesc.displayMode.window.height  = 300;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ��������ʵ��
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ������������
	LightSoundDesc soundDesc;
	s1 = engine->createSound( soundDesc );
	s2 = engine->createSound( soundDesc );

	// �������ļ���ȡ���ڴ���
	s1->load( "..\\resource\\sound\\start.wav" );
	s2->load( "..\\resource\\sound\\destory.wav" );
	// ����ͬʱ���Ŷ��������֧�ֻ�����
	s1->play();
	s2->play();

	// ��ʾ��ʾ��Ϣ
	text->color( 0, 255, 0 );
	text->setTextPos( 138, 122 );
	text->drawText( "ͬʱ���Ŷ������......" );
	engine->swapBuffers();

	_sleep( 6000 );

	// ֹͣ����
	s1->stop();
	s2->stop();

	// �ͷŷ���Ķ���
	engine->releaseText( text );  // �ͷ�����ʵ��
	engine->releaseSound( s1 );   // �ͷ���������
	engine->releaseSound( s2 );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return(0);
}