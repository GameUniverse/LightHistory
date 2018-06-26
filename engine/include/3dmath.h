/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   3dmath.h
 *  ����:   3D ��ѧ����
 *
 ****************************************************************************/


/*! \file 3dmath.h
 * 3D ��ѧ����.
 * ���ļ��� 3D ��ѧ����ͷ�ļ�.
 */

/** ����Բ���ʡ� */
#define	LIGHT_PI	3.1415926535897932384626433832795028841971693993751f

/* ��С��� */
#define	ON_EPSILON		0.001

/* 0-2 �������ƽ�� */
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2

/* 3-5 ����ӽ��������ƽ�� */
#define	PLANE_ANYX		3
#define	PLANE_ANYY		4
#define	PLANE_ANYZ		5

#define	SIDE_FRONT		0
#define	SIDE_ON			2
#define	SIDE_BACK		1
#define	SIDE_CROSS		-2

#define EL_FALSE        0
#define EL_TRUE         1


/* �����׼�������� */
extern "C"
{

/*! \fn void gCrossProduct (vec3_t v1, vec3_t v2, vec3_t cross)
 *  \brief ���
 *
 *  ���
 *
 *  \param vec3_t v1 ���� a
 *
 *  \param vec3_t v2 ���� b
 *
 *  \param vec3_t cross ��ֱ������ a �� b ��һ��������
 *
 *  \return ��
 *
 *  \see 
 */
void gCrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);

/*! \fn float gDotProduct (const vec3_t a, const vec3_t b)
 *  \brief ���
 *
 *  ���
 *
 *  \param const vec3_t a ���� a
 *
 *  \param const vec3_t b ���� b 
 *
 *  \return �������� a �� b �ĵ��ֵ��
 *
 *  \see 
 */
float gDotProduct (const vec3_t a, const vec3_t b);

/*! \fn float gVectorNormalize (vec3_t vector)
 *  \brief ���
 *
 *  ���
 *
 *  \param vec3_t vector Ҫ��񻯵�����
 * 
 *  \return ��񻯺������������ vector �У��˴����������ĳ��ȡ�
 *
 *  \see 
 */
float gVectorNormalize (vec3_t vector);

/*! \fn void gVectorScale (vec3_t vector, float scale, vec3_t out)
 *  \brief ��ԭ�����Ŷ���
 *
 *  ��ԭ�����Ŷ���
 *
 *  \param vec3_t vector Ҫ���ŵĶ�������
 *
 *  \param float scale ���ű���
 *
 *  \param vec3_t out ���ź�Ķ�������
 *
 *  \return ��
 *
 *  \see 
 */
void gVectorScale (vec3_t vector, float scale, vec3_t out);

/*! \fn void gVectorAdd (vec3_t v1, vec3_t v2, vec3_t out)
 *  \brief ����������ĺ�
 *
 *  ����������ĺ�
 *
 *  \param vec3_t v1 ���� a
 *
 *  \param vec3_t v2 ���� b
 *
 *  \param vec3_t out ���� a �� b �ĺ�
 *
 *  \return ��
 *
 *  \see 
 */
void gVectorAdd (vec3_t v1, vec3_t v2, vec3_t out);

/*! \fn void gVectorSubtract (const vec3_t v1, const vec3_t v2, vec3_t out)
 *  \brief ����������Ĳ�
 *
 *  ����������Ĳ�
 *
 *  \param const vec3_t v1 ���� a
 *
 *  \param const vec3_t v2 ���� b
 *
 *  \param vec3_t out ���� a �� b �Ĳ�
 *
 *  \return ��
 *
 *  \see 
 */
void gVectorSubtract (const vec3_t v1, const vec3_t v2, vec3_t out);

/*! \fn void gVectorCopy (vec3_t in, vec3_t out)
 *  \brief ���ƶ���
 *
 *  ���ƶ���
 *
 *  \param vec3_t in Ҫ���ƵĶ���
 *
 *  \param vec3_t out ���ƺ�Ķ���
 * 
 *  \return ��
 *
 *  \see 
 */
void gVectorCopy (vec3_t in, vec3_t out);

