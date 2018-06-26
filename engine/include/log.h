/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   log.h
 *  ����:   ��־����
 *
 ****************************************************************************/


/*! \file log.h
 * ��־����.
 * ���ļ�����־����ͷ�ļ�.
 */


/** ��־�������� */
class LightLogDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightLogDesc()
	{
		memset( this, 0, sizeof(LightLogDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		VEC3( position, 0, 0, 0 );		
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightLog
 *  \brief ��־�� 
 *
 *  ���ฺ����־����Ϣ����������ƺ͹���Ŀǰ֧��������ļ���
 *  ÿ�� LightLog ʵ��������ͨ�� LightEngine ��� createLog �������䣬 releaseLog �ͷš�
 */

class LightLog
{

public:

	/*! \brief ����־����豸
     *	
     *  \param device[in] Ҫ�򿪵���־����豸���ƣ�Ŀǰֻ֧���ļ��豸��Ӧ���˲�����Ϊһ���ļ��������Ա���·������
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ����������óɹ������� 0�������������ʧ�ܣ����ش�����롣
     */
	virtual int open ( const char *device ) = 0;

	/*! \brief ���������Ϣ
     *	 
     *  \param string[in] Ҫ������Ե���Ϣ
     *	 	 
	 *  \remarks ������û�������Ϣ��     
     */
	virtual void debug ( const char *string ) = 0;

    /*! \brief ���һ����Ϣ
     *	 
     *  \param string[in] Ҫ�����һ����Ϣ
     *	 	 
	 *  \remarks ������û�������Ϣ��     
     */
	virtual void message ( const char *string ) = 0;

	/*! \brief ���������Ϣ
     *	 
     *  \param string[in] Ҫ����ľ�����Ϣ
     *	 	 
	 *  \remarks ������û�������Ϣ��     
     */
	virtual void warning ( const char *string ) = 0;

	/*! \brief ���������Ϣ
     *	 
     *  \param string[in] Ҫ����Ĵ�����Ϣ
     *	 	 
	 *  \remarks ������û�������Ϣ��     
     */
	virtual void error ( const char *string ) = 0;

	/*! \brief �ر���־����豸
     *	 
     *  \param device[in] Ҫ�رյ���־����豸���ƣ�Ŀǰֻ֧���ļ��豸��Ӧ���˲�����Ϊһ���ļ��������Ա���·������
     *	 	 
	 *  \remarks ������û�������Ϣ��
	 *
     *  \return ����������óɹ������� 0�������������ʧ�ܣ����ش�����롣
     */
	virtual int close ( const char *device ) = 0;

};