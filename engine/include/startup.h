/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   startup.h
 *  ����:   ������������
 *
 ****************************************************************************/


/** \file startup.h
 * ���洴������
 * ���ļ������洴������ͷ�ļ�.
 */


/*! \fn LightEngine * LightEngineCreate( LightEngineDesc & engineDesc )
 *  \brief ������������ʵ��
 *
 *  �������������һ��ʵ����������һ�� LightEngine ָ�롣Ŀǰ��ͬһ��Ӧ�ó����иú���ֻ�ܵ���һ�Σ�Ҳ����˵ֻ�ܴ��������һ��ʵ������
 *  ��ͬ����ͬʱʹ�ù��������໥û��Ӱ�졣
 *
 *  \param engineDesc ����������������ָ������ʹ�õ����ԡ�
 *
 *  \remarks ������ʹ������ǰ����Ҫ���õĵ�һ������������Ĵ󲿷ֹ��ܶ���Ҫͨ������ LightEngine ����ɡ�
 *
 *  \return ����������óɹ�������һ�� LightEngine ָ�룬���򷵻� NULL ��
 */
LightEngine * LightEngineCreate( LightEngineDesc & engineDesc );

/*! \fn LightEngine * LightEngineCreate( LightEngineDesc * desc )
 *  \brief �ͷŹ�������ʵ��
 *
 *  �ͷŹ��������ʵ����
 *
 *  \param Ҫ�ͷŵĹ�������ʵ��ָ�룬Ŀǰ��ͬһ��������ֻ�ܴ���һ��ʵ����
 *
 *  \remarks ����������ʹ�ý����󣬱���Ҫ���õ�һ��������
 *
 *  \return ����������óɹ�������һ�� LightEngine ָ�룬���򷵻� NULL ��
 */
void LightEngineRelease( LightEngine * engine );

/*! \fn LightEngine * LightEngineSingle( void )
 *  \brief ��ѯ��������ȫ��ָ��
 *
 *  ��ѯ��������ȫ��ָ�룬�ú��������� LightEngineCreate ����֮����ã����������������ڼ䣬ֻ���������һ��άһʵ����
 *
 *  \param ������û�в�����
 *
 *  \remarks ����Ĵ󲿷ֹ��ܶ���Ҫͨ������ LightEngine ����ɣ�����һ�δ�������ʵ�����Ժ���ʱ����ͨ�����øú�������ȡ�����ȫ��ָ�롣
 *
 *  \return ����������óɹ�������һ�� LightEngine ָ�룬���򷵻� NULL ��
 */
LightEngine * LightEngineGet( void );
