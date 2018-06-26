/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   camera.h
 *  ����:   ���������
 *
 ****************************************************************************/


/*! \file camera.h
 * ���������
 */


class LightEngine;


/** �����״̬�� */
typedef struct
{
	/** �����λ�� */
	vec3_t position;

	/** ���������λ�� */
	vec3_t focus;

	/** ��������ϵķ��� */
	vec3_t up;

} LightCameraState;

/** ����������� */
typedef struct
{
	/** �����λ�� */
	vec3_t position;

	/** ���������λ�� */
	vec3_t focus;

	/** ��������ϵķ��� */
	vec3_t up;

} LightCameraDesc;


/*! \class LightCamera
 * \brief �������
 *
 *  ���ฺ��������Ŀ��ơ�
 *  ÿ�� LightCamera ʵ��������ͨ�� LightEngine ��� NewCamera �������䡣 
 */

class LightCamera
{

public:

	/*! \brief ��ѯ������ 
	*	 
	*  \return ��������ָ��
	*
	*  \see 
	*/	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn  void Viewport( int x, int y, int width, int height ) = 0
	 *  \brief �����ӿ�
	 *
	 *  �����ӿ�
	 *
	 *  \param int x �ӿ����Ͻ� x ����
	 *
	 *  \param int y �ӿ����Ͻ� y ����
	 *
	 *  \param int width �ӿڿ��
	 *
	 *  \param int height �ӿڸ߶�
	 *
	 *  \return ������������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual void viewport( int x, int y, int width, int height ) = 0;

	/*! \fn  void Perspective( double fovy, double aspect, double znear, double zfar ) = 0
	 *  \brief ����Գ�͸����ͼ��
	 *
	 *  ����Գ�͸����ͼ��
	 *
	 *  \param double fovy �� x-z ƽ���������ĽǶȣ���ֵ���������� [0.0��180.0] �ڡ�
	 *
	 *  \param double aspect ����ȣ���ƽ��̨��Ŀ�Ⱥ͸߶�֮�ȡ�
	 *
	 *  \param double znear �ӵ㣨�� z �Ḻ��������ü�ƽ��ľ��롣
	 *
	 *  \param double zfar �ӵ㣨�� z �Ḻ������Զ�ü�ƽ��ľ��롣
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void perspective( double fovy, double aspect, double znear, double zfar ) = 0;

	/*! \fn  void Ortho( double left, double right, double bottom, double top, double zNear, double zFar ) = 0
	 *  \brief ����������ͼ��
	 *
	 *  ����������ͼ��
	 *
	 *  \param double left Զ���ü�ƽ��ľ����� x ����
	 *
	 *  \param double right Զ���ü�ƽ��ľ����� x ����
	 *
	 *  \param double bottom Զ���ü�ƽ��ľ����� y ����
	 *
	 *  \param double top Զ���ü�ƽ��ľ����� y ����
	 *
	 *  \param double znear �ӵ㣨�� z �Ḻ��������ü�ƽ��ľ��롣
	 *
	 *  \param double zfar �ӵ㣨�� z �Ḻ������Զ�ü�ƽ��ľ��롣
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void ortho( double left, double right, double bottom, double top, double zNear, double zFar ) = 0;

	/*! \fn  void LookAt( double eyex, double eyey, double eyez,
     *                    double centerx, double centery, double centerz,
	 *                    double upx, double upy, double upz ) = 0
	 *  \brief �������������
	 *
	 *  �������������
	 *
	 *  \param double eyex �ӵ㣨�۾�����λ�ã� x ����
	 *
	 *  \param double eyey �ӵ㣨�۾�����λ�ã� y ����
	 *
	 *  \param double eyez �ӵ㣨�۾�����λ�ã� z ����
	 *
	 *  \param double centerx �����ϵ�����һ�� x ����
	 *
	 *  \param double centery �����ϵ�����һ�� y ����
	 *
	 *  \param double centerz �����ϵ�����һ�� z ����
	 *
	 *  \param double upx ���Ϸ��򣨼���ͼ�����¶��ϵķ�����һ��� x ����
	 *
	 *  \param double upy ���Ϸ��򣨼���ͼ�����¶��ϵķ�����һ��� y ����
	 *
	 *  \param double upz ���Ϸ��򣨼���ͼ�����¶��ϵķ�����һ��� z ����
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void lookAt( double eyex, double eyey, double eyez,
                 double centerx, double centery, double centerz,
	             double upx, double upy, double upz ) = 0;

	/*! \brief ����Ϊ��ǰ������
	 *
	 *  \see 
	 */
	virtual void active() = 0;

