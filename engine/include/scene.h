/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   scene.h
 *  ����:   ��������
 *
 ****************************************************************************/


/*! \file scene.h
 * ��������
 * ���ļ��ǳ�������ͷ�ļ�.
 */


class LightEngine;


/** ���߽ṹ */
typedef struct
{
	/** ����ԭ�� */
	vec3_t  orig;

	/** ��񻯵ķ��� */
	vec3_t  dir;

} LightRay;

/** ��ɫ���ͣ���̬��̬�ģ�*/
enum LightShapesType
{
	/** Ͷ�侲̬��ɫ */
	LIGHT_STATIC_SHAPES		= (1<<0),

	/** Ͷ�䶯̬��ɫ */
	LIGHT_DYNAMIC_SHAPES	= (1<<1),

	/** ͬʱͶ�侲̬�Ͷ�̬��ɫ */
	LIGHT_ALL_SHAPES		= LIGHT_STATIC_SHAPES|LIGHT_DYNAMIC_SHAPES
};

/** ָ�� LightRaycastHit ��Щ��ԱӦ�ò���������Ϊ raycasting ������ʾ��־ʹ��ʱ���������б���Щ��Ա�Ѿ������������ LightRaycastHit �� flags ��Աʱ��*/
enum LightRaycastBit
{
	LIGHT_RAYCAST_SHAPE		    = (1<<0),								// "shape" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_IMPACT		= (1<<1),								// "worldImpact" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_NORMAL		= (1<<2),								// "worldNormal" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_FACE_INDEX	= (1<<3),								// "faceID" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_DISTANCE		= (1<<4),								// "distance" member of #NxRaycastHit is valid
	LIGHT_RAYCAST_UV			= (1<<5),								// "u" and "v" members of #NxRaycastHit are valid
	LIGHT_RAYCAST_FACE_NORMAL	= (1<<6),								// Same as NX_RAYCAST_NORMAL but computes a non-smoothed normal
	LIGHT_RAYCAST_MATERIAL		= (1<<7),								// "material" member of #NxRaycastHit is valid
};

/** ����ṹ��ȡ���ι���Ͷ���� */
struct LightRaycastHit
{
	/** ����ײ����״�������ı�־��LIGHT_RAYCAST_SHAPE��*/	
	LightActor * 	shape;

	/** ������ռ��е���ײ�㣨�����ı�־��LIGHT_RAYCAST_IMPACT) */
	vec3_t			worldImpact;
					
	/** ������ռ��е���ײ���ߣ������ı�־��LIGHT_RAYCAST_NORMAL / LIGHT_RAYCAST_FACE_NORMAL��*/
	vec3_t			worldNormal;

	/** ����ײ��������������ı�־��LIGHT_RAYCAST_FACE_INDEX��*/
	unsigned long 	faceID;

	/** ����ͬ�� */
	unsigned long	internalFaceID;	

	/** �ӹ�����㵽��ײ��ľ��루�����ı�־��LIGHT_RAYCAST_DISTANCE��*/
	float 			distance;

	/** ��ײ�������꣨�����ı�־��LIGHT_RAYCAST_UV��*/
	float 			u,

	/** ����ͬ�� */
		            v;

	/** ����ײ������ʵ������������ı�־��LIGHT_RAYCAST_MATERIAL��*/
	unsigned short 	materialIndex;

	/** LightRaycastBit ���ϱ�־�ֶΣ���һ����־λ���ú���ô��Ӧ�ĳ�Ա����Ч�ġ�
	
	LightRaycastBit ��־�ܴ��ݸ� raycasting �����������������������ṹ��ָ����Ա���Ӷ����Ż����������ٶȵ����á�*/	
	unsigned long 	flags;
};

/** �Ӵ�ͨ����Ϣ */
enum LightContactPairFlag
{
	/** ������ɫ��ʼ�Ӵ�ʱ���ʹ˱��� */
	LIGHT_NOTIFY_ON_START_TOUCH					    = (1<<1),

	/** ������ɫֹͣ�Ӵ�ʱ���ʹ˱��� */
	LIGHT_NOTIFY_ON_END_TOUCH						= (1<<2),

