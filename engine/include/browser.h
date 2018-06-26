/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   browser.h
 *  ����:   ���������
 *
 ****************************************************************************/


/*! \file browser.h
 * ���������.
 * ���ļ������������ͷ�ļ�.
 */

/* �ظ����ţ�ֱ����ȷֹͣ */
#define LIGHT_REPEAT_INFINITE  0x7FFFFFFF

/* ����״̬ */
#define LIGHT_STATE_STOPPED   0
#define LIGHT_STATE_PAUSED    1
#define LIGHT_STATE_PLAYING   2


/** ������������� */
class LightBrowserDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightBrowserDesc()
	{
		memset( this, 0, sizeof(LightBrowserDesc) );
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


/*! \class LightBrowser
 *  \brief ������� 
 *
 *  ���ฺ�𽻻�ʽ�ļ��Ĳ��ţ�֧�� GIF��SWF����ҳ�ļ���֧�ֱ��غ��������ֲ��ŷ�ʽ��
 *  ÿ�� LightBrowser ʵ��������ͨ�� LightEngine ��� createBrowser �������䣬 releaseBrowser �ͷš�
 */

class LightBrowser
{

public:

	/*! \brief �򿪽���ʽ�ļ�
	 *
	 *  ֧�� GIF��SWF����ҳ�ļ���֧�ֱ��غ��������ֲ��ŷ�ʽ��
	 *
	 *  \param filename ����ʽ�ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see close, play, stop
	 */
	virtual int open( const char *address ) = 0;

	/*! \brief ���ò��Ŵ���λ�úʹ�С
	 *	 
	 *  \param x �������Ͻ� x ����
	 *
	 *  \param y �������Ͻ� y ����
	 *
	 *  \param width ���ڿ��
	 *
	 *  \param height ���ڸ߶�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setWindowPosition( int x, int y, int width, int height ) = 0;

	/*! \brief ���ò���λ��
	 *	 
	 *  \param position ����λ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int seek( double position ) = 0;

	/*! \brief �����ظ����Ŵ���
	 *	 
	 *  \param repeats �ظ����ŵĴ��������Ҫһֱ�ظ����ţ�ֱ����ȷֹͣ��������Ϊ LIGHT_REPEAT_INFINITE ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setRepeats( int repeats ) = 0;

	/*! \brief ����
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int play( void ) = 0;

	/*! \brief ��ͣ
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int pause( void ) = 0;

	/*! \brief ֹͣ
	 *		 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int stop( void ) = 0;

	/*! \brief ��ѯ����״̬
	 *	 
	 *  \return  ���ص�ǰ����״̬���������������һ�ֲ���״̬��
	 *           \li LIGHT_STATE_STOPPED   ֹͣ״̬
	 *           \li LIGHT_STATE_PAUSED    ��ͣ״̬
	 *           \li LIGHT_STATE_PLAYING   ���ڲ���
	 */
	virtual int getState( void ) = 0;

	/*! \brief �رս���ʽ�ļ�
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int close( void ) = 0;

};