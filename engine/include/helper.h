/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   helper.cpp
 *  内容:   助手类
 *
 ****************************************************************************/


//-----------------------------------------------------------------------------
// Miscellaneous helper functions
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


// 替换路径文件名称
void ReplaceFilename( const char *path, const char *filename, char *replaced_path );

/* 将 ANSI 格式的字符串转换成 UTF8 格式 */
char const *AnsiToUtf8(char const *szAnsi);

// 画一个圆锥体
void DrawCone( vec3_t position, quat_t orientation, float baseRadius, float height, int slices, int stacks );

// 画一个圆
void DrawCircle( vec3_t position, quat_t orientation, float radius, int segment );
