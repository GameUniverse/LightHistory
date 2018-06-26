/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   skeleton.h
 *  内容:   骨骼动画函数
 *
 ****************************************************************************/


/*! \file skeleton.h
 * 骨骼动画函数.
 * 此文件是骨骼动画函数头文件.
 */


class LightEngine;


/** 骨骼动画描述符类 */
class LightSkeletonDesc
{
public:

	/** 骨骼动画名称 */
	char name[17];

	/** 骨骼动画文件名称 */
	char file[33];

	/** 骨骼动画类型 */
	//LightParticleType  type;

	/** 骨骼动画中心位置 */
	vec3_t center;

	/** 骨骼动画世界位置 */
	vec3_t global_position;

	/** 骨骼动画世界方向 */
	quat_t global_orientation;

	/** 骨骼动画局部位置 */
	vec3_t local_position;

	/** 骨骼动画局部方向 */
	quat_t local_orientation;

	/** 将要被复制到 userData */
	void * userData;

	/** 构造器设置到缺省值 */	
	LIGHT_INLINE LightSkeletonDesc()
	{
		memset( this, 0, sizeof(LightSkeletonDesc) );
		setToDefault();
	}

	/** 将结构设置成缺省值 */	
	LIGHT_INLINE void setToDefault()
	{
		strcpy( name, "" );
		strcpy( file, "" );
		//type = LIGHT_PARTICLE_NORMAL;
		VEC3( center, 0.0f, 0.0f, 0.0f );
		VEC3( global_position, 0.0f, 0.0f, 0.0f );
		VEC4( global_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		VEC3( local_position, 0.0f, 0.0f, 0.0f );
		VEC4( local_orientation, 0.0f, 0.0f, 1.0f, 0.0f );
		userData = NULL;
	}

	/** 如果描述符是有效的返回 TRUE */	
	LIGHT_INLINE bool isValid() { return TRUE; }
};


/*! \class LightSkeleton
 *  \brief 骨骼动画类
 *
 *  本类负责骨骼动画文件的读取、控制和渲染，支持真实的骨骼动画，支持多动画混合，支持任意动画任意帧的混合。 
 *  每个 LightSkeleton 实例都必须通过 LightEngine 类的 createSkeleton 方法分配， releaseSkeleton 释放。
 */

class LightSkeleton
{

public:

	/*! \brief 查询父引擎
	 *	 	 
	 *  \return 返回父引擎引用
	 *
	 *  \see 
	 */	
	virtual	LightEngine * getEngine() = 0;

	/*! \brief 读取骨骼动画文件
	 *
	 *  读取骨骼动画文件，支持真实的骨骼动画文件。
	 *
	 *  \param filename[in] 骨骼动画文件名，内容是文本格式，需要手工编写，通常以 cfg 为文件名后缀，具体格式见示例程序。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int load( const char *filename ) = 0;


	// 位置和方向

	/*! \brief 设置骨骼动画中心位置
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

	/*! \brief 把骨骼动画绑定到骨骼动画骨头上
	 *	 
	 *  绑定后，骨骼动画将跟随绑定的骨头进行运动（包括位置和方向），同一时刻，只有最后绑定的骨头有效。
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

	/*! \brief 设置骨骼动画世界位置
	 *	 
	 *  \param x 世界位置的 x 坐标
	 *
	 *  \param y 世界位置的 y 坐标
	 *
	 *  \param z 世界位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setGlobalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置骨骼动画世界方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的骨骼动画世界方向四元数
     *	 
     */
	virtual	void setGlobalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置骨骼动画世界方向（使用绕轴旋转）
     *
	 *  设置骨骼动画世界方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 骨骼动画绕轴旋转角度
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

	/*! \brief 设置骨骼动画局部位置
	 *	 
	 *  \param x 局部位置的 x 坐标
	 *
	 *  \param y 局部位置的 y 坐标
	 *
	 *  \param z 局部位置的 z 坐标
	 *	 
	 *  \see 
	 */
	virtual void setLocalPosition( float x, float y, float z ) = 0;

