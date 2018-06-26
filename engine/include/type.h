/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   type.h
 *  内容:   常量结构定义头文件
 *
 ****************************************************************************/


/*! \file type.h
 * 常量结构定义.
 * 此文件是常量结构定义头文件.
 */


/** 二维矢量坐标(x,y) */
typedef float vec2_t[2];

/** 三维矢量坐标(x,y,z) */
typedef float vec3_t[3];

/** 四维矢量坐标(x,y,z,w) */
typedef float vec4_t[4];

/** 四元数(x,y,z,w) */
typedef float quat_t[4];

/* 3 x 3 矩阵

表示方式：

   | a0  a1  a2 |
   | a3  a4  a5 |
   | a6  a7  a8 |
                   */
typedef float mat33_t[3][3];

/* 3 x 4 矩阵

表示方式：

   | a0  a1  a2 |
   | a3  a4  a5 |
   | a6  a7  a8 |
   | a9  a10 a11|
                   */
typedef float mat34_t[4][3];

/* 4 x 4 矩阵

表示方式：

   | a0  a1  a2  a3 |
   | a4  a5  a6  a7 |
   | a8  a9  a10 a11|
   | a12 a13 a14 a15|
                       */
typedef float mat44_t[4][4];

/** 2 维矢量赋值宏 */
#define VEC2( vec2, x, y ) { vec2[0] = x; vec2[1] = y; }

/** 3 维矢量赋值宏 */
#define VEC3( vec3, x, y, z ) { vec3[0] = x; vec3[1] = y; vec3[2] = z; }

/** 4 维矢量赋值宏 */
#define VEC4( vec4, x, y, z, w ) { vec4[0] = x; vec4[1] = y; vec4[2] = z; vec4[3] = w; }

/** 随机浮点数宏，生成一个 min ~ max 范围内的随机浮点数 */
#define RANDOM_FLOAT( min, max )  min + ( max - min ) * ( (float) rand () / RAND_MAX )

/** 把角度转换成弧度 */
#define ANGLE_TO_RADIAN( angle ) angle / ( 180 / LIGHT_PI )

/** 把弧度转换成角度 */
#define RADIAN_TO_ANGLE( radian ) radian * ( 180 / LIGHT_PI )

// 矩阵（4x4）
typedef float matrix_t[4][4];

///*! \struct vertex_s
///*  \brief 顶点结构
///*/
typedef struct vertex_s
{
	vec3_t position;    /* 空间坐标 */
	vec3_t normal;      /* 法线向量 */
	float  texcoord[2]; /* 纹理坐标 */	
} vertex_t;

/** 32 位浮点数最大值 */
#define	LIGHT_MAX_F32			3.402823466e+38F

/** 内嵌函数 */
#define LIGHT_INLINE  inline
