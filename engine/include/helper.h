/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   helper.cpp
 *  ����:   ������
 *
 ****************************************************************************/


//-----------------------------------------------------------------------------
// Miscellaneous helper functions
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


// �滻·���ļ�����
void ReplaceFilename( const char *path, const char *filename, char *replaced_path );

/* �� ANSI ��ʽ���ַ���ת���� UTF8 ��ʽ */
char const *AnsiToUtf8(char const *szAnsi);

// ��һ��Բ׶��
void DrawCone( vec3_t position, quat_t orientation, float baseRadius, float height, int slices, int stacks );

// ��һ��Բ
void DrawCircle( vec3_t position, quat_t orientation, float radius, int segment );