	/*! \fn void setPosition( float x, float y, float z ) = 0
	 *  \brief ���������λ��
	 *
	 *  ���������λ��
	 *
	 *  \param float x �����λ�� x ����
	 *
	 *  \param float y �����λ�� y ����
	 *
	 *  \param float z �����λ�� z ����
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void setPosition( float x, float y, float z ) = 0;

	/*! \fn void setFocus( float x, float y, float z ) = 0
	 *  \brief ������������㣨�����ϵ�һ�㣩λ��
	 *
	 *  ������������㣨�����ϵ�һ�㣩λ��
	 *
	 *  \param float x ���������λ�� x ����
	 *
	 *  \param float y ���������λ�� y ����
	 *
	 *  \param float z ���������λ�� z ����
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void setFocus( float x, float y, float z ) = 0;

	/*! \fn void setUp( float x, float y, float z ) = 0
	 *  \brief ������������ϵķ���
	 *
	 *  ������������ϵķ���
	 *
	 *  \param float x ��������Ϸ���� x ����
	 *
	 *  \param float y ��������Ϸ���� y ����
	 *
	 *  \param float z ��������Ϸ���� z ����
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void setUp( float x, float y, float z ) = 0;

	/*! \fn void rotateHorizontal( float angle ) = 0
	 *  \brief ��ˮƽ������ת�����
	 *
	 *  ��ˮƽ������ת�����
	 *
	 *  \param float angle �������ת�ĽǶ�
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void rotateHorizontal( float angle ) = 0;

	/*! \fn void rotateVertical( float angle ) = 0
	 *  \brief �ش�ֱ��ˮƽ��ķ�����ת�����
	 *
	 *  �ش�ֱ��ˮƽ��ķ�����ת�����
	 *
	 *  \param float angle �������ת�ĽǶ�
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void rotateVertical( float angle ) = 0;

	/*! \fn void rotateFocus( float angle ) = 0
	 *  \brief �����ߣ������λ�õ��������ɵ�ֱ�ߣ�Ϊ����ת�����
	 *
	 *  �����ߣ������λ�õ��������ɵ�ֱ�ߣ�Ϊ����ת�����
	 *
	 *  \param float angle �������ת�ĽǶ�
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	//virtual void rotateFocus( float angle ) = 0;

	/*! \fn void translate( float x, float y, float z ) = 0
	 *  \brief ����ƽ�������
	 *
	 *  ����ƽ�������
	 *
	 *  \param float x �����ƽ�������� x ����
	 *	 
	 *  \param float y �����ƽ�������� y ����
	 *	 
	 *  \param float z �����ƽ�������� z ����
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void translate( float x, float y, float z ) = 0;

	/*! \fn void setFocusDistance( float distance ) = 0
	 *  \brief ����������Ľ���
	 *
	 *  ����������Ľ���
	 *
	 *  \param float distance ������Ľ���
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void setFocusDistance( float distance ) = 0;

	/*! \fn void lockFocus( bool lock ) = 0
	 *  \brief ����/����������Ľ���
	 *
	 *  ����/����������Ľ���
	 *
	 *  \param bool lock Ҫִ�еĲ�����TRUE = ������FALSE = ����
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void lockFocus( bool lock ) = 0;

	/*! \fn void getPosition( vec3_t position ) = 0
	 *  \brief ��ѯ�����λ��
	 *
	 *  ��ѯ�����λ��
	 *
	 *  \param vec3_t position ����ָ�룬���ڷ��������λ��
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void getPosition( vec3_t position ) = 0;

	/*! \fn void getFocus( vec3_t focus ) = 0
	 *  \brief ��ѯ��������㣨�����ϵ�һ�㣩λ��
	 *
	 *  ��ѯ��������㣨�����ϵ�һ�㣩λ��
	 *
	 *  \param vec3_t focus ����ָ�룬���ڷ������������λ��
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void getFocus( vec3_t focus ) = 0;

	/*! \fn void getUp( vec3_t up ) = 0
	 *  \brief ��ѯ��������ϵķ���
	 *
	 *  ��ѯ��������ϵķ���
	 *
	 *  \param vec3_t up ����ָ�룬���÷�����������ϵķ���
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void getUp( vec3_t up ) = 0;

	/*! \fn float getFocusDistance() = 0
	 *  \brief ��ѯ������Ľ���
	 *
	 *  ��ѯ������Ľ���
	 *
	 *  \param ������û�в���
	 *	 
	 *  \return ����������Ľ��ࡣ
	 *
	 *  \see 
	 */
	virtual float getFocusDistance() = 0;

