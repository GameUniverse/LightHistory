/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   socket.h
 *  ����:   ���纯��
 *
 ****************************************************************************/


/*! \file socket.h
 * ���纯��.
 * ���ļ������纯��ͷ�ļ�.
 */


/** �����¼����� */
#define LIGHT_FD_READ_BIT      0
#define LIGHT_FD_READ          (1 << LIGHT_FD_READ_BIT)

#define LIGHT_FD_WRITE_BIT     1
#define LIGHT_FD_WRITE         (1 << LIGHT_FD_WRITE_BIT)

#define LIGHT_FD_OOB_BIT       2
#define LIGHT_FD_OOB           (1 << LIGHT_FD_OOB_BIT)

#define LIGHT_FD_ACCEPT_BIT    3
#define LIGHT_FD_ACCEPT        (1 << LIGHT_FD_ACCEPT_BIT)

#define LIGHT_FD_CONNECT_BIT   4
#define LIGHT_FD_CONNECT       (1 << LIGHT_FD_CONNECT_BIT)

#define LIGHT_FD_CLOSE_BIT     5
#define LIGHT_FD_CLOSE         (1 << LIGHT_FD_CLOSE_BIT)

#define LIGHT_FD_QOS_BIT       6
#define LIGHT_FD_QOS           (1 << LIGHT_FD_QOS_BIT)

#define LIGHT_FD_GROUP_QOS_BIT 7
#define LIGHT_FD_GROUP_QOS     (1 << LIGHT_FD_GROUP_QOS_BIT)

#define LIGHT_FD_ROUTING_INTERFACE_CHANGE_BIT 8
#define LIGHT_FD_ROUTING_INTERFACE_CHANGE     (1 << LIGHT_FD_ROUTING_INTERFACE_CHANGE_BIT)

#define LIGHT_FD_ADDRESS_LIST_CHANGE_BIT 9
#define LIGHT_FD_ADDRESS_LIST_CHANGE     (1 << LIGHT_FD_ADDRESS_LIST_CHANGE_BIT)

#define LIGHT_FD_MAX_EVENTS    10
#define LIGHT_FD_ALL_EVENTS    ((1 << LIGHT_FD_MAX_EVENTS) - 1)

// �Զ��� SOCKET ��Ϣ
#define LIGHT_WM_SOCKET  WM_USER + 1000

// �׽��ֵ�ַ�ṹ
struct socketaddr
{
	unsigned short port;    // �˿ں�
	unsigned long  address; // IP ��ַ
};

/** ���������׽������� */
typedef struct
{
	/** ��Ϊ��������ͨ�����ڴ�����Ϣ�����Ա���Ҫ����������󶨵�һ������ */
	HWND hwnd;

} LightSocketDesc;


/*! \class LightSocket
 *  \brief �����׽�����
 *
 *  ���ฺ�������������ͨѶ��֧�ֿͻ��˺ͷ����������ַ�ʽ��
 *  ÿ�� LightSocket ʵ��������ͨ�� LightEngine ��� NewSocket �������䡣
 */

class LightSocket
{

public:

	// SOCKET ����
    #define LIGHT_SOCK_STREAM   1  // ��
    #define LIGHT_SOCK_DGRAM    2  // ���ݱ�

	// ͨѶЭ��
    #define LIGHT_IPPROTO_TCP   6  // TCP/IP Э��
    #define LIGHT_IPPROTO_UDP   17 // UDP Э��

