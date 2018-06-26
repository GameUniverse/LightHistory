/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   texture.h
 *  ����:   �������������ܶ�ȡ 25 �� .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal, .pbm, .pcd, .pcx, .pgm, .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga �� .tif .hdr �ļ���
            ֧�ֱ���ĸ�ʽ�� 15 �֣� .bmp, .dds, .h, .jpg, .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga �� .tif. 

 *
 ****************************************************************************/


/*! \file texture.h
 * ������.
 * ���ļ���������ͷ�ļ�.
 */

// ָ������ԭ��
#define LIGHT_ORIGIN_UPPER_LEFT  0
#define LIGHT_ORIGIN_LOWER_LEFT  1

// ����ͨ��
#define LIGHT_TEXTURE_CHANNEL_2D   0
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_X   3
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_X   4
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Y   5
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Y   6
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_POSITIVE_Z   7
#define LIGHT_TEXTURE_CHANNEL_CUBE_MAP_NEGATIVE_Z   8

// �����
#define LIGHT_TEXTURE_LAYER_0   0
#define LIGHT_TEXTURE_LAYER_1   1
#define LIGHT_TEXTURE_LAYER_2   2
#define LIGHT_TEXTURE_LAYER_3   3
#define LIGHT_TEXTURE_LAYER_4   4
#define LIGHT_TEXTURE_LAYER_5   5
#define LIGHT_TEXTURE_LAYER_6   6
#define LIGHT_TEXTURE_LAYER_7   7

// ͼ���ļ���ʽ
#define LIGHT_AUTO         0x0000
#define LIGHT_BMP          0x0420
#define LIGHT_CUT          0x0421
#define LIGHT_DOOM         0x0422
#define LIGHT_DOOM_FLAT    0x0423
#define LIGHT_ICO          0x0424
#define LIGHT_JPG          0x0425
#define LIGHT_JFIF         0x0425
#define LIGHT_LBM          0x0426
#define LIGHT_PCD          0x0427
#define LIGHT_PCX          0x0428
#define LIGHT_PIC          0x0429
#define LIGHT_PNG          0x042A
#define LIGHT_PNM          0x042B
#define LIGHT_SGI          0x042C
#define LIGHT_TGA          0x042D
#define LIGHT_TIF          0x042E
#define LIGHT_CHEAD        0x042F
#define LIGHT_RAW          0x0430
#define LIGHT_MDL          0x0431
#define LIGHT_WAL          0x0432
#define LIGHT_LIF          0x0434
#define LIGHT_MNG          0x0435
#define LIGHT_JNG          0x0435
#define LIGHT_GIF          0x0436
#define LIGHT_DDS          0x0437
#define LIGHT_DCX          0x0438
#define LIGHT_PSD          0x0439
#define LIGHT_EXIF         0x043A
#define LIGHT_PSP          0x043B
#define LIGHT_PIX          0x043C
#define LIGHT_PXR          0x043D
#define LIGHT_XPM          0x043E
#define LIGHT_HDR          0x043F

#define LIGHT_JASC_PAL     0x0475


class LightEngine;


/** ������������ */
class LightTextureDesc
{
public:

	/** �������� */
	char name[17];

