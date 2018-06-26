

#include "main.h"

/* CEGUI 窗口消息监听函数 */ 
LRESULT CALLBACK CEGUIWindowMessageProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static bool ShowCursorFlag = TRUE;

	// 处理窗口消息
	CEGUI::System& guiSystem = CEGUI::System::getSingleton();
	switch (uMsg)
	{
	case WM_IME_CHAR:
		char cchar[2];
		wchar_t wchar;
		
		cchar[0] = HIBYTE( LOWORD( wParam ) );
		cchar[1] = LOBYTE( LOWORD( wParam ) );
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cchar, 2, &wchar, 1);	
		guiSystem.injectChar( wchar );//CEGUI::utf32( ));
		break;

	case WM_CHAR:
		if( !(wParam & 0x80) )
			guiSystem.injectChar( wParam );
		break;

	case WM_KEYDOWN:
		//guiSystem.injectKeyDown(convert_vkey_to_scode(wParam));
		guiSystem.injectKeyDown( ConvertVirtualKeyToScanCode( wParam ) );
		break;

	case WM_KEYUP:
		//guiSystem.injectKeyUp(convert_vkey_to_scode(wParam));
		guiSystem.injectKeyUp( ConvertVirtualKeyToScanCode( wParam ) );
		break;

	case WM_MOUSELEAVE:
		// 鼠标离开窗口
	case WM_NCMOUSEMOVE:
		// 鼠标在非客户区移动，这时候让系统鼠标显示，因为玩家可能需要点住这里拖动窗口
		if( !ShowCursorFlag )
		{
			ShowCursor( TRUE );
			CEGUI::MouseCursor::getSingleton().hide();
			ShowCursorFlag = TRUE;
		}
		break;

	case WM_MOUSEMOVE:
		// 鼠标在客户区移动，这时候让系统鼠标隐藏，显示用户自定义鼠标
		if( ShowCursorFlag )
		{
			CEGUI::MouseCursor::getSingleton().show();
			ShowCursor(FALSE);
			ShowCursorFlag = FALSE;
			
			// 跟踪鼠标事件
			TRACKMOUSEEVENT MouseEvent;
			ZeroMemory( &MouseEvent, sizeof(MouseEvent) );
			MouseEvent.cbSize = sizeof(MouseEvent);
			MouseEvent.dwFlags = TME_LEAVE;
			MouseEvent.hwndTrack = hwnd;
			TrackMouseEvent( &MouseEvent );
		}
		guiSystem.injectMousePosition( LOWORD( lParam ), HIWORD( lParam ) );
		break;

	case WM_LBUTTONDOWN:
		guiSystem.injectMouseButtonDown(CEGUI::LeftButton);
		break;

	case WM_LBUTTONUP:
        guiSystem.injectMouseButtonUp(CEGUI::LeftButton);
        break;

    case WM_RBUTTONDOWN:
        guiSystem.injectMouseButtonDown(CEGUI::RightButton);
        break;

    case WM_RBUTTONUP:
        guiSystem.injectMouseButtonUp(CEGUI::RightButton);
        break;

    case WM_MBUTTONDOWN:
        guiSystem.injectMouseButtonDown(CEGUI::MiddleButton);
        break;

    case WM_MBUTTONUP:
        guiSystem.injectMouseButtonUp(CEGUI::MiddleButton);
        break;

    //case WM_MOUSEWHEEL:
        //guiSystem.injectMouseWheelChange(static_cast<f32>(static_cast<s16>(HIWORD(wParam))) / static_cast<f32>(120));
    //    break;

	case WM_SIZE:
		/*if (CEGUI::System::getSingletonPtr() != NULL)
		{
			CEGUI::Renderer *pRenderer = CEGUI::System::getSingleton().getRenderer();
			if (pRenderer != NULL)
			{
				pRenderer->getSize();
				CEGUI::EventArgs args;
				pRenderer->fireEvent(CEGUI::Renderer::EventDisplaySizeChanged, args, CEGUI::Renderer::EventNamespace);
			}
		}*/
		break;

	default:
		break;
	}

	return 0;
}

