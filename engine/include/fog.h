/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   fog.h
 *  ����:   ����
 *
 ****************************************************************************/


/*! \file fog.h
 * ����.
 * ���ļ�������ͷ�ļ�.
 */


class LightEngine;


// ������
/*#define LIGHT_SKY_BOX       0    // ��պ�
#define LIGHT_SKY_DOME      1    // ��ն�
#define LIGHT_SKY_PLANE     2    // �����*/


/** �������� */
typedef struct
{
	/** ������ */
	int    type;

	/** ����ɫ */
	float  color[4];

	/** ���ܶ� */
	float  density;

	/** ��ʼ��λ�� */
	float  start;

	/** �������λ�� */
	float  end;

	/** �����ʾƷ�� */
	int    quality;

	/** ���������� */
	bool   enable;

} LightFogDesc;


/*! \brief ����
 *
 *  ���ฺ����Ŀ������رպͲ������á�
 *  ÿ�� LightFog ʵ��������ͨ�� LightEngine ��� createFog �������䡣 
 */

class LightFog
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ��������ָ��
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���������ɫ
	 *	
	 *  \param red[in] ����ɫ�ĺ�ɫ����
     *	
	 *  \param green[in] ����ɫ����ɫ����
     *	
	 *  \param blue[in] ����ɫ����ɫ����
     *	
	 *  \param alpha[in] ����ɫ�� ALPHA ����
     *	
	 *  \see 
	 */
	virtual void color( float red, float green, float blue, float alpha ) = 0;

	/*! \brief ��������ܶ�
	 *	
	 *  \param density[in] ����ܶ�
     *
	 *  \see 
	 */
	virtual void density( float density ) = 0;

	/*! \brief ������ķ�Χ
	 *	
	 *  \param start[in] ����Ļ����ʼƽ��ľ���
     *
	 *  \param end[in] ����Ļ�������ƽ��ľ���
     *
	 *  \see 
	 */
	virtual void bound( float start, float end ) = 0;

	/*! \brief ���������ʾƷ��
	 *	
	 *  \param quality[in] �����ʾƷ��
     *
	 *  \see 
	 */
	virtual void quality( int quality ) = 0;

	/*! \brief ������
	 *		 
	 *  \see 
	 */
	virtual void enable() = 0;

	/*! \brief �ر���
	 *		 
	 *  \see 
	 */
	virtual void disable() = 0;

};