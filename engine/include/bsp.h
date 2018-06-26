/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   LightBsp.h
 *  ����:   ����������
 *
 ****************************************************************************/


/*! \file bsp.h
 * ����������.
 * ���ļ��Ƕ���������ͷ�ļ�.
 */


#define LIGHT_MAX_BSP_HOMEPLACE   256 // �����ҳ�������

// ��ҳ�����ṹ
typedef struct homeplace_s
{
	vec3_t pos;   // ���λ��
	float  angle; // ��ҽǶ�
} homeplace_t;

// �������ݽṹ
typedef struct bsp_data_s
{
	int    NumHomeplace;                             // ��ҳ�������
	homeplace_t Homeplaces[LIGHT_MAX_BSP_HOMEPLACE]; // ��ҳ������б�

} bsp_data_t;


/** �������������� */
class LightBSPTreeDesc
{
public:

	/** ȫ���������� */
	vec3_t position;

	/** ��Ҫ�����Ƶ� userData */
	void * userData;

	/** ���������õ�ȱʡֵ */	
	LIGHT_INLINE LightBSPTreeDesc()
	{
		memset( this, 0, sizeof(LightBSPTreeDesc) );
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


/*! \class LightBSPTree
 * \brief ��������
 *
 *  ���ฺ���ͼ�ļ��Ķ�ȡ����ʾ����������������������ĺ��Ĳ��֡�
 *  ÿ�� LightBSPTree ʵ��������ͨ�� LightEngine ��� createBSPTree �������䣬 releaseBSPTree �ͷš�
 */

class LightBSPTree
{

public:

	/*! \brief ��ѯ������
	 *	 
	 *  \return ���ظ���������
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \fn void Lighteness( float lighteness ) = 0
	 *  \brief ���õ�ͼ����ֵ�������ڶ�ȡ��ͼ֮ǰ���ò���Ч��ȱʡֵΪ 10 ��
	 *
	 *  ���õ�ͼ����ֵ�������ڶ�ȡ��ͼ֮ǰ���ò���Ч��ȱʡֵΪ 10 ��
	 *
	 *  \param float lighteness ��ͼ����ֵ
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void Lighteness( float lighteness ) = 0;

	/*! \fn bool Load(const char *strFileName) = 0
	 *  \brief ��ָ���� .bsp ���ڳ����ļ������ڴ�
	 *
	 *  ��ָ���� .bsp ���ڳ����ļ������ڴ�
	 *
	 *  \param float lighteness ��ͼ�ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual bool Load(const char *strFileName) = 0;

	/*! \brief ����һ���������������
	*	 
	*  \return �µ�����������
	*
	*  \see 
	*/	
	virtual LightTriangleMesh * createTriangleMesh() = 0;
	
	/*! \fn int FindLeaf( float x, float y, float z ) = 0
	 *  \brief ��ѯָ�������ڵ�Ҷ�ڵ㣨����������
	 *
	 *  ��ѯָ�������ڵ�Ҷ�ڵ㣨����������
	 *
	 *  \param float x �õ�� x ����ֵ
	 *
	 *  \param float y �õ�� y ����ֵ
	 *
	 *  \param float z �õ�� z ����ֵ
	 *
	 *  \return �õ�����Ҷ�ڵ������ֵ
	 *
	 *  \see 
	 */
	virtual int FindLeaf( float x, float y, float z ) = 0;

	/*! \fn int AttachModel( LightModelMD3 *model ) = 0
	 *  \brief ��ָ��ģ�����ͼ��
	 *
	 *  ��ָ��ģ�����ͼ��
	 *
	 *  \param LightModelMD3 *model Ҫ�󶨵�ģ��
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int AttachModel( LightModelMD3 *model ) = 0;

	/*! \fn void Gravity( float gravity ) = 0
	 *  \brief ���õ�ͼ����
	 *
	 *  ���õ�ͼ����
	 *
	 *  \param float gravity ����ֵ
	 *	 
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void Gravity( float gravity ) = 0;

	/*! \fn int GetData( bsp_data_t * bsp_data ) = 0
	 *  \brief ��ѯ���ڳ�������
	 *
	 *  ��ѯ���ڳ������ݣ�������ҳ����������
	 *
	 *  \param bsp_data_t * bsp_data Ҫ�������ݵĽṹָ��
	 *	 
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int GetData( bsp_data_t * bsp_data ) = 0;

	/*! \fn void Update( void ) = 0
	 *  \brief ���³���״̬
	 *
	 *  ���³���״̬
	 *
	 *  \param ������û�в���
	 *	 
	 *
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void Update( void ) = 0;

	/*! \fn virtual void Render( void ) = 0
	 *  \brief ��Ⱦ����
	 *
	 *  ��Ⱦ����
	 *
	 *  \param ������û�в���
	 *	 
	 *
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void Render( void ) = 0;

	/*! \fn void RenderSingle( void ) = 0
	 *  \brief ������Ⱦ����������Ⱦģ�ͺ���Ӱ��
	 *
	 *  ������Ⱦ����������Ⱦģ�ͺ���Ӱ��
	 *
	 *  \param ������û�в���
	 *	 
	 *
	 *  \return ������û�з���ֵ
	 *
	 *  \see 
	 */
	virtual void RenderSingle( void ) = 0;

	/*! \fn void RenderProjection() = 0
	 *  \brief ��ͶӰ����ģʽ��Ⱦ����
	 *
	 *  ��ͶӰ����ģʽ��Ⱦ����
	 *
	 *  \param ��
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void RenderProjection() = 0;

	/*! \fn  void RenderBlendFace() = 0
	 *  \brief ��Ⱦ�����е�͸����
	 *
	 *  ��Ⱦ�����е�͸����
	 *
	 *  \param ��
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void RenderBlendFace() = 0;

	/*! \fn CVector3 TraceRay(CVector3 vStart, CVector3 vEnd) = 0
	 *  \brief ����ָ�����߶��볡���е�͹���Ƿ�����ײ
	 *
	 *  ����ָ�����߶��볡���е�͹���Ƿ�����ײ
	 *
	 *  \param CVector3 vStart �߶���ʼ��
	 *
	 *  \param CVector3 vEnd �߶ν�����
	 *	 
	 *  \return CVector3 ������ײ�ĵ�
	 *
	 *  \see 
	 */
	virtual CVector3 TraceRay(CVector3 vStart, CVector3 vEnd) = 0;

	/*! \fn  CVector3 TraceSphere(CVector3 vStart, CVector3 vEnd, float radius) = 0
	 *  \brief ����ָ���������볡���е�͹���Ƿ�����ײ
	 *
	 *  ����ָ���������볡���е�͹���Ƿ�����ײ
	 *
	 *  \param CVector3 vStart �߶���ʼ��
	 *
	 *  \param CVector3 vEnd �߶ν�����
	 *	 
	 *  \param float radius ����İ뾶
	 *	 
	 *  \return CVector3 ������ײ�ĵ�
	 *
	 *  \see 
	 */
	virtual CVector3 TraceSphere(CVector3 vStart, CVector3 vEnd, float radius) = 0;

	/*! \fn  CVector3 TraceBox(CVector3 vStart, CVector3 vEnd, CVector3 vMin, CVector3 vMax) = 0
	 *  \brief ����ָ���İ�Χ�У�AABB���볡���е�͹���Ƿ�����ײ
	 *
	 *  ����ָ���İ�Χ�У�AABB���볡���е�͹���Ƿ�����ײ
	 *
	 *  \param CVector3 vStart �߶���ʼ��
	 *
	 *  \param CVector3 vEnd �߶ν�����
	 *	 
	 *  \param CVector3 vMin ��Χ�У�AABB���Խ��߶���
	 *	 
	 *  \param CVector3 vMax ��Χ�У�AABB���Խ�����һ������
	 *	 
	 *  \return CVector3 ������ײ�ĵ�
	 *
	 *  \see 
	 */
	virtual CVector3 TraceBox(CVector3 vStart, CVector3 vEnd, CVector3 vMin, CVector3 vMax) = 0;

	/*! \fn  bool IsOnGround() = 0
	 *  \brief ��ѯ���һ����ײ����Ƿ�����淢����ײ
	 *
	 *  ��ѯ���һ����ײ����Ƿ�����淢����ײ
	 *
	 *  \param ��
	 *
	 *  \return �������淢����ײ������ TRUE �����򷵻� FALSE ��
	 *
	 *  \see 
	 */
	virtual bool IsOnGround() = 0;

	/*! \fn  bool Collided() = 0
	 *  \brief ��ѯ���һ����ײ����Ƿ�����ײ
	 *
	 *  ��ѯ���һ����ײ����Ƿ�����ײ
	 *
	 *  \param ��
	 *
	 *  \return ���������ײ������ TRUE �����򷵻� FALSE ��
	 *
	 *  \see 
	 */
	virtual bool Collided() = 0;

	/*! \fn  void Destroy() = 0
	 *  \brief �ͷŵ�ͼ��ռ�ڴ�
	 *
	 *  �ͷŵ�ͼ��ռ�ڴ�
	 *
	 *  \param ��
	 *
	 *  \return ��
	 *
	 *  \see 
	 */
	virtual void Destroy() = 0;
};