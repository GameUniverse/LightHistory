

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// �ű�������ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightScript *script;	

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );
	
	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �����ű�����
	LightScriptDesc scriptDesc;
	script = engine->createScript( scriptDesc );

	// ���ű��ļ������ڴ�
	script->load( "..\\example\\ϵͳ����\\�ű�����\\script.as" );

	// ����ű��ļ�
	if( !script->build( NULL ) )
	{
		// ָ��Ҫִ�еĺ���
		int f = script->getFunctionIDByName( NULL, "main" );
		script->prepare( f );

		// ִ�нű��ļ�
		script->execute();
	}
	else
		MessageBox( 0, "�ű��﷨���󣬱���ʧ�ܣ����޸Ľű����������У�", "�ű��﷨����", MB_OK );

	// �ͷŽű�����
	engine->releaseScript( script );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}