	/*! \fn void move( float forwardBack, float leftRight, float upDown ) = 0
	 *  \brief �����������Ϊ��׼�����ƶ������
	 *
	 *  �����������Ϊ��׼�����ƶ������
	 *
	 *  \param float forwardBack �����ǰ��/���˵ľ��룬> 0 Ϊǰ����< 0 Ϊ���ˣ�= 0 Ϊ�˷���ֹ
	 *	 
	 *  \param float leftRight ���������/���Ƶľ��룬> 0 Ϊ���ƣ�< 0 Ϊ���ƣ�= 0 Ϊ�˷���ֹ
	 *	 
	 *  \param float upDown ���������/�½��ľ��룬> 0 Ϊ������< 0 Ϊ�½���= 0 Ϊ�˷���ֹ
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void move( float forwardBack, float leftRight, float upDown ) = 0;

	/*! \fn void movePreview( LightCameraState * state, float forwardBack, float leftRight, float upDown ) = 0
	 *  \brief ��ȡ��Ԥ���ķ�ʽ�����ƶ������������Ϊ��׼����������״̬
	 *
	 *  ��ȡ��Ԥ���ķ�ʽ�����ƶ������������Ϊ��׼����������״̬��������������ƶ����״̬������ʵ���ƶ��������
	 *
	 *  \param LightCameraState * state ���������״̬��ָ��
	 *	 
	 *  \param float forwardBack �����ǰ��/���˵ľ��룬> 0 Ϊǰ����< 0 Ϊ���ˣ�= 0 Ϊ�˷���ֹ
	 *	 
	 *  \param float leftRight ���������/���Ƶľ��룬> 0 Ϊ���ƣ�< 0 Ϊ���ƣ�= 0 Ϊ�˷���ֹ
	 *	 
	 *  \param float upDown ���������/�½��ľ��룬> 0 Ϊ������< 0 Ϊ�½���= 0 Ϊ�˷���ֹ
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void movePreview( LightCameraState * state, float forwardBack, float leftRight, float upDown ) = 0;

	/*! \fn  void Rotate( vec3_t pos, vec3_t rotate, float length, vec3_t translation, bool fly, vec3_t eye, vec3_t center, vec3_t up ) = 0
     *  \brief �����������ת�ǶȺ�ƽ����������������
	 *
	 *  �����������ת�ǶȺ�ƽ���������������ꡣ������ֻ���㲢���� LookAt ��������Ҫ����������ֵ������Ӱ���������ʵ�ʲ�����
	 *  ͨ���ڼ����һ���ڶ��������˳��ӽ�ʱʹ�ã����Ҫ��������Ӧ���������������Ҫ���� LookAt �������˺���ǰ5������Ϊ
	 *  �������������������������������
	 *  
	 *
	 *  \param vec3_t pos �������Ҳ���۾�������λ�õ�����ֵ                                                                  [�������]
	 *
	 *  \param vec3_t rotate �������ת�Ƕ� rotate[0] = ˮƽ��ת�Ƕȣ��������Ϊ����ת��ͷ����
	 *                                      rotate[1] = ��ֱ��ת�Ƕȣ��������Ϊ̧��ͷ�����Ͽ���
	 *                                      rotate[2] = ��������ת�Ƕȣ�Ŀǰ��֧�ִ˹��ܣ���Ч��                              [�������]
	 *
	 *  \param float length ���߳��ȣ�Ҳ�����۾����ӵ㣨�����ϵ�����һ�㣩�ľ���                                              [�������]
	 *
	 *  \param vec3_t translation ��������ƶ�����translation[0] = ǰ����> 0�������ˣ�< 0��
	                                              translation[1] = ���ƣ�> 0�������ƣ�< 0��
												  translation[2] = ������> 0�����½���< 0�����˲������� fly ��־������        [�������]
	 *
	 *  \param bool fly �Ƿ�Ϊ����ģʽ�� 0 Ϊ����ģʽ���������������ˮƽ�����ƶ������������ƶ�����ָ translation[0]��
	 *                                   1 Ϊ����ģʽ��������������ƶ�                                                       [�������]
	 *
	 *  \param vec3_t eye �ӵ㣨�۾�����λ�ã�����                                                                            [������]
	 *
	 *  \param vec3_t center �����ϵ�����һ������                                                                             [������]
	 *
	 *  \param vec3_t up ���Ϸ��򣨼���ͼ�����¶��ϵķ�����һ�������                                                       [������]
	 *
	 *  \return ������û�з���ֵ��
	 *
	 *  \see LookAt
	 */
	virtual void rotate( vec3_t pos, vec3_t rotate, float length, vec3_t translation, bool fly, vec3_t eye, vec3_t center, vec3_t up ) = 0;

	/*! \fn  int Push ( void ) = 0
	 *  \brief ���������ǰ״̬ѹ���ջ
	 *
	 *  ���������ǰ״̬ѹ���ջ
	 *
	 *  \param ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int push ( void ) = 0;

	/*! \fn  int Pop ( void ) = 0
	 *  \brief ���������״̬��ջ��������Ϊ��ǰ״̬
	 *
	 *  ���������״̬��ջ��������Ϊ��ǰ״̬
	 *
	 *  \param ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int pop ( void ) = 0;

	/*! \fn  int UpdateCamera( void ) = 0
	 *  \brief Ӧ�����������
	 *
	 *  Ӧ�����������
	 *
	 *  \param ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual void updateCamera( void ) = 0;

};