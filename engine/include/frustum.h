/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   frustum.h
 *  ����:   ��׶�庯��
 *
 ****************************************************************************/


/*! \file frustum.h
 * ��׶�庯��.
 * ���ļ�����׶�庯��ͷ�ļ�.
 */

/*! \class LightFrustum
 * \brief ��׶����
 *
 *  ���ฺ����׶��Ŀɼ��Բ��ԣ�֧�ֵ㡢�����塢�����������Ĳ��ԡ�
 *  ÿ�� LightFrustum ʵ��������ͨ�� LightEngine ��� NewFrustum �������䡣  
 */

class LightFrustum
{

public:
	
	/*! \brief ����ͶӰ�����ģ���Ӿ��������׶�壨ÿ���������ת���ƶ�ʱ���ã�
	 *	 
	 *  \see 
	 */
	virtual void calculateFrustum() = 0;

	/*! \brief ���ָ�����Ƿ�����׶���У�����Ƿ��� TRUE�����򷵻� FALSE ��
	 *
	 *  \param float x Ҫ����� x ����
	 *
	 *  \param float y Ҫ����� y ����
	 *
	 *  \param float z Ҫ����� z ����
	 *
	 *  \return ����Ƿ��� TRUE�����򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool pointInFrustum( float x, float y, float z ) = 0;

	/*! \brief ���ָ�������Ƿ�����׶���ཻ������Ƿ��� TRUE�����򷵻� FALSE ��
	 *	 
	 *  \param float x ����Բ�ĵ� x ����
	 *
	 *  \param float y ����Բ�ĵ� y ����
	 *
	 *  \param float z ����Բ�ĵ� z ����
	 *
	 *  \param float radius ����İ뾶
	 *
	 *  \return ����Ƿ��� TRUE�����򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool sphereInFrustum( float x, float y, float z, float radius ) = 0;

	/*! \brief ���ָ���������Ƿ�����׶���ཻ������Ƿ��� TRUE�����򷵻� FALSE ��
	 *
	 *  \param float x ���������ĵ� x ����
	 *
	 *  \param float y ���������ĵ� y ����
	 *
	 *  \param float z ���������ĵ� z ����
	 *
	 *  \param float size ������߳�
	 *
	 *  \return ����Ƿ��� TRUE�����򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool cubeInFrustum( float x, float y, float z, float size ) = 0;

	/*! \brief ���ָ���������Ƿ�����׶���ཻ������Ƿ��� TRUE�����򷵻� FALSE ��
	 *
	 *  \param float x ���������ĵ� x ����
	 *
	 *  \param float y ���������ĵ� y ����
	 *
	 *  \param float z ���������ĵ� z ����
	 *
	 *  \param float sizeX ������ x �᷽��ı߳�
	 *
	 *  \param float sizeY ������ y �᷽��ı߳�
	 *
	 *  \param float sizeZ ������ z �᷽��ı߳�
	 *
	 *  \return ����Ƿ��� TRUE�����򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool boxInFrustum( float x, float y, float z, float sizeX, float sizeY, float sizeZ ) = 0;

};