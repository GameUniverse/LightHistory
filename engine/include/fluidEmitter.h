/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   fluidEmitter.h
 *  ����:   ���巢��������
 *
 ****************************************************************************/


/*! \file fluidEmitter.h
 * ���巢��������.
 * ���ļ������巢��������ͷ�ļ�.
 */


class LightFluid;


enum LightFluidEmitterFlag
{

	LIGHT_FEF_VISUALIZATION		= (1<<0),

	LIGHT_FEF_FORCE_ON_BODY		= (1<<2),
	
	LIGHT_FEF_ADD_BODY_VELOCITY	= (1<<3),
	
	LIGHT_FEF_ENABLED				= (1<<4),
	
};

enum LightEmitterShape
{
	LIGHT_FE_RECTANGULAR		= (1<<0),
	LIGHT_FE_ELLIPSE			= (1<<1)
};

enum LightEmitterType
{
	LIGHT_FE_CONSTANT_PRESSURE		= (1<<0),
	LIGHT_FE_CONSTANT_FLOW_RATE	= (1<<1)
};


/** ���巢�����������ṹ */
typedef struct
{
	/** ����� frameShape�����������壩�ķ�����λ�úͷ��� */
	mat34_t			relPose;

	/** ����� frameShape�����������壩�ķ�����λ�� */
	vec3_t          relPosition;

	/** ����� frameShape�����������壩�ķ�����������Ԫ�� */
	quat_t          relOrientationQuat;

	/** ��ɫָ��ָ������Ҫ�󶨵Ľ�ɫ */
	LightActor *	frameShape;

	/** ��������תģʽ */
	int 	type;

	/** ��������������������������� */
	int 	maxParticles;

	/** ����������״����ָ��Ϊ���λ���Բ */
	int 	shape;
	
	/** �������ڵ�һ�����᷽��Ĵ�С�����������ķ���relPose �� relOrientationQuat ������ */
	float 	dimensionX;

	/** ����ͬ�� */
	float 	dimensionY;

	/** �����������ÿһ���᷽����������ֵ���϶���һ����ֵ�� */
    vec3_t	randomPos;

	/** ���䷽�������Ƕ�ƫ�� */
	float 	randomAngle;

	/** �����ȥ���������ӵ��ٶȴ�С */
	float 	fluidVelocityMagnitude;

	/** ����ٶ�ָ��ÿ���ӷ�����ٸ����� */
	float 	rate;
	
	/** ָ������Ϊ��λ�ķ������ӵ��������� */
	float 	particleLifetime;

	float 	repulsionCoefficient;
	
	int 	flags;

} LightFluidEmitterDesc;


/*! \class LightFluidEmitter
 *  \brief ���巢������
 *
 *  ���ฺ��һ�����巢�����Ĵ������������Ⱦ�ȹ��ܡ�
 *  ÿ�� LightFluidEmitter ʵ��������ͨ�� LightFluid ��� createEmitter �������䣬ͨ�� releaseEmitter �����ͷš� 
 */

class LightFluidEmitter
{

public:

	/*! \fn LightFluid * getFluid() = 0
	 *  \brief ��ѯ������
	 *
	 *  ��ѯ������
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return LightFluid * ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightFluid * getFluid() = 0;

};