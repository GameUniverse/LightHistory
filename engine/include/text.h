/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   text.h
 *  ����:   ������
 *
 ****************************************************************************/


/*! \file text.h
 * ���ֺ���.
 * ���ļ������ֺ���ͷ�ļ�.
 */

/* ���ֱ������ģʽ */
#define LIGHT_TRANSPARENT    0  // ͸����
#define LIGHT_OPAQUE         1  // ��͸����


/** ������������ */
class LightTextDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightTextDesc()
	{
		memset( this, 0, sizeof(LightTextDesc) );
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


/*! \class LightText
 * \brief ������
 *
 *  ���ฺ�����ֵĸ�����ʾ��֧��������ʾ��ͬʱ֧�ָ������塢��С���������ת��б�塢�»��ߡ�����������������ʾ��
 *  ÿ�� LightText ʵ��������ͨ�� LightEngine ��� createText �������䣬 releaseText �ͷš�
 */

class LightText
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ��ʾָ�������֣�֧�����ģ�
	 *	 
	 *  \param string[in] Ҫ��ʾ���ַ������� 0 ������֧������
	 *
	 *  \remarks ��������صı�ע��Ϣ��
	 */
	virtual void drawText( const char *string ) = 0;

	/*! \brief ��ѯ�ַ����Ŀ�Ⱥ͸߶�
	 *	 
	 *  \param string[in] Ҫ��ѯ���ַ������� 0 ������֧������	 
	 *
	 *  \param size[out] �����ַ�����Ⱥ͸߶����ݵ�ָ��
	 *
	 *  \remarks ��������صı�ע��Ϣ��
	 */
	virtual int getTextSize( const char *string, SIZE *size ) = 0;

	/*! \brief ���õ�ǰ������ɫ
	 *	 
	 *  \param red[in] ��ɫ�ĺ�ɫ����
	 *
	 *  \param green[in] ��ɫ����ɫ����
	 *
	 *  \param blue[in] ��ɫ����ɫ����
	 *
	 *  \remarks �졢�̡���������ɫ��������Ч��Χ��Ϊ 0~255 �� 0 Ϊ��� 255 Ϊ������
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void color( int red, int green, int blue ) = 0;
    
	/*! \brief �������ֱ������ģʽ
	 *	 
	 *  \param mode[in] ���ֱ������ģʽ�� LIGHT_TRANSPARENT Ϊ͸���ģ� LIGHT_OPAQUE Ϊ��͸���ġ�
	 *
	 *  \remarks ȱʡ�����Ϊ LIGHT_TRANSPARENT��͸���ġ�
	 *
	 *  \return ����ԭ�������ֱ������ģʽ��
	 */
	virtual int setBackMode( int mode ) = 0;

	/*! \brief ���õ�ǰ���ֱ���ɫ
	 *	 
	 *  \param red[in] ��ɫ�ĺ�ɫ����
	 *
	 *  \param green[in] ��ɫ����ɫ����
	 *
	 *  \param blue[in] ��ɫ����ɫ����
	 *
	 *  \remarks �졢�̡���������ɫ��������Ч��Χ��Ϊ 0~255 �� 0 Ϊ��� 255 Ϊ������
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void backColor( int red, int green, int blue ) = 0;
    
	/*! \brief ����������ʾλ��
	 *
	 *  ������������Ļ�ϣ�ȫ����ʽ�£��򴰿��У����ڷ�ʽ�£�����ʾλ�á�
	 *
	 *  \param x[in] ����λ�õ� x ����
	 *
	 *  \param y[in] ����λ�õ� y ����
	 *	
	 *  \remarks ����Ӧλ����Ļ�ڣ�ȫ����ʽ�£��򴰿��У����ڷ�ʽ�£���������޷���ʾ��
	 */
	virtual void setTextPos( int x, int y ) = 0;

	/*! \brief �����ַ����
	 *
	 *  ���������ַ�֮��ľ���
	 *
	 *  \param space[in] �����ַ�֮��ľ��룬������Ϊ��λ
	 *
	 *  \remarks һ�㲻�����ô˼��ֵ��ȱʡ��ֵ��������󲿷���Ҫ��
	 *
	 *  \return ����ԭ�����ַ����ֵ��
	 */
	virtual int setCharSpace( int space ) = 0;

	/*! \brief ��������
	 *
	 *  ע�⣺���ɹ��ڵ�Ƶ�����ô˺���������������ڴ���Ƭ���³������б�����
	 *
	 *  \param FontName[in] ָ������
	 *
	 *  \param Height[in] ָ������߶�
	 *
	 *  \param Width[in] ָ��������
	 *
	 *  \param Weight[in] ָ�����������(FW_BOLD=700)
	 *
	 *  \param Escapement[in] ָ���Ƕ�(1/10��)
	 *
	 *  \param Italic[in] ָ���Ƿ�б��
	 *
	 *  \param Underline[in] ָ���Ƿ����»���
	 *
	 *  \param StrikeOut[in] ָ���Ƿ���StrikeOut����
	 *
	 *  \param Quality[in] ָ���������
	 *
	 *  \remarks ȱʡ��Ϊ���壬12���֡�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setFont( const char *FontName, int Height, int Width, int Weight, int Escapement, bool Italic, bool Underline, bool StrikeOut, int Quality ) = 0;

};