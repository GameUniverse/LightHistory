/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   joint.h
 *  ����:   �ؽں���
 *
 ****************************************************************************/


/*! \file joint.h
 * �ؽں���.
 * ���ļ��ǹؽں���ͷ�ļ�.
 */


/** �ؽ����� */
enum LightJointType
{
	/** ����������ؽڣ�������ɫ���������ƽ���˶���������ת */
	LIGHT_JOINT_PRISMATIC,

	/** ��ҳ���������ؽڣ�������ɫ�����ƹ�ͬ��������ת�˶� */
	LIGHT_JOINT_REVOLUTE,

	/** Բ��������ؽڣ�������ɫ���������������ƽ���˶���Ҳ�������������ת�˶� */
	LIGHT_JOINT_CYLINDRICAL,

	/** ���ѹؽڣ�Ҳ������� */	
	LIGHT_JOINT_SPHERICAL,

	/** �����߹ؽ� */
	LIGHT_JOINT_POINT_ON_LINE,

    /** ������ؽ� */
	LIGHT_JOINT_POINT_IN_PLANE,

	/** ����ؽڣ�һ����ɫ�ϵ�һ�����һ����ɫ�ϵ�һ��ʼ�ձ���һ������ľ��� */	
	LIGHT_JOINT_DISTANCE,

	/** һ�����ֹؽ� */	
	LIGHT_JOINT_PULLEY,

	/** һ���̶����ӣ�������ɫ֮��û������˶����ͺ����ý�ˮճס��һ�� */	
	LIGHT_JOINT_FIXED,

	
	LIGHT_JOINT_D6,

	/* ͨ������ͳ����Ч��ö�ٸ���������һ���ؽ����� */
	LIGHT_JOINT_COUNT,
	LIGHT_JOINT_FORCE_DWORD = 0x7fffffff
};

/** �ؽڱ�־λ */
enum LightJointFlag
{
	/** ����󶨵��ؽڵĸ���֮����ײ��⼤��˱�־λΪ�档ȱʡ������ɹؽ����ӵ�һ�Ը��岻������ײԼ�� */
    LIGHT_JF_COLLISION_ENABLED	= (1<<0),

	/** Ϊ����ؽڴ򿪵�����Ⱦ�� */
    LIGHT_JF_VISUALIZATION		= (1<<1),
};

/** �����������ṹ */
typedef struct
{
	/** ����ϵ�� */
    float spring;
	
	/** ����ϵ�� */
	float damper;
	
	/** Ŀǰ����Ϊ 0 */
	float targetValue;

} LightSpringDesc;

/** ����һ���ؽ����� */
typedef struct
{
	/** �Ƕ�/λ�ü������Զ���� */
	float value;

	/** �������� */
	float restitution;

	/* [��û��ʵ��!] ���ô�ֵС�� 1 �������������Ч�� */
	float hardness;

} LightJointLimitDesc;

/** ����һ˫�ؽ����� */
typedef struct
{
	/** �͵����ƣ�С��ֵ�� */
	LightJointLimitDesc low;

	/** �ߵ����ƣ����ֵ�� */
	LightJointLimitDesc high;

} LightJointLimitPairDesc;

/** �������ѹؽ���Ϊ�ı�־λ */
enum LightSphericalJointFlag
{
	/** ���Ť��������Ч���˱�־λΪ�� */
	LIGHT_SJF_TWIST_LIMIT_ENABLED  = 1 << 0,
	
	/** ����ڶ�������Ч���˱�־λΪ�� */
	LIGHT_SJF_SWING_LIMIT_ENABLED  = 1 << 1,
	
	/** ���Ť��������Ч���˱�־λΪ�� */
	LIGHT_SJF_TWIST_SPRING_ENABLED = 1 << 2,
	
	/** ����ڶ�������Ч���˱�־λΪ�� */
	LIGHT_SJF_SWING_SPRING_ENABLED = 1 << 3,
	
	/** ����ؽڵ�����Ч���˱�־λΪ�� */
	LIGHT_SJF_JOINT_SPRING_ENABLED = 1 << 4,

	/** �������˶���������Լ�� */
    LIGHT_SJF_PERPENDICULAR_DIR_CONSTRAINTS	= 1 << 5,
};

/** ���ѹؽ������� */
typedef struct
{
	/** �� actor 0 �ؽڿռ䶨���ҡ�������� */
	vec3_t swingAxis;
		
	/** ͶӰ�ؽڵ�ͶӰ���� */
	float  projectionDistance;

	/** Χ��Ť������ת���� */
	LightJointLimitPairDesc twistLimit;

	/** Ť����ڶ����� */
	LightJointLimitDesc swingLimit;
	
	/** Ť�������� */
	LightSpringDesc	 twistSpring;

	/** �ڶ������� */
	LightSpringDesc	 swingSpring;

	/** �ùؽ������ĵ��� */
	LightSpringDesc	 jointSpring;

	/** ����һ���� LightSphericalJointFlag ��������ϱ�־λ */
	unsigned long    flags;

	//NxJointProjectionMode projectionMode;

} LightSphericalJointDesc;

