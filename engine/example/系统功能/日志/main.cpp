

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 日志演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightLog *log;

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engine = LightEngineCreate( engineDesc );

	// 分配日志实例
	LightLogDesc logDesc;
	log = engine->createLog( logDesc );
	
	// 打开日志文件
	log->open( "testlog.txt" );

	// 输出日志信息
	log->message( "本程序演示光线引擎（LightEngine）丰富的日志功能\r\n\r\n" );
	log->debug( "这是一条调试信息\r\n" );	
	log->warning( "这是一条警告信息\r\n" );
	log->error( "这是一条错误信息\r\n" );

	// 关闭日志文件（目前暂时用 NULL ）
	log->close( NULL );

	// 显示提示信息
	MessageBox( 0, "日志文件 testlog.txt 已经生成！", "提示", MB_OK );

	// 释放日志实例
	engine->releaseLog( log );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}