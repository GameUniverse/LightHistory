/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   type.h
 *  ����:   �����ṹ����ͷ�ļ�
 *
 ****************************************************************************/


/*! \file type.h
 * �����ṹ����.
 * ���ļ��ǳ����ṹ����ͷ�ļ�.
 */


/** ��άʸ������(x,y) */
typedef float vec2_t[2];

/** ��άʸ������(x,y,z) */
typedef float vec3_t[3];

/** ��άʸ������(x,y,z,w) */
typedef float vec4_t[4];

/** ��Ԫ��(x,y,z,w) */
typedef float quat_t[4];

/* 3 x 3 ����

��ʾ��ʽ��

   | a0  a1  a2 |
   | a3  a4  a5 |
   | a6  a7  a8 |
                   */
typedef float mat33_t[3][3];

/* 3 x 4 ����

��ʾ��ʽ��

   | a0  a1  a2 |
   | a3  a4  a5 |
   | a6  a7  a8 |
   | a9  a10 a11|
                   */
typedef float mat34_t[4][3];

/* 4 x 4 ����

��ʾ��ʽ��

   | a0  a1  a2  a3 |
   | a4  a5  a6  a7 |
   | a8  a9  a10 a11|
   | a12 a13 a14 a15|
                       */
typedef float mat44_t[4][4];

/** 2 άʸ����ֵ�� */
#define VEC2( vec2, x, y ) { vec2[0] = x; vec2[1] = y; }

/** 3 άʸ����ֵ�� */
#define VEC3( vec3, x, y, z ) { vec3[0] = x; vec3[1] = y; vec3[2] = z; }

/** 4 άʸ����ֵ�� */
#define VEC4( vec4, x, y, z, w ) { vec4[0] = x; vec4[1] = y; vec4[2] = z; vec4[3] = w; }

/** ����������꣬����һ�� min ~ max ��Χ�ڵ���������� */
#define RANDOM_FLOAT( min, max )  min + ( max - min ) * ( (float) rand () / RAND_MAX )

/** �ѽǶ�ת���ɻ��� */
#define ANGLE_TO_RADIAN( angle ) angle / ( 180 / LIGHT_PI )

/** �ѻ���ת���ɽǶ� */
#define RADIAN_TO_ANGLE( radian ) radian * ( 180 / LIGHT_PI )

// ����4x4��
typedef float matrix_t[4][4];

///*! \struct vertex_s
///*  \brief ����ṹ
///*/
typedef struct vertex_s
{
	vec3_t position;    /* �ռ����� */
	vec3_t normal;      /* �������� */
	float  texcoord[2]; /* �������� */	
} vertex_t;

/** 32 λ���������ֵ */
#define	LIGHT_MAX_F32			3.402823466e+38F

/** ��Ƕ���� */
#define LIGHT_INLINE  inline
