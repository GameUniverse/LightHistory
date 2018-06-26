/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   video.h
 *  ����:   ��Ƶ(��Ƶ)����
 *
 ****************************************************************************/


/*! \file video.h
 * ��Ƶ(��Ƶ)����.
 * ���ļ�����Ƶ(��Ƶ)����ͷ�ļ�.
 */

/* �ظ����ţ�ֱ����ȷֹͣ */
#define LIGHT_REPEAT_INFINITE  0x7FFFFFFF

/* ����״̬ */
#define LIGHT_STATE_STOPPED   0
#define LIGHT_STATE_PAUSED    1
#define LIGHT_STATE_PLAYING   2


/** ��Ƶ�������� */
class LightVideoDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightVideoDesc()
	{
		memset( this, 0, sizeof(LightVideoDesc) );
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


/*! \class LightVideo
 *  \brief ��Ƶ/��Ƶ�� 
 *
 *  ���ฺ����Ƶ/��Ƶ�ļ��Ĳ��ţ�֧�� MPEG2��AVI��MP3��WAV��MIDI�ȴ󲿷ֳ�����
 *  ��Ƶ����Ƶ�ļ���ÿ�� LightVideo ʵ��������ͨ�� LightEngine ��� NewVideo �������䡣 
 */

class LightVideo
{

public:

	/*! \brief ��ѯ������
	 *
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ����Ƶ�ļ�
	 *
	 *  ֧�� MPEG2��AVI��MP3��WAV��MIDI�ȴ󲿷ֳ�������Ƶ����Ƶ�ļ���
	 *
	 *  \param filename[in] ��Ƶ�ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see close, play, stop
	 */
	virtual int open ( const char *filename ) = 0;

	/*! \brief ���ò��Ŵ���(ȫ����Ч)
	 *	 
	 *  \param left[in] ������߿�����
	 *
	 *  \param top[in] �����ϱ߿�����
	 *
	 *  \param right[in] �����ұ߿�����
	 *
	 *  \param bottom[in] �����±߿�����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setWindow ( int left, int top, int right, int bottom ) = 0;

	/*! \brief ���ò���λ��
	 *	 
	 *  \param position[in] ����λ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int seek ( double position ) = 0;

	/*! \brief �����ظ����Ŵ���
	 *	 
	 *  \param repeats[in] �ظ����ŵĴ��������Ҫһֱ�ظ����ţ�ֱ����ȷֹͣ��������Ϊ LIGHT_REPEAT_INFINITE ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setRepeats ( int repeats ) = 0;

	/*! \brief ����
	 *
	 *  ������Ƶ�ļ���
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int play ( void ) = 0;

	/*! \brief ��ͣ
	 *
	 *  ��ͣ������Ƶ�ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int pause ( void ) = 0;

	/*! \brief ֹͣ
	 *
	 *  ֹͣ������Ƶ�ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int stop ( void ) = 0;

	/*! \brief ��ѯ����״̬
	 *
	 *  ��ѯ��Ƶ�ļ�����״̬��
	 *
	 *  \return  ���ص�ǰ����״̬���������������һ�ֲ���״̬��
	 *           \li LIGHT_STATE_STOPPED   ֹͣ״̬
	 *           \li LIGHT_STATE_PAUSED    ��ͣ״̬
	 *           \li LIGHT_STATE_PLAYING   ���ڲ���
	 */
	virtual int getState ( void ) = 0;

	/*! \brief �ر���Ƶ(��Ƶ)�ļ�
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int close ( void ) = 0;

};