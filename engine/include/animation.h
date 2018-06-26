/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   animation.h
 *  ����:   ���㶯������
 *
 ****************************************************************************/


/*! \file animation.h
 * ���㶯������.
 * ���ļ��Ƕ��㶯������ͷ�ļ�.
 */


/** ���㶯���������� */
class LightAnimationDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightAnimationDesc()
	{
		memset( this, 0, sizeof(LightAnimationDesc) );
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


/*! \class LightAnimation
 *  \brief ���㶯���� 
 *
 *  ���ฺ�𶥵㶯���ļ��Ķ�ȡ����ʾ��Ŀǰ֧�� MD2 ���㶯���ļ���
 *  ÿ�� LightAnimation ʵ��������ͨ�� LightEngine ��� createAnimation �������䣬 releaseAnimation �ͷš�
 */

class LightAnimation
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn int Load ( const char *filename ) = 0
     *  \brief ���붥�㶯���ļ�
     *
	 *  �����㶯���ļ������ڴ���
	 *
     *  \param filename ���㶯���ļ���.
     *
	 *  \remarks Ŀǰ֧�� MD2 ���㶯���ļ���
	 *
     *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
     */
	virtual int Load ( const char *filename ) = 0;

	/*! \fn void SetPos( float x, float y, float z ) = 0
	 *  \brief ���ö��㶯��λ��
	 *
	 *  ���ö��㶯��λ��
	 *
	 *  \param float x ���㶯��λ�õ� x ����
	 *	
	 *  \param float y ���㶯��λ�õ� y ����
	 *	
	 *  \param float z ���㶯��λ�õ� z ����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void SetPos( float x, float y, float z ) = 0;

	/*! \fn void SetRotate( float angle, float x, float y, float z ) = 0
	 *  \brief ���ö��㶯����ת�Ƕ�
	 *
	 *  ���ö��㶯����ת�Ƕȣ����㶯����һ������ת��������������һ��������ʾ��
	 *
	 *  \param float angle ���㶯������ת�Ƕȣ��Զ�Ϊ��λ�������ǰ��ת�������� 180 �ȣ�
	 *
	 *  \param float x �������� x ����
	 *
	 *  \param float y �������� y ����
	 *
	 *  \param float z �������� z ����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void SetRotate( float angle, float x, float y, float z ) = 0;

	/*! \fn void SetRotateMatrix( const float * rotate ) = 0
 	 *  \brief ���ö��㶯����ת����
	 *
	 *  ���ö��㶯����ת����
	 *
	 *  \param const float * rotate ��ָ��ָ��һ�� 4x3 ����ת����
	 *	 
	 *  \return  ������û�з���ֵ
	 */
    virtual void SetRotateMatrix( const float * rotate ) = 0;

	/*! \fn void Render( void ) = 0
	 *  \brief ��Ⱦ����
	 *
	 *  ��������Ⱦ����Ļ�򴰿�
	 *
	 *  \param ������û�в�����
	 *	
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void Render( void ) = 0;

	/*! \fn int Play ( void ) = 0
	 *  \brief ����
	 *
	 *  ���Ŷ����ڴ�Ķ��㶯��
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks 
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int Play ( void ) = 0;

	/*! \fn int Pause ( void ) = 0
	 *  \brief ��ͣ
	 *
	 *  ��ͣ���ڲ��ŵĶ��㶯��
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int Pause ( void ) = 0;

	/*! \fn int Stop ( void ) = 0
	 *  \brief ֹͣ
	 *
	 *  ֹͣ���ڲ��ŵĶ��㶯��
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual int Stop ( void ) = 0;

	/*! \fn int Insert( int insert ) = 0
	 *  \brief ���붯��
	 *
	 *  ���붯��
	 *
	 *  \param int insert Ҫ�����λ��
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int Insert( int insert ) = 0;

	/*! \fn int Edit( int animation, int start, int end, const char *name ) = 0
	 *  \brief �༭����
	 *
	 *  �༭����
	 *
	 *  \param int animation Ҫ�༭�Ķ���
	 *
	 *  \param int start ������ʼ֡
	 *
	 *  \param int end ��������֡
	 *
	 *  \param const char *name �µĶ�������
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int Edit( int animation, int start, int end, const char *name ) = 0;

	/*! \fn int SetState( int state ) = 0
	 *  \brief ���õ�ǰ����
	 *
	 *  ���õ�ǰ����
	 *
	 *  \param int state ��ǰ����
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int SetState( int state ) = 0;

	/*! \fn int SetType( int type ) = 0
	 *  \brief ���ö��㶯������
	 *
	 *  ���ö��㶯������
	 *
	 *  \param int type �������ͣ���Ϊ 0 ʱ���ö���ѭ������ʱ�����һ֡�͵�һ֡��
	 *                  ���в�ֵ��������β��ӵĶ������������ܵĶ�������Ҳ��ȱʡ��
	 *                  �������ͣ���Ϊ 1 ʱ���ö���ѭ������ʱ�����һ֡�͵�һ֡��
	 *                  �����в�ֵ��������β����ӵĶ����������﹥���Ķ�����
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ���ؽű���ִ��״̬��
	 */
	virtual int SetType( int type ) = 0;

	/*! \fn void Unload ( void ) = 0
	 *  \brief �ͷŶ��㶯����ռ�ڴ�
	 *
	 *  �ͷŶ��㶯����ռ�ڴ�
	 *
	 *  \param ������û�в�����
	 *
	 *  \remarks ������û�������Ϣ��
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void Unload ( void ) = 0;	

};