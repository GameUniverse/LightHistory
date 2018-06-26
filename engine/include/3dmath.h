/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   3dmath.h
 *  内容:   3D 数学函数
 *
 ****************************************************************************/


/*! \file 3dmath.h
 * 3D 数学函数.
 * 此文件是 3D 数学函数头文件.
 */

/** 常量圆周率∏ */
#define	LIGHT_PI	3.1415926535897932384626433832795028841971693993751f

/* 最小误差 */
#define	ON_EPSILON		0.001

/* 0-2 是轴对齐平面 */
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2

/* 3-5 是最接近的轴对齐平面 */
#define	PLANE_ANYX		3
#define	PLANE_ANYY		4
#define	PLANE_ANYZ		5

#define	SIDE_FRONT		0
#define	SIDE_ON			2
#define	SIDE_BACK		1
#define	SIDE_CROSS		-2

#define EL_FALSE        0
#define EL_TRUE         1


/* 输出标准函数名称 */
extern "C"
{

/*! \fn void gCrossProduct (vec3_t v1, vec3_t v2, vec3_t cross)
 *  \brief 叉乘
 *
 *  叉乘
 *
 *  \param vec3_t v1 向量 a
 *
 *  \param vec3_t v2 向量 b
 *
 *  \param vec3_t cross 垂直于向量 a 和 b 的一个新向量
 *
 *  \return 无
 *
 *  \see 
 */
void gCrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);

/*! \fn float gDotProduct (const vec3_t a, const vec3_t b)
 *  \brief 点乘
 *
 *  点乘
 *
 *  \param const vec3_t a 向量 a
 *
 *  \param const vec3_t b 向量 b 
 *
 *  \return 返回向量 a 和 b 的点乘值。
 *
 *  \see 
 */
float gDotProduct (const vec3_t a, const vec3_t b);

/*! \fn float gVectorNormalize (vec3_t vector)
 *  \brief 归格化
 *
 *  归格化
 *
 *  \param vec3_t vector 要归格化的向量
 * 
 *  \return 归格化后的向量返回在 vector 中，此处返回向量的长度。
 *
 *  \see 
 */
float gVectorNormalize (vec3_t vector);

/*! \fn void gVectorScale (vec3_t vector, float scale, vec3_t out)
 *  \brief 沿原点缩放顶点
 *
 *  沿原点缩放顶点
 *
 *  \param vec3_t vector 要缩放的顶点坐标
 *
 *  \param float scale 缩放比例
 *
 *  \param vec3_t out 缩放后的顶点坐标
 *
 *  \return 无
 *
 *  \see 
 */
void gVectorScale (vec3_t vector, float scale, vec3_t out);

/*! \fn void gVectorAdd (vec3_t v1, vec3_t v2, vec3_t out)
 *  \brief 计算两顶点的和
 *
 *  计算两顶点的和
 *
 *  \param vec3_t v1 顶点 a
 *
 *  \param vec3_t v2 顶点 b
 *
 *  \param vec3_t out 顶点 a 和 b 的和
 *
 *  \return 无
 *
 *  \see 
 */
void gVectorAdd (vec3_t v1, vec3_t v2, vec3_t out);

/*! \fn void gVectorSubtract (const vec3_t v1, const vec3_t v2, vec3_t out)
 *  \brief 计算两顶点的差
 *
 *  计算两顶点的差
 *
 *  \param const vec3_t v1 顶点 a
 *
 *  \param const vec3_t v2 顶点 b
 *
 *  \param vec3_t out 顶点 a 和 b 的差
 *
 *  \return 无
 *
 *  \see 
 */
void gVectorSubtract (const vec3_t v1, const vec3_t v2, vec3_t out);

/*! \fn void gVectorCopy (vec3_t in, vec3_t out)
 *  \brief 复制顶点
 *
 *  复制顶点
 *
 *  \param vec3_t in 要复制的顶点
 *
 *  \param vec3_t out 复制后的顶点
 * 
 *  \return 无
 *
 *  \see 
 */
void gVectorCopy (vec3_t in, vec3_t out);

/*! \brief 计算两点之间的距离
 * 
 *  \param p1[in] 第一个点的位置
 *
 *  \param p2[in] 第二个点的位置
 * 
 *  \return 返回两点之间的距离。
 *
 *  \see
 */
float gVectorDistance( vec3_t p1, vec3_t p2 );

/*! \fn void gTranslateMatrix (const vec3_t vec, float matrix[3][4])
 *  \brief 计算平移矩阵
 *
 *  计算平移矩阵
 *
 *  \param const vec3_t vec 平移矢量
 *
 *  \param float matrix[3][4] 该矢量的平移矩阵
 * 
 *  \return 无
 *
 *  \see 
 */
void gTranslateMatrix (const vec3_t vec, float matrix[3][4]);

/*! \fn void gRotateXMatrix (const float angle, float matrix[3][4])
 *  \brief 计算 X 轴旋转矩阵
 *
 *  计算 X 轴旋转矩阵
 *
 *  \param const float angle 绕 x 轴的旋转角度
 *
 *  \param float matrix[3][4] 对应的旋转矩阵
 * 
 *  \return 无
 *
 *  \see 
 */