	/** ������ɫ�����Ӵ�ʱ���ʹ˱��� */
	LIGHT_NOTIFY_ON_TOUCH							= (1<<3),
};

// �û���ɫ�Ӵ����溯��ԭ��
typedef void LightUserContactReport( LightActor * a, LightActor * b, unsigned long events );

/** �����������ṹ */
typedef struct
{
	/** �������� */
	int    type;

} LightSceneDesc;


/*! \class LightScene
 * \brief ������
 *
 *  ���ฺ�𳡾��ļ��Ķ�ȡ����ʾ�͹���Ŀǰ֧�� 3ds ��ʽ�ľ�̬���񳡾��ļ��� 
 *  ÿ�� LightScene ʵ��������ͨ�� LightEngine ��� createScene �������䡣 
 */

class LightScene
{

public:

	/*! \brief ��ѯ������ 
	 *	 
	 *  \return ��������ָ��
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn LightActor * createActor( const LightActorDesc * desc ) = 0
	 *  \brief ����һ����ɫ
	 *
	 *  ����һ����ɫ
	 *
	 *  \param const LightActorDesc * desc ��ɫ������ָ�룬����˵��Ҫ������ɫ��������
	 *	 
	 *  \return �����Ѵ����Ľ�ɫָ��
	 *
	 *  \see 
	 */
	virtual LightActor * createActor( const LightActorDesc & actorDesc ) = 0;

	/*! \fn void releaseActor( LightActor * actor ) = 0
	 *  \brief �ͷ�һ����ɫ
	 *
	 *  �ͷ�һ����ɫ
	 *
	 *  \param LightActor * actor Ҫ�ͷŽ�ɫ��ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseActor( LightActor * actor ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \fn LightJoint * createJoint( const LightJointDesc * jointDesc ) = 0
	 *  \brief ����һ���ؽ�
	 *
	 *  ����һ���ؽ�
	 *
	 *  \param const LightJointDesc * jointDesc �ؽ�������ָ�룬����˵��Ҫ�����ؽڵ�������
	 *	 
	 *  \return �����Ѵ����Ĺؽ�ָ��
	 *
	 *  \see 
	 */
	virtual LightJoint * createJoint( const LightJointDesc & jointDesc ) = 0;

	/*! \fn void releaseJoint( LightJoint * joint ) = 0
	 *  \brief �ͷ�һ���ؽ�
	 *
	 *  �ͷ�һ���ؽ�
	 *
	 *  \param LightJoint * joint Ҫ�ͷŹؽڵ�ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseJoint( LightJoint * joint ) = 0;

	/*! \fn LightFluid * createFluid( const LightFluidDesc * fluidDesc ) = 0
	 *  \brief ����һ������
	 *
	 *  ����һ������
	 *
	 *  \param const LightFluidDesc * fluidDesc ����������ָ�룬����˵��Ҫ���������������
	 *	 
	 *  \return �����Ѵ���������ָ��
	 *
	 *  \see 
	 */
	virtual LightFluid * createFluid( const LightFluidDesc & fluidDesc ) = 0;

	/*! \fn void releaseFluid( LightFluid * fluid ) = 0
	 *  \brief �ͷ�һ������
	 *
	 *  �ͷ�һ������
	 *
	 *  \param LightFluid * fluid Ҫ�ͷ������ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseFluid( LightFluid * fluid ) = 0;

#endif

	/*! \fn LightPhysicsMaterial * createPhysicsMaterial( const LightPhysicsMaterialDesc * physicsMaterialDesc ) = 0
	 *  \brief ����һ���������
	 *
	 *  ����һ���������
	 *
	 *  \param const LightPhysicsMaterialDesc * physicsMaterialDesc �������������ָ�룬����˵��Ҫ����������ʵ�������
	 *	 
	 *  \return �����Ѵ������������ָ��
	 *
	 *  \see 
	 */
	virtual LightPhysicsMaterial * createPhysicsMaterial( const LightPhysicsMaterialDesc & physicsMaterialDesc ) = 0;

