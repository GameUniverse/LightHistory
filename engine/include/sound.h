/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   sound.h
 *  ����:   ������
 *
 ****************************************************************************/


/*! \file sound.h
 * ��������.
 * ���ļ������������ļ�.
 */


/* ��������ģʽ */
#define LIGHT_S3DMODE_NORMAL         0x0000
#define LIGHT_S3DMODE_HEADRELATIVE   0x0001
#define LIGHT_S3DMODE_DISABLE        0x0002


/** ������������ */
class LightSoundDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightSoundDesc()
	{
		memset( this, 0, sizeof(LightSoundDesc) );
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


/*! \class LightSound
 *  \brief ������
 *
 *  ��������Ϸ�е���Ҫ�Բ��Զ�����û����������Ϸ�������޷�����ġ����ฺ�������ļ�
 *  �Ĳ��ţ�֧�� WAV �� MIDI ��ʽ�������ļ���ÿһ��������������Ϊ��Դ��ÿ����Դ����
 *  һ�� LightSound ʵ����ÿ��ʵ��������ͨ�� LightEngine ��� createSound �������䣬
 *  releaseSound �ͷš�
 *  �������ṩ����Ϸ��������Ҫ��������Ҫ���ԣ��ٶȿ�Ϳɿ�����ǿ��ͬʱ��֧���������ԣ�
 *
 *  \li ��Ӳ������ʱ�Զ�����Ӳ�����١�
 *  \li �����������Ƶ���Դ��ϡ�
 *  \li ���̵����������ӳ١�
 *  \li ����Ӳ���������Զ����ı亯����
 */

class LightSound
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief ���������ļ�
     *
	 *  �������ļ������ڴ���
	 *
     *  \param filename[in] �����ļ�����
     *
	 *  \remarks ֧�� WAV �� MIDI �ļ���
	 *
     *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
     */
	virtual int load ( const char *filename ) = 0;

	/*! \brief �����ظ����Ŵ���
	 *
	 *  ���������ظ����ŵĴ���
	 *
	 *  \param repeats[in] ��������
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int setRepeats ( int repeats ) = 0;

	/*! \brief ����
	 *
	 *  ���Ŷ����ڴ������
	 *
	 *  \remarks ��ȫ֧�ֻ�����֧�ֶ������ͬʱ���ţ�Ҳ֧��ͬһ������ͬʱ���Ŷ�Ρ�
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int play ( void ) = 0;

	/*! \brief ��ͣ
	 *
	 *  ��ͣ���ڲ��ŵ�����
	 *	 
	 *  \return ������û�з���ֵ��
	 */
	virtual int pause ( void ) = 0;

	/*! \brief ֹͣ
	 *
	 *  ֹͣ���ڲ��ŵ�����
	 *	 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int stop ( void ) = 0;

	/*! \brief ��ѯ��������״̬
	 *	 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ���������Ĳ���״̬��
	 */
	virtual int getState( void ) = 0;

	/*! \brief �ͷ�����(MIDI)������(WAV)�ļ���ռ�ڴ�
	 *	 
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void unload ( void ) = 0;


	/*! \brief ��������λ��
	 *
	 *  ���� 3D ����������λ��
	 *
	 *  \param x[in] ����λ�õ� x ����
	 *
	 *  \param y[in] ����λ�õ� y ����
	 *
	 *  \param z[in] ����λ�õ� z ����
	 *
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setListenerPosition( float x, float y, float z ) = 0;

	/*! \brief �������ڷ���
	 *
	 *  ���� 3D ���������ڷ���
	 *
	 *  \param xFront[in] ����ǰ���� x ����
	 *
	 *  \param yFront[in] ����ǰ���� y ����
	 *
	 *  \param zFront[in] ����ǰ���� z ����
	 *
	 *  \param xTop[in] �����Ϸ��� x ����
	 *
	 *  \param yTop[in] �����Ϸ��� y ����
	 *
	 *  \param zTop[in] �����Ϸ��� z ����
	 *
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setListenerOrientation( float xFront, float yFront, float zFront, float xTop, float yTop, float zTop ) = 0;

	/*! \brief ���������ٶ�
	 *
	 *  ���� 3D �����������ٶ�
	 *
	 *  \param x[in] �����ٶȵ� x ����
	 *
	 *  \param y[in] �����ٶȵ� y ����
	 *
	 *  \param z[in] �����ٶȵ� z ����
	 *
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setListenerVelocity( float x, float y, float z ) = 0;

	/*! \brief ���þ�������
	 *
	 *  ���� 3D �����ľ�������
	 *
	 *  \param DistanceFactor[in] ��������
	 *	 
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setDistanceFactor( float DistanceFactor ) = 0;

	/*! \brief ���ö���������
	 *
	 *  ���� 3D �����Ķ���������
	 *
	 *  \param DopplerFactor[in] ����������
	 *	 
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setDopplerFactor( float DopplerFactor ) = 0;

	/*! \brief ��������˥������
	 *
	 *  ���� 3D ����������˥������
	 *
	 *  \param RolloffFactor[in] ����˥������
	 *	 
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setRolloffFactor( float RolloffFactor ) = 0;


	/*! \brief ������������ģʽ
	 *
	 *  ���� 3D ��������������ģʽ
	 *
	 *  \param mode[in] ��������ģʽ����Ϊ������ͷ����غͽ�������ģʽ��
	 *	 
	 *  \remarks һ���������ú󣬶�������������Ч��
	 *
	 *  \note LIGHT_S3DMODE_NORMAL ������ģʽ����Դ��λ�úͷ����ڿռ����ǲ���ġ�ͨ��������Դ��������������ƶ���ת��
	 *  �������LIGHT_S3DMODE_HEADRELATIVE ��ͷ�����ģʽ����Դ�� 3D ���Ժ����ߵĵ�ǰλ�ã��ٶȺͳ����йء���������
	 *  ����תʱ���������Զ����ڿռ������¶�λ��ͷ�����ģʽ�������ڴ������۷������ߵ�ͷ�����˽е���������������Ĭ��
	 *  ģʽ��Ȼ�����󲿷ֺ�����һ���ƶ������������� 3D ������LIGHT_S3DMODE_DISABLE �ǽ���ģʽ��3D ������������Ч�ģ�
	 *  ���������Ǵ����ߵ�ͷ�����ķ����ġ�
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setMode( int mode ) = 0;

	/*! \brief ��������λ��
	 *
	 *  ���������� 3D �����е�λ��
	 *
	 *  \param x[in] ����λ�õ� x ����
	 *
	 *  \param y[in] ����λ�õ� y ����
	 *
	 *  \param z[in] ����λ�õ� z ����
	 *
	 *  \remarks һ�����ú�һֱ��Ч��ֱ����������Ϊֹ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setPosition ( float x, float y, float z ) = 0;

	/*! \brief ���������ٶ�
	 *
	 *  ���������� 3D �����е��ٶ�
	 *
	 *  \param x[in] �����ٶȵ� x ����
	 *
	 *  \param y[in] �����ٶȵ� y ����
	 *
	 *  \param z[in] �����ٶȵ� z ����
	 *
	 *  \remarks һ�����ú�һֱ��Ч��ֱ����������Ϊֹ��
	 *
	 *  \note �ٶȵĵ�λ����/�롣
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setVelocity ( float x, float y, float z ) = 0;

	/*! \brief ��������׶��Ƕ�
	 *	 
	 *  \param inncone[in] ��׶��Ƕ�
	 *
	 *  \param outcone[in] ��׶��Ƕ�
	 *	 
	 *  \remarks һ�����ú�һֱ��Ч��ֱ����������Ϊֹ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setConeAngles ( int inncone, int outcone ) = 0;

	/*! \brief ��������׶�巽��
	 *	 
	 *  \param x[in] ����׶�巽��� x ����
	 *
	 *  \param y[in] ����׶�巽��� y ����
	 *
	 *  \param z[in] ����׶�巽��� z ����
	 *
	 *  \remarks һ�����ú�һֱ��Ч��ֱ����������Ϊֹ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setConeOrientation( float x, float y, float z ) = 0;

	/*! \brief ��������׶���������
	 *	 
	 *  \param inncone[in] ����׶���������
	 *	 
	 *  \remarks һ�����ú�һֱ��Ч��ֱ����������Ϊֹ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setConeOutsideVolume( long ConeOutsideVolume ) = 0;

	/*! \brief ��������������
	 *
	 *  �������������롣��һ����Դ�����ߵľ���ﵽĳ����������������������ټ��٣����������������롣
	 *
	 *  \param MaxDistance[in] ����������
	 *	 
	 *  \remarks Ĭ�ϵ���������ʮ�ڣ���ʾ��ʹ�������Ѿ�ԶԶ����������Χ֮��ʱ��������˥�������ᱻ���㣬���Զ������
	 *  ��������˵��Ϊ�˱��ⲻ��Ҫ�ļ��㣬Ӧ���趨һ�������������ֵ��������ֵҲ�������ڷ�ֹһ������̫Զʱ��������
	 *  �������ֵĬ�����ף�m����ʾ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setMaxDistance( float MaxDistance ) = 0;

	/*! \brief ����������С����
	 *
	 *  ����������С���롣��һ����Դ�����ߵľ�����ĳ��ֵ֮��ʱ���������������������ֵ�����ᷢ��˥����������������С���롣
	 *
	 *  \param MaxDistance[in] ������С����
	 *	 
	 *  \remarks ���������õ���С����������������ž���˥�����ٶȡ�������˵������Ϊһ���������潫��һ��ֵ�趨Ϊ 100km ��
	 *  Ϊһֻ�۷��趨Ϊ 2cm �����������趨�£���������Զ�� 200km �������������������������ԭ����һ�룻����ֻҪԶ���۷�
	 *  4m Զ�������۷����������ԭ����һ���ˡ�Ĭ�ϵ���С������ 1 ����λ�������Ĭ�Ͼ������ӵĻ����� 1m �������Ĭ��ֵ�£�
	 *  ������Զ������ 1m ʱ������������������������������ 2m ʱ��������һ���������� 4m ʱ���������ķ�֮һ�������Դ������
	 *  ����������Ҫ�趨һ���Ƚϴ����С���룬�Ա㵱���ƿ���ʱ����������˥������ô�졣�������ֵĬ�����ף�m����ʾ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int setMinDistance( float MinDistance ) = 0;
};