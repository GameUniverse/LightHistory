/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2007 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �ļ�:   md3.h
 *  ����:   md3 ģ�ͺ���
 *
 ****************************************************************************/


/*! \file md3.h
 * md3 ģ�ͺ���
 * ���ļ��� md3 ģ�ͺ���ͷ�ļ�.
 */

struct t3DModel;

// ģ�Ͳ��� ID
#define LIGHT_MD3_LOWER   0	  // ��֫ģ�� ID
#define LIGHT_MD3_UPPER	  1	  // ��֫ģ�� ID
#define LIGHT_MD3_HEAD	  2	  // ͷ��ģ�� ID
#define LIGHT_MD3_WEAPON  3	  // ����ģ�� ID

/*! \class LightModelMD3
 * \brief MD3 ģ����
 *
 *  ���ฺ�� MD3 ģ���ļ��Ķ�ȡ����ʾ��֧�������ϲ����²��������ö�����֧�������󶨡� 
 *  ÿ�� LightModelMD3 ʵ��������ͨ�� LightEngine ��� NewModelMD3 �������䡣 
 */

class LightModelMD3
{

public:
	
	/*! \fn bool LoadModel( LPSTR strModel ) = 0
	 *  \brief ��ģ���ļ������ڴ�
	 *
	 *  �ļ���ǰ׺���ᱻ�ӵ� _upper.md3, _lower.md3 or _head.md3 ǰ�棬Ȼ���ٽ�������ڴ档
	 *	 
	 *  \param LPSTR strModel ģ���ļ���ǰ׺
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual bool LoadModel( LPSTR strModel ) = 0;

	/*! \fn bool LoadWeapon( LPSTR strModel ) = 0
	 *  \brief ������ģ�Ͷ����ڴ�
	 *
	 *  �ļ���ǰ׺���ᱻ�ӵ� .md3 ǰ�棬Ȼ���ٽ�������ڴ档
	 *	 
	 *  \param LPSTR strModel ģ���ļ���ǰ׺
	 *
	 *  \remarks ����ģ�ͱ������ڴ�󣬻��Զ��������ģ�Ͱ󶨣�������ģ����ȷ�˶���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual bool LoadWeapon( LPSTR strModel ) = 0;

	/*! \fn void SetBoundBox ( float x, float y, float z ) = 0
	 *  \brief ����ģ�Ͱ�Χ�д�С
	 *
	 *  ����ģ�Ͱ�Χ�д�С
	 *
	 *  \param float x ��Χ�� x �᷽��Ĵ�С
	 *	
	 *  \param float y ��Χ�� y �᷽��Ĵ�С
	 *	
	 *  \param float z ��Χ�� z �᷽��Ĵ�С
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void SetBoundBox ( float x, float y, float z ) = 0;

	/*! \fn const float * GetBoundBox ( void ) = 0
	 *  \brief ��ѯģ�Ͱ�Χ�д�С
	 *
	 *  ��ѯģ�Ͱ�Χ�д�С
	 *
	 *  \param ������û�в�����
	 *		 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����ָ���Χ�д�С��ֻ��ָ�롣
	 */
	virtual const float * GetBoundBox ( void ) = 0;

	/*! \fn void SetUpperState( LPSTR UpperState ) = 0
	 *  \brief ����ģ���ϲ�����
	 *
	 *  ����ģ���ϲ�����
	 *
	 *  \param LPSTR UpperState ģ���ϲ�����
	 *	
	 *  \remarks ������һ���ַ���ָ����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual void SetUpperState( LPSTR UpperState ) = 0;

	/*! \fn void SetLowerState( LPSTR LowerState ) = 0
	 *  \brief ����ģ���²�����
	 *
	 *  ����ģ���²�����
	 *
	 *  \param LPSTR UpperState ģ���²�����
	 *	
	 *  \remarks ������һ���ַ���ָ����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual void SetLowerState( LPSTR LowerState ) = 0;

	/*! \fn LPSTR GetUpperState( void ) = 0
	 *  \brief ��ѯģ���ϲ�����
	 *
	 *  ��ѯģ���ϲ�����
	 *
	 *  \param ������û���κβ���
	 *	
	 *  \remarks ������һ���ַ���ָ����
	 *
	 *  \return ����������óɹ�������һ�������ַ���ָ�룻�����������ʧ�ܣ����ؿ�ָ�� NULL��
	 */
	virtual LPSTR GetUpperState( void ) = 0;

