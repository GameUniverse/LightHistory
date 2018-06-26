/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   engine.h
 *  ����:   ������
 *
 ****************************************************************************/


/*! \file engine.h
 * ���溯��.
 * ���ļ������溯��ͷ�ļ�.
 */

/* �������� */
#define LIGHT_DEPTH_BUFFER_BIT               0x00000100
#define LIGHT_COLOR_BUFFER_BIT               0x00004000


/** ��Ⱦ���ݱ�־ */
enum LightRenderFlag
{
	/** ��ɫ��Ⱦ��־λ���� LIGHT_RENDER_TEXTURE λΪ 1 ʱ����λ�����ԣ� */
	LIGHT_RENDER_COLOR     = 0x00000001,

	/** ��Ⱦ�����־λ */
	LIGHT_RENDER_TEXTURE   = 0x00000002,

	/** ��Ⱦ������ͼ��־λ */
	LIGHT_RENDER_LIGHTMAP  = 0x00000004,

	/** ��Ⱦ�߿��־λ */
	LIGHT_RENDER_LINE      = 0x00000008,

	/** ��Ⱦ��Ӱ��־λ */
	LIGHT_RENDER_SHADOW    = 0x00000010,

	/** ��Ⱦѡ����־λ */
	LIGHT_RENDER_SELECT    = 0x00000020

};

/** ��������ö������ */
enum LightEnum
{
	/** OpenGL ͼ����Ⱦ�� */
	LIGHT_OPENGL_RENDER,

	/** D3D9 ͼ����Ⱦ�� */
	LIGHT_D3D9_RENDER,

	/** D3D10 ͼ����Ⱦ�� */
	LIGHT_D3D10_RENDER,

	/** ���ͼ����Ⱦ�� */
	LIGHT_SOFTWARE_RENDER,

	/** ������ʾģʽ */
	LIGHT_WINDOW_MODE,

	/** ȫ����ʾģʽ */
	LIGHT_FULLSCREEN_MODE,

	/** ��ȫ����ʾģʽ */
	LIGHT_HALFSCREEN_MODE,

	/** �󶨴�����ʾģʽ */
	LIGHT_ATTACH_MODE

};


/** ��ʾģʽ�������� */
class LightDisplaymodeDesc
{
public:

	/** ���ھ�� */
	HWND hwnd;

	/** ͼ����Ⱦ�� */
	LightEnum render;

	/** ��ʾģʽ */
	LightEnum mode;

	/** ����ģʽ���� */
	struct
	{ 
		/** �������Ͻ� x ���� */
		int x;

		/** �������Ͻ� y ���� */
		int y;

		/** ���ڿ�� */
		int width;

		/** ���ڸ߶� */
		int height;

	} window;

	/** ȫ��ģʽ���� */
	struct
	{ 
		/** ��Ļˮƽ�ֱ��� */
		int width;

		/** ��Ļ��ֱ�ֱ��� */
		int height;

		/** ��Ļ��ɫ��� */
		int color;

