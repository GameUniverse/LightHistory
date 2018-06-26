/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   network.h
 *  ����:   �������溯��
 *
 ****************************************************************************/


/** \file network.h
 * �������溯��
 * ���ļ����������溯��ͷ�ļ�.
 */


/** ���������������� */
typedef struct
{
	/** ��Ϊ��������ͨ�����ڴ�����Ϣ�����Ա���Ҫ����������󶨵�һ������ */
	HWND hwnd;

} LightNetworkDesc;


/*! \class LightNetwork
 * \brief ����������
 *
 *  ���ฺ��󲿷�����ϵͳ���ܵĵ��ú����������������ʵ�����䣬��������������Ҫ��һ���ࡣ
 *  �����ʵ��ָ��ֻ��ͨ�������������洴������ LightNetworkCreate �õ����ٸ����ӣ�
 *  \n
 *  \n 
 *  \n  LightNetwork * network;
 *  \n  LightNetworkDesc desc;
 *  \n  
 *  \n  // ����������������ʵ��	
 *  \n  memset( &desc, 0, sizeof(desc) );
 *  \n  desc.hwnd = hwnd;
 *  \n  network = LightNetworkCreate( desc );
 *  \n  
 *  \n  // ��һЩ����...
 *  \n  
 *  \n  // �ͷŹ�����������ʵ��
 *  \n  LightNetworkRelease( network );
 */

class LightNetwork
{

public:

	/*! \brief ֪ͨ���������յ�һ��������Ϣ
	 *	 
	 *  \return �����Ϣ�Ѵ����� TRUE, ���򷵻� FALSE ֵ
	 *
	 *  \see 
	 */
	virtual bool receiveMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) = 0;

	/*! \brief ע�ᴰ����Ϣ��������
	 *
	 *  ע�ᴰ����Ϣ��������������ע������Ϣ������������Щ���������յ����ڷ�����������Ϣ��
	 *
	 *  \param lpfnWndProc ������Ϣ��������
	 *	 
	 *  \return ����ɹ����� TRUE, ���򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool registerMessageProc( WNDPROC lpfnWndProc ) = 0;

	/*! \brief �Ƴ�������Ϣ��������
	 *
	 *  �Ƴ�������Ϣ����������ֻ���Ƴ�ǰ����ע��Ĵ�����Ϣ����������
	 *
	 *  \param lpfnWndProc ������Ϣ��������
	 *	 
	 *  \return ����ɹ����� TRUE, ���򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool removeMessageProc( WNDPROC lpfnWndProc ) = 0;

	/*! \brief ����һ�������׽���
	 *
	 *  \param socketDesc �����׽���������ָ�룬����˵��Ҫ�����׽��ֵ�������
	 *	 
	 *  \return �����Ѵ������׽���ָ��
	 *
	 *  \see 
	 */
	virtual LightSocket * createSocket( const LightSocketDesc & socketDesc ) = 0;

	/*! \brief �ͷ�һ�������׽���	 
	 *
	 *  \param socket Ҫ�ͷ������׽��ֵ�ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseSocket( LightSocket * socket ) = 0;

};