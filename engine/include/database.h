/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   database.h
 *  ����:   ���ݿ⺯��
 *
 ****************************************************************************/


/*! \file database.h
 * ���ݿ⺯��.
 * ���ļ������ݿ⺯��ͷ�ļ�.
 */


/** �������ݿ����� */
typedef struct
{
	/** ��Ϊ��������ͨ�����ڴ�����Ϣ�����Ա���Ҫ����������󶨵�һ������ */
	//HWND hwnd;

} LightDatabaseDesc;


/*! \brief ���ݿ���
 *
 *  ���ฺ������������ݿ������
 *  ÿ�� LightDatabase ʵ��������ͨ�� LightCreateDatabase �������䡣
 */

class LightDatabase
{

public:

	/*! \brief ���ӵ�ָ�����ݿ�	 
	 *
	 *  \param host[in] ������
	 *
	 *  \param user[in] �û���
	 *
	 *  \param password[in] ����
	 *
	 *  \param database[in] ���ݿ���
	 *
	 *  \param port[in] ���ݿ�˿�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int connect( const char *host, const char *user, const char *password, const char *database, unsigned int port ) = 0;

	/*! \brief ��ָ�������ݿ��ļ�
	 *	 
	 *  \param database ���ݿ��ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int selectDatabase( const char *database ) = 0;

	/*! \brief ��ѯָ��������
	 *	 
	 *  \param query Ҫִ�еĲ�ѯ����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int query( const char *query ) = 0;

};