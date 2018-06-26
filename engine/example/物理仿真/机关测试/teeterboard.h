


// 跷跷板类
class teeterboard
{

public:

	// 功能：创建跷跷板
	// 参数：vec3_t position1, position2       跷跷板轴两端所在的两个点
	//       LightScene * scene                创建该机关的场景
	//       LightMesh * mesh                  代表活塞的静态网格
	//       vec3_t box                        跷跷板的大小（box[0], box[1], box[2] 分别表示 x，y，z 三个轴方向的大小，静态网格的大小不影响跷跷板的物理大小）
	//       float mass                        跷跷板质量
	//       vec3_t position                   向跷跷板施加力的位置（局部坐标，最中心为 [0,0,0] ）
	//       vec3_t force                      向跷跷板施加力的大小
	//       bool render                       是否渲染物理对象
	void create( vec3_t position1, vec3_t position2, LightScene * scene, LightMesh * mesh, vec3_t box, float mass, vec3_t position, vec3_t force, bool render=FALSE )
	{
		gVectorCopy( position1, m_position1 );
		gVectorCopy( position2, m_position2 );
		m_position[0] = ( m_position1[0] + m_position2[0] ) / 2;
		m_position[1] = ( m_position1[1] + m_position2[1] ) / 2;
		m_position[2] = ( m_position1[2] + m_position2[2] ) / 2;
		m_scene = scene;
		m_mesh = mesh;
		gVectorCopy( box, m_box );
		m_mass = mass;
		m_render = render;
		gVectorCopy( position, m_barycenter );
		gVectorCopy( force, m_force );
		m_distance = gVectorDistance( position1, position2 );

		// 创建长方体
		LightActorDesc desc;
		memset( &desc, 0, sizeof(desc) );
		desc.type = LIGHT_SHAPE_BOX;
		desc.dynamic = TRUE;
		gVectorCopy( box, desc.box.size );
		gVectorCopy( m_position, desc.pos );
		VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
		desc.angle = 0.0f;
		desc.mass = m_mass;
		desc.hide = FALSE;	
		actor = m_scene->createActor( desc );

		LightJointDesc jointDesc;		

		// 创建矩形活塞关节
		gVectorSubtract( position2, position1, m_normal );
		gVectorNormalize( m_normal );
		jointDesc.type = LIGHT_JOINT_REVOLUTE; // 矩形活塞关节
		actor->wakeUp( 1e10 );
		jointDesc.actor[0] = actor;
		jointDesc.actor[1] = 0;
		gVectorCopy( m_normal, jointDesc.localAxis[0] );
		gVectorCopy( m_position, jointDesc.localAnchor[0] );		
		joint = scene->createJoint( jointDesc );

		m_state = 0;
		wakeTime = 0;
	}

	// 更新矩形活塞状态
	void update()
	{
		vec3_t pos;

		// 查询角色位置
		actor->getGlobalPosition( &pos[0], &pos[1], &pos[2] );		
		// 将静态网格绑定到长方体
		m_mesh->setGlobalPose( actor->getGlobalPoseMatrix44() );
		// 让跷跷板一端下垂
		actor->AddForceAtPos( m_force[0], m_force[1], m_force[2], m_barycenter[0], m_barycenter[1], m_barycenter[2] );
	}

	// 渲染矩形活塞
	void render()
	{
		// 显示静态网格
		if( m_render )
			actor->render();
		m_mesh->render();
	}

	vec3_t m_position1, m_position2;
	vec3_t m_position;	
	int    m_state;
	float  m_distance;
	vec3_t m_normal;
	unsigned long wakeTime;
	LightScene    *m_scene;
	LightMesh     *m_mesh;
	vec3_t        m_box;
	float         m_mass;
	vec3_t        m_barycenter;
	vec3_t        m_force;
	bool          m_render;
	LightActor    *actor;
	LightJoint    *joint;
};