/* 将 Windows 虚拟键转换为 CEGUI 定义的扫描码 */
CEGUI::Key::Scan ConvertVirtualKeyToScanCode( WPARAM VirtualKey )
{
	static bool Initial = FALSE;
	static CEGUI::Key::Scan KeyMapping[256];

	// 初始化按键映射图
	if( Initial == FALSE )
	{
		KeyMapping[VK_BACK]		= CEGUI::Key::Backspace;		// backspace
		KeyMapping[VK_TAB]		= CEGUI::Key::Tab;				// tab
		KeyMapping[VK_RETURN]		= CEGUI::Key::Return;			// enter
		KeyMapping[VK_SHIFT]		= CEGUI::Key::LeftShift;		// shift, left shift
		KeyMapping[VK_CONTROL]	= CEGUI::Key::LeftControl;		// ctrl, left ctrl
		KeyMapping[VK_MENU]		= CEGUI::Key::LeftAlt;			// alt, left alt
		KeyMapping[VK_PAUSE]		= CEGUI::Key::Pause;			// pause
		KeyMapping[VK_CAPITAL]	= CEGUI::Key::Capital;			// capital
		KeyMapping[VK_ESCAPE]		= CEGUI::Key::Escape;			// escape
		KeyMapping[VK_SPACE]		= CEGUI::Key::Space;			// space
		KeyMapping[VK_PRIOR]		= CEGUI::Key::PageUp;			// pageup
		KeyMapping[VK_NEXT]		= CEGUI::Key::PageDown;			// pagedown
		KeyMapping[VK_HOME]		= CEGUI::Key::Home;				// home
		KeyMapping[VK_END]		= CEGUI::Key::End;				// end
		KeyMapping[VK_LEFT]		= CEGUI::Key::ArrowLeft;		// left on arrow keyboard
		KeyMapping[VK_RIGHT]		= CEGUI::Key::ArrowRight;		// right on arrow keyboard
		KeyMapping[VK_UP]			= CEGUI::Key::ArrowUp;			// up on arrow keyboard
		KeyMapping[VK_DOWN]		= CEGUI::Key::ArrowDown;		// down on arrow keyboard
		KeyMapping[VK_SNAPSHOT]	= CEGUI::Key::SysRq;			// print screen/sys request
		KeyMapping[VK_INSERT]		= CEGUI::Key::Insert;			// insert
		KeyMapping[VK_DELETE]		= CEGUI::Key::Delete;			// delete
		KeyMapping[VK_HELP]		= CEGUI::Key::F1;				// F1 / HELP

		KeyMapping[0x30]			= CEGUI::Key::Zero;				// 0
		KeyMapping[0x31]			= CEGUI::Key::One;				// 1
		KeyMapping[0x32]			= CEGUI::Key::Two;				// 2
		KeyMapping[0x33]			= CEGUI::Key::Three;			// 3
		KeyMapping[0x34]			= CEGUI::Key::Four;				// 4
		KeyMapping[0x35]			= CEGUI::Key::Five;				// 5
		KeyMapping[0x36]			= CEGUI::Key::Six;				// 6
		KeyMapping[0x37]			= CEGUI::Key::Seven;			// 7
		KeyMapping[0x38]			= CEGUI::Key::Eight;			// 8
		KeyMapping[0x39]			= CEGUI::Key::Nine;				// 9

		KeyMapping[0x41]			= CEGUI::Key::A;				// A
		KeyMapping[0x42]			= CEGUI::Key::B;				// B
		KeyMapping[0x43]			= CEGUI::Key::C;				// C
		KeyMapping[0x44]			= CEGUI::Key::D;				// D
		KeyMapping[0x45]			= CEGUI::Key::E;				// E
		KeyMapping[0x46]			= CEGUI::Key::F;				// F
		KeyMapping[0x47]			= CEGUI::Key::G;				// G
		KeyMapping[0x48]			= CEGUI::Key::H;				// H
		KeyMapping[0x49]			= CEGUI::Key::I;				// I
		KeyMapping[0x4A]			= CEGUI::Key::J;				// J
		KeyMapping[0x4B]			= CEGUI::Key::K;				// K
		KeyMapping[0x4C]			= CEGUI::Key::L;				// L
		KeyMapping[0x4D]			= CEGUI::Key::M;				// M
		KeyMapping[0x4E]			= CEGUI::Key::N;				// N
		KeyMapping[0x4F]			= CEGUI::Key::O;				// O
		KeyMapping[0x50]			= CEGUI::Key::P;				// P
		KeyMapping[0x51]			= CEGUI::Key::Q;				// Q
		KeyMapping[0x52]			= CEGUI::Key::R;				// R
		KeyMapping[0x53]			= CEGUI::Key::S;				// S
		KeyMapping[0x54]			= CEGUI::Key::T;				// T
		KeyMapping[0x55]			= CEGUI::Key::U;				// U
		KeyMapping[0x56]			= CEGUI::Key::V;				// V
		KeyMapping[0x57]			= CEGUI::Key::W;				// W
		KeyMapping[0x58]			= CEGUI::Key::X;				// X
		KeyMapping[0x59]			= CEGUI::Key::Y;				// Y
		KeyMapping[0x5A]			= CEGUI::Key::Z;				// Z

		KeyMapping[VK_LWIN]		= CEGUI::Key::LeftWindows;		// L Windows
		KeyMapping[VK_RWIN]		= CEGUI::Key::RightWindows;		// R Windows
		KeyMapping[VK_APPS]		= CEGUI::Key::AppMenu;			// App key
		KeyMapping[VK_SLEEP]		= CEGUI::Key::Sleep;			// sleep key

		KeyMapping[VK_NUMPAD0]	= CEGUI::Key::Numpad0;			// 0 on num pad
		KeyMapping[VK_NUMPAD1]	= CEGUI::Key::Numpad1;			// 1 on num pad
		KeyMapping[VK_NUMPAD2]	= CEGUI::Key::Numpad2;			// 2 on num pad
		KeyMapping[VK_NUMPAD3]	= CEGUI::Key::Numpad3;			// 3 on num pad
		KeyMapping[VK_NUMPAD4]	= CEGUI::Key::Numpad4;			// 4 on num pad
		KeyMapping[VK_NUMPAD5]	= CEGUI::Key::Numpad5;			// 5 on num pad
		KeyMapping[VK_NUMPAD6]	= CEGUI::Key::Numpad6;			// 6 on num pad
		KeyMapping[VK_NUMPAD7]	= CEGUI::Key::Numpad7;			// 7 on num pad
		KeyMapping[VK_NUMPAD8]	= CEGUI::Key::Numpad8;			// 8 on num pad
		KeyMapping[VK_NUMPAD9]	= CEGUI::Key::Numpad9;			// 9 on num pad
		KeyMapping[VK_MULTIPLY]	= CEGUI::Key::Multiply;			// * on num pad
		KeyMapping[VK_ADD]		= CEGUI::Key::Add;				// + on num pad
		KeyMapping[VK_SEPARATOR]	= 
		KeyMapping[VK_SUBTRACT]	= CEGUI::Key::Subtract;			// - on num pad
		KeyMapping[VK_DECIMAL]	= CEGUI::Key::Decimal;			// . on num pad
		KeyMapping[VK_DIVIDE]		= CEGUI::Key::Divide;			// / on num pad

		KeyMapping[VK_F1]			= CEGUI::Key::F1;				// F1
		KeyMapping[VK_F2]			= CEGUI::Key::F2;				// F2
		KeyMapping[VK_F3]			= CEGUI::Key::F3;				// F3
		KeyMapping[VK_F4]			= CEGUI::Key::F4;				// F4
		KeyMapping[VK_F5]			= CEGUI::Key::F5;				// F5
		KeyMapping[VK_F6]			= CEGUI::Key::F6;				// F6
		KeyMapping[VK_F7]			= CEGUI::Key::F7;				// F7
		KeyMapping[VK_F8]			= CEGUI::Key::F8;				// F8
		KeyMapping[VK_F9]			= CEGUI::Key::F9;				// F9
		KeyMapping[VK_F10]		= CEGUI::Key::F10;				// F10
		KeyMapping[VK_F11]		= CEGUI::Key::F11;				// F11
		KeyMapping[VK_F12]		= CEGUI::Key::F12;				// F12
		KeyMapping[VK_F13]		= CEGUI::Key::F13;				// F13
		KeyMapping[VK_F14]		= CEGUI::Key::F14;				// F14
		KeyMapping[VK_F15]		= CEGUI::Key::F15;				// F15

		KeyMapping[VK_NUMLOCK]	= CEGUI::Key::NumLock;			// num lock on num pad
		KeyMapping[VK_SCROLL]		= CEGUI::Key::ScrollLock;		// scroll lock


		KeyMapping[VK_LSHIFT]		= CEGUI::Key::LeftShift;		// L shift
		KeyMapping[VK_RSHIFT]		= CEGUI::Key::RightShift;		// R shift
		KeyMapping[VK_LCONTROL]	= CEGUI::Key::LeftControl;		// L ctrl
		KeyMapping[VK_RCONTROL]	= CEGUI::Key::RightControl;		// R ctrl
		KeyMapping[VK_LMENU]		= CEGUI::Key::LeftAlt;			// L alt
		KeyMapping[VK_RMENU]		= CEGUI::Key::RightAlt;			// R alt

		Initial = TRUE;
	}

	return KeyMapping[VirtualKey & 0xFF];
}