/** ���ƾ���ؽ���Ϊ�ı�־ */
enum LightDistanceJointFlag
{
	/** �����λΪ 1���ؽ�ִ�����ֿ����� */
	LIGHT_DJF_MAX_DISTANCE_ENABLED = 1 << 0,

	/** �����λΪ 1���ؽ�ִ����С�ֿ����� */
	LIGHT_DJF_MIN_DISTANCE_ENABLED = 1 << 1,

	/** �����λΪ 1�����Լ��� */
	LIGHT_DJF_SPRING_ENABLED	   = 1 << 2,
};

/** ����ؽ������� */
typedef struct
{
	/** ���������������λ��֮������������� */
	float maxDistance;

	/** ���������������λ��֮�����С������� */
	float minDistance;
	
	/** ����ؽڵ��ԣ�spring.targetValue �ֶβ�ʹ�� */
	LightSpringDesc spring;

	/** ����һ���� LightDistanceJointFlag ���������λ��־ */
	unsigned long   flags;

} LightDistanceJointDesc;

/** ����һ���ؽڷ����� */
typedef struct
{
	/** �������跨�ﵽ������ٶ� */
	float velTarget;

	/** �������ܱ�ʩ�ӵ����������ת�أ�*/
	float maxForce;

    /** ���Ϊ�棬���ؽ��ٶȴ��� velTarget ʱ��������������ɲ�� */	
	bool  freeSpin;
} LightMotorDesc;

/** ���ƻ��ֹؽ���Ϊ�ı�־λ */
enum LightPulleyJointFlag
{
	/** ����ñ�־λΪ 1���ؽ�ͬʱά��һ����С���룬�������һ�������� */
	LIGHT_PJF_IS_RIGID = 1 << 0,

	/** ����ñ�־λΪ 1������������ */
	LIGHT_PJF_MOTOR_ENABLED = 1 << 1
};

/** ���ֹؽ������� */
typedef struct
{
	/** ������ռ�����������������������ֵ�λ�� */
	vec3_t pulley[2];

	/** ���������������������೤�ȣ��˾�����㷽��Ϊ ||(pulley0 - anchor0)|| +  ||(pulley1 - anchor1)|| * ratio */
	float  distance;

	/** Լ���ж�Ӳ���� 0 �� 1����Ӳ�� ֮�� */
	float  stiffness;

	/** ������ */
	float  ratio;

	/** ����һ���� LightPulleyJointFlag ��������ϱ�־λ */
	unsigned long  flags;

	/** ��ѡ��Ĺؽڷ����� */
	LightMotorDesc	motor;

} LightPulleyJointDesc;

/** �ؽ��������ṹ */
typedef struct
{
	/** �ؽ����� */
	LightJointType type;
	
	/** �ؽ����ӵ�������ɫ */
	LightActor * actor[2];

	/** �ؽڿռ�� X �ᣬ�� actor[i] �Ŀռ䣬 �� localAxis[i] ��ֱ�� */
	vec3_t localNormal[2];

	/** �ؽڿռ�� Z �ᣬ�� actor[i] �Ŀռ䡣���ǹؽڵ��������ᡣ*/
	vec3_t localAxis[2];
	
	/** �� actor[i] �ռ�Ĺؽڰ󶨵� */
	vec3_t localAnchor[2];

	/** �ؽ��ƻ�֮ǰ�ܳ��ܵ�����������Ť�أ�����������ֵ */
	float  maxForce;

	/** ����ͬ�� */
	float  maxTorque;

	/** ����ؽ�Լ�����ƶ����� */
	float solverExtrapolationFactor;

	/** �л������ڼ��ٶȵ�Ч�� */
	int   useAccelerationSpring;
	
	/** ��Ҫ���Ƶ� LightJoint::userData */
	void * userData;

	/* ����ʹ�õĵ������ơ�����ַ������治���ƣ���������ָ�롣*/
	const char * name;

	/* ����һ�� NxJointFlag ��������϶�����λ */
	unsigned long jointFlags;

	/** ����ؽڲ��� */
	LightDistanceJointDesc distanceJoint;

	/** ���ѹؽڲ��� */
	LightSphericalJointDesc sphericalJoint;

	/** ���ֹؽڲ��� */
	LightPulleyJointDesc pulleyJointDesc;

} LightJointDesc;


