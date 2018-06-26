

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ��־��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightLog *log;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engine = LightEngineCreate( engineDesc );

	// ������־ʵ��
	LightLogDesc logDesc;
	log = engine->createLog( logDesc );
	
	// ����־�ļ�
	log->open( "testlog.txt" );

	// �����־��Ϣ
	log->message( "��������ʾ�������棨LightEngine���ḻ����־����\r\n\r\n" );
	log->debug( "����һ��������Ϣ\r\n" );	
	log->warning( "����һ��������Ϣ\r\n" );
	log->error( "����һ��������Ϣ\r\n" );

	// �ر���־�ļ���Ŀǰ��ʱ�� NULL ��
	log->close( NULL );

	// ��ʾ��ʾ��Ϣ
	MessageBox( 0, "��־�ļ� testlog.txt �Ѿ����ɣ�", "��ʾ", MB_OK );

	// �ͷ���־ʵ��
	engine->releaseLog( log );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}