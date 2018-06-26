/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   level.h
 *  ����:   ��������
 *
 ****************************************************************************/


/*! \file level.h
 * ��������.
 * ���ļ��ǳ�������ͷ�ļ�.
 */


class LightEngine;


// ����������
class LightLevelDesc
{
	int    type;                 // ��������
	vec3_t position;             // ����λ��

};


/*! \brief ������ 
 *
 *  ���ฺ�𳡾��ļ��Ķ�ȡ����Ⱦ�����ơ����棬֧�ֵ��Ρ����硢BSP��ʽ�ĳ�����
 *  ÿ�� LightLevel ʵ��������ͨ�� LightEngine ��� createLevel �������䡣
 */

class LightLevel
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ��������ָ��
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief �������ļ������ڴ�
	 *	 
	 *  \param filename �����ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int load( const char * filename ) = 0;

	/*! \brief ��Ⱦ����
	 *	 	 
	 */
	virtual void render( void ) = 0;

	/*! \brief ��ѯ��ʾ����������
	 *		 
	 *  \return ���س�������ʾ������������
	 */
	virtual int getTrianglesCount( void ) = 0;

	/*! \brief ��ѯ����ָ��
	 *	 
	 *  \return ���س�����ĵ���ָ�롣
	 */
	//virtual LightTerrain * getTerrain( void ) = 0;

	/*! \brief ��ָ���ľ�̬����󶨵�������
	 *
	 *  \param mesh[in] Ҫ�󶨵ľ�̬����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int attachMesh( LightMesh * mesh ) = 0;

	/*! \brief ��ָ���ľ�̬����ӳ����з���
	 *
	 *  \param mesh[in] Ҫ����ľ�̬����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int detachMesh( LightMesh * mesh ) = 0;

	/*! \brief ��ѯ�����о�̬���������
	 *		 
	 *  \return ���س����о�̬���������
	 */
	virtual int getMeshCount( void ) = 0;

	/*! \brief ��ѯ��̬����ָ��
	 *
	 *  \param mesh Ҫ��ѯ�ľ�̬��������
	 *
	 *  \return ���س�����ľ�̬����ָ�롣
	 */
	virtual LightMesh * getMesh( int mesh ) = 0;

	/*! \brief ���������浽�ļ���
	 *	 
	 *  \param filename �����ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int save( const char * filename ) = 0;

	/*! \brief �������ļ����ڴ������
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int unload( void ) = 0;

};