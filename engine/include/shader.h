/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   shader.h
 *  ����:   ��ɫ���Ժ���
 *
 ****************************************************************************/


/*! \file shader.h
 * ��ɫ���Ժ�����
 * ���ļ�����ɫ���Ժ���ͷ�ļ�.
 */


/** ��ɫ���������� */
class LightShaderDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightShaderDesc()
	{
		memset( this, 0, sizeof(LightShaderDesc) );
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


/*! \class LightShader
 *  \brief ��ɫ����
 *
 *  ���ฺ�� OpenGL ��ɫ���ԵĶ�ȡ�����롢���Ӻ����С�
 *  ÿ�� LightShader ʵ��������ͨ�� LightEngine ��� createShader �������䣬 releaseShader �ͷš�
 */

class LightShader
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���ļ���ȡ shader ����
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *
	 *  \param vertex ���������ļ���
	 *
	 *  \param fragment Ƭ�������ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int load( const char *vertex, const char *fragment ) = 0;

	/*! \brief ���ַ�����ȡ shader ����
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *
	 *  \param vertex ���������ļ���
	 *
	 *  \param fragment Ƭ�������ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int loadString( const char *vertex, const char *fragment ) = 0;

	/*! \brief ���� shader ����
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual bool compile( void ) = 0;

	/*! \brief ���� shader ����
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual bool link( void ) = 0;

	/*! \brief ��ѯ�������
	 *
	 *  ���ݱ������Ʋ�ѯ����������˾�������������ñ�����ֵ��
	 *
	 *  \param name[in] Ҫ��ѯ����������
	 *	 
	 *  \return �˺�������һ����������ʾ�ñ����ľ�������û���ҵ��ñ��������� name �Ա���ǰ׺ ��gl_�� ��ʼ���򷵻� -1 ��
	 *
	 *  \see 
	 */
	virtual int getVariableHandle( const char * name ) = 0;

	/*! \fn void Variable{1|2|3|4}{f|i}( int handle, TYPE v ) = 0
	 *  \brief ���ñ�����ֵ
	 *	 
	 *  \param int handle Ҫ���ñ����ľ��
	 *	 
	 *  \param TYPE v Ҫ���ñ�����ֵ
	 *	 
	 *  \return �˺���û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void variable1f( int handle, float value ) = 0;
	virtual void variable2f( int handle, float x, float y ) = 0;
	virtual void variable3f( int handle, float x, float y, float z ) = 0;
	virtual void variable4f( int handle, float x, float y, float z, float w ) = 0;
	virtual void variable1i( int handle, int value ) = 0;
	virtual void variable2i( int handle, int x, int y ) = 0;
	virtual void variable3i( int handle, int x, int y, int z ) = 0;
	virtual void variable4i( int handle, int x, int y, int z, int w ) = 0;

	/*! \brief ��ʼʹ�� shader ����
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *	 
	 *  \see 
	 */
	virtual void begin( void ) = 0;

	/*! \brief ֹͣʹ�� shader ����
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *	 
	 *  \see 
	 */
	virtual void end( void ) = 0;

	/*! \brief ��ѯ��Ϣ��־
	 *
	 *  ֧�� OpenGL ��ɫ���ԡ�
	 *
	 *  \param string[out] �����Ϣ��־���ַ���ָ�롣
	 *	 
	 *  \param size[in] �����Ϣ��־���ַ�����С��
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int getInfoLog( char *string, int size ) = 0;

	/*! \brief �ͷ� shader ������ռ�ڴ�
	 *
	 *  �ͷ� shader ������ռ�ڴ�
	 */
	virtual void unload ( void ) = 0;

};