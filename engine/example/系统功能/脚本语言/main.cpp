

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 脚本语言演示程序
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightScript *script;	

	// 创建光线引擎实例
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // 窗口显示模式
	engineDesc.displayMode.window.x       = 200;                // 窗口左上角 x 坐标
	engineDesc.displayMode.window.y       = 150;                // 窗口左上角 y 坐标
	engineDesc.displayMode.window.width   = 640;                // 窗口宽度
	engineDesc.displayMode.window.height  = 480;                // 窗口高度
	engine = LightEngineCreate( engineDesc );
	
	// 关闭垂直同步
	engine->disable( LIGHT_SWAP_INTERVAL );

	// 创建脚本对象
	LightScriptDesc scriptDesc;
	script = engine->createScript( scriptDesc );

	// 将脚本文件读入内存
	script->load( "..\\example\\系统功能\\脚本语言\\script.as" );

	// 编译脚本文件
	if( !script->build( NULL ) )
	{
		// 指定要执行的函数
		int f = script->getFunctionIDByName( NULL, "main" );
		script->prepare( f );

		// 执行脚本文件
		script->execute();
	}
	else
		MessageBox( 0, "脚本语法错误，编译失败，请修改脚本后重新运行！", "脚本语法错误", MB_OK );

	// 释放脚本对象
	engine->releaseScript( script );

	// 释放光线引擎实例
	LightEngineRelease( engine );

	return 0;
}