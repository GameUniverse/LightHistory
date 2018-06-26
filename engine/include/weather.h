/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   weather.h
 *  ����:   ��������
 *
 ****************************************************************************/


/*! \file weather.h
 * ��������.
 * ���ļ�����������ͷ�ļ�.
 */


class LightEngine;


// ��������
#define LIGHT_WEATHER_RAIN            0    // ��
#define LIGHT_WEATHER_SNOW            1    // ѩ
#define LIGHT_WEATHER_LIGHTNING       2    // ����


// ����������
typedef struct
{
	int    type;                 // ��������
	int    numparticle;          // ������
	vec3_t box;                  // �����г�������
	vec3_t position;             // ������λ�ã�������������
	float  drop_velocity_min;    // ����������С�ٶ�
	float  drop_velocity_max;    // ������������ٶ�
	vec3_t wind;                 // ����
	
	//LightTexture * top;      // ��պж���������ն��������Ҳ�õ��Ǵ�����
	//LightTexture * front;    // ��պ�ǰ������	
	//LightTexture * cloud;    // ��պ��Ʋ�����

} LightWeatherDesc;


/*! \brief ������ 
 *
 *  ���ฺ�������Ĺ�������ʾ��֧���ꡢѩ�������������͵�������
 *  ÿ�� LightWeather ʵ��������ͨ�� LightEngine ��� createWeather �������䡣 
 */

class LightWeather
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ��������ָ��
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ��Ⱦ����
	 *		 
	 *  \see 
	 */
	virtual void render() = 0;

};