	/*! \brief 设置骨骼动画局部方向（使用四元数）
     *	 
     *  \param quat[in] 要设置的骨骼动画局部方向四元数
     *	 
     */
	virtual	void setLocalOrientationQuat( const quat_t quat ) = 0;

	/*! \brief 设置骨骼动画局部方向（使用绕轴旋转）
     *
	 *  设置骨骼动画局部方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[in] 骨骼动画绕轴旋转角度
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

	/*! \brief 查询骨骼动画世界位置
	 *	 
	 *  \param position[out] 返回骨骼动画世界位置
	 *	 
	 *  \see 
	 */
	virtual void getGlobalPosition( vec3_t position ) = 0;

	/*! \brief 查询骨骼动画世界方向（使用四元数）
     *	 
     *  \param orientation[out] 返回骨骼动画世界方向四元数
     *	 
     */
	virtual	void getGlobalOrientationQuat( quat_t orientation ) = 0;

	/*! \brief 查询骨骼动画世界方向（使用绕轴旋转）
     *
	 *  查询骨骼动画世界方向（使用绕轴旋转指定角度的表示方式）
	 *
	 *  \param angle[out] 返回绕轴旋转角度
     *
     *  \param axis[out] 返回旋转轴向量
     *	 
	 *  \remarks 旋转时以原点和该向量组成的线段为轴进行旋转。
	 *
     */
	virtual	void getGlobalOrientationAngleAxis( float & angle, vec3_t axis ) = 0;

	/*! \brief 查询骨头标识符（ID）
	 *	 
	 *  \param name[in] 要查询骨头的名称
	 *
	 *  \return 如果要查询的骨头存在，返回骨头标识符（ID，是一个正整数）；否则，返回 -1 。
	 *
	 *  \see 
	 */
	virtual int getBoneId( const char * name ) = 0;

	/*! \brief 查询骨头位置
	 *	 
	 *  \param bone[in] 骨头标识符（ID）
	 *	 
	 *  \param position[out] 返回骨头位置
	 *	 
	 *  \see 
	 */
	virtual void getBonePosition( int bone, vec3_t position ) = 0;

	/*! \brief 查询骨头方向（使用四元数）
     *	 
	 *  \param bone[in] 骨头标识符（ID）
	 *	 
     *  \param quat[out] 返回骨头方向（使用四元数）
     *	 
     */
	virtual	void getBoneOrientationQuat( int bone, quat_t quat ) = 0;


#ifdef LIGHT_CORPORATION_EDITION

	// 物理骨骼

	/*! \brief 创建碰撞检测用的物理骨骼
	 *
	 *  \param scene 要创建物理骨骼的场景
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 *
	 *  \see 
	 */
	virtual int createSkeleton( LightScene * scene ) = 0;

	/*! \brief 查询创建的物理骨头数
	 *
	 *  \return 如果物理骨骼已经创建，返回物理骨头数；否则，返回零。
	 *
	 *  \see 
	 */
	virtual int getNumberBones() = 0;

	/*! \brief 查询物理骨头角色指针
	 *
	 *  \return 如果物理骨骼已经创建，返回物理骨头数组指针；否则，返回 NULL 。
	 *
	 *  \see 
	 */
	virtual LightActor * const * getBones() = 0;

	/*! \brief 更新骨骼动画状态
	 * 
	 *  同时更新物理状态
	 *
	 *  \see 
	 */
	virtual void update() = 0;


	// 换装

	/*! \brief 读取骨骼动画网格文件
	 *
	 *  读取骨骼动画网格文件
	 *
	 *  \param filename[in] 骨骼动画网格文件名，通常以 cmf 和 xmf 为文件名后缀。
	 *
	 *  \return 如果函数调用成功，返回网格的句柄；如果函数调用失败，返回 0。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器。
	 *
	 *  \see 
	 */
	virtual int loadMesh( const char *filename ) = 0;