/*! \class LightJoint
 *  \brief �ؽ��� 
 *
 *  ���������������һ���֣��������ؽڵĴ������󶨺����á�
 *  ÿ�� LightJoint ʵ��������ͨ�� LightScene ��� createJoint ���������� 
 */

class LightJoint
{

public:

	/*! \brief ��ѯ������	 
	 *	 
	 *  \return ���ظ�����ָ��
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;

	/*! \brief ��ѯ�ؽڰ󶨵Ľ�ɫ	 
	 *
	 *  \param actor1[out] �ؽڰ󶨵ĵ�һ����ɫ
	 *	 
	 *  \param actor2[out] �ؽڰ󶨵ĵڶ�����ɫ
	 *	 	 
	 *  \see 
	 */	
	virtual void getActors( LightActor ** actor1, LightActor ** actor2 ) = 0;

	/*! \brief ����������ɫ�󶨵��λ�ã�ʹ��ȫ�����꣩
	 *
	 *  \param vec[in] ��ɫ�󶨵��λ�ã�ʹ��ȫ�����꣩
	 *	 	 
	 *  \see 
	 */	
	virtual void setGlobalAnchor( const vec3_t & vec ) = 0;

	/*! \brief ���ùؽ��������᷽��ʹ��ȫ�����꣩
	 *
	 *  \param vec[in] �ؽ��������᷽��ʹ��ȫ�����꣩
	 *	 	 
	 *  \see 
	 */	
	virtual void setGlobalAxis( const vec3_t & vec ) = 0;

	/*! \brief ��ѯ�ؽڰ󶨵�λ��
	 *
	 *  \param vec[out] ���عؽڰ󶨵�λ�ã�ʹ��ȫ�����꣩
	 *	 	 
	 *  \see 
	 */	
	virtual	void getGlobalAnchor( vec3_t & vec ) = 0;

	/*! \brief ��ѯ�ؽ��������᷽��
	 *
	 *  \param vec[out] ���عؽ��������᷽��ʹ��ȫ�����꣩
	 *	 	 
	 *  \see 
	 */	
	virtual	void getGlobalAxis( vec3_t & vec ) = 0;

	/*! \brief ��ѯ����ؽڵ�����
	 *	 
	 *  \return �ؽ�����
	 *
	 *  \see 
	 */	
	virtual LightJointType getType() = 0;

	/*! \brief ����һ�������ַ���������Ϊ���� getName() ��ѯ
	 *
	 *  \param name[in] ���ö������Ƶ��ַ���
	 *	 	 
	 *  \see 
	 */	
	virtual	void setName( const char * name ) = 0;

	/*! \brief ��ѯ setName() ���õ������ַ���
	 *	 
	 *  \return �������������ַ���
	 *
	 *  \see 
	 */	
	virtual	const char * getName() = 0;


	// ����

	/*! \brief �������Ƶ�
	 *
	 *  \param point[in] ���ƿ��Ƶ㣨ʹ��ȫ�����꣩
	 *	 
	 *  \param pointIsOnActor2[in] ���Ϊ�棬point �󶨵��ڶ�����ɫ������󶨵���һ����ɫ
	 *	 	 
	 *  \see 
	 */	
	virtual void setLimitPoint( const vec3_t & point, bool pointIsOnActor2 = true ) = 0;

	/*! \brief ��ѯȫ�ֿռ����Ƶ�
	 *
	 *  \param worldLimitPoint[out] �����洢ȫ�ֿռ����Ƶ�
	 *	 
	 *  \return ���Ϊ�棬���Ƶ�󶨵���ɫ 2������󶨵���ɫ 1��
	 *
	 *  \see 
	 */	
	virtual bool getLimitPoint( vec3_t & worldLimitPoint ) = 0;

	/*! \brief ����һ������ƽ��
	 *
	 *  \param normal[in] ����ƽ�淨�ߣ�ʹ��ȫ�����꣩
	 *	 
	 *  \param pointInPlane[in] ����ƽ���ϵ�һ�㣨ʹ��ȫ�����꣩
	 *	 
	 *  \param restitution[in] ����ƽ�浯��
	 *	 
	 *  \return ���Ƿ��� TRUE��
	 *
	 *  \see 
	 */	
	virtual bool addLimitPlane( const vec3_t & normal, const vec3_t & pointInPlane, float restitution = 0.0f ) = 0;

	/*! \brief ɾ���������ӵ��ؽڵ�����ƽ��
	 *	 
	 *  \see 
	 */	
	virtual void purgeLimitPlanes() = 0;


	// ����������

	/** ���ܽ��������κ���;��ͨ��������һ�����󴴽� 1:1 ��Ӧ�Ĺ�ϵ��*/
	void * userData;

};