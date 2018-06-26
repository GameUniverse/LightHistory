/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2007 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �ļ�:   lensflare.h
 *  ����:   ͸�����κ���
 *
 ****************************************************************************/


/*! \file lensflare.h
 *  ͸�����κ���.
 * ���ļ���͸�����κ���ͷ�ļ�.
 */

/*! \class LightLensFlare
 * \brief ͸��������
 *
 *  ���ฺ��͸�����εĴ�������ʾ��
 *  ÿ�� LightLensFlare ʵ��������ͨ�� LightEngine ��� NewLensFlare �������䡣 
 */

class LightLensFlare
{

public:

	/*! \fn void Release() = 0
	 *  \brief ���͸������
	 *
	 *  ���͸�����Ρ�
	 *
	 *  \param ��
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void Release() = 0;

	/*! \fn void SetPosition( float x, float y, float z ) = 0
	 *  \brief ����͸������λ��
	 *
	 *  ����͸������λ��
	 *
	 *  \param float x ͸������λ�õ� x ����
	 *
	 *  \param float y ͸������λ�õ� y ����
	 *
	 *  \param float z ͸������λ�õ� z ����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void SetPosition( float x, float y, float z ) = 0;

	/*! \fn void AddSubNode( float size, float pos, LightTexture *texture ) = 0
	 *  \brief ����һ��͸�������ӽڵ�
	 *
	 *  ����һ��͸�������ӽڵ�
	 *
	 *  \param float size �ڵ��С
	 *
	 *  \param float pos �ڵ�λ��
	 *
	 *  \param LightTexture *texture �ڵ�����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void AddSubNode( float size, float pos, LightTexture *texture ) = 0;

	/*! \fn void AddMainNode( float size, LightTexture *texture ) = 0
	 *  \brief ����һ��͸���������ڵ�
	 *
	 *  ����һ��͸���������ڵ�
	 *
	 *  \param float size �ڵ��С
	 *
	 *  \param LightTexture *texture �ڵ�����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void AddMainNode( float size, LightTexture *texture ) = 0;

	/*! \fn void Draw() = 0
	 *  \brief ��ʾ͸������
	 *
	 *  ��ʾ͸������
	 *
	 *  \param ��
	 *	 
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void Draw() = 0;
	
};
