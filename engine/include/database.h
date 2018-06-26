/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2008 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   database.h
 *  内容:   数据库函数
 *
 ****************************************************************************/


/*! \file database.h
 * 数据库函数.
 * 此文件是数据库函数头文件.
 */


/** 描述数据库特性 */
typedef struct
{
	/** 因为网络引擎通过窗口传递消息，所以必须要将网络引擎绑定到一个窗口 */
	//HWND hwnd;

} LightDatabaseDesc;


/*! \brief 数据库类
 *
 *  本类负责最基本的数据库操作。
 *  每个 LightDatabase 实例都必须通过 LightCreateDatabase 函数分配。
 */

class LightDatabase
{

public:

	/*! \brief 连接到指定数据库	 
	 *
	 *  \param host[in] 主机名
	 *
	 *  \param user[in] 用户名
	 *
	 *  \param password[in] 密码
	 *
	 *  \param database[in] 数据库名
	 *
	 *  \param port[in] 数据库端口
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int connect( const char *host, const char *user, const char *password, const char *database, unsigned int port ) = 0;

	/*! \brief 打开指定的数据库文件
	 *	 
	 *  \param database 数据库文件名
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int selectDatabase( const char *database ) = 0;

	/*! \brief 查询指定的数据
	 *	 
	 *  \param query 要执行的查询命令
	 *
	 *  \return 如果函数调用成功，返回非零值；如果函数调用失败，返回零。
	 */
	virtual int query( const char *query ) = 0;

};