	/*! \fn LPSTR GetLowerState( void ) = 0
	 *  \brief ��ѯģ���²�����
	 *
	 *  ��ѯģ���²�����
	 *
	 *  \param ������û���κβ���
	 *	
	 *  \remarks ������һ���ַ���ָ����
	 *
	 *  \return ����������óɹ�������һ�������ַ���ָ�룻�����������ʧ�ܣ����ؿ�ָ�� NULL��
	 */
	virtual LPSTR GetLowerState( void ) = 0;

	/*! \fn void Render( void ) = 0
	 *  \brief ��Ⱦģ��
	 *
	 *  ��ģ����Ⱦ����Ļ�򴰿�
	 *
	 *  \param ������û�в�����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void Render( void ) = 0;

	/*! \fn void RenderShadow( void ) = 0
	 *  \brief 	��Ⱦģ����Ӱ
	 *
	 *  ��ģ����Ӱ��Ⱦ����Ļ�򴰿�
	 *
	 *  \param ������û�в�����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void RenderShadow( void ) = 0;

	/*! \fn void Adjust( float x, float y, float z ) = 0
	 *  \brief У׼ģ��λ��
	 *
	 *  �ƶ�ģ��λ�ã�ʹ�䴦����ȷ������λ�á�
	 *
	 *  \param float x У׼���� x ����
	 *	
	 *  \param float y У׼���� y ����
	 *	
	 *  \param float z У׼���� z ����
	 *	
	 *  \remarks ��һ�ε��øú���ǰһֱ��Ч��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void Adjust( float x, float y, float z ) = 0;

	/*! \fn void SetPos( float x, float y, float z ) = 0
	 *  \brief ����ģ��λ��
	 *
	 *  ����ģ���ڳ����е�λ�����ꡣ
	 *
	 *  \param float x ģ��λ�õ� x ����
	 *	
	 *  \param float y ģ��λ�õ� y ����
	 *	
	 *  \param float z ģ��λ�õ� z ����
	 *	
	 *  \remarks ֱ�ӽ�ģ�͵�λ������Ϊ ��x, y, z������������ײ���ļ��㡣
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual void SetPos( float x, float y, float z ) = 0;

	/*! \fn void Goto( float x, float y, float z ) = 0
	 *  \brief �ƶ���ָ��λ��
	 *
	 *  ��ģ���ƶ���ָ��λ��
	 *
	 *  \param float x Ŀ��λ�õ� x ����
	 *	
	 *  \param float y Ŀ��λ�õ� y ����
	 *	
	 *  \param float z Ŀ��λ�õ� z ����
	 *	
	 *  \remarks ���ģ������λ���볡��û�з�����ײ����λ�����óɹ�������ģ��λ�ñ�����Ϊ��ײ��λ�á�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual void Goto( float x, float y, float z ) = 0;

	/*! \fn void SetRotate( float angle, float x, float y, float z ) = 0
	 *  \brief ����ģ����ת�Ƕ�
	 *
	 *  ����ģ���ڳ����е���ת�Ƕȡ�
	 *
	 *  \param float angle ģ�͵���ת�Ƕ�
	 *	
	 *  \param float x ��ת������ x ����
	 *	
	 *  \param float y ��ת������ y ����
	 *	
	 *  \param float z ��ת������ z ����
	 *	
	 *  \remarks ��תʱ��ԭ��͸�������ɵ��߶�Ϊ�������ת�����ģ�����½Ƕ��볡��û�з�����ײ������ת�Ƕ�λ�����óɹ���
	 *  ����ģ�ͽǶȱ�����Ϊ��ײ����ת�Ƕȡ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
    virtual void SetRotate( float angle, float x, float y, float z ) = 0;

	/*! \fn void GetPos( vec3_t pos ) = 0
	 *  \brief ��ѯģ��λ��
	 *
	 *  ��ѯģ���ڳ����е�λ�����ꡣ
	 *
	 *  \param vec3_t pos ģ��λ�ýṹָ��
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��ģ��λ���Ѿ�ͨ������ָ�뷵�ء�
	 */
	virtual void GetPos( vec3_t pos ) = 0;

