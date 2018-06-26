/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   image.h
 *  ����:   ͼ����
 *
 ****************************************************************************/


/*! \file image.h
 * ͼ����.
 * ���ļ���ͼ����ͷ�ļ�.
 */


class LightImage;


/* ͼ����ʾ��Ч��־ */
#define LIGHT_IMAGE_SOURRECT    0x00000001
#define LIGHT_IMAGE_DESTRECT    0x00000002
#define LIGHT_IMAGE_ROTATE      0x00000004
#define LIGHT_IMAGE_BLEND       0x00000008
#define LIGHT_IMAGE_LIGHTENESS  0x00000010
#define LIGHT_IMAGE_REVERSALX   0x00000020
#define LIGHT_IMAGE_REVERSALY   0x00000040

#ifdef LIGHT_CORPORATION_EDITION

#define LIGHT_IMAGE_MASK        0x00000080
#define LIGHT_IMAGE_MASKRECT    0x00000100
#define LIGHT_IMAGE_SECTOR      0x00000200
#define LIGHT_IMAGE_LAYER       0x00000400

#endif

/** ͼ����Ⱦ�������� */
class LightImageRenderDesc
{
public:

	/** ��־       */
	DWORD flags;

	/** ��Ⱦ��     */
	short layer;

	/** Դ����     */
	RECT  sour_rect;

	/** Ŀ������   */
	RECT  dest_rect;

	/** ͼ������ */
	struct
	{
		/** ����ͼ�� */
		LightImage * image;

		/** ��������   */
		RECT  rect;

	} mask;

	/** ������Ӱ */
	struct
	{
		/** ���νǶ� */
		float angle;

		/** ��Ӱ��ɫ */
		int shadow_color[3];

	} sector;

	/** ��ת�Ƕ�   */
	float rotate;

	/** ͸����     */
	float blend;