	/*! \fn int Socket( int type, int protocol ) = 0
	 *  \brief ����һ�������׽��֣��������˻�ͻ��ˣ�
	 *
	 *  �ͻ�����Ҫ��������˷�����������һ�����������յ�����Ӧ�˿ͻ��˵���������
	 *  ������һ�����ӡ�
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int socket( int type, int protocol ) = 0;

	/*! \fn int Bind( const char* ip, unsigned short port ) = 0
	 *  \brief ����һ������������ˣ��������ˣ�
	 *
	 *  �ͻ�����Ҫ��������˷�����������һ�����������յ�����Ӧ�˿ͻ��˵���������
	 *  ������һ�����ӡ�
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int bind( const char* ip, unsigned short port ) = 0;

	/*! \fn int Listen( void ) = 0
	 *  \brief �����ͻ��˵��������󣨷������ˣ�
	 *
	 *  �������˵����� Listen() �����������ʱ�ͻ��˵��� Connect() �����������
	 *  ����Ļ����������˱����ٵ��� Accept() �����������������˺Ϳͻ��˲�����ʽ
	 *  ���ͨ�ų�������Ӷ�����
	 *
	 *  \param ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int listen( void ) = 0;

	/*! \fn LightSocket* Accept( void ) = 0
	 *  \brief ���ܿͻ��˵��������󣨷������ˣ�
	 *
	 *  Ϊ��ʹ�������˽��ܿͻ��˵��������󣬾�Ҫʹ�� Accept() �������ú����½�һ��
	 *  SOCKET ��ͻ���������ԭ�ȼ����� SOCKET �����������״̬���ȴ���������������
	 *
	 *  \param  ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual LightSocket* accept( void ) = 0;

	/*! \fn int Connect( const char* ip, unsigned short port ) = 0
	 *  \brief ��������˷����������󣨿ͻ��ˣ�
	 *
	 *  �ͻ�����Ҫ��������˷�����������һ�����������յ�����Ӧ�˿ͻ��˵���������
	 *  ������һ�����ӡ�
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int connect( const char* ip, unsigned short port ) = 0;

	/*! \fn int Send( const char* buf, int len ) = 0
	 *  \brief �������ݣ��������˻�ͻ��ˣ�
	 *
	 *  �ͻ�����Ҫ��������˷�����������һ�����������յ�����Ӧ�˿ͻ��˵���������
	 *  ������һ�����ӡ�
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int send( const char* buf, int len ) = 0;

	/*! \fn int Recv( char* buf, int len ) = 0
	 *  \brief �������ݣ��������˻�ͻ��ˣ�
	 *
	 *  �ͻ�����Ҫ��������˷�����������һ�����������յ�����Ӧ�˿ͻ��˵���������
	 *  ������һ�����ӡ�
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int recv( char* buf, int len ) = 0;

	/*! \fn unsigned long GetSocket( void ) = 0
	 *  \brief ��ѯ�����׽��ֵ� SOCKET ������������˻�ͻ��ˣ�
	 *
	 *  �������д��ڶ�����ӵ�ʱ��SOCKET ����������ֲ�ͬ���ӵ���Ϣ��	 
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ظ������׽��ֵ� SOCKET ����������������ʧ�ܣ������㡣
	 */
	virtual unsigned long getSocket( void ) = 0;

	/*! \fn int GetPeerName( struct socketaddr* address ) = 0
	 *  \brief ��ѯ�Է��� IP ��ַ�Ͷ˿ںţ��������˻�ͻ��ˣ�
	 *
	 *  ��ѯ�Է��� IP ��ַ�Ͷ˿ںţ�����ĶԷ�ָ�����뱾�����׽�����������һ����
	 *
	 *  \param struct socketaddr* address ���նԷ� IP ��ַ�Ͷ˿ںŵĽṹָ��
	 *	 
	 *  \return ����������óɹ������� 0�������������ʧ�ܣ����� -1��
	 */
	virtual int getPeerName( struct socketaddr* address ) = 0;

	/*! \fn int GetSockName( struct socketaddr* address ) = 0
	 *  \brief ��ѯ���ص� IP ��ַ�Ͷ˿ںţ��������˻�ͻ��ˣ�
	 *
	 *  ��ѯ���ص� IP ��ַ�Ͷ˿ںţ�����ı���ָ���Ǳ��׽��֡�
	 *
	 *  \param struct socketaddr* address ���ձ��� IP ��ַ�Ͷ˿ںŵĽṹָ��
	 *	 
	 *  \return ����������óɹ������� 0�������������ʧ�ܣ����� -1��
	 */
	virtual int getSockName( struct socketaddr* address ) = 0;

	/*! \brief �ر��Ѿ������������׽��֣��������˻�ͻ��ˣ�
	 *
	 *  ���Ͽ����ӻ�����Ҫ���׽���ʱ���ô˺�����	 
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int closeSocket( void ) = 0;

    #define LIGHT_SD_RECEIVE   0x00
    #define LIGHT_SD_SEND      0x01
    #define LIGHT_SD_BOTH      0x02

	/*! \brief �ر��Ѿ������������׽��֣��������˻�ͻ��ˣ�
	 *
	 *  ���Ͽ����ӻ�����Ҫ���׽���ʱ���ô˺�����	 
	 *
	 *  \param  ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int shutdown( int how ) = 0;

};