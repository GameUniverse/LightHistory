/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   input.h
 *  内容:   输入函数
 *
 ****************************************************************************/


/*! \file input.h
 * 输入函数
 * 
 */


/** 输入接口描述符类 */
class LightInputDesc
{
public:

	/** 全局世界坐标 */
	vec3_t position;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightInputDesc()
	{
		memset( this, 0, sizeof(LightInputDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		VEC3( position, 0, 0, 0 );		
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightInput
 * \brief 输入类
 *
 *  本类负责键盘、鼠标、游戏杆的输入和状态查询，所有输入设备采用统一界面，非常方便。
 *  每个 LightInput 实例都必须通过 LightEngine 类的 createInput 方法分配， releaseInput 释放。
 */

class LightInput
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 读取一个按键
	 *		 
	 *  \remarks 按键的定义见头文件。
	 *
	 *  \return 如果函数调用成功，返回最早的一个按键值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual unsigned long getKey( void ) = 0;

	/*! \brief 查询按键状态
	 *	 
	 *  \param key[in] 要查询的按键
	 *
	 *  \remarks 按键的定义见头文件。
	 *
	 *  \return 如果该键处于按下状态，返回非零值；如果该键处于弹起状态，返回零。
	 *
	 *  \see 
	 */
	virtual long getKeyState( unsigned long key ) = 0;

	/*! \brief 查询光标位置
	 *	 
	 *  \param lpPoint[out] 返回光标位置的指针
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual bool getCursorPos( LPPOINT lpPoint ) = 0;

	/*! \brief 设置光标位置
	 *	 
	 *  \param x[in] 光标位置的 x 坐标
	 *
	 *  \param y[in] 光标位置的 y 坐标
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual bool setCursorPos( int x, int y ) = 0;
};


/****************************************************************************
 *
 *      鼠标按键定义
 *
 ****************************************************************************/
#define KEY_MOUSE_X            0x100
#define KEY_MOUSE_Y            0x104
#define KEY_MOUSE_Z            0x108
#define KEY_MOUSE_BUTTON0      0x10C
#define KEY_MOUSE_BUTTON1      0x10D
#define KEY_MOUSE_BUTTON2      0x10E
#define KEY_MOUSE_BUTTON3      0x10F
#define KEY_MOUSE_BUTTON4      0x110
#define KEY_MOUSE_BUTTON5      0x111
#define KEY_MOUSE_BUTTON6      0x112
#define KEY_MOUSE_BUTTON7      0x113

/****************************************************************************
 *
 *      游戏杆按键定义
 *
 ****************************************************************************/
#define KEY_JOYSTICK_X            0x200
#define KEY_JOYSTICK_Y            0x204
#define KEY_JOYSTICK_Z            0x208
#define KEY_JOYSTICK_RX           0x20C
#define KEY_JOYSTICK_RY           0x210
#define KEY_JOYSTICK_RZ           0x214
#define KEY_JOYSTICK_BUTTON0      0x230
#define KEY_JOYSTICK_BUTTON1      0x231
#define KEY_JOYSTICK_BUTTON2      0x232
#define KEY_JOYSTICK_BUTTON3      0x233
#define KEY_JOYSTICK_BUTTON4      0x234
#define KEY_JOYSTICK_BUTTON5      0x235
#define KEY_JOYSTICK_BUTTON6      0x236
#define KEY_JOYSTICK_BUTTON7      0x237
#define KEY_JOYSTICK_BUTTON8      0x238
#define KEY_JOYSTICK_BUTTON9      0x239
#define KEY_JOYSTICK_BUTTON10     0x23A
#define KEY_JOYSTICK_BUTTON11     0x23B
#define KEY_JOYSTICK_BUTTON12     0x23C
#define KEY_JOYSTICK_BUTTON13     0x23D
#define KEY_JOYSTICK_BUTTON14     0x23E
#define KEY_JOYSTICK_BUTTON15     0x23F
#define KEY_JOYSTICK_BUTTON16     0x240
#define KEY_JOYSTICK_BUTTON17     0x241
#define KEY_JOYSTICK_BUTTON18     0x242
#define KEY_JOYSTICK_BUTTON19     0x243
#define KEY_JOYSTICK_BUTTON20     0x244
#define KEY_JOYSTICK_BUTTON21     0x245
#define KEY_JOYSTICK_BUTTON22     0x246
#define KEY_JOYSTICK_BUTTON23     0x247
#define KEY_JOYSTICK_BUTTON24     0x248
#define KEY_JOYSTICK_BUTTON25     0x249
#define KEY_JOYSTICK_BUTTON26     0x24A
#define KEY_JOYSTICK_BUTTON27     0x24B
#define KEY_JOYSTICK_BUTTON28     0x24C
#define KEY_JOYSTICK_BUTTON29     0x24D
#define KEY_JOYSTICK_BUTTON30     0x24E
#define KEY_JOYSTICK_BUTTON31     0x24F

/****************************************************************************
 *
 *      键盘扫描码定义
 *
 ****************************************************************************/
#define KEY_ESCAPE          0x01
#define KEY_1               0x02
#define KEY_2               0x03
#define KEY_3               0x04
#define KEY_4               0x05
#define KEY_5               0x06
#define KEY_6               0x07
#define KEY_7               0x08
#define KEY_8               0x09
#define KEY_9               0x0A
#define KEY_0               0x0B
#define KEY_MINUS           0x0C    /* - on main keyboard */
#define KEY_EQUALS          0x0D
#define KEY_BACK            0x0E    /* backspace */
#define KEY_TAB             0x0F
#define KEY_Q               0x10
#define KEY_W               0x11
#define KEY_E               0x12
#define KEY_R               0x13
#define KEY_T               0x14
#define KEY_Y               0x15
#define KEY_U               0x16
#define KEY_I               0x17
#define KEY_O               0x18
#define KEY_P               0x19
#define KEY_LBRACKET        0x1A
#define KEY_RBRACKET        0x1B
#define KEY_RETURN          0x1C    /* Enter on main keyboard */
#define KEY_LCONTROL        0x1D
#define KEY_A               0x1E
#define KEY_S               0x1F
#define KEY_D               0x20
#define KEY_F               0x21
#define KEY_G               0x22
#define KEY_H               0x23
#define KEY_J               0x24
#define KEY_K               0x25
#define KEY_L               0x26
#define KEY_SEMICOLON       0x27
#define KEY_APOSTROPHE      0x28
#define KEY_GRAVE           0x29    /* accent grave */
#define KEY_LSHIFT          0x2A
#define KEY_BACKSLASH       0x2B
#define KEY_Z               0x2C
#define KEY_X               0x2D
#define KEY_C               0x2E
#define KEY_V               0x2F
#define KEY_B               0x30
#define KEY_N               0x31
#define KEY_M               0x32
#define KEY_COMMA           0x33
#define KEY_PERIOD          0x34    /* . on main keyboard */
#define KEY_SLASH           0x35    /* / on main keyboard */
#define KEY_RSHIFT          0x36
#define KEY_MULTIPLY        0x37    /* * on numeric keypad */
#define KEY_LMENU           0x38    /* left Alt */
#define KEY_SPACE           0x39
#define KEY_CAPITAL         0x3A
#define KEY_F1              0x3B
#define KEY_F2              0x3C
#define KEY_F3              0x3D
#define KEY_F4              0x3E
#define KEY_F5              0x3F
#define KEY_F6              0x40
#define KEY_F7              0x41
#define KEY_F8              0x42
#define KEY_F9              0x43
#define KEY_F10             0x44
#define KEY_NUMLOCK         0x45
#define KEY_SCROLL          0x46    /* Scroll Lock */
#define KEY_NUMPAD7         0x47
#define KEY_NUMPAD8         0x48
#define KEY_NUMPAD9         0x49
#define KEY_SUBTRACT        0x4A    /* - on numeric keypad */
#define KEY_NUMPAD4         0x4B
#define KEY_NUMPAD5         0x4C
#define KEY_NUMPAD6         0x4D
#define KEY_ADD             0x4E    /* + on numeric keypad */
#define KEY_NUMPAD1         0x4F
#define KEY_NUMPAD2         0x50
#define KEY_NUMPAD3         0x51
#define KEY_NUMPAD0         0x52
#define KEY_DECIMAL         0x53    /* . on numeric keypad */
#define KEY_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define KEY_F11             0x57
#define KEY_F12             0x58
#define KEY_F13             0x64    /*                     (NEC PC98) */
#define KEY_F14             0x65    /*                     (NEC PC98) */
#define KEY_F15             0x66    /*                     (NEC PC98) */
#define KEY_KANA            0x70    /* (Japanese keyboard)            */
#define KEY_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define KEY_CONVERT         0x79    /* (Japanese keyboard)            */
#define KEY_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define KEY_YEN             0x7D    /* (Japanese keyboard)            */
#define KEY_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define KEY_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define KEY_PREVTRACK       0x90    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
#define KEY_AT              0x91    /*                     (NEC PC98) */
#define KEY_COLON           0x92    /*                     (NEC PC98) */
#define KEY_UNDERLINE       0x93    /*                     (NEC PC98) */
#define KEY_KANJI           0x94    /* (Japanese keyboard)            */
#define KEY_STOP            0x95    /*                     (NEC PC98) */
#define KEY_AX              0x96    /*                     (Japan AX) */
#define KEY_UNLABELED       0x97    /*                        (J3100) */
#define KEY_NEXTTRACK       0x99    /* Next Track */
#define KEY_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define KEY_RCONTROL        0x9D
#define KEY_MUTE            0xA0    /* Mute */
#define KEY_CALCULATOR      0xA1    /* Calculator */
#define KEY_PLAYPAUSE       0xA2    /* Play / Pause */
#define KEY_MEDIASTOP       0xA4    /* Media Stop */
#define KEY_VOLUMEDOWN      0xAE    /* Volume - */
#define KEY_VOLUMEUP        0xB0    /* Volume + */
#define KEY_WEBHOME         0xB2    /* Web home */
#define KEY_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define KEY_DIVIDE          0xB5    /* / on numeric keypad */
#define KEY_SYSRQ           0xB7
#define KEY_RMENU           0xB8    /* right Alt */
#define KEY_PAUSE           0xC5    /* Pause */
#define KEY_HOME            0xC7    /* Home on arrow keypad */
#define KEY_UP              0xC8    /* UpArrow on arrow keypad */
#define KEY_PRIOR           0xC9    /* PgUp on arrow keypad */
#define KEY_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define KEY_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define KEY_END             0xCF    /* End on arrow keypad */
#define KEY_DOWN            0xD0    /* DownArrow on arrow keypad */
#define KEY_NEXT            0xD1    /* PgDn on arrow keypad */
#define KEY_INSERT          0xD2    /* Insert on arrow keypad */
#define KEY_DELETE          0xD3    /* Delete on arrow keypad */
#define KEY_LWIN            0xDB    /* Left Windows key */
#define KEY_RWIN            0xDC    /* Right Windows key */
#define KEY_APPS            0xDD    /* AppMenu key */
#define KEY_POWER           0xDE    /* System Power */
#define KEY_SLEEP           0xDF    /* System Sleep */
#define KEY_WAKE            0xE3    /* System Wake */
#define KEY_WEBSEARCH       0xE5    /* Web Search */
#define KEY_WEBFAVORITES    0xE6    /* Web Favorites */
#define KEY_WEBREFRESH      0xE7    /* Web Refresh */
#define KEY_WEBSTOP         0xE8    /* Web Stop */
#define KEY_WEBFORWARD      0xE9    /* Web Forward */
#define KEY_WEBBACK         0xEA    /* Web Back */
#define KEY_MYCOMPUTER      0xEB    /* My Computer */
#define KEY_MAIL            0xEC    /* Mail */
#define KEY_MEDIASELECT     0xED    /* Media Select */

/*
 *  Alternate names for keys, to facilitate transition from DOS.
 */
#define KEY_BACKSPACE       KEY_BACK            /* backspace */
#define KEY_NUMPADSTAR      KEY_MULTIPLY        /* * on numeric keypad */
#define KEY_LALT            KEY_LMENU           /* left Alt */
#define KEY_CAPSLOCK        KEY_CAPITAL         /* CapsLock */
#define KEY_NUMPADMINUS     KEY_SUBTRACT        /* - on numeric keypad */
#define KEY_NUMPADPLUS      KEY_ADD             /* + on numeric keypad */
#define KEY_NUMPADPERIOD    KEY_DECIMAL         /* . on numeric keypad */
#define KEY_NUMPADSLASH     KEY_DIVIDE          /* / on numeric keypad */
#define KEY_RALT            KEY_RMENU           /* right Alt */
#define KEY_UPARROW         KEY_UP              /* UpArrow on arrow keypad */
#define KEY_PGUP            KEY_PRIOR           /* PgUp on arrow keypad */
#define KEY_LEFTARROW       KEY_LEFT            /* LeftArrow on arrow keypad */
#define KEY_RIGHTARROW      KEY_RIGHT           /* RightArrow on arrow keypad */
#define KEY_DOWNARROW       KEY_DOWN            /* DownArrow on arrow keypad */
#define KEY_PGDN            KEY_NEXT            /* PgDn on arrow keypad */