	/*! \fn void releasePhysicsMaterial( LightPhysicsMaterial * physicsMaterial ) = 0
	 *  \brief �ͷ�һ���������
	 *
	 *  �ͷ�һ���������
	 *
	 *  \param LightPhysicsMaterial * physicsMaterial Ҫ�ͷ�������ʵ�ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releasePhysicsMaterial( LightPhysicsMaterial * physicsMaterial ) = 0;

	/*! \fn LightCharacter * createCharacter( const LightCharacterDesc * characterDesc ) = 0
	 *  \brief ����һ����ɫ���ƶ���
	 *
	 *  ����һ����ɫ���ƶ���
	 *
	 *  \param const LightCharacterDesc * characterDesc ��ɫ�������������ṹָ�롣
	 *	 
	 *  \return ����Ҫ�����Ľ�ɫ���ƶ���ָ��
	 *
	 *  \see 
	 */
	virtual LightCharacter * createCharacter( const LightCharacterDesc & characterDesc ) = 0;

	/*! \fn void releaseCharacter( LightCharacter * character ) = 0
	 *  \brief �ͷ�һ����ɫ���ƶ���
	 *
	 *  �ͷ�һ����ɫ���ƶ���
	 *
	 *  \param LightCharacter * character Ҫ�ͷŵĽ�ɫ���ƶ���
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void releaseCharacter( LightCharacter * character ) = 0;

	/*! \brief ��Ⱦ����
	 *
	 *  ��������Ⱦ����Ļ�򴰿�
	 *
	 *  \param ������û�в�����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void render( void ) = 0;

	/*! \brief ָ��һ����״���Ƿ�ִ����ײ���
	 *
	 *  LightCollisionGroup ��һ�� 0~31 ֮���������
	 *
	 *  \param[in] group1 ��һ��
	 *	
	 *  \param[in] group2 �ڶ���
	 *	
	 *  \param[in] enable TRUE ������FALSE �رգ�������֮�����ײ��⡣
	 *	
	 *  \see 
	 */
	virtual void setGroupCollisionFlag( LightCollisionGroup group1, LightCollisionGroup group2, bool enable ) = 0;

	/*! \brief ��ѯ������״��֮���Ƿ�ִ����ײ���
	 *	 
	 *  LightCollisionGroup ��һ�� 0~31 ֮���������
	 *
	 *  \param[in] group1 ��һ��
	 *	
	 *  \param[in] group2 �ڶ���
	 *	
	 *  \return ������֮�����ײ���״̬��TRUE ������FALSE �رգ���
	 *
	 *  \see 
	 */
	virtual bool getGroupCollisionFlag( LightCollisionGroup group1, LightCollisionGroup group2 ) = 0;

	/*! \brief �����û���ɫ�Ӵ����溯��
	 *	 
	 *  \param callback �û���ɫ�Ӵ������������ָ��
	 *		 
	 *  \see 
	 */
	virtual void setUserContactReport( LightUserContactReport * callback ) = 0;

	// ����Ͷ��

	/*! \brief �жϹ����Ƿ����ɫ AABB��������Χ�У��ཻ
	 *
	 *  \param[in] worldRay �����糡����Ͷ��Ĺ���
	 *
	 *  \param[in] shapesType ѡ��ҪͶ��Ľ�ɫ���ͣ���̬����̬����̬�Ͷ�̬��
	 *
	 *  \param[in] groups ��ɫ��������
	 *
	 *  \param[in] maxDist �ع�����ǰ����ཻ��������
	 *
	 *  \param[in] groupsMask ��ѡ�Ľ�ɫ��������
	 *	 
	 *  \return ����������κ�һ����ɫ AABB��������Χ�У��ཻ���������� TRUE�����򷵻� FALSE��
	 *
	 *  \see 
	 */
	virtual bool raycastAnyBounds( const LightRay & worldRay, LightShapesType shapesType, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, const LightGroupsMask * groupsMask=NULL ) = 0;

