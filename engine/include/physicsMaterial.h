/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   physicsMaterial.h
 *  ����:   ������ʺ���
 *
 ****************************************************************************/


/*! \file physicsMaterial.h
 * ������ʺ���
 * ���ļ���������ʺ���ͷ�ļ�.
 */


class LightScene;


// �����������ṹ
typedef struct
{
	/// ��̬ĥ����ϵ����ȡֵ��Χ [0��+�����]
	float dynamicFriction;
	
	/// ��̬ĥ����ϵ����ȡֵ��Χ [0,+�����]
	float staticFriction;
	
	/// ����ϵ����ȡֵ��ΧΪ [0��1.0]
	float restitution;

} LightPhysicsMaterialDesc;


/*! \class LightPhysicsMaterial
 * \brief ���������
 *
 *  ���ฺ�𳡾��ļ��Ķ�ȡ����ʾ�͹���Ŀǰ֧�� 3ds ��ʽ�ľ�̬���񳡾��ļ��� 
 *  ÿ�� LightScene ʵ��������ͨ�� LightEngine ��� NewMesh �������䡣 
 */

class LightPhysicsMaterial
{

public:

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

	/*! \fn int getMaterialIndex() = 0
	 *  \brief ��ѯ��������
	 *
	 *  ��ѯ��������
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ز��ʵ�����ֵ
	 *
	 *  \see 
	 */
	virtual	int getMaterialIndex() = 0;

	/*! \fn void setToDefault() = 0
	 *  \brief ����������Ϊȱʡ����
	 *
	 *  ����������Ϊȱʡ����
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual	void setToDefault() = 0;

	/*! \fn void loadFromDesc( const LightPhysicsMaterialDesc & desc ) = 0
	 *  \brief �Ӳ�����������ȡ��������
	 *
	 *  �Ӳ�����������ȡ��������
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ز��ʵ�����ֵ
	 *
	 *  \see 
	 */
	virtual	void loadFromDesc( const LightPhysicsMaterialDesc & desc ) = 0;

	/*! \fn void saveToDesc( LightPhysicsMaterialDesc & desc ) const = 0
	 *  \brief ���������Ա��浽������������
	 *
	 *  ���������Ա��浽������������
	 *
	 *  \param LightPhysicsMaterialDesc & desc Ҫ�������Ե�Ŀ�����������
	 *	 
	 *  \return ���ز��ʵ�����ֵ
	 *
	 *  \see 
	 */
	virtual	void saveToDesc( LightPhysicsMaterialDesc & desc ) = 0;

	/*! \fn void setDynamicFriction( float factor ) = 0
	 *  \brief ���ö�̬Ħ����ϵ��
	 *
	 *  ���ö�̬Ħ����ϵ��
	 *
	 *  \param float factor ��̬ĥ����ϵ����ȡֵ��ΧΪ��0��+�����
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */	
	virtual	void setDynamicFriction( float factor ) = 0;

	/*! \fn float getDynamicFriction() const = 0
	 *  \brief ��ѯ��̬Ħ����ϵ��
	 *
	 *  ��ѯ��̬Ħ����ϵ��
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ض�̬ĥ����ϵ����ȡֵ��ΧΪ��0��+�����
	 *
	 *  \see 
	 */	
	virtual	float getDynamicFriction() = 0;

	/*! \fn void setStaticFriction( float factor ) = 0
	 *  \brief ���þ�̬Ħ����ϵ��
	 *
	 *  ���þ�̬Ħ����ϵ��
	 *
	 *  \param float factor ��̬ĥ����ϵ����ȡֵ��ΧΪ��0��+�����
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */	
	virtual	void setStaticFriction( float factor ) = 0;
	
	/*! \fn float getStaticFriction() const = 0
	 *  \brief ��ѯ��̬Ħ����ϵ��
	 *
	 *  ��ѯ��̬Ħ����ϵ��
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ؾ�̬ĥ����ϵ����ȡֵ��ΧΪ��0�������
	 *
	 *  \see 
	 */	
	virtual	float getStaticFriction() = 0;

	/*! \fn void setRestitution( float factor ) = 0
	 *  \brief ���õ���ϵ��
	 *
	 *  ���õ���ϵ��
	 *
	 *  \param float factor ����ϵ����ȡֵ��ΧΪ��0��1��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */	
	virtual	void setRestitution( float factor ) = 0;

	/*! \fn float getRestitution() const = 0
	 *  \brief ��ѯ����ϵ��
	 *
	 *  ��ѯ����ϵ��
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ���ص���ϵ����ȡֵ��ΧΪ��0��1��
	 *
	 *  \see 
	 */	
	virtual	float getRestitution() = 0;


	// ����������
	void * userData;	//!< ���ܽ��������κ���;��ͨ��������һ�����󴴽� 1:1 ��Ӧ�Ĺ�ϵ��

};