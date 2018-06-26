/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   lighting.h
 *  ����:   �ƹ⺯��
 *
 ****************************************************************************/


/*! \file lighting.h
 * �ƹ⺯��.
 * ���ļ��ǵƹ⺯��ͷ�ļ�.
 */

class LightEngine;


/* �ƹ����� */
#define LIGHT_POINT_LIGHTING          0   /* ���Դ     */
#define LIGHT_ORIENTATION_LIGHTING    1   /* �����     */
#define LIGHT_SPOTLIGHT_LIGHTING      2   /* �۹��     */

/* �ƹ����ɫ */
#define LIGHT_AMBIENT    1259   /* ������     */
#define LIGHT_DIFFUSE    1260   /* ������     */
#define LIGHT_SPECULAR   1261   /* ���淴��� */

/* �ƹ��˥������ */
#define LIGHT_CONSTANT   1262   /* �㶨˥������ */
#define LIGHT_LINEAR     1263   /* ����˥������ */
#define LIGHT_QUADRATIC  1264   /* ����˥������ */

/** �ƹ������� */
typedef struct
{
	/** �ƹ����� */
	int    type;

	/** �ƹ�λ�� */
	float  position[4];

	/** ��������ɫ */
	float  ambient[4];

	/** ���������ɫ */
	float  diffuse[4];

	/** �߹���ɫ */
	float  specular[4];

	/** ����˥������ */
	float  constant;

	/** ����˥������ */
	float  linear;

	/** ����˥������ */
	float  quadratic;

	/** �۹�Ʋ��� */
	struct
	{
		/** �ƹ�ۼ�Ŀ��λ�� */
		vec3_t target;

		/** �۹�ָ�� */
		float  exponent;

		/** �۹�Ƕ� */
		float angle;

	} spotlight;

	/** ���������ƹ� */
	bool   enable;

} LightLightDesc;


/*! \brief �ƹ���
 *
 *  ���ฺ��̬�ƹ�Ĺ���
 *  ÿ�� LightLight ʵ��������ͨ�� LightEngine ��� createLight �������䣬����ʵ����ͬʱ��Ҳ�ʹ�����һ����̬�ƹ⡣ 
 */

class LightLight
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���õƹ��λ��
	 *	 
	 *  \param x[in] �ƹ�λ�õ� x ����
	 *
	 *  \param y[in] �ƹ�λ�õ� y ����
	 *
	 *  \param z[in] �ƹ�λ�õ� z ����
	 *
	 *  \param w[in] �ƹ�λ�õ� w ����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int setPosition( float x, float y, float z, float w ) = 0;

	/*! \brief ���õƹ����ɫֵ
	 *	 
	 *  \param name[in]  Ҫ���õĵƹ���ɫ������ѡ�����������һ��ֵ��
	 *                   \li LIGHT_AMBIENT   ������
	 *                   \li LIGHT_DIFFUSE   ������
	 *                   \li LIGHT_SPECULAR  ���淴���
	 *
	 *  \param red[in] �ƹ���ɫ�ĺ�ɫ�ɷ�
	 *
	 *  \param green[in] �ƹ���ɫ����ɫ�ɷ�
	 *
	 *  \param blue[in] �ƹ���ɫ����ɫ�ɷ�
	 *
	 *  \param alpha[in] �ƹ���ɫ�� Alpha ɫ�ɷ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int setColor( int name, float red, float green, float blue, float alpha ) = 0;

	/*! \brief ���õƹ�ľ۹����
	 *	 
	 *  \param x[in]  �۹ⷽ��� x ����
	 *
	 *  \param y[in] �۹ⷽ��� y ����
	 *
	 *  \param z[in] �۹ⷽ��� z ����
	 *
	 *  \param exponent[in] �ƹ�ľ۹�ָ��
	 *
	 *  \param angle[in] �ƹ�ľ۹�Ƕ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int setSpotlight( float x, float y, float z, float exponent, float angle ) = 0;

	/*! \brief ���õƹ��˥������
	 *	 
	 *  \param name[in] Ҫ���õ�˥�����ӡ�����ѡ�����������һ��ֵ��
	 *                  \li LIGHT_CONSTANT   �㶨˥������
	 *                  \li LIGHT_LINEAR     ����˥������
	 *                  \li LIGHT_QUADRATIC  ����˥������
	 *
	 *  \param attenuation[in] ˥�����ӵ�ֵ
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int setAttenuation( int name, float attenuation ) = 0;

	/*! \brief �򿪵ƹ�
	 *	 
	 *  \see 
	 */
	virtual void enable() = 0;

	/*! \brief �رյƹ�
	 *	 
	 *  \see 
	 */
	virtual void disable() = 0;

};