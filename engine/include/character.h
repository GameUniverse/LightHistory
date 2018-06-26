/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   character.h
 *  ����:   ��ɫ���ƺ���
 *
 ****************************************************************************/


/*! \file character.h
 * ��ɫ���ƺ���.
 * ���ļ��ǽ�ɫ���ƺ���ͷ�ļ�.
 */


// ��ɫ����������
enum LightCharacterType
{
	LIGHT_CHARACTER_BOX,     // ������
	LIGHT_CHARACTER_CAPSULE  // ����  
};

// ��ɫ��������������־λ
#define	LIGHT_CHARACTER_SLOPELIMIT  0x0001
#define	LIGHT_CHARACTER_SKINWIDTH   0x0002
#define	LIGHT_CHARACTER_STEPOFFSET  0x0004

typedef struct
{
	LightCharacterType  type;        // ��ɫ����������
	int                 flags;       // ��Ч���ݱ�־λ
	vec3_t              position;    // ��ɫ������λ��
	float 			    slopeLimit;  // ��ɫ����������������¶ȣ��ýǶȵ����ұ�ʾ��ȱʡֵ 0.707��
	float		        skinWidth;   // ��ɫ��������ǿ�ȣ�ȱʡֵ 0.1��
	float		        stepOffset;  // ��ɫ������������������ϰ���߶ȣ�ȱʡֵ 0.5��
	//NxUserControllerHitReport*	callback;
	//NxCCTInteractionFlag		interactionFlag;	

	struct { vec3_t size;   } box;      // �����峤������

	struct { float  radius;
			 float  height; } capsule;  // ������İ뾶�͸�

} LightCharacterDesc;


/*! \class LightCharacter
 *  \brief ��ɫ������ 
 *
 *  ���ฺ��һ����ɫ�����������е���ȷ���㣬�������ߡ���Ծ�Ⱦ��󲿷ֹ��ܡ�
 *  ÿ�� LightCharacter ʵ��������ͨ�� LightEngine ��� createCharacter �������䣬ͨ�� releaseCharacter �����ͷš� 
 */

class LightCharacter
{

public:

	enum LightCharacterFlag
	{
		LIGHT_CHARACTER_COLLISION_SIDES = (1<<0), // ��ɫ���淢������ײ
		LIGHT_CHARACTER_COLLISION_UP    = (1<<1), // ��ɫ���淢������ײ
		LIGHT_CHARACTER_COLLISION_DOWN  = (1<<2), // ��ɫ���淢������ײ
	};

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ�����ָ��
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;

	/*! \fn void move( const vec3_t vector, float minDist, unsigned long * collisionFlags, float sharpness ) = 0
	 *  \brief �ƶ���ɫ������
	 *
	 * �ƶ���ɫ������
	 *
	 *  \param const vec3_t vector �ǵ�ǰ֡��λ����������һ������£�����Ľ�ɫ�����ƶ�ʱ�����Ǵ�ֱ���µ�������ˮƽ�ƶ��������ɴ˲���ָ��������ϡ�
	 *                             ע������һ��λ����������һ���򣩣���ֻ�Ե�ǰ֡�����ã����Ҳ����ۼӣ�������һ���ٶ��������ڶ����򣩻�������������������
	 *
	 *  \param float minDist ����ǰֹͣλ�Ƶݹ��㷨����С����ֵ��ȱʡֵ�� 1��
	 *
	 *  \param unsigned long * collisionFlags ��һ��λ����ָ�룬�����ڽ�ɫ�ƶ��ڼ��û�Ҫ��ѯ����ײ�¼������� LightCharacterFlag ��־����ϣ����������������ֲ�ͬ�Ľ�ɫ������
	 *                                       ���磬���˱�־Ϊ 0 ʱ���Ϳ��Բ���һ�����µĶ������� LIGHT_CHARACTER_COLLISION_DOWN ��־����ʱ���Ϳ��Բ���վ���Ķ�����
	 * 
	 *  \param float sharpness �˲������������Ժ�ʹ�ã���������Ϊ 1.0f��
	 *
	 *  \remarks 
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void move( const vec3_t vector, float minDist, unsigned long * collisionFlags, float sharpness ) = 0;

	/*! \fn bool setPosition( const vec3_t position ) = 0
	 *  \brief ���ý�ɫ��������λ��
	 *
	 *  ���ý�ɫ��������λ��
	 *
	 *  \param const vec3_t position ��ɫ�������µ�λ��
	 *
	 *  \remarks 
	 *
	 *  \return Ŀǰ���Ƿ��� TRUE��
	 */
	virtual bool setPosition( const vec3_t position ) = 0;

	/*! \brief ��ѯ��ɫ��������λ��
	 *	 
	 *  \remarks 
	 *
	 *  \return ���ؽ�ɫ��������ȫ����������ֵ��
	 */
	virtual const vec3_t * getPosition() = 0;

	/*! \brief ��ѯ��ɫ���������˺��λ��
	 *	 
	 *  \remarks 
	 *
	 *  \return ��ɫ���������˺��ȫ����������ֵ��
	 */
	virtual	const vec3_t& getFilteredPosition()	= 0;

	/*! \brief ���ò����߶�
	 *	 
	 *  \param offset[in] ��ɫ���������������ϰ���߶�
	 */
	virtual	void setStepOffset( const float offset ) = 0;

	/*! \brief ����/��ֹ�����ɫ����������ײ���
	 *	 
	 *  \param enabled[in] TRUE ������ɫ����������ײ���
	 */
	virtual	void setCollision( bool enabled ) = 0;

	/*! \brief ��Ⱦ��ɫ������
	 *	 	 
	 *  \remarks 	 
	 */
	virtual void render() = 0;

};