	/*! \brief �жϹ����Ƿ����ɫ�ཻ
	 *
	 *  \param[in] worldRay �����糡����Ͷ��Ĺ���
	 *
	 *  \param[in] shapesType ѡ��ҪͶ��Ľ�ɫ���ͣ���̬����̬����̬�Ͷ�̬��
	 *
	 *  \param[in] groups ��ɫ��������
	 *
	 *  \param[in] maxDist �ع�����ǰ����ཻ��������
	 *
	 *  \param[in] groupsMask ��ѡ�Ľ�ɫ��������
	 *
	 *  \param[in] cache �־��ȹ̵Ĺ���Ͷ�����ʹ�õĻ��棬��������д��
	 *
	 *  \return ����������κ�һ����ɫ AABB��������Χ�У��ཻ���������� TRUE�����򷵻� FALSE��
	 *
	 *  \see 
	 */	
	virtual bool raycastAnyShape( const LightRay & worldRay, LightShapesType shapesType, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, const LightGroupsMask * groupsMask=NULL, LightActor ** cache=NULL ) = 0;

	
	/*virtual NxU32						raycastAllBounds		(const NxRay& worldRay, NxUserRaycastReport& report, NxShapesType shapesType, NxU32 groups=0xffffffff, NxReal maxDist=NX_MAX_F32, NxU32 hintFlags=0xffffffff, const NxGroupsMask* groupsMask=NULL) const = 0;

	virtual NxU32						raycastAllShapes		(const NxRay& worldRay, NxUserRaycastReport& report, NxShapesType shapesType, NxU32 groups=0xffffffff, NxReal maxDist=NX_MAX_F32, NxU32 hintFlags=0xffffffff, const NxGroupsMask* groupsMask=NULL) const = 0;
*/
	
	/*! \brief ���ص�һ��������ཻ AABB��������Χ�У������� shapeType ���͵���״
	 *
	 *  \param[in] worldRay �����糡����Ͷ��Ĺ���
	 *
	 *  \param[in] shapesType ѡ��ҪͶ��Ľ�ɫ���ͣ���̬����̬����̬�Ͷ�̬��
	 *
	 *  \param[out] hit �ཻ������
	 *
	 *  \param[in] groups ��ɫ��������
	 *
	 *  \param[in] maxDist �ع�����ǰ����ཻ��������
	 *
     *  \param[in] hintFlags �����û�ָ�����Ƕ� LightRaycastHit ���ĸ��ֶ��Ǹ���Ȥ��
	 *
	 *  \param[in] groupsMask ��ѡ�Ľ�ɫ��������
	 *     
	 *  \return ����������ཻ�� AABB��������Χ�У���������״
	 *
	 *  \see 
	 */	
	virtual LightActor * raycastClosestBounds( const LightRay & worldRay, LightShapesType shapesType, LightRaycastHit & hit, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, unsigned long hintFlags=0xffffffff, const LightGroupsMask* groupsMask=NULL ) = 0;
	
	/*! \brief ���ص�һ��������ཻ shapeType ���͵���״
	 *
	 *  \param[in] worldRay �����糡����Ͷ��Ĺ���
	 *
	 *  \param[in] shapesType ѡ��ҪͶ��Ľ�ɫ���ͣ���̬����̬����̬�Ͷ�̬��
	 *
	 *  \param[out] hit �ཻ������
	 *
	 *  \param[in] groups ��ɫ��������
	 *
	 *  \param[in] maxDist �ع�����ǰ����ཻ��������
	 *
     *  \param[in] hintFlags �����û�ָ�����Ƕ� LightRaycastHit ���ĸ��ֶ��Ǹ���Ȥ��
	 *
	 *  \param[in] groupsMask ��ѡ�Ľ�ɫ��������
	 *
     *  \param[in] cache �־��ȹ̵Ĺ���Ͷ�����ʹ�õĻ��棬��������д��
	 *	 
	 *  \return ����������ཻ����״
	 *
	 *  \see 
	 */
	virtual LightActor * raycastClosestShape( const LightRay & worldRay, LightShapesType shapesType, LightRaycastHit & hit, unsigned long groups=0xffffffff, float maxDist=LIGHT_MAX_F32, unsigned long hintFlags=0xffffffff, const LightGroupsMask* groupsMask=NULL, LightActor ** cache=NULL ) = 0;

};