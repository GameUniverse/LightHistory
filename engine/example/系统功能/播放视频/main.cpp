

#include "windows.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ������Ƶ��ʾ����
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
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ��������ʵ��
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ������Ƶ(��Ƶ)����
	LightVideoDesc videoDesc;
	video = engine->createVideo( videoDesc );

	// ����Ƶ(��Ƶ)�ļ�
	video->open("..\\resource\\video\\lake.mpg");

	// ����
	video->play();

	// �ȴ���Ƶ�������
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