		/** ��Ļˢ���� */
		int refurbish;

	} fullscreen;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */
	LIGHT_INLINE LightDisplaymodeDesc()
	{
		memset( this, 0, sizeof(LightDisplaymodeDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		hwnd = NULL;
		render = LIGHT_OPENGL_RENDER;
		mode = LIGHT_WINDOW_MODE;
		window.x = 80;
		window.y = 60;
		window.width = 640;
		window.height = 480;
		fullscreen.width = 800;
		fullscreen.height = 600;
		fullscreen.color = 16;
		fullscreen.refurbish = 0;
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/** ���������������� */
class LightEngineDesc
{
public:

	/** ��ʾģʽ */
	LightDisplaymodeDesc displayMode;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightEngineDesc()
	{
		//memset( this, 0, sizeof(LightEngineDesc) );
		setToDefault();
	}

	/** ���ṹ���ó�ȱʡֵ */	
	LIGHT_INLINE void setToDefault()
	{
		userData = NULL;
	}

	/** �������������Ч�ķ��� TRUE */
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightEngine
 * \brief ������
 *
 *  ���ฺ��󲿷�ϵͳ���ܵĵ��ú������������ʵ�����䣬����������Ҫ��һ���ࡣ
 *  �����ʵ��ָ��ֻ��ͨ�����ú��� LightEngineCreate �õ���
 *  �ͷ�ʱ���ú��� LightEngineRelease���м������ʱ���� LightEngineGet �õ�
 *  ����ʵ��ȫ��ָ�롣
 *  \n
 *  \n �÷�ʾ����
 *  \n
 *  \n // ������������ʵ��
 *  \n LightEngine     *engine;
 *  \n LightEngineDesc  engineDesc;
 *  \n engineDesc.display_mode   = LIGHT_WINDOW_MODE;  // ������ʾģʽ
 *  \n engineDesc.window.x       = 200;                // �������Ͻ� x ����
 *  \n engineDesc.window.y       = 150;                // �������Ͻ� y ����
 *  \n engineDesc.window.width   = 640;                // ���ڿ��
 *  \n engineDesc.window.height  = 480;                // ���ڸ߶�
 *  \n engine = LightEngineCreate( engineDesc );
 *  \n 
 *  \n // ʹ������...
 *  \n 
 *  \n // �ͷŹ�������ʵ��
 *  \n LightEngineRelease( engine );
 */

class LightEngine
{

public:

	/*! \brief ��������״̬
	 *
	 *  ��������״̬�ĸ���
	 *	 
	 *  \see updateLight
	 */
	virtual void updatePhysics( void ) = 0;

	/*! \brief ���µƹ�����
	 *
	 *  ���ڵƹ�ĸ���
	 *
	 *  \see updatePhysics
	 */
	virtual void updateLight() = 0;

	/*! \brief ����ȾĿ��
	 *		 
	 *  \param[in] render ��ȾĿ�꣨��ֵ������׼���Ժ�ʹ�ã����ڱ�����Ϊ 0��
	 *	 
	 *  \see 
	 */
	virtual void attachRender( int render=0 ) = 0;

	/*! \brief ������ȾĿ��
	 *	 
	 *  \see 
	 */
	virtual void detachRender( void ) = 0;

	/*! \brief ���õ�ǰ��ɫֵ
	 *	
	 *  ����ɫֵӰ��������Ⱦ���ݣ��κ���Ⱦ�����ڵ����ɫֵ�������Ը�ֵ��
	 *
	 *  \param[in] red ��ɫ�ĺ�ɫ�ɷ֣�ȡֵ��Χ[0,1]����ͬ��
	 *  \param[in] green ��ɫ����ɫ�ɷ�
	 *  \param[in] blue ��ɫ����ɫ�ɷ�
	 *  \param[in] alpha ��ɫ�� Alpha �ɷ�
	 *	 
	 *  \see colorMask
	 */
	virtual void color( float red, float green, float blue, float alpha ) = 0;

	/*! \brief �������ֹ��д��"֡������"��ָ����ɫ�ɷ�
	 *	
	 *  �κ���Ⱦ�����ڵ����ɫֵ�����ܸ�ֵӰ�졣
	 *
	 *  \param[in] red ��ɫ�ĺ�ɫ�ɷ֣�ȡֵ��Χ[TRUE,FALSE]��TURE Ϊ����FALSE Ϊ��ֹ����ͬ��
	 *  \param[in] green ��ɫ����ɫ�ɷ�
	 *  \param[in] blue ��ɫ����ɫ�ɷ�
	 *  \param[in] alpha ��ɫ�� Alpha �ɷ�
	 *	 
	 *  \see color
	 */
	virtual void colorMask( bool red, bool green, bool blue, bool alpha ) = 0;

	/*! \brief ������������ɫֵ
	 *
	 *  ����������������ɫֵ
	 *
	 *  \param int red ��ɫ�ĺ�ɫ�ɷ�
	 *  \param int green ��ɫ����ɫ�ɷ�
	 *  \param int blue ��ɫ����ɫ�ɷ�
	 *  \param int alpha ��ɫ�� Alpha �ɷ�
	 *	 
	 *  \see clearDepth
	 */
	virtual void clearColor( int red, int green, int blue, int alpha ) = 0;

	/*! \brief �������������ֵ
	 *
	 *  �����������������ֵ
	 *
	 *  \param float depth ���������ֵ
	 *	 
	 *  \see clearColor
	 */
	virtual void clearDepth( float depth ) = 0;

	/*! \brief ���ָ������
	 *
	 *  �������ָ������
	 *
	 *  \param int mask Ҫ����Ļ���
	 *	 
	 *  \see clearColor, clearDepth
	 */
	virtual void clear( int mask ) = 0;


	// ѡ��

	/*! \brief ����ѡ��ģʽ������
	 *	 
	 *  \param size ��������С
	 *	 
	 *  \param buffer ����ѡ������
	 *	 
	 *  \see 
	 */
	virtual void selectBuffer( int size, unsigned int * buffer ) = 0;

	/*! \brief ����ʰȡ���β���
	 *	 
	 *  \param x ʰȡ��������λ��
	 *	 
	 *  \param y ����ͬ��
	 *	 
	 *  \param width ʰȡ���δ�С
	 *	 
	 *  \param height ����ͬ��
	 *	 
	 *  \see 
	 */
	virtual void pickRectangle( double x, double y, double width, double height ) = 0;

    #define LIGHT_RENDER  0
    #define LIGHT_SELECT  1

	/*! \brief ����������Ⱦģʽ
	 *	 
	 *  \param mode ������Ⱦģʽ��LIGHT_RENDER �� ������Ⱦ��LIGHT_SELECT �� ѡ��ģʽ��
	 *	 
	 *  \return �����ǰ��ȾģʽΪ LIGHT_SELECT��ʹ�ò��� LIGHT_RENDER ����ʱ������ѡ�е�ͼԪ�������򷵻� 0��
	 *
	 *  \see 
	 */
	virtual int renderMode( int mode ) = 0;

	/*! \brief ��ʼ�����ƶ�ջ
	 *	 
	 *  \see 
	 */
	virtual void initNames( void ) = 0;

	/*! \brief ѹ�����ƶ�ջ
	 *	 
	 *  \param name ��Ҫѹ�����ƶ�ջ������
	 *	 	 
	 *  \see 
	 */
	virtual void pushName( unsigned int name ) = 0;

	/*! \brief �������ƶ�ջ
	 *	 
	 *  \see 
	 */
	virtual void popName( void ) = 0;

	/*! \brief ��һ�����Ƽ��ص����ƶ�ջ
	 *	 
	 *  \param name ��Ҫ�滻���ƶ�ջ������һ������
	 *	 	 
	 *  \see 
	 */
	virtual void loadName( unsigned int name ) = 0;


	// ��Ⱦ����

	/*! \brief ����ָ������Ⱦ���ݱ�־
	 *	 
	 *  \param renderFlag[in] ��Ⱦ���ݱ�־
	 *		 
	 *  \see 
	 */
	virtual void raiseRenderFlag( LightRenderFlag renderFlag ) = 0;

	/*! \brief ���ָ������Ⱦ���ݱ�־
	 *	 
	 *  \param renderFlag[in] ��Ⱦ���ݱ�־
	 *		 
	 *  \see 
	 */
	virtual void clearRenderFlag( LightRenderFlag renderFlag ) = 0;

	/*! \brief ��ѯָ������Ⱦ���ݱ�־
	 *	 
	 *  \param renderFlag[in] ��Ⱦ���ݱ�־
	 *		 
	 *  \see 
	 */
	virtual bool readRenderFlag( LightRenderFlag renderFlag ) = 0;


	/*! \brief ������Ϸ������ʾ����
	 *
	 *  ������Ϸ������ʾ����
	 *
	 *  \param ��
	 *
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see clear, clearColor, clearDepth
	 */
	virtual bool swapBuffers( void ) = 0;

	/*! \brief ��ѯÿ������ʾ��֡��
	 *	 
	 *  \return ����ÿ������ʾ��֡��
	 *
	 *  \see swapBuffers
	 */
	virtual int getFramePerSecond( void ) = 0;

	/*! \brief �ı���ʾģʽ����
	 *	 
	 *  \param displaymodeDesc[in] ��ʾģʽ������������˵��Ҫ������ʾģʽ��������
	 *
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */
	virtual int changeDisplaySettings( LightDisplaymodeDesc & displaymodeDesc ) = 0;


    #define LIGHT_OPENGL_COORDINATE_SYSTEM  0  // ȱʡ����
    #define LIGHT_3DSMAX_COORDINATE_SYSTEM  1

	/*! \brief ������������ϵͳ
	 *	 
	 *  \param int system Ҫ���õ�����ϵͳ
	 *	 
	 *  \return ��������ԭ��������ϵͳ
	 *
	 *  \see 
	 */
	virtual int coordinateSystem( int system ) = 0;

	/*! \brief ���õ�ǰ��ͼģʽ��2D/3D��
	 *	 
	 *  \param bool Ortho2D ��ͼģʽ��TRUE = 2D��FALSE = 3D	 
	 */
	virtual void ortho2D( bool Ortho2D ) = 0;

	/*! \brief ���´���״̬
	 *	 
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */
	virtual int updateWindowState( void ) = 0;

	/*! \brief ���ùؼ�ɫ��͸��ɫ��
	 *	 
	 *  \param int red ��ɫ������0~255��
	 *
	 *  \param int green ��ɫ������0~255��
	 *
	 *  \param int blue ��ɫ������0~255��
	 *
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */
	virtual int setKeyColor( int red, int green, int blue ) = 0;

	// �������
	// Parameter                             // (f (R) ,f (G) ,f (B) ,f (A) ) 
    #define LIGHT_ZERO 0                     // (0,0,0,0)
    #define LIGHT_ONE  1                     // (1,1,1,1)
    #define LIGHT_SRC_COLOR 0x0300           // (RS/kR,GS/kG,BS/kB,AS/kA)
    #define LIGHT_ONE_MINUS_SRC_COLOR 0x0301 // (1,1,1,1) - (RS/kR,GS/kG,BS/kB,AS/kA)
    #define LIGHT_DST_COLOR 0x0306           // (Rd/kR,Gd/kG,Bd/kB,Ad/kA)
    #define LIGHT_ONE_MINUS_DST_COLOR 0x0307 // (1,1,1,1) 
    #define LIGHT_SRC_ALPHA 0x0302           // AS/kA,AS/kA,AS/kA,AS/kA 
    #define LIGHT_ONE_MINUS_SRC_ALPHA 0x0303 // (1,1,1,1) - (AS/kA,AS/kA,AS/kA,AS/kA) 
    #define LIGHT_DST_ALPHA 0x0304           // (AD/kA,AD/kA,AD/kA,AD/kA) 
    #define LIGHT_ONE_MINUS_DST_ALPHA 0x0305 // (1,1,1,1) - (AD/kA,AD/kA,AD/kA,AD/kA) 
    #define LIGHT_SRC_ALPHA_SATURATE 0x0308  // (i,i,i,1)

	/*! \brief ָ����ϵ������㷨
	 *
	 *  ָ����ϵ������㷨
	 *
	 *  \param sfactor Դ������ӣ�����ȡֵ LIGHT_ZERO, LIGHT_ONE, LIGHT_DST_COLOR, LIGHT_ONE_MINUS_DST_COLOR, LIGHT_SRC_ALPHA, LIGHT_ONE_MINUS_SRC_ALPHA, LIGHT_DST_ALPHA, LIGHT_ONE_MINUS_DST_ALPHA, �� LIGHT_SRC_ALPHA_SATURATE��
	 *
	 *  \param dfactor Ŀ�������ӣ�����ȡֵ LIGHT_ZERO, LIGHT_ONE, LIGHT_SRC_COLOR, LIGHT_ONE_MINUS_SRC_COLOR, LIGHT_SRC_ALPHA, LIGHT_ONE_MINUS_SRC_ALPHA, LIGHT_DST_ALPHA, �� LIGHT_ONE_MINUS_DST_ALPHA��
	 *	 
	 *  \see 
	 */
	virtual void blendFunc( int sfactor, int dfactor ) = 0;

	// ��Ⱦ�޳���
    #define LIGHT_FRONT             1
    #define LIGHT_BACK              2
    #define LIGHT_FRONT_AND_BACK    3

	/*! \brief ָ����ȾʱҪ�޳�����
	 *	 	 
	 *  \param mode ָ��Ҫ�޳����滹�Ǳ��棬����ȡֵ LIGHT_FRONT��LIGHT_BACK������ LIGHT_FRONT_AND_BACK Ҳ���Ͽɵģ�ȱʡֵ�� LIGHT_BACK��
	 *	 
	 *  \see 
	 */
	virtual void cullFace( int mode ) = 0;

	/*! \brief ��ѯ��Ƶ�豸������
	 *	 
	 *  \param int device Ҫ��ѯ����Ƶ�豸��ͨ�������ϵͳֻ��һ����Ƶ�豸�����ֵ��Ϊ 0
	 *	 
	 *  \return ������Ƶ�豸������ֵ�����֣�WORD���������������������֣�WORD����������
	 *          ��������������Χ�� 0x0000 �� 0xFFFF��0x0000 = ������0xFFFF = ���������
	 *
	 *  \see 
	 */	
	virtual DWORD getOutVolume( int device ) = 0;

	/*! \brief ������Ƶ�豸������
	 *	 
	 *  \param int device Ҫ���õ���Ƶ�豸��ͨ�������ϵͳֻ��һ����Ƶ�豸�����ֵ��Ϊ 0
	 *
	 *  \param int left ��������������������Χ�� 0x0000 �� 0xFFFF��0x0000 = ������0xFFFF = ���������
	 *
	 *  \param int blue ��������������������Χͬ�ϡ�
	 *
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */	
	virtual int setOutVolume( int device, int left, int right ) = 0;

	/*! \brief ת�����ڿͻ������꣨2D���������������꣨3D��
	 *
	 *  ��Ҫע����Ǵ˺�����ִ�н��ȡ������Ⱦͼ��Ҳ����˵������Ҫ��ѯ��Ŀ�������Ⱦ���������ô˺��������ܵõ���ȷ�Ľ����
	 *
	 *  \param x ���ڿͻ������꣨2D��x ����
	 *
	 *  \param y ���ڿͻ������꣨2D��y ����
	 *
	 *  \param point һ����������ָ�룬���ص��Ǹô��ڿͻ������꣨2D����Ӧ�ĳ����������꣨3D����x��y��z��
	 *	 
	 *  \see 
	 */	
	virtual void windowToWorld( int x, int y, vec3_t point ) = 0;

	/*! \brief ת�������������꣨3D�������ڿͻ������꣨2D��
	 *
	 *  ��Ҫע����Ǵ˺�����ִ�н��ȡ������Ⱦͼ��Ҳ����˵������Ҫ��ѯ��Ŀ�������Ⱦ���������ô˺��������ܵõ���ȷ�Ľ����
	 *
	 *  \param x �����������꣨3D��x ����
	 *
	 *  \param y �����������꣨3D��y ����
	 *
	 *  \param z �����������꣨3D��z ����
	 *
	 *  \param point һ����������ָ�룬���ص��Ǹó����������꣨3D����Ӧ�Ĵ��ڿͻ������꣨2D����x��y��z��
	 *	 
	 *  \see 
	 */	
	virtual void worldToWindow( float x, float y, float z, vec3_t point ) = 0;

	/*! \brief ������Ϣ
	 *
	 *  ������Ϣ
	 *
	 *  \param ��
	 *	 
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */
	virtual bool dispatchMessage( void ) = 0;

	/*! \brief ע�ᴰ����Ϣ��������
	 *
	 *  ע�ᴰ����Ϣ��������������ע������Ϣ������������Щ���������յ����ڷ�����������Ϣ��
	 *
	 *  \param WNDPROC lpfnWndProc ������Ϣ��������
	 *	 
	 *  \return ����ɹ����� TRUE, ���򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool registerMessageProc( WNDPROC lpfnWndProc ) = 0;

	/*! \brief �Ƴ�������Ϣ��������
	 *
	 *  �Ƴ�������Ϣ����������ֻ���Ƴ�ǰ����ע��Ĵ�����Ϣ����������
	 *
	 *  \param WNDPROC lpfnWndProc ������Ϣ��������
	 *	 
	 *  \return ����ɹ����� TRUE, ���򷵻� FALSE
	 *
	 *  \see 
	 */
	virtual bool removeMessageProc( WNDPROC lpfnWndProc ) = 0;


	// ���

	/*! \brief ��ȡ����ļ�
	 *
	 *  �������� .CUR �� .ANI  ��β�� windows ����ļ���
	 *
	 *  \param filename[in] ����ļ�����
	 *	 
	 *  \return �����ȡ�ɹ�������ֵ����ʾ��������ֵ�����򷵻ظ�ֵ��
	 *
	 *  \see destroyCursor��setCursor��showCursor
	 */
	virtual int loadCursor( const char * filename ) = 0;

	/*! \brief ���ٹ��
	 *
	 *  �˺����ͷ�ָ�����ռ�õ��κ��ڴ档
	 *
	 *  \param cursor[in] ����������� loadCursor �õ�
	 *	 
	 *  \return ����������óɹ����� TRUE, ���򷵻� FALSE
	 *
	 *  \see loadCursor��setCursor��showCursor
	 */
	virtual bool destroyCursor( int cursor ) = 0;

	/*! \brief ���õ�ǰ���
	 *	 
	 *  \param cursor[in] ����������� loadCursor �õ�
	 *	 
	 *  \return ������óɹ����� TRUE, ���򷵻� FALSE
	 *
	 *  \see loadCursor��destroyCursor��showCursor
	 */
	virtual bool setCursor( int cursor ) = 0;

	/*! \brief ��ʾ�������أ����
	 *	 
	 *  \param show[in] ָ����ʾ�������أ���꣬TRUE ��ʾ��꣬FALSE ���ع�ꡣ
	 *	 	 
	 *  \see loadCursor��destroyCursor��setCursor
	 */
	virtual void showCursor( bool show ) = 0;


	/*! \brief ��ѯϵͳ��������������ǧ��֮һ����
	 *
	 *  \return ����ϵͳ��������������ǧ��֮һ����
	 *
	 *  \see 
	 */
	virtual unsigned long getTickCount( void ) = 0;

	/*! \brief ����ȫ�ֻ��������ɫֵ
	 *	 
	 *  \param float red ��ɫ����
	 *
	 *  \param float green ��ɫ����
	 *
	 *  \param float blue ��ɫ����
	 *
	 *  \param float alpha Alpha ����
	 *
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */
	virtual int lightAmbient( float red, float green, float blue, float alpha ) = 0;

	/* ״̬���� */
	
	/*! \brief ��ѯ���ھ��
	 *
	 *  \return ���ش��ھ��
	 *
	 *  \see 
	 */
	virtual HWND getWindowHandle( void ) = 0;

    #define LIGHT_WINDOW_CAPTION       1
    #define LIGHT_WORK_DIRECTORY       2
    #define LIGHT_VIDEO_DIRECTORY      3
    #define LIGHT_MUSIC_DIRECTORY      4
    #define LIGHT_SOUND_DIRECTORY      5
    #define LIGHT_TEXTURE_DIRECTORY    6
    #define LIGHT_LEVEL_DIRECTORY      7
    #define LIGHT_MODEL_DIRECTORY      8
    #define LIGHT_IMAGE_DIRECTORY      9
    #define LIGHT_SCRIPT_DIRECTORY     10
	#define LIGHT_SKY_DIRECTORY        11
	#define LIGHT_PARTICLE_DIRECTORY   12

	/*! \brief ����ָ���ַ���
	 *	 
	 *  \param int name Ҫ���õ��ַ���
	 *  \param const char *string �ַ���ָ��
	 *
	 *  \return ����ɹ����� 0, ���򷵻ط� 0 ֵ
	 *
	 *  \see 
	 */
	virtual bool setString( int name, const char *string ) = 0;

	/*! \brief ��ѯָ���ַ���
	 *	 
	 *  \param int name Ҫ��ѯ���ַ���
	 *
	 *  \return ����ɹ�����һ���ַ���ָ�루���ַ����� 0 ��β���� ���򷵻� NULL ��
	 *
	 *  \see 
	 */
	virtual const char * getString( int name ) = 0;

	#define LIGHT_ENABLE         1    /* ����     */
	#define LIGHT_DISABLE        0    /* ��ֹ     */
	#define LIGHT_AUTOMATIC      2    /* �Զ�     */

    #define LIGHT_KEY_COLOR      12   /* �ؼ�ɫ   */
    #define LIGHT_BLEND          13   /* ���     */
    #define LIGHT_TEXTURE        14   /* ����     */
    #define LIGHT_SWAP_INTERVAL  15   /* ��ֱͬ�� */
    #define LIGHT_PROJECTION     16   /* ͶӰ���� */
    #define LIGHT_LIGHTING       17   /* ����     */
    #define LIGHT_LOCAL_VIEWER   18   /* �ֲ��ӵ� */
    #define LIGHT_TWO_SIDE       19   /* ˫����� */
    #define LIGHT_FOG            20   /* ��       */
    #define LIGHT_DEPTH_TEST     21   /* ��Ȳ��� */
    #define LIGHT_SAMPLES        22   /* ���ز��� */
    #define LIGHT_CUBE_MAP       23   /* ����ӳ�� */
    #define	LIGHT_CULL_FACE      24   /* �޳���   */

	/*! \brief ����ָ������
	 *	 
	 *  \param int name Ҫ����Ĺ���
	 *	 
	 *  \see 
	 */
	virtual void enable( int name ) = 0;

	/*! \brief ��ָֹ������
	 *	 
	 *  \param int name Ҫ��ֹ�Ĺ���
	 *	 
	 *  \see 
	 */
	virtual void disable( int name ) = 0;

	/*! \brief �Զ�ָ������
	 *
	 *  ���øú��������潫�������Ҫ�Զ��������ָֹ���Ĺ��ܡ�
	 *
	 *  \param int name Ҫ�Զ��Ĺ���
	 *	 
	 *  \see 
	 */
	virtual void automatic( int name ) = 0;

#define LIGHT_MAX_LIGHTS                 5
#define LIGHT_MAX_TEXTURE_SIZE           6
#define LIGHT_RENDERED_NUM_TRIANGLE      7
#define LIGHT_RENDERED_NUM_MESH          8
#define LIGHT_RENDERED_NUM_MODEL         9
#define LIGHT_RENDERED_NUM_LEAF          10

	/*! \brief ��ѯָ����������
	 *	 
	 *  \param int name Ҫ��ѯ��������
	 *	 
	 *  \return ����Ҫ��ѯ��������
	 *
	 *  \see 
	 */
	virtual int getInteger( int name ) = 0;

	/*! \brief �����ڲ�����
	 * 
	 *  ����������������ã�������ܻᵼ���ڴ����
	 *	 
	 *  \param name[in] ��������
	 *	 
	 *  \param ...[in] ��������
	 *	
	 *  \return ��������ֵ
	 *
	 *  \see 
	 */
	virtual int debugging( int num, ... ) = 0;


	// ��������

	/*! \fn LightLensFlare * NewLensFlare( void )
	 *  \brief ����һ����ͷ����
	 *
	 *  ����һ����ͷ����
	 *
	 *  \param ��
	 *	 
	 *  \return ����Ҫ�����ľ�ͷ������ָ��
	 *
	 *  \see 
	 */
	virtual LightLensFlare * NewLensFlare( void ) = 0;

	/*! \fn LightModelMD3 * NewModelMD3( void )
	 *  \brief ����һ�� MD3 ģ��
	 *
	 *  ����һ�� MD3 ģ��
	 *
	 *  \param ��
	 *	 
	 *  \return ����Ҫ������ MD3 ģ����ָ��
	 *
	 *  \see 
	 */
	virtual LightModelMD3 * NewModelMD3( void ) = 0;

	/*! \fn LightFrustum * NewFrustum( void )
	 *  \brief ����һ����׶��
	 *
	 *  ����һ����׶��
	 *
	 *  \param ��
	 *	 
	 *  \return ����Ҫ��������׶����ָ��
	 *
	 *  \see 
	 */
	virtual LightFrustum * NewFrustum( void ) = 0;

	/*! \fn LightCollide * NewCollide( void ) = 0
	 *  \brief ����һ����ײ������
	 *
	 *  ����һ����ײ������
	 *
	 *  \param ��
	 *	 
	 *  \return ����Ҫ��������ײ������ָ��
	 *
	 *  \see 
	 */
	//virtual LightCollide * NewCollide( void ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \fn LightTerrain * NewTerrain ( void ) = 0
	 *  \brief ����һ�����ζ���
	 *
	 *  ����һ�����ζ���
	 *
	 *  \param ��
	 *	 
	 *  \return ����Ҫ�����ĵ��ζ���ָ��
	 *
	 *  \see 
	 */
	virtual LightTerrain * NewTerrain ( void ) = 0;

#endif

	/*! \brief ����һ������
	 *	 
	 *  \param sceneDesc ����������ָ�룬����˵��Ҫ����������������
	 *	 
	 *  \return ���ش���������ָ��
	 *
	 *  \see 
	 */
	virtual LightScene * createScene( const LightSceneDesc & sceneDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param scene Ҫ�ͷų�����ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseScene( LightScene * scene ) = 0;

	/*! \brief ����һ�������
	 *	 
	 *  \param cameraDesc �����������ָ�룬����˵��Ҫ�����������������
	 *	 
	 *  \return ����Ҫ�����������ָ��
	 *
	 *  \see 
	 */
	virtual LightCamera * createCamera( const LightCameraDesc & cameraDesc ) = 0;

	/*! \brief �ͷ�һ�������
	 *	 
	 *  \param camera Ҫ�ͷ��������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseCamera( LightCamera * camera ) = 0;

	/*! \brief ����һ�����
	 *	 
	 *  \param skyDesc ���������������˵��Ҫ������յ�������
	 *	 
	 *  \return �����Ѵ��������ָ��
	 *
	 *  \see 
	 */
	virtual LightSky * createSky( const LightSkyDesc & skyDesc ) = 0;

	/*! \brief �ͷ�һ�����
	 *	 
	 *  \param sky Ҫ�ͷ���յ�ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseSky( LightSky * sky ) = 0;

	/*! \brief ����һ����
	 *	 
	 *  \param fogDesc[in] ��������������˵��Ҫ�������������
	 *	 
	 *  \return �����Ѵ�������ָ��
	 *
	 *  \see 
	 */
	virtual LightFog * createFog( const LightFogDesc & fogDesc ) = 0;

	/*! \brief �ͷ�һ����
	 *	 
	 *  \param fog[in] Ҫ�ͷ����ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseFog( LightFog * fog ) = 0;

	/*! \fn LightBillboardPool * createBillboardPool( const LightBillboardPoolDesc * billboardPoolDesc ) = 0
	 *  \brief ����һ��������
	 *
	 *  ����һ��������
	 *
	 *  \param const LightBillboardPoolDesc * billboardPoolDesc ������������ָ�룬����˵��Ҫ���������ص�������
	 *	 
	 *  \return �����Ѵ����Ĳ�����ָ��
	 *
	 *  \see 
	 */
	virtual LightBillboardPool * createBillboardPool( const LightBillboardPoolDesc & billboardPoolDesc ) = 0;

	/*! \fn void releaseBillboardPool(  LightBillboardPool * billboardPool ) = 0
	 *  \brief �ͷ�һ��������
	 *
	 *  �ͷ�һ��������
	 *
	 *  \param LightBillboardPool * billboardPool Ҫ�ͷŲ����ص�ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseBillboardPool(  LightBillboardPool * billboardPool ) = 0;

	/*! \fn LightParticle * createParticle( const LightParticleDesc * particleDesc ) = 0
	 *  \brief ����һ������
	 *
	 *  ����һ������
	 *
	 *  \param const LightParticleDesc * particleDesc ����������ָ�룬����˵��Ҫ�������ӵ�������
	 *	 
	 *  \return �����Ѵ���������ָ��
	 *
	 *  \see 
	 */
	virtual LightParticle * createParticle( const LightParticleDesc & particleDesc ) = 0;

	/*! \fn void releaseParticle( LightParticle * particle ) = 0
	 *  \brief �ͷ�һ������
	 *
	 *  �ͷ�һ������
	 *
	 *  \param LightParticle * particle Ҫ�ͷ����ӵ�ָ��
	 *	 
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void releaseParticle( LightParticle * particle ) = 0;

	/*! \brief ����һ������
	 *	 
	 *  \param levelDesc[in] ����������������˵��Ҫ����������������
	 *	 
	 *  \return �����Ѵ����ĳ���ָ��
	 *
	 *  \see 
	 */
	virtual LightLevel * createLevel( const LightLevelDesc & levelDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param level[in] Ҫ�ͷų�����ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseLevel( LightLevel * level ) = 0;

	/*! \brief ����һ����������
	 *	 
	 *  \param skeletonDesc[in] ��������������������˵��Ҫ��������������������
	 *	 
	 *  \return �����Ѵ����Ĺ�������ָ��
	 *
	 *  \see 
	 */
	virtual LightSkeleton * createSkeleton( const LightSkeletonDesc & skeletonDesc ) = 0;

	/*! \brief �ͷ�һ����������
	 *	 
	 *  \param skeleton[in] Ҫ�ͷŹ���������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseSkeleton( LightSkeleton * skeleton ) = 0;

	/*! \brief ����һ����̬����
	 *	 
	 *  \param meshDesc[in] ��̬����������������˵��Ҫ������̬�����������
	 *	 
	 *  \return �����Ѵ����ľ�̬����ָ��
	 *
	 *  \see 
	 */
	virtual LightMesh * createMesh( const LightMeshDesc & meshDesc ) = 0;

	/*! \brief �ͷ�һ����̬����
	 *	 
	 *  \param mesh[in] Ҫ�ͷž�̬�����ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseMesh( LightMesh * mesh ) = 0;

	/*! \brief ����һ������
	 *	 
	 *  \param textureDesc[in] ����������������˵��Ҫ���������������
	 *	 
	 *  \return �����Ѵ���������ָ��
	 *
	 *  \see 
	 */
	virtual LightTexture * createTexture( const LightTextureDesc & textureDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param texture[in] Ҫ�ͷ������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseTexture( LightTexture * texture ) = 0;

	/*! \brief ����һ��ͼ��
	 *	 
	 *  \param imageDesc[in] ͼ��������������˵��Ҫ����ͼ���������
	 *	 
	 *  \return �����Ѵ�����ͼ��ָ��
	 *
	 *  \see 
	 */
	virtual LightImage * createImage( const LightImageDesc & imageDesc ) = 0;

	/*! \brief �ͷ�һ��ͼ��
	 *	 
	 *  \param image[in] Ҫ�ͷ�ͼ���ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseImage( LightImage * image ) = 0;

	/*! \brief ����һ����Ƶ
	 *	 
	 *  \param videoDesc[in] ��Ƶ������������˵��Ҫ������Ƶ��������
	 *	 
	 *  \return �����Ѵ�������Ƶָ��
	 *
	 *  \see 
	 */
	virtual LightVideo * createVideo( const LightVideoDesc & videoDesc ) = 0;

	/*! \brief �ͷ�һ����Ƶ
	 *	 
	 *  \param video[in] Ҫ�ͷ���Ƶ��ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseVideo( LightVideo * video ) = 0;

	/*! \brief ����һ������
	 *	 
	 *  \param textDesc[in] ����������������˵��Ҫ�������ֵ�������
	 *	 
	 *  \return �����Ѵ���������ָ��
	 *
	 *  \see 
	 */
	virtual LightText * createText( const LightTextDesc & textDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param text[in] Ҫ�ͷ����ֵ�ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseText( LightText * text ) = 0;

	/*! \brief ����һ����־
	 *	 
	 *  \param logDesc[in] ��־������������˵��Ҫ������־��������
	 *	 
	 *  \return �����Ѵ�������־ָ��
	 *
	 *  \see 
	 */
	virtual LightLog * createLog( const LightLogDesc & logDesc ) = 0;

	/*! \brief �ͷ�һ����־
	 *	 
	 *  \param log[in] Ҫ�ͷ���־��ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseLog( LightLog * log ) = 0;

#ifdef LIGHT_CORPORATION_EDITION

	/*! \brief ����һ������
	 *	 
	 *  \param weatherDesc[in] ����������������˵��Ҫ����������������
	 *	 
	 *  \return �����Ѵ���������ָ��
	 *
	 *  \see 
	 */
	virtual LightWeather * createWeather( const LightWeatherDesc & weatherDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param weather[in] Ҫ�ͷ�������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseWeather( LightWeather * weather ) = 0;

	/*! \brief ����һ�������
	 *	
	 *  \param browserDesc[in] �����������������˵��Ҫ�����������������
	 *	 
	 *  \return �����Ѵ����������ָ��
	 *
	 *  \see 
	 */
	virtual LightBrowser * createBrowser( const LightBrowserDesc & browserDesc ) = 0;

	/*! \brief �ͷ�һ�������
	 *	 
	 *  \param browser[in] Ҫ�ͷ��������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseBrowser( LightBrowser * browser ) = 0;

	/*! \brief ����һ����ɫ��
	 *	
	 *  \param shaderDesc[in] ��ɫ��������������˵��Ҫ������ɫ����������
	 *	 
	 *  \return �����Ѵ�������ɫ��ָ��
	 *
	 *  \see 
	 */
	virtual LightShader * createShader( const LightShaderDesc & shaderDesc ) = 0;

	/*! \brief �ͷ�һ����ɫ��
	 *	 
	 *  \param shader[in] Ҫ�ͷ���ɫ����ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseShader( LightShader * shader ) = 0;

	/*! \brief ����һ��ˮ
	 *	
	 *  \param waterDesc[in] ˮ������������˵��Ҫ����ˮ��������
	 *	 
	 *  \return �����Ѵ�����ˮָ��
	 *
	 *  \see 
	 */
	virtual LightWater * createWater( const LightWaterDesc & waterDesc ) = 0;

	/*! \brief �ͷ�һ��ˮ
	 *	 
	 *  \param water[in] Ҫ�ͷ�ˮ��ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseWater( LightWater * water ) = 0;

#endif

	/*! \brief ����һ���ű�
	 *	
	 *  \param scriptDesc[in] �ű�������������˵��Ҫ�����ű���������
	 *	 
	 *  \return �����Ѵ����Ľű�ָ��
	 *
	 *  \see 
	 */
	virtual LightScript * createScript( const LightScriptDesc & scriptDesc ) = 0;

	/*! \brief �ͷ�һ���ű�
	 *	 
	 *  \param script[in] Ҫ�ͷŽű���ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseScript( LightScript * script ) = 0;

	/*! \brief ����һ������
	 *	
	 *  \param brushDesc[in] ����������������˵��Ҫ�������ʵ�������
	 *	 
	 *  \return �����Ѵ����Ļ���ָ��
	 *
	 *  \see 
	 */
	virtual LightBrush * createBrush( const LightBrushDesc & brushDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param brush[in] Ҫ�ͷŻ��ʵ�ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseBrush( LightBrush * brush ) = 0;

	/*! \brief ����һ������ӿ�
	 *	
	 *  \param inputDesc[in] ����ӿ�������������˵��Ҫ��������ӿڵ�������
	 *	 
	 *  \return �����Ѵ���������ӿ�ָ��
	 *
	 *  \see 
	 */
	virtual LightInput * createInput( const LightInputDesc & inputDesc ) = 0;

	/*! \brief �ͷ�һ������ӿ�
	 *	 
	 *  \param input[in] Ҫ�ͷ�����ӿڵ�ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseInput( LightInput * input ) = 0;

	/*! \brief ����һ������
	 *	
	 *  \param soundDesc[in] ����������������˵��Ҫ����������������
	 *	 
	 *  \return �����Ѵ���������ָ��
	 *
	 *  \see 
	 */
	virtual LightSound * createSound( const LightSoundDesc & soundDesc ) = 0;

	/*! \brief �ͷ�һ������
	 *	 
	 *  \param sound[in] Ҫ�ͷ�������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseSound( LightSound * sound ) = 0;

	/*! \brief ����һ�����㶯��
	 *	
	 *  \param animationDesc[in] ���㶯��������������˵��Ҫ�������㶯����������
	 *	 
	 *  \return �����Ѵ����Ķ��㶯��ָ��
	 *
	 *  \see 
	 */
	virtual LightAnimation * createAnimation( const LightAnimationDesc & animationDesc ) = 0;

	/*! \brief �ͷ�һ�����㶯��
	 *	 
	 *  \param animation[in] Ҫ�ͷŶ��㶯����ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseAnimation( LightAnimation * animation ) = 0;

	/*! \brief ����һ��������
	 *	
	 *  \param bsptreeDesc[in] ������������������˵��Ҫ������������������
	 *	 
	 *  \return �����Ѵ����Ķ�����ָ��
	 *
	 *  \see 
	 */
	virtual LightBSPTree * createBSPTree( const LightBSPTreeDesc & bsptreeDesc ) = 0;

	/*! \brief �ͷ�һ��������
	 *	 
	 *  \param bsptree[in] Ҫ�ͷŶ�������ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseBSPTree( LightBSPTree * bsptree ) = 0;

	/*! \brief ����һ���ƹ�
	 *	 
	 *  \param lightDesc[in] �ƹ�������������˵��Ҫ�����ƹ��������
	 *	 
	 *  \return �����Ѵ����ĵƹ�ָ��
	 *
	 *  \see 
	 */
	virtual LightLight * createLight( const LightLightDesc & lightDesc ) = 0;

	/*! \brief �ͷ�һ���ƹ�
	 *	 
	 *  \param light[in] Ҫ�ͷŵƹ��ָ��
	 *	 	 
	 *  \see 
	 */
	virtual void releaseLight( LightLight * light ) = 0;

	/*! \brief ��ѯ��������
	 *	 	 
	 *  \return ������������
	 *
	 *  \see 
	 */
	virtual int getTextureNumber() = 0;

	/*! \brief ��ѯ���� ID�������������ƣ�
	 *	 
	 *  \param name[in] �������ơ�
	 *	 
	 *  \return �������� ID
	 *
	 *  \see 
	 */
	virtual int getTextureID( const char * name ) = 0;

	/*! \brief ��ѯ������������ ID��
	 *	 
	 *  \param id[in] ���� ID��
	 *	 
	 *  \return ��������ָ��
	 *
	 *  \see 
	 */
	virtual LightTexture * getTexture( int id ) = 0;

};