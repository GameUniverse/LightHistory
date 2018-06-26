/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2008 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   terrain.h
 *  ����:   ���κ���
 *
 ****************************************************************************/


/*! \file terrain.h
 * ���κ���.
 * ���ļ��ǵ��κ���ͷ�ļ�.
 */


/*! \class LightTerrain
 *  \brief ������ 
 *
 *  ���ฺ������ļ��Ķ�ȡ����Ⱦ��֧�ָ߶�ͼ��ʽ�ĵ��Ρ�
 *  ÿ�� LightTerrain ʵ��������ͨ�� LightEngine ��� NewTerrain �������䡣
 */

class LightTerrain
{

public:

	/*! \brief �������ļ������ڴ�
	 *
	 *  ֧�ָ߶�ͼ��ʽ�ĵ�ͼ��
	 *
	 *  \param filename �����ļ���
	 *
	 *  \param format �����ļ�����ʽ
	 *
	 *  \param width �����ļ����
	 *
	 *  \param height �����ļ��߶�
	 *
	 *  \param bits �����ļ�ͨ��λ��
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int load( const char *filename, int format, int width, int height, int bits ) = 0;

	/*! \brief ���õ��δ�С
	 *	 
	 *  \param width ���ο�ȣ�ָ x �᷽��Ĵ�С������Ϊ 2 �� n ���� + 1
	 *
	 *  \param height ���θ߶ȣ�ָ y �᷽��Ĵ�С������Ϊ 2 �� n ���� + 1
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int SetSize ( int width, int height ) = 0;

	/*! \brief ��ѯ���δ�С
	 *	 
	 *  \param LPSIZE lpSize ���ص��δ�С�����ݽṹָ�룬���� LPSIZE �ĳ�Ա cx �� cy �ֱ�Ϊ���εĿ�Ⱥ͸߶�
	 *	
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int GetSize ( LPSIZE lpSize ) = 0;

	/*! \fn int SetTexture ( int name, LightTexture * texture ) = 0
	 *  \brief ���õ�������
	 *
	 *  ���õ�������
	 *
	 *  \param int name Ҫ���õĵ��������
	 *
	 *  \param LightTexture * texture Ҫ���õĵ�������
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int SetTexture ( int name, LightTexture * texture ) = 0;

	/*! \brief ���õ��δ�ש��С
	 *	 
	 *  \param width ���δ�ש��ȣ�ָ x �᷽��Ĵ�С������Ϊ 2 �� n ���ݣ�<b>ȡֵ��Χ:</b> [32,���ο��-1]
	 *
	 *  \param height ���δ�ש�߶ȣ�ָ y �᷽��Ĵ�С������Ϊ 2 �� n ���ݣ�<b>ȡֵ��Χ:</b> [32,���θ߶�-1]
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int setTile( int width, int height ) = 0;

	/*! \brief ��ѯ���δ�ש��С
	 *	 
	 *  \param LPSIZE lpSize ���ص��δ�ש��С�����ݽṹָ�룬���� LPSIZE �ĳ�Ա cx �� cy �ֱ�Ϊ���δ�ש�Ŀ�Ⱥ͸߶�
	 *	
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int getTile( LPSIZE lpSize ) = 0;

	/*! \fn void BuildLODData( void ) = 0
	 *  \brief ���� LOD ����Ҫ������
	 *
	 *  ���� LOD ����Ҫ�����ݣ�������
	 *
	 *  \param ������û�в�����
	 *
	 *  \return ������û�з���ֵ��
	 */
	virtual void BuildLODData( void ) = 0;

	/*! \fn virtual void SetLODFactor( float distance, float fluctuant ) = 0
	 *  \brief ���õ�����ʾ LOD ����
	 *
	 *  ���õ�����ʾ LOD ���ӣ��˺����������ڵ�����ʾƷ�ʺ��ٶȡ�
	 *
	 *  \param float distance LOD �ľ������ӣ�ȡֵ��ΧΪ 2.5 ~ 5����ֵԽ�󣬵�����ʾƷ��Խ�ߣ�����ʾ�ٶȻ��½�
	 *
	 *  \param float fluctuant LOD ������̶����ӣ�ȡֵ��ΧΪ 25 ~ 50����ֵԽ�󣬵�����ʾƷ��Խ�ߣ�����ʾ�ٶȻ��½�
	 *
	 *  \return ������û�з���ֵ��
	 *
	 *  \see 
	 */
	virtual void SetLODFactor( float distance, float fluctuant ) = 0;

    #define LIGHT_RENDER_LOD  5  // ʹ�� LOD

	/*! \fn int RenderMode ( int mode ) = 0
	 *  \brief ���õ�����Ⱦģʽ
	 *
	 *  ���õ�����Ⱦģʽ��
	 *
	 *  \param int mode ������Ⱦģʽ
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int RenderMode ( int mode ) = 0;

	/*! \brief ��Ⱦ����
	 *		 
	 */
	virtual void render() = 0;

	/*! \fn float GetHeight ( float x, float y ) = 0
	 *  \brief ��ѯ����ָ��λ�õĸ߶�ֵ
	 *
	 *  ��ѯ����ָ��λ�õĸ߶�ֵ��
	 *
	 *  \param float x λ�õ� x ����
	 *
	 *  \param float y λ�õ� y ���꣬ʵ������ z ����
	 *
	 *  \return ���ص���ָ��λ�õĸ߶�ֵ��
	 */
	virtual float GetHeight ( float x, float y ) = 0;

	/*! \fn int SetHeight ( float x, float y, float height ) = 0
	 *  \brief ���õ���ָ��λ�õĸ߶�ֵ
	 *
	 *  ���õ���ָ��λ�õĸ߶�ֵ��
	 *
	 *  \param float x λ�õ� x ����
	 *
	 *  \param float y λ�õ� y ���꣬ʵ������ z ����
	 *
	 *  \param float height ָ��λ�� ( x, y ) �ĸ߶�ֵ
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 */
	virtual int SetHeight ( float x, float y, float height ) = 0;

	/*! \fn int GetTrianglesCount( void ) = 0
	 *  \brief ��ѯ��ʾ����������
	 *
	 *  ��ѯ��ʾ������������
	 *
	 *  \param ������û�в�����
	 *
	 *  \return ���ص�������ʾ������������
	 */
	virtual int GetTrianglesCount( void ) = 0;

	/*! \brief ����һ���߶ȳ�����
	 *	 
	 *  \return �����ĸ߶ȳ�����
	 *
	 *  \see 
	 */	
	virtual LightHeightField * createHeightField( vec3_t position, vec3_t box ) = 0;

	/*! \fn int Load ( const char *filename ) = 0
	 *  \brief �����α��浽�ļ���
	 *
	 *  ֧�ָ߶�ͼ��ʽ�ĵ�ͼ��
	 *
	 *  \param const char *filename �����ļ���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int Save ( const char *filename ) = 0;

	/*! \fn int Unload ( void ) = 0
	 *  \brief �������ļ����ڴ������
	 *
	 *  �������ļ����ڴ��������
	 *
	 *  \param ������û�в���
	 *
	 *  \return ����������óɹ������ط���ֵ�������������ʧ�ܣ������㡣
	 *
	 *  \see 
	 */
	virtual int Unload ( void ) = 0;

};