/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   fluid.h
 *  ����:   ���庯��
 *
 ****************************************************************************/


/*! \file fluid.h
 * ���庯��.
 * ���ļ������庯��ͷ�ļ�.
 */


/*// ��ɫ����������
enum LightCharacterType
{
	LIGHT_CHARACTER_BOX,     // ������
	LIGHT_CHARACTER_CAPSULE  // ����  
};

// ��ɫ��������������־λ
#define	LIGHT_CHARACTER_SLOPELIMIT  0x0001
#define	LIGHT_CHARACTER_SKINWIDTH   0x0002
#define	LIGHT_CHARACTER_STEPOFFSET  0x0004*/

/** �����������ṹ */
typedef struct
{
	///**	����������ӵ�����ʱ������ */
	//LightParticleData	initialParticleData;

	/**	����ʹ�õ���������� */
	int 	maxParticles;

	/**	����ʱ�ı��������� */
	int 	numReserveParticles;

	/** ���Ӳ�����С����������ʾ�������������޹أ� */
	float   particleBillboardWidth;

	/** ����ͬ�� */
	float   particleBillboardHeight;

	///**	The particle resolution given as particles per linear meter measured when the fluid is in its rest state (relaxed). */	
	float 	restParticlesPerMeter;
	
	/** �����ܶȣ�ˮ��Լ�� 1000�� */
	float 	restDensity;
	
	/** �����໥���÷�Χ�뾶 */
	float 	kernelRadiusMultiplier;
	
	/** ����������һ��ʱ�䲽������ǰ���������� */
	float 	motionLimitMultiplier;
	
	/** �������Ӻ���ײ������֮��ľ��룬��ֵ�����������ڼ�һֱ��Ч */
	float 	collisionDistanceMultiplier;
	
	/** ����������������ƽ�� */
	int 	packetSizeMultiplier;
	
	/** ���ӵ�Ӳ�ȣ��໥�����漰��ѹ�� */
	float 	stiffness;
	
	/** �����ճ�Զ�������ճ�Ե���Ϊ */
	float 	viscosity;

	/** ����ı�����������һ�����Ӽ�������� */
	float 	surfaceTension;
	
	/** �ٶ�˥���ٳ���������ȫ�ֳ�����Ӧ�õ�ÿһ������ */
	float 	damping;
	
	/** ����һ�����ӡ����롱ʱ�䳤�� */
	float 	fadeInTime;
	
	/** ���ٶȣ�m/s^2�������е�ʱ�䲽Ӧ�õ����е����� */
	vec3_t	externalAcceleration;
		
	/** �����������Ӻ;�̬��������ײ�ĵ���ϵ�� */
	float 	restitutionForStaticShapes;
		
	/** ����������ھ�̬���������Ķ�̬ĥ����ϵ�� */
	float 	dynamicFrictionForStaticShapes;
		
	/** ����������ھ�̬���������ľ�̬ĥ����ϵ�� */
	float 	staticFrictionForStaticShapes;
	
	/** �������Ӻ;�̬����֮����ײʱ�������� */
	float 	attractionForStaticShapes;
	
	/** �����������ӺͶ�̬��������ײ�ĵ���ϵ�� */
	float 	restitutionForDynamicShapes;
		
	/** ����������ڶ�̬���������Ķ�̬ĥ����ϵ�� */
	float 	dynamicFrictionForDynamicShapes;
	
	/** ����������ڶ�̬���������ľ�̬ĥ����ϵ�� */
	float 	staticFrictionForDynamicShapes;
	
	/** �������ӺͶ�̬����֮����ײʱ�������� */
	float 	attractionForDynamicShapes;
	
	/** ����һ���ƶ���ϵ���������嵽��ײ�ĸ��� */
	float 	collisionResponseCoefficient;

} LightFluidDesc;


/*! \class LightFluid
 *  \brief ������
 *
 *  ���ฺ��һ������Ĵ������������Ⱦ�ȹ��ܡ�
 *  ÿ�� LightFluid ʵ��������ͨ�� LightScene ��� createFluid �������䣬ͨ�� releaseFluid �����ͷš� 
 */

class LightFluid
{

public:

	/*enum LightCharacterFlag
	{
		LIGHT_CHARACTER_COLLISION_SIDES = (1<<0), // ��ɫ���淢������ײ
		LIGHT_CHARACTER_COLLISION_UP    = (1<<1), // ��ɫ���淢������ײ
		LIGHT_CHARACTER_COLLISION_DOWN  = (1<<2), // ��ɫ���淢������ײ
	};*/

	/*! \fn LightScene * getScene() = 0
	 *  \brief ��ѯ������
	 *
	 *  ��ѯ������
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;

	/*! \fn LightFluidEmitter * createEmitter( const LightFluidEmitterDesc * fluidEmitterDesc ) = 0
	 *  \brief ����һ�����巢����
	 *
	 *  ����һ�����巢����
	 *
	 *  \param const LightFluidEmitterDesc * fluidEmitterDesc ���巢����������ָ�룬����˵��Ҫ�������巢������������
	 *	 
	 *  \return �����Ѵ��������巢����ָ��
	 *
	 *  \see 
	 */
	virtual LightFluidEmitter * createEmitter( const LightFluidEmitterDesc * fluidEmitterDesc ) = 0;

	/*! \fn void releaseEmitter( LightFluidEmitter * fluidEmitter ) = 0
	 *  \brief �ͷ�һ�����巢����
	 *
	 *  �ͷ�һ�����巢����
	 *
	 *  \param LightFluidEmitter * fluidEmitter Ҫ�ͷ����巢������ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseEmitter( LightFluidEmitter * fluidEmitter ) = 0;

	/*! \fn void render() = 0
	 *  \brief ��Ⱦ����
	 *
	 *  ��Ⱦ����
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks 
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void render() = 0;

};