	/*! \brief 查询骨骼动画网格总数
	 *	 
	 *  \return 如果函数调用成功，返回网格的总数；如果函数调用失败，返回 0。
	 *
	 *  \remarks 
	 *
	 *  \see 
	 */
	virtual int getMeshCount( void ) = 0;

	/*! \brief 查询骨骼动画子网格总数
	 *	 
	 *  \param mesh[in] 要查询的骨骼动画网格
	 *
	 *  \return 如果函数调用成功，返回子网格的总数；如果函数调用失败，返回 0。
	 *
	 *  \remarks 
	 *
	 *  \see 
	 */
	virtual int getSubmeshCount( int mesh ) = 0;

	/*! \brief 读取骨骼动画材质文件
	 *	 
	 *  \param filename[in] 骨骼动画材质文件名，通常以 crf 和 xrf 为文件名后缀。
	 *
	 *  \return 如果函数调用成功，返回网格的句柄；如果函数调用失败，返回 0。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器的材质。
	 *
	 *  \see 
	 */
	virtual int loadMaterial( const char *filename ) = 0;

	/*! \brief 查询骨骼动画子网格材质句柄
	 *	 
	 *  \param mesh[in] 要查询的骨骼动画网格句柄
	 *
	 *  \param submesh[in] 要查询的骨骼动画子网格句柄
	 *
	 *  \return 如果函数调用成功，返回骨骼动画子网格材质的句柄；如果函数调用失败，返回 0。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器的材质。
	 *
	 *  \see 
	 */
	virtual int getSubmeshMaterial( int mesh, int submesh ) = 0;

	/*! \brief 指定骨骼动画子网格材质
	 *	 
	 *  \param mesh[in] 要指定的骨骼动画网格句柄
	 *
	 *  \param submesh[in] 要指定的骨骼动画子网格句柄
	 *
	 *  \param material[in] 要指定的骨骼动画子网格材质句柄
	 *	 
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器的材质。
	 *
	 *  \see 
	 */
	virtual void setSubmeshMaterial( int mesh, int submesh, int material ) = 0;

	/*! \brief 从内存中释放骨骼动画材质
	 *	 
	 *  \param material[in] 要释放的骨骼动画材质句柄
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器的材质。
	 *
	 *  \see 
	 */
	virtual int unloadMaterial( int material ) = 0;

	/*! \brief 根据网格名称查询网格句柄
	 *	 
	 *  \param meshname[in] 骨骼动画网格名称，此网格必须已经读入内存中。
	 *
	 *  \return 如果函数调用成功，返回网格的句柄；如果函数调用失败，返回 0。
	 *
	 *  \remarks 
	 *
	 *  \see 
	 */
	virtual int getMeshId( const char *meshname ) = 0;

	/*! \brief 设置网格名称
	 *	 
	 *  \param mesh[in] 要设置名称的网格句柄
	 *
	 *  \param name[in] 要设置的骨骼动画网格名称
	 *	 
	 *  \see 
	 */
	virtual void setMeshName( int mesh, const char *name ) = 0;

	/*! \brief 对网格进行缩放
	 *
	 *  对骨骼动画网格进行缩放，缩放效果会累积，每次缩放都是在前次缩放的结果上进行的。
	 *
	 *  \param mesh[in] 要进行缩放的骨骼动画网格句柄
	 *	
	 *  \param factor[in] 骨骼动画网格缩放因子（1.0 为正常大小）
	 *	 
	 *  \return  本函数没有返回值
	 */
    virtual void scaleMesh( int mesh, float factor ) = 0;

	/*! \brief 将网格绑定到骨骼动画
	 *	 
	 *  \param mesh[in] 要绑定网格的句柄
	 *
	 *  \return 如果函数调用成功，返回 TRUE；如果函数调用失败，返回 FALSE。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器。
	 *
	 *  \see 
	 */
	virtual bool attachMesh( int mesh ) = 0;

