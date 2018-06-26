/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   water.h
 *  ����:   ˮ����
 *
 ****************************************************************************/


/*! \file water.h
 * ˮ����.
 * ���ļ���ˮ����ͷ�ļ�.
 */


// ˮ����
#define LIGHT_WATER_RECTANGLE       0    // ˮ����


/** ˮ�������� */
class LightWaterDesc
{
public:

	/** ˮ���� */
	int    type;

	/** ˮ�ĳ�ʼλ�� */
	vec3_t pos;

	/** ˮ��ķ�����ͼ */
	LightTexture * normal;

	/** GLSL ���� shader �ļ��� */
	char vertex[64];

	/** GLSL Ƭ�� shader �ļ��� */
	char fragment[64];

	/** ˮ���γ��Ϳ� */
	struct { float width;
		     float height; } rectangle;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */
	LIGHT_INLINE LightWaterDesc()
	{
		memset( this, 0, sizeof(LightWaterDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */
	LIGHT_INLINE void setToDefault()
	{
		type = LIGHT_WATER_RECTANGLE;
		VEC3( pos, 0.0f, 0.0f, 0.0f );
		normal = NULL;
		strcpy( vertex, "" );
		strcpy( fragment, "" );
		rectangle.width = 64;
		rectangle.height = 64;
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightWater
 *  \brief ˮ��
 *
 *  ���ฺ��ˮ�Ĺ��������¡���ʾ������ʵ�ַǳ������ˮ��Ч����֧��ˮ��ķ��䡢���䡢��͹��ͼ�������ع��պ�����Ч����
 *  ÿ�� LightWater ʵ��������ͨ�� LightEngine ��� createWater �������䣬 releaseWater �ͷš�
 */

class LightWater
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

    #define LIGHT_REFLECTION_MAP  1  // ����ͼ
	#define LIGHT_REFRACTION_MAP  2  // ����ͼ

	/*! \brief ��ʼ��Ⱦˮ�淴�䣨���䣩ͼ
	 *	 
	 *  \param map[in] ָ��Ҫ��Ⱦ����ͼ��������ͼ
	 *	 
	 *  \see 
	 */
	virtual void begin( int map ) = 0;

	/*! \brief ֹͣ��Ⱦˮ�淴�䣨���䣩ͼ
	 *	 
	 *  \see 
	 */
	virtual void end( void ) = 0;

	/*! \brief ��Ⱦˮ
	 *
	 *  \see 
	 */
	virtual void render ( void ) = 0;

};