/*! \brief ��������֮��ľ���
 * 
 *  \param p1[in] ��һ�����λ��
 *
 *  \param p2[in] �ڶ������λ��
 * 
 *  \return ��������֮��ľ��롣
 *
 *  \see
 */
float gVectorDistance( vec3_t p1, vec3_t p2 );

/*! \fn void gTranslateMatrix (const vec3_t vec, float matrix[3][4])
 *  \brief ����ƽ�ƾ���
 *
 *  ����ƽ�ƾ���
 *
 *  \param const vec3_t vec ƽ��ʸ��
 *
 *  \param float matrix[3][4] ��ʸ����ƽ�ƾ���
 * 
 *  \return ��
 *
 *  \see 
 */
void gTranslateMatrix (const vec3_t vec, float matrix[3][4]);

/*! \fn void gRotateXMatrix (const float angle, float matrix[3][4])
 *  \brief ���� X ����ת����
 *
 *  ���� X ����ת����
 *
 *  \param const float angle �� x �����ת�Ƕ�
 *
 *  \param float matrix[3][4] ��Ӧ����ת����
 * 
 *  \return ��
 *
 *  \see 
 */
void gRotateXMatrix (const float angle, float matrix[3][4]);

/*! \fn void gRotateYMatrix (const float angle, float matrix[3][4])
 *  \brief ���� Y ����ת����
 *
 *  ���� Y ����ת����
 *
 *  \param const float angle �� y �����ת�Ƕ�
 *
 *  \param float matrix[3][4] ��Ӧ����ת����
 * 
 *  \return ��
 *
 *  \see 
 */
void gRotateYMatrix (const float angle, float matrix[3][4]);

/*! \fn void gRotateZMatrix (const float angle, float matrix[3][4])
 *  \brief ���� Z ����ת����
 *
 *  ���� Z ����ת����
 *
 *  \param const float angle �� z �����ת�Ƕ�
 *
 *  \param float matrix[3][4] ��Ӧ����ת����
 * 
 *  \return ��
 *
 *  \see 
 */
void gRotateZMatrix (const float angle, float matrix[3][4]);

/*! \fn void gRotateMatrix (const vec3_t angles, float matrix[3][4])
 *  \brief ������ת����
 *
 *  ������ת����
 *
 *  \param const float angle �� x��y �� z �����ת�Ƕ�
 *
 *  \param float matrix[3][4] ��Ӧ����ת����
 * 
 *  \return ��
 *
 *  \see 
 */
void gRotateMatrix (const vec3_t angles, float matrix[3][4]);

/*! \fn void gMultiplyMatrix (const float a[3][4], const float b[3][4], float out[3][4])
 *  \brief �������������
 *
 *  �������������
 *
 *  \param const float a[3][4] ���� a
 *
 *  \param const float b[3][4] ���� b
 *
 *  \param const float out[3][4] ���� a �� b �ĳ˻�
 * 
 *  \return ��
 *
 *  \see 
 */
void gMultiplyMatrix (const float a[3][4], const float b[3][4], float out[3][4]);

/*! \brief ��Ԫ���˷�
 *
 *  ��Ԫ���˷���a * b = out��
 *
 *  \param a[in] ��ʾ��ת������
 *
 *  \param b[in] ��ʾ��ת������
 *
 *  \param out[out] ������ת�ۼӵĽ�����൱������ b ����ת������ a ����ת
 *  
 *  \see 
 */
void gQuaternionMultiply( quat_t a, quat_t b, quat_t out );

// �ӽǶ�������������Ԫ��
void gQuaternionFromAngleAxisFast( float angleRadians, const vec3_t axis, quat_t quat );

// ��Ԫ�����
void gQuaternionNormalize( quat_t quat );

// ������λ��ת��Ԫ��
void gQuaternionIdentity( quat_t quat );

// ����Ԫ����ѯ�Ƕ�������
void gQuaternionGetAngleAxis( const quat_t quat, float * angleRadians, vec3_t axis );

// ���������η���
int gTriangleNormal( vec3_t a, vec3_t b, vec3_t c, vec3_t normal );

// ��������ת����ֱ������
void gSphereToRightAngleCoordinates( float radius, float angle_z, float angle_xy, vec3_t rightAngleCoordinates );

// �Ѽ�����ת����ֱ��ƽ������
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