	/*! \brief 将网格从骨骼动画分离
	 *
	 *  将网格从骨骼动画分离。网格分离后，所用数据仍存在于内存中，但不参加运算和显示，还可以再次绑定到骨骼动画，如果要彻底从内存中删除该网格，请调用 UnloadMesh 函数。
	 *
	 *  \param mesh[in] 要分离网格的句柄
	 *
	 *  \return 如果函数调用成功，返回 TRUE；如果函数调用失败，返回 FALSE。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器。
	 *
	 *  \see 
	 */
	virtual bool detachMesh( int mesh ) = 0;

	/*! \brief 释放骨骼动画网格所占内存
	 *	 
	 *  \param mesh[in] 要释放网格的句柄
	 *
	 *  \return 如果函数调用成功，返回零；如果函数调用失败，返回错误代码。
	 *
	 *  \remarks 此函数通常使用在换装系统中，用于游戏过程中动态更换衣服和武器。
	 *
	 *  \see 
	 */
	virtual int unloadMesh( int mesh ) = 0;

	/*! \brief 编辑指定动画
	 *
	 *  编辑指定动画，主要用于精确到帧的动画混合。
	 *
	 *  \param state[in] 要编辑的动画
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int editState( int state ) = 0;

	/*! \brief 复制指定的动画帧
	 *
	 *  复制指定的动画帧，主要用于精确到帧的动画混合。
	 *
	 *  \param destframe[in] 目标帧的第一帧，一共复制多少帧由 numframe 决定
	 *
	 *  \param bone[in] 要复制的骨头通道
	 *
	 *  \param state[in] 要复制的动画
	 *
	 *  \param startframe[in] 要复制的第一帧动画
	 *
	 *  \param numframe[in] 要复制的动画帧数
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int copyState( int destframe, const char *bone, int state, int startframe, int numframe ) = 0;

	/*! \brief 显示/隐藏指定的网格
	 *	 
	 *  \param mesh[in] 要显示/隐藏的网格。
	 *
	 *  \param show[in] 要显示/隐藏的命令，当为 TRUE 时，显示该网格，如果为 FALSE，则隐藏该网格。
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int showMesh( int mesh, bool show ) = 0;

	/*! \brief 混合动画
	 *	 
	 *  \param animation[in] 要混合的动画
	 *
	 *  \param weight[in] 该动画的权重，1.0 为最大
	 *
	 *  \param animation[in] 从开始混合到结束混合所需要时间，以秒为单位
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual bool blendCycle( int animation, float weight, float delay ) = 0;

	/*! \brief 清除混合动画
	 *	 
	 *  \param animation[in] 要清除的动画
	 *	 
	 *  \param animation[in] 从开始清除到结束清除所需要时间，以秒为单位
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual bool clearCycle( int animation, float delay ) = 0;

	/*! \brief 执行单个动画
	 *	 
	 *  \param animation[in] 要执行的动画
	 *
	 *  \param delayIn[in] 该动画淡入的时间
	 *
	 *  \param delayOut[in] 该动画淡出的时间
	 *
	 *  \param weightTarget[in] 该动画的目标权重，最大值为 1.0f
	 *
	 *  \param autoLock[in] 循环播放标志，false = 循环播放
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual bool executeAction( int animation, float delayIn, float delayOut, float weightTarget, bool autoLock ) = 0;

	/*! \brief 清除单个动画
	 *	 
	 *  \param animation[in] 要清除的动画
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual bool removeAction( int animation ) = 0;

#endif


	/*! \brief 查询骨骼动画细节等级
	 *	 
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual float getLodLevel() = 0;

	/*! \brief 设置骨骼动画细节等级
	 *	 
	 *  \param lodLevel[in] 骨骼动画细节等级
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual void setLodLevel( float lodLevel ) = 0;

	// 动画类型
    #define LIGHT_TYPE_CYCLE    0  // 循环播放
    #define LIGHT_TYPE_ACTION   1  // 单次播放
    #define LIGHT_TYPE_POSE     2  // 静止播放

	/*! \brief 设置当前动画类型
	 *	 
	 *  \param type[in] 要设置的动画类型
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void animationType( int type ) = 0;

	/*! \brief 查询当前动画长度
	 *	 
	 *  \return 返回当前动画长度，以秒为单位。
	 */
	virtual float getAnimationDuration( void ) = 0;

