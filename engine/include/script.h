/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   script.h
 *  ����:   �ű�����
 *
 ****************************************************************************/


/*! \file script.h
 * �ű�����.
 * ���ļ��ǽű�����ͷ�ļ�.
 */


/** �ű��������� */
class LightScriptDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightScriptDesc()
	{
		memset( this, 0, sizeof(LightScriptDesc) );
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


/*! \class LightScript
 *  \brief �ű���
 *
 *  ���ฺ�� c/c++ �ű��ļ��Ķ�ȡ�����ͣ�ִ�У�֧��������󲿷ֹ��ܡ�
 *  ÿ�� LightScript ʵ��������ͨ�� LightEngine ��� createScript �������䣬 releaseScript �ͷš�
 */

class LightScript
{

public:

	/*! \brief ��ѯ������
	 *
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ����ű��ļ�
     *
	 *  ���ű��ļ������ڴ���
	 *
     *  \param filename[in] �ű��ļ���.
     *
	 *  \remarks ֧�� lua �ű��ļ���
	 *
     *  \return ����������óɹ������� 0�������������ʧ�ܣ����ش�����롣
     */
	virtual int load ( const char *filename ) = 0;

	/*! \brief ����ű�
	 *
	 *  ��������ڴ�Ľű�
	 *	 
	 *  \remarks 
	 *
	 *  \return ����������óɹ������� 0�������������ʧ�ܣ����ش�����롣
	 */
	virtual int build( const char *module ) = 0;

	/*! \brief ���ݺ���������ѯ�������
	 *
	 *  ִ�б����Ľű�
	 *	 
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int getFunctionIDByIndex( const char *module, int index ) = 0;

	/*! \brief ���ݺ������Ʋ�ѯ�������
	 *
	 *  ִ�б����Ľű�
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int getFunctionIDByName( const char *module, const char *name ) = 0;

	/*! \brief ���ݺ���˵����ѯ�������
	 *
	 *  ִ�б����Ľű�
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int getFunctionIDByDecl(const char *module, const char *decl) = 0;

	/*! \brief ׼��ִ��ָ���ĺ���
	 *	 
	 *  \param ������û�в�����
	 *
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int prepare( int funcId ) = 0;

	/*! \brief ִ�нű�
	 *
	 *  ִ�б����Ľű�
	 *	 
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int execute() = 0;

	/*! \brief ��ֹ�ű�
	 *
	 *  ִ�б����Ľű�
	 *	 
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int abort() = 0;

	/*! \brief ��ͣ�ű�
	 *	 
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int suspend() = 0;

	/*! \brief ִ��ָ���Ľű��ַ���
	 *	 
	 *  \param ������û�в�����
	 *
	 *  \remarks ���Խ���ִ�нű���
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int executeString(const char *module, const char *script ) = 0;

	/*! \brief ��ѯ�ű�ִ��״̬
	 *	 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ���ؽű���ִ��״̬��
	 */
	virtual int getState( void ) = 0;

	/*! \brief �ͷŽű��ļ���ռ�ڴ�
	 *	 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void unload ( void ) = 0;	

};