	/** ����       */
	float lighteness;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightImageRenderDesc()
	{
		memset( this, 0, sizeof(LightImageRenderDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */
	LIGHT_INLINE void setToDefault()
	{
		flags = 0;
		layer = 0;
		sour_rect.left = 0;
		sour_rect.top = 0;
		sour_rect.right = 128;
		sour_rect.bottom = 128;
		dest_rect.left = 0;
		dest_rect.top = 0;
		dest_rect.right = 128;
		dest_rect.bottom = 128;
		mask.image = NULL;
		mask.rect.left = 0;
		mask.rect.top = 0;
		mask.rect.right = 128;
		mask.rect.bottom = 128;
		rotate = 0.0f;
		blend = 1.0f;
		lighteness = 1.0f;
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


class LightEngine;


/** ͼ���������� */
class LightImageDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */
	LIGHT_INLINE LightImageDesc()
	{
		memset( this, 0, sizeof(LightImageDesc) );
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


/*! \class LightImage
 * \brief ͼ����
 *
 *  ���ฺ��ͼ���ļ��Ķ�ȡ����ʾ��֧����Ⱦ��ͼ��
 *  ֧�� 25 ��ͼ���ļ� .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal, .pbm, .pcd, .pcx, .pgm,
 *  .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga, .tif �� .hdr �Ķ�ȡ��֧�� 15 ��ͼ���ļ� .bmp, .dds, .h, .jpg,
 *  .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga �� .tif �ı��档
 *  ÿ�� LightImage ʵ��������ͨ�� LightEngine ��� createImage �������䣬 releaseImage �ͷš�
 */

class LightImage
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ��ͼ���ļ������ڴ�
	 *	 
	 *  \param filename[in] ͼ���ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int load ( const char *filename ) = 0;

	/*! \brief ���ڴ��д���ͼ��
	 *	 
	 *  \param width[in] ͼ����
	 *
	 *  \param height[in] ͼ��߶�
	 *
	 *  \param rgba[in] ͼ����ɫ����ָ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int build( int width, int height, unsigned char *rgba ) = 0;
    
	/*! \brief ������ͼ��
	 *	 
	 *  \param width[in] ͼ����
	 *
	 *  \param height[in] ͼ��߶�
	 *
	 *  \param type[in] ͼ������
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int create( int width, int height, int type ) = 0;

	/*! \brief ��ѯͼ���Ƿ���Ч
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual bool isValid( void ) = 0;

	/*! \brief ���ö��������ٶ�
	 *	 
	 *  \param speed[in] �������ŵ��ٶȣ���ÿ֡������ʱ���ʾ����ǧ��֮һ��Ϊ��λ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int speed( int speed ) = 0;

	/*! \brief ��ָ��λ����ʾͼ��
	 *	 
	 *  \param x ͼ�����Ͻ�����Ļ�� x ����
	 *
	 *  \param y ͼ�����Ͻ�����Ļ�� y ����
	 *	 
	 *  \see 
	 */
	virtual void render( int x, int y ) = 0;

	/*! \brief ��ָ��λ����ʾͼ����Ч
	 *	 
	 *  \param x ͼ�����Ͻ�����Ļ�� x ����
	 *
	 *  \param y ͼ�����Ͻ�����Ļ�� y ����
	 *	 
	 *  \param desc ͼ����ʾ��Ч������������ṹ��ͷ�ļ��Ķ��塣
	 *		 
	 *  \see 
	 */
	virtual void renderDesc( int x, int y, LightImageRenderDesc & desc ) = 0;

	/*! \brief ����ͼ��֡
	 *
	 *  �²����ͼ��֡������Ϊ��ǰͼ��֡��
	 *
	 *  \param position[in] ����λ�á�
	 *
	 *  \param order[in] �������0 = ǰ�棬1 = ���档
	 *
	 *  \return ����������óɹ���������ͼ��֡λ�ã����򣬷��� -1��
	 *
	 *  \see 
	 */
	virtual int insertFrame( int position, int order = 0 ) = 0;

	/*! \brief ɾ��ͼ��֡
	 *
	 *  ���ɾ����ǰ֡��Ч����ǰ֡������Ϊ 0��
	 *
	 *  \param frame[in] ��ǰͼ��֡��
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ط���ֵ��
	 *
	 *  \see 
	 */
	virtual int deleteFrame( int frame ) = 0;

	/*! \brief ѡ��ǰͼ��֡
	 *
	 *  ָ����ǰҪ��Ⱦ�Ͳ�����֡���ڵ��� load �� save ǰ����ָ��Ҫ��ȡ�ͱ����Ŀ��֡��ֻ��֡����ͼ����Ч����
	 *
	 *  \param int frame ��ǰͼ��֡��
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ط���ֵ��
	 *
	 *  \see 
	 */
	virtual int selectFrame( int frame ) = 0;

	/*! \brief ��ѯͼ��Ŀ�Ⱥ͸߶�
	 *	 
	 *  \param size[out] ����ͼ���С
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int getSize ( SIZE & size ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \brief ��Ⱦ��ͼ��
	 *	 
	 *  \param texture[in] ��ȾĿ�꣨TRUE = ��Ⱦ��ͼ��FALSE = ��Ⱦ�����ڣ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int renderToTexture( bool texture ) = 0;

	/*! \brief ��ͼ����ɫ���ݱ��浽ָ����ͼ���ļ��С�
	 *
	 *  ��ͼ����ɫ���ݱ��浽ָ����ͼ���ļ��С�����Ƕ���ͼ���򱣴�֡��
	 *  ֧�� 15 ��ͼ���ļ� .bmp, .dds, .h, .jpg, .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga �� .tif �ı���
	 *
	 *  \param filename[in]  Ҫ������ɫ���ݵ�ͼ���ļ���
	 *	 
	 *  \param format[in]  ͼ���ļ��ĸ�ʽ������� LIGHT_AUTO ������ļ���չ��ȷ����
	 *	 
	 *  \param color[in]  ͼ���ļ�����ɫģʽ
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int save( const char *filename, int format, int color ) = 0;

#endif

	/*! \brief ���ڴ����ͷ�ͼ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int unload ( void ) = 0;

};