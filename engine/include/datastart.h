/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   datastart.h
 *  ����:   ���ݿ�������������
 *
 ****************************************************************************/


/** \file datastart.h
 * ���ݿ�������������
 * ���ļ������ݿ�������������ͷ�ļ�.
 */


/*! \brief ����һ���������ݿ�����ʵ��
 *
 *  ����һ���������ݿ�����ʵ���������� LightDatabase ָ�롣
 *
 *  \param ������û�в�����
 *
 *  \remarks ������ʹ�����ݿ�����ǰ����Ҫ���õĵ�һ�����������ݿ�����Ĵ󲿷ֹ��ܶ���Ҫͨ������ LightDatabase ����ɡ�
 *
 *  \return ����������óɹ�������һ�� LightDatabase ָ�룬���򷵻� NULL ��
 */
LightDatabase * LightDatabaseCreate( LightDatabaseDesc & databaseDesc );

/*! \brief �ͷŹ������ݿ�����ʵ��
 *
 *  \param Ҫ�ͷŵĹ������ݿ�����ʵ��ָ�룬Ŀǰ��ͬһ��������ֻ�ܴ���һ��ʵ����
 *
 *  \remarks ����������ʹ�ý����󣬱���Ҫ���õ�һ��������
 *
 *  \return ����������óɹ�������һ�� LightDatabase ָ�룬���򷵻� NULL ��
 */
void LightDatabaseRelease( LightDatabase * database );
