/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   physicsMaterial.h
 *  内容:   物理材质函数
 *
 ****************************************************************************/


/*! \file physicsMaterial.h
 * 物理材质函数
 * 此文件是物理材质函数头文件.
 */


class LightScene;


// 场景描述符结构
typedef struct
{
	/// 动态磨擦力系数，取值范围 [0，+无穷大]
	float dynamicFriction;
	
	/// 静态磨擦力系数，取值范围 [0,+无穷大]
	float staticFriction;
	
	/// 弹力系数，取值范围为 [0，1.0]
	float restitution;

} LightPhysicsMaterialDesc;


/*! \class LightPhysicsMaterial
 * \brief 物理材质类
 *
 *  本类负责场景文件的读取、显示和管理，目前支持 3ds 格式的静态网格场景文件。 
 *  每个 LightScene 实例都必须通过 LightEngine 类的 NewMesh 方法分配。 
 */

class LightPhysicsMaterial
{

public:

	/*! \fn LightScene * getScene() = 0
	 *  \brief 查询父场景
	 *
	 *  查询父场景
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回父场景引用
	 *
	 *  \see 
	 */	
	virtual	LightScene * getScene() = 0;

	/*! \fn int getMaterialIndex() = 0
	 *  \brief 查询材质索引
	 *
	 *  查询材质索引
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回材质的索引值
	 *
	 *  \see 
	 */
	virtual	int getMaterialIndex() = 0;

	/*! \fn void setToDefault() = 0
	 *  \brief 将材质设置为缺省属性
	 *
	 *  将材质设置为缺省属性
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */
	virtual	void setToDefault() = 0;

	/*! \fn void loadFromDesc( const LightPhysicsMaterialDesc & desc ) = 0
	 *  \brief 从材质描述符读取材质属性
	 *
	 *  从材质描述符读取材质属性
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回材质的索引值
	 *
	 *  \see 
	 */
	virtual	void loadFromDesc( const LightPhysicsMaterialDesc & desc ) = 0;

	/*! \fn void saveToDesc( LightPhysicsMaterialDesc & desc ) const = 0
	 *  \brief 将材质属性保存到材质描述符中
	 *
	 *  将材质属性保存到材质描述符中
	 *
	 *  \param LightPhysicsMaterialDesc & desc 要保存属性的目标材质描述符
	 *	 
	 *  \return 返回材质的索引值
	 *
	 *  \see 
	 */
	virtual	void saveToDesc( LightPhysicsMaterialDesc & desc ) = 0;

	/*! \fn void setDynamicFriction( float factor ) = 0
	 *  \brief 设置动态摩擦力系数
	 *
	 *  设置动态摩擦力系数
	 *
	 *  \param float factor 动态磨擦力系数，取值范围为（0，+无穷大）
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */	
	virtual	void setDynamicFriction( float factor ) = 0;

	/*! \fn float getDynamicFriction() const = 0
	 *  \brief 查询动态摩擦力系数
	 *
	 *  查询动态摩擦力系数
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回动态磨擦力系数，取值范围为（0，+无穷大）
	 *
	 *  \see 
	 */	
	virtual	float getDynamicFriction() = 0;

	/*! \fn void setStaticFriction( float factor ) = 0
	 *  \brief 设置静态摩擦力系数
	 *
	 *  设置静态摩擦力系数
	 *
	 *  \param float factor 静态磨擦力系数，取值范围为（0，+无穷大）
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */	
	virtual	void setStaticFriction( float factor ) = 0;
	
	/*! \fn float getStaticFriction() const = 0
	 *  \brief 查询静态摩擦力系数
	 *
	 *  查询静态摩擦力系数
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回静态磨擦力系数，取值范围为（0，无穷大）
	 *
	 *  \see 
	 */	
	virtual	float getStaticFriction() = 0;

	/*! \fn void setRestitution( float factor ) = 0
	 *  \brief 设置弹力系数
	 *
	 *  设置弹力系数
	 *
	 *  \param float factor 弹力系数，取值范围为（0，1）
	 *	 
	 *  \return 本函数没有返回值
	 *
	 *  \see 
	 */	
	virtual	void setRestitution( float factor ) = 0;

	/*! \fn float getRestitution() const = 0
	 *  \brief 查询弹力系数
	 *
	 *  查询弹力系数
	 *
	 *  \param 本函数没有参数
	 *	 
	 *  \return 返回弹力系数，取值范围为（0，1）
	 *
	 *  \see 
	 */	
	virtual	float getRestitution() = 0;


	// 公共变量：
	void * userData;	//!< 你能将它用于任何用途，通常用来和一个对象创建 1:1 对应的关系。

};