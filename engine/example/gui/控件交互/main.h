

#define _WIN32_WINNT 0x4000

#include "windows.h"
#include "Winuser.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#include "..\\..\\..\\include\\helper.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// 包含 CEGUI 头文件
#include "RendererModules/OpenGLGUIRenderer/openglrenderer.h"
#include "CEGUI.h"
#include "CEGUIDefaultResourceProvider.h"

#include "utility.h"


/*************************************************************************
        member functions used as event handlers
*************************************************************************/
bool handleQuit(const CEGUI::EventArgs& e);
bool horzMoveHandler(const CEGUI::EventArgs& e);
bool vertMoveHandler(const CEGUI::EventArgs& e);
bool vscrollHandler(const CEGUI::EventArgs& e);

// some free functions used as event handlers
bool sliderHandler(const CEGUI::EventArgs& e);
bool formatChangedHandler(const CEGUI::EventArgs& e);
bool textChangedHandler(const CEGUI::EventArgs& e);