	/*! \brief 查询当前动画已播放时间
	 *	 
	 *  \return 返回当前动画已播放时间，以秒为单位。
	 */
	virtual float getAnimationTime( void ) = 0;

	/*! \brief 设置当前动画已播放时间
	 *	 
	 *  \param time[in] 要设置的当前动画已播放时间，以秒为单位
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void setAnimationTime( float time ) = 0;

	/*! \brief 设置动画播放时间因子
	 *	 
	 *  \param factor[in] 要设置的时间因子，1.0 = 正常速度播放，2.0 = 两倍的速度播放，0.5 = 二分之一的速度播放，以此类推。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void setTimeFactor( float factor ) = 0;

	/*! \brief 查询动画播放时间因子
	 *	 
	 *  \param factor[in] 本函数没有参数。
	 *
	 *  \return 返回要查询的时间因子，返回值的具体含义见 SetTimeFactor 函数。
	 */
	virtual float getTimeFactor( void ) = 0;

	/*! \brief 指定当前动画
	 *	 
	 *  \param animation[in] 指定的动画
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void animation( int animation ) = 0;

    /*! \brief 设置骨骼动画世界矩阵（矩阵包含位置和方向信息）
 	 *	
	 *  \param mat[in] 要设置的骨骼动画矩阵（4x4矩阵）
	 */
	virtual	void setGlobalPose( const mat44_t & mat ) = 0;

	/*! \brief 设置骨骼动画旋转矩阵
	 *
	 *  \param rotate[in] 该指针指向一个 4x3 的旋转矩阵	 
	 */
    virtual void setRotateMatrix( const mat34_t & rotate ) = 0;

	/*! \brief 对骨骼动画进行缩放
	 *
	 *  对骨骼动画进行缩放，缩放效果会累积，每次缩放都是在前次缩放的结果上进行的。
	 *
	 *  \param factor[in] 骨骼动画缩放因子（1.0 为正常大小）
	 *	 
	 *  \return  本函数没有返回值
	 */
    virtual void scale( float factor ) = 0;

	/*! \brief 查询骨骼动画的包围盒
	 *
	 *  \return  本函数返回一个 vec3_t 类型的指针，有两个向量，分别表示 AABB 盒的两个顶点
	 */
	virtual vec3_t * getBoundingBox() = 0;

	/*! \brief 渲染骨骼动画
	 *
	 *  \remarks 本函数没有相关信息。
	 */
	virtual void render() = 0;

	/*! \brief 播放骨骼动画
	 *
	 *  \remarks 本函数没有相关信息。
	 */
	virtual void play() = 0;

	/*! \brief 暂停骨骼动画
	 *
	 *  使骨骼动画停留在当前帧上不动
	 *
	 *  \remarks 本函数没有相关信息。
	 */
	virtual void pause() = 0;

	/*! \brief 停止骨骼动画
	 *
	 *  骨骼动画停止播放，并回到第一帧的位置
	 *
	 *  \remarks 本函数没有相关信息。
	 */
	virtual void stop() = 0;

	/*! \fn void Unload ( void ) = 0
	 *  \brief 释放骨骼动画所占内存
	 *
	 *  释放骨骼动画所占内存
	 *
	 *  \param 本函数没有参数。
	 *
	 *  \remarks 本函数没有相关信息。
	 *
	 *  \return 本函数没有返回值。
	 */
	virtual void unload ( void ) = 0;

};