void gRotateXMatrix (const float angle, float matrix[3][4]);

/*! \fn void gRotateYMatrix (const float angle, float matrix[3][4])
 *  \brief 计算 Y 轴旋转矩阵
 *
 *  计算 Y 轴旋转矩阵
 *
 *  \param const float angle 绕 y 轴的旋转角度
 *
 *  \param float matrix[3][4] 对应的旋转矩阵
 * 
 *  \return 无
 *
 *  \see 
 */
void gRotateYMatrix (const float angle, float matrix[3][4]);

/*! \fn void gRotateZMatrix (const float angle, float matrix[3][4])
 *  \brief 计算 Z 轴旋转矩阵
 *
 *  计算 Z 轴旋转矩阵
 *
 *  \param const float angle 绕 z 轴的旋转角度
 *
 *  \param float matrix[3][4] 对应的旋转矩阵
 * 
 *  \return 无
 *
 *  \see 
 */
void gRotateZMatrix (const float angle, float matrix[3][4]);

/*! \fn void gRotateMatrix (const vec3_t angles, float matrix[3][4])
 *  \brief 计算旋转矩阵
 *
 *  计算旋转矩阵
 *
 *  \param const float angle 绕 x、y 和 z 轴的旋转角度
 *
 *  \param float matrix[3][4] 对应的旋转矩阵
 * 
 *  \return 无
 *
 *  \see 
 */
void gRotateMatrix (const vec3_t angles, float matrix[3][4]);

/*! \fn void gMultiplyMatrix (const float a[3][4], const float b[3][4], float out[3][4])
 *  \brief 将两个矩阵相乘
 *
 *  将两个矩阵相乘
 *
 *  \param const float a[3][4] 矩阵 a
 *
 *  \param const float b[3][4] 矩阵 b
 *
 *  \param const float out[3][4] 矩阵 a 和 b 的乘积
 * 
 *  \return 无
 *
 *  \see 
 */
void gMultiplyMatrix (const float a[3][4], const float b[3][4], float out[3][4]);

/*! \brief 四元数乘法
 *
 *  四元数乘法（a * b = out）
 *
 *  \param a[in] 表示旋转的因数
 *
 *  \param b[in] 表示旋转的因数
 *
 *  \param out[out] 两个旋转累加的结果，相当于先做 b 的旋转，再做 a 的旋转
 *  
 *  \see 
 */
void gQuaternionMultiply( quat_t a, quat_t b, quat_t out );

// 从角度轴描述创建四元数
void gQuaternionFromAngleAxisFast( float angleRadians, const vec3_t axis, quat_t quat );

// 四元数规格化
void gQuaternionNormalize( quat_t quat );

// 创建单位旋转四元数
void gQuaternionIdentity( quat_t quat );

// 从四元数查询角度轴描述
void gQuaternionGetAngleAxis( const quat_t quat, float * angleRadians, vec3_t axis );

// 计算三角形法线
int gTriangleNormal( vec3_t a, vec3_t b, vec3_t c, vec3_t normal );

// 把球坐标转换成直角坐标
void gSphereToRightAngleCoordinates( float radius, float angle_z, float angle_xy, vec3_t rightAngleCoordinates );

// 把极坐标转换成直角平面坐标
void gPolarToRightAngleCoordinates( float radius, float angle, vec2_t rightAngleCoordinates );

}

// This is our basic 3D point/vector class
struct CVector3
{
public:
	
	// A default constructor
	CVector3() {}

	// This is our constructor that allows us to initialize our data upon creating an instance
	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 vVector)
	{
		// Return the added vectors result.
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 vVector)
	{
		// Return the subtracted vectors result
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	CVector3 operator*(float num)
	{
		// Return the scaled vector
		return CVector3(x * num, y * num, z * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	CVector3 operator/(float num)
	{
		// Return the scale vector
		return CVector3(x / num, y / num, z / num);
	}

	float x, y, z;						
};

// This is our basic 2D point class.  This will be used to store the UV coordinates.
class CVector2 
{
public:

		// A default constructor
	CVector2() {}

	// This is our constructor that allows us to initialize our data upon creating an instance
	CVector2(float X, float Y) 
	{ 
		x = X; y = Y;
	}

	// Here we overload the + operator so we can add vectors together 
	CVector2 operator+(CVector2 vVector)
	{
		// Return the added vectors result.
		return CVector2(vVector.x + x, vVector.y + y);
	}

	// Here we overload the - operator so we can subtract vectors 
	CVector2 operator-(CVector2 vVector)
	{
		// Return the subtracted vectors result
		return CVector2(x - vVector.x, y - vVector.y);
	}
	
	// Here we overload the * operator so we can multiply by scalars
	CVector2 operator*(float num)
	{
		// Return the scaled vector
		return CVector2(x * num, y * num);
	}

	// Here we overload the / operator so we can divide by a scalar
	CVector2 operator/(float num)
	{
		// Return the scale vector
		return CVector2(x / num, y / num);
	}

	float x, y;
};