	/*! \fn bool IsOnGround() = 0
	 *  \brief ��ѯģ���Ƿ������Ӵ�
	 *
	 *  ��ѯģ���Ƿ������Ӵ�
	 *
	 *  \param ������û�в�����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ���ģ�������Ӵ����� TRUE�����򷵻� FALSE��
	 */
	virtual bool IsOnGround() = 0;

	/*! \fn bool CrossRay( vec3_t a, vec3_t b, vec3_t cross ) = 0
	 *  \brief ���ָ���߶���ģ���Ƿ��ཻ
	 *
	 *  ���ָ���߶���ģ���Ƿ��ཻ������ཻ�����ؽ��㣩��
	 *
	 *  \param  vec3_t a �߶���ʼ��������
	 *	
	 *  \param  vec3_t b �߶ν�����������
	 *	
	 *  \param  vec3_t cross �߶���ģ�͵Ľ�������
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����߶���ģ���ཻ������ TRUE��ͬʱ�� cross �з��ؽ������꣬���򷵻� FALSE��
	 */
	virtual bool CrossRay( vec3_t a, vec3_t b, vec3_t cross ) = 0;

	/*! \fn bool CrossSphere( vec3_t start, vec3_t end, float radius, vec3_t cross ) = 0
	 *  \brief ���ָ��������ģ���Ƿ�����ײ
	 *
	 *  ���ָ��������ģ���Ƿ�����ײ�����������ײ�����ؽ��㣩��
	 *
	 *  \param vec3_t start �����˶���ʼ��
	 *
	 *  \param vec3_t end �����˶�������
	 *	 
	 *  \param  float radius ����뾶
	 *	
	 *  \param  vec3_t cross ������ģ�͵Ľ�������
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ���������ģ���ཻ������ TRUE��ͬʱ�� cross �з��ؽ������꣬���򷵻� FALSE��
	 */
	virtual bool CrossSphere( vec3_t start, vec3_t end, float radius, vec3_t cross ) = 0;

	/*! \fn bool CrossBox( vec3_t start, vec3_t end, vec3_t min, vec3_t max, vec3_t cross ) = 0
	 *  \brief ���ָ����Χ����ģ���Ƿ�����ײ
	 *
	 *  ���ָ����Χ�У�AABB����ģ���Ƿ�����ײ�����������ײ�����ؽ��㣩��
	 *
	 *  \param vec3_t start ��Χ���˶���ʼ��
	 *
	 *  \param vec3_t end ��Χ���˶�������
	 *	 
	 *  \param  vec3_t min ��Χ�жԽ�����С����
	 *	
	 *  \param  vec3_t max ��Χ�жԽ�����󶥵�
	 *	
	 *  \param  vec3_t cross ��Χ����ģ�͵Ľ�������
	 *	
	 *  \remarks  ������û�������Ϣ��
	 *
	 *  \return  �����Χ����ģ���ཻ������ TRUE��ͬʱ�� cross �з��ؽ������꣬���򷵻� FALSE��
	 */
	virtual bool CrossBox( vec3_t start, vec3_t end, vec3_t min, vec3_t max, vec3_t cross ) = 0;

};