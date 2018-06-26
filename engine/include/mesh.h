/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   mesh.h
 *  内容:   静态网格函数
 *
 ****************************************************************************/


/*! \file mesh.h
 * 静态网格函数
 * 此文件是静态网格函数头文件.
 */


class LightEngine;


/** 静态网格描述符类 */
class LightMeshDesc
{
public:

	/** 静态网格名称 */
	char   name[17];

	/** 静态网格文件名称 */
	char file[33];

	/** 静态网格中心位置 */
	vec3_t center;

	/** 静态网格世界位置 */
	vec3_t global_position;

	/** 静态网格世界方向 */
	quat_t global_orientation;

	/** 静态网格局部位置 */
	vec3_t local_position;

	/** 静态网格局部方向 */
	quat_t local_orientation;

	/** 投射阴影 */
	bool shadow_cast;

	/** 接收阴影 */
	bool shadow_receive;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightMeshDesc()
	{
		memset( this, 0, sizeof(LightMeshDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "" );
		strcpy( file, "" );
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		shadow_cast = FALSE;
		shadow_receive = FALSE;
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightMesh
 * \brief 静态网格类
 *
 *  本类负责静态网格文件的读取和显示，目前支持 3ds 格式的静态网格文件。 
 *  每个 LightMesh 实例都必须通过 LightEngine 类的 NewMesh 方法分配。 
 */

class LightMesh
{

public:

	/*! \brief 查询父引擎
	 *	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 设置静态网格名称
	 *
	 *  缺省静态网格名称为空。当静态网格名称为空时，调用 load 函数后，静态网格名称会改变为静态网格文件名，否则，静态网格名称不会改变。
	 *
	 *  \param name[in] 静态网格名称，当超出长度时，只取前 16 个字符（字节）。
	 *	 
	 *  \see 
	 */
	virtual void setName( const char * name ) = 0;

	/*! \brief 查询静态网格名称
	 *
	 *  静态网格名称一般为静态网格文件名，缺省静态网格名称为空。
	 *
	 *  \param name[out] 返回静态网格名称，缓冲区不得小于 17 字节（16 个字符（字节）＋'\0'）。
	 *	
	 *  \see 
	 */
	virtual void getName( char * name ) = 0;

	/*! \brief 将静态网格文件读入内存
	 *	 
	 *  \param mesh[in] 静态网格文件名，必须指定扩展名
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual bool load( const char * mesh ) = 0;

	/*! \brief 设置静态网格中心位置
	 *	 
	 *  \param x 中心位置的 x 坐标
	 *
	 *  \param y 中心位置的 y 坐标
	 *
	 *  \param z 中心位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setCenter( float x, float y, float z ) = 0;

	/*! \brief 把静态网格绑定到骨骼动画骨头上
	 *	 
	 *  绑定后，静态网格将跟随绑定的骨头进行运动（包括位置和方向），同一时刻，只有最后绑定的骨头有效。
	 *
	 *  \param skeleton[in] 要绑定的骨骼动画，当该参数为 NULL 时解除绑定
	 *
	 *  \param bone[in] 要绑定的骨头
	 *
	 *  \return 如果函数调用成功，返回 0；否则，返回错误代码。
	 *
	 *  \see 
	 */
	virtual int attach( LightSkeleton * skeleton, int bone ) = 0;

	/*! \brief 设置静态网格世界位置
	 *	 
	 *  \param x 静态网格世界位置的 x 坐标
	 *
	 *  \param y 静态网格世界位置的 y 坐标
	 *
	 *  \param z 静态网格世界位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置静态网格世界方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的静态网格世界方向四元数
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置静态网格世界方向（使用绕轴旋转）
     *
	 *  设置静态网格世界方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 静态网格绕轴旋转角度
     *
     *  \param x[in] 旋转轴向量 x 分量
     *
	 *  \param y[in] 旋转轴向量 y 分量
     *
	 *  \param z[in] 旋转轴向量 z 分量
     *
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。
	 *
     */
	virtual	void setGlobalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;

	/*! \brief 设置静态网格局部位置
	 *	 
	 *  \param x 静态网格局部位置的 x 坐标
	 *
	 *  \param y 静态网格局部位置的 y 坐标
	 *
	 *  \param z 静态网格局部位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置静态网格局部方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的静态网格局部方向四元数
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置静态网格局部方向（使用绕轴旋转）
     *
	 *  设置静态网格局部方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 静态网格绕轴旋转角度
     *
     *  \param x[in] 旋转轴向量 x 分量
     *
	 *  \param y[in] 旋转轴向量 y 分量
     *
	 *  \param z[in] 旋转轴向量 z 分量
     *
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。
	 *
     */
	virtual	void setLocalOrientationAngleAxis( float angle, float x, float y, float z ) = 0;

	/*! \fn void render( void ) = 0
	 *  \brief 渲染静态网格
	 *
	 *  将静态网格渲染到屏幕或窗口
	 *
	 *  \param 本函数没有参数。
	 *	
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void render( void ) = 0;

	/*! \brief 设置静态网格世界矩阵（矩阵包含位置和方向信息）
	 *	
	 *  \param mat[in] 要设置的静态网格矩阵（4x4矩阵）
	 */
	virtual	void setGlobalPose( const mat44_t & mat ) = 0;

	/*! \brief 设置静态网格旋转矩阵
	 *
	 *  \param rotate[in] 该指针指向一个 4x3 的旋转矩阵	 
	 */
    virtual void setRotateMatrix( const mat34_t & rotate ) = 0;

	/*! \brief 设置静态网格缩放比例
	 *	 
	 *  \param x[in] 网格沿 x 轴的缩放比例
	 *	
	 *  \param y[in] 网格沿 y 轴的缩放比例
	 *	
	 *  \param z[in] 网格沿 z 轴的缩放比例
	 *	
	 *  \remarks 当 （x，y，z）都等于 1.0f 时，网格大小不变，这是网格的缺省比例。
	 *
	 *  \return 此函数没有返回值。
	 */
    virtual void scale( float x, float y, float z ) = 0;

	/*! \brief 查询静态网格位置
	 *
	 *  查询静态网格在场景中的位置坐标。
	 *
	 *  \param position[out] 返回静态网格位置
	 *	
	 *  \remarks 本函数没有相关信息。	  
	 */
	virtual void getGlobalPosition( vec3_t position ) = 0;

	/*! \brief 创建三角形网格对象
	 *	 
	 *  \return 新的三角形网格
	 *
	 *  \see 
	 */
	virtual LightTriangleMesh * createTriangleMesh() = 0;

	/*! \brief 释放三角形网格对象
	 *	 
	 *  \param mesh[in] 要释放的三角形网格
	 *
	 *  \see 
	 */	
	virtual void releaseTriangleMesh( LightTriangleMesh * mesh ) = 0;

	/*! \brief 释放静态网格文件所占内存
	 *	 
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual bool unload( void ) = 0;

};