	/** �����ļ����� */
	char file[33];

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightTextureDesc()
	{
		memset( this, 0, sizeof(LightTextureDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "" );
		strcpy( file, "" );
		VEC3( position, 0, 0, 0 );		
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightTexture
 * \brief ������
 *
 *  ���ฺ������Ķ�ȡ�������͹���֧�� 25 ��ͼ���ļ� .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal,
 *  .pbm, .pcd, .pcx, .pgm, .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga, .tif �� .hdr �Ķ�ȡ��֧�� 15 ��ͼ���ļ� .bmp,
 *  .dds, .h, .jpg, .pal, .pbm, .pcx, .hdr, .pgm,.png, .ppm, .raw, .sgi, .tga �� .tif �ı��档ÿ�� LightTexture ʵ������
 *  ��ͨ�� LightEngine ��� createTexture �������䣬 releaseTexture �ͷš�
 */

class LightTexture
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ��������ԭ��
	 *
	 *  ����ȡ����ʱʹ�á�
	 *
	 *  \param mode[in] ԭ��λ��
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void setOrigin( int mode ) = 0;

	/*! \brief ��ѯ����ԭ��
	 *	
	 *  \return ��������ԭ��
	 *
	 *  \see 
	 */
	virtual int getOrigin( void ) = 0;

	/*! \brief ���� 2 ���ݴ�С����
	 *	 
	 *  \param power2[in] TRUE = 2 ���ݴ�С��FALSE = �� 2 ���ݴ�С
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int power2( bool power2 ) = 0;

	/*! \brief ���õ�ǰ����ͨ��������ȡ����ʱʹ��
	 *	 
	 *  \param channel[in] ��ǰ����ͨ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int channel( int channel ) = 0;

	/*! \brief ���õ�ǰ����㣬����������ʱʹ��
	 *	 
	 *  \param layer[in] ��ǰ�����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int layer( int layer ) = 0;

	/*! \brief ������������
	 *
	 *  ȱʡ��������Ϊ�ա�����������Ϊ��ʱ������ load �������������ƻ�ı�Ϊ�����ļ����������������Ʋ���ı䡣
	 *
	 *  \param name[in] �������ƣ�����������ʱ��ֻȡǰ 16 ���ַ����ֽڣ���
	 *	 
	 *  \see 
	 */
	virtual void setName( const char * name ) = 0;

	/*! \brief ��ѯ��������
	 *
	 *  ��������һ��Ϊ�����ļ�����ȱʡ��������Ϊ�ա�
	 *
	 *  \param name[out] �����������ƣ�����������С�� 17 �ֽڣ�16 ���ַ����ֽڣ���'\0'����
	 *	
	 *  \see 
	 */
	virtual void getName( char * name ) = 0;

	/*! \brief �������ļ������ڴ�
	 *
	 *  �������ļ������ڴ棬�����ܶ�ȡ 25 �� .bmp, .cut, .dds, .doom, .gif, .ico, .jpg, .lbm, .mdl, .mng, .pal, .pbm, .pcd, .pcx, .pgm, .pic, .png, .ppm, .psd, .psp, .raw, .sgi, .tga �� .tif .hdr �ļ���
	 *
	 *  \param filename[in] �ļ�������
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int load( const char *filename ) = 0;

	/*! \brief ���ڴ��д�������
	 *	 
	 *  \param width[in] ������
	 *
	 *  \param height[in] ����߶�
	 *
	 *  \param rgba[in] �������ݣ�RGBA��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int build( int width, int height, unsigned char *rgba ) = 0;

	/*! \brief ����������
	 *	 
	 *  \param width[in] ������
	 *
	 *  \param height[in] ����߶�
	 *
	 *  \param type[in] �������ͣ� 0 = ��ͨ���� 1 = ����Ⱦ����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int create( int width, int height, int type ) = 0;

	/*! \brief ����դ�񶯻�
	 *
	 *  ����������Ļ���������դ�񶯻���
	 *
	 *  \param width[in] դ�񶯻��Ŀ��
	 *
	 *  \param height[in] դ�񶯻��ĸ߶�
	 *
	 *  \param numframe[in] ����֡��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int grid( int width, int height, int numframe ) = 0;

	/*! \brief ��ѯ����ԭʼ�Ŀ�Ⱥ͸߶�
	 *	 
	 *  \param size[in] ���������С
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int getSize( SIZE & size ) = 0;

	/*! \brief ��ѯ����ʵ�ʣ������ݣ��Ŀ�Ⱥ͸߶�
	 *	
	 *  \param size ��������ʵ�ʣ������ݣ��Ĵ�С
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int getSizePower2( SIZE & size ) = 0;

	/*! \brief ��ѯ�����Ƿ���Ч
	 *
	 *  \return ���������Ч������ TRUE�����򷵻� FALSE ��
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

	/*! \brief ��������Ϊ��ǰ����
	 *
	 *  ��������Ϊ��ǰ��������Ƕ����������Զ����Ŷ�����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int active( void ) = 0;

	/*! \brief ��������֡
	 *
	 *  �²��������֡������Ϊ��ǰ����֡��
	 *
	 *  \param position[in] ����λ�á�
	 *
	 *  \param order[in] �������0 = ǰ�棬1 = ���档
	 *
	 *  \return ����������óɹ�������������֡λ�ã����򣬷��� -1��
	 *
	 *  \see 
	 */
	virtual int insertFrame( int position, int order = 0 ) = 0;

	/*! \brief ɾ������֡
	 *
	 *  ���ɾ����ǰ֡��Ч����ǰ֡������Ϊ 0��
	 *
	 *  \param frame[in] ��ǰ����֡��
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ط���ֵ��
	 *
	 *  \see 
	 */
	virtual int deleteFrame( int frame ) = 0;

	/*! \brief ѡ��ǰ����֡
	 *
	 *  ָ����ǰҪ��Ⱦ�Ͳ�����֡���ڵ��� load �� save ǰ����ָ��Ҫ��ȡ�ͱ����Ŀ��֡��ֻ��֡����������Ч����
	 *
	 *  \param frame[in] ��ǰ����֡��
	 *
	 *  \return ����������óɹ��������㣻�����������ʧ�ܣ����ط���ֵ��
	 *
	 *  \see 
	 */
	virtual int selectFrame( int frame ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \brief ��Ⱦ������
	 *	 
	 *  \param texture[in] ��ȾĿ�꣨TRUE = ��Ⱦ������FALSE = ��Ⱦ�����ڣ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int renderToTexture( bool texture ) = 0;

	/*! \brief ��������ɫ���ݱ��浽ָ����ͼ���ļ��С�
	 *
	 *  ��������ɫ���ݱ��浽ָ����ͼ���ļ��С�����Ƕ��������򱣴�֡��
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

	/*! \brief ���ڴ����ͷ�����
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int unload( void ) = 0;

};