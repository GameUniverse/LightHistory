/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   sky.h
 *  ����:   ��պ���
 *
 ****************************************************************************/


/*! \file sky.h
 * ��պ���.
 * ���ļ�����պ���ͷ�ļ�.
 */


class LightEngine;


// �������
#define LIGHT_SKY_BOX       0    // ��պ�
#define LIGHT_SKY_DOME      1    // ��ն�
#define LIGHT_SKY_PLANE     2    // �����


/** ����������� */
class LightSkyDesc
{
public:

	/** ������� */
	int    type;

#ifdef LIGHT_CORPORATION_EDITION

	/** �����ת�ٶȣ��Զ�/��Ϊ��λ�� */
	float  rotate_velocity;

	/** �����ת�ᣬͨ��һ��������ָ�� */
	vec3_t rotate_axis;

	/** �Ʋ�д�С */
	vec3_t cloud_size;

	/** �Ʋ��ƶ��ٶ� */
	vec3_t cloud_velocity;

	/** �Ʋ��������ű��� */
	float  cloud_scale;

#endif

	/** ��պж���������ն��������Ҳ�õ��Ǵ����� */
	LightTexture * top;

	/** ��պ�ǰ������ */
	LightTexture * front;

	/** ��պк������� */
	LightTexture * back;

	/** ��պ��������� */
	LightTexture * left;

	/** ��պ��������� */
	LightTexture * right;

	/** ��պе������� */
	LightTexture * bottom;

#ifdef LIGHT_CORPORATION_EDITION

	/** ��պ��Ʋ����� */
	LightTexture * cloud;

#endif

	/** ��պг������� */
	struct { vec3_t size;   } box;

	struct { float  radius;
	         float  dtheta;
			 float  dphi;
			 float  hTile;
			 float  vTile;  } dome;   // ����İ뾶

	struct { float  radius;
			 int    divisions;
			 float  PlanetRadius;
			 float  AtmosphereRadius;
			 float  hTile;
			 float  vTile;  } plane; // Բ����İ뾶�͸�

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightSkyDesc()
	{
		memset( this, 0, sizeof(LightSkyDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */
	LIGHT_INLINE void setToDefault()
	{
		type = LIGHT_SKY_BOX;

#ifdef LIGHT_CORPORATION_EDITION

		rotate_velocity = 0.0f;
		VEC3( rotate_axis, 0.0f, 0.0f, 1.0f );
		VEC3( cloud_size, 64.0f, 64.0f, 64.0f );
		VEC3( cloud_velocity, 0.0f, 0.0f, 0.0f );
		cloud_scale = 1.0f;
		cloud = NULL;

#endif

		top = NULL;
		front = NULL;
		back = NULL;
		left = NULL;
		right = NULL;
		bottom = NULL;

		VEC3( box.size, 64.0f, 64.0f, 64.0f );

	/*struct { float  radius;
	         float  dtheta;
			 float  dphi;
			 float  hTile;
			 float  vTile;  } dome;   // ����İ뾶

	struct { float  radius;
			 int    divisions;
			 float  PlanetRadius;
			 float  AtmosphereRadius;
			 float  hTile;
			 float  vTile;  } plane; // Բ����İ뾶�͸�*/

		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightSky
 *  \brief ����� 
 *
 *  ���ฺ����յĹ�������ʾ��֧����պС���ն���������������͵���ա�
 *  ÿ�� LightSky ʵ��������ͨ�� LightEngine ��� createSky �������䣬 releaseSky �ͷš�
 */

class LightSky
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ��������ָ��
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ��Ⱦ���
	 *		 
	 *  \see 
	 */
	virtual void render ( void ) = 0;

};