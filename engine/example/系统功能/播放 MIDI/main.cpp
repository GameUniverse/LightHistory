

#include "windows.h"
#include <stdio.h>
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ���� MIDI ��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightVideo  *video;
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

	// ������Ƶ(��Ƶ)����
	LightVideoDesc videoDesc;
	video = engine->createVideo( videoDesc );

	// �� MIDI �ļ�
	video->open("..\\resource\\music\\canyon.mid");
	// ���� MP3
	video->play();

	// ��ʾ��ʾ��Ϣ
	text->color( 0, 255, 0 );
	text->setTextPos( 145, 122 );
	text->drawText("���ڲ��� MIDI ......");				
	engine->swapBuffers();

	// �ȴ� MP3 �������
	do
	{
	} while( video->getState() && engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseVideo( video );  // �ͷ���Ƶ(��Ƶ)����
	engine->releaseText( text );    // �ͷ�����ʵ��

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return(0);
}