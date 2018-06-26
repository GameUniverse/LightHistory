


// 矩形活塞类
class stopcock
{

public:

	// 功能：创建矩形活塞
	// 参数：vec3_t position1, position2       活塞往返运动的两个点
	//       float velocity1, float velocity2  活塞往返运动的速度
	//       float break1, float break2        活塞在两个点停顿的时间
	//       LightScene * scene                创建该机关的场景
	//       LightMesh * mesh                  代表活塞的静态网格
	//       vec3_t position                   活塞的初始位置
	//       vec3_t box                        活塞的大小（box[0], box[1], box[2] 分别表示 x，y，z 三个轴方向的大小，静态网格的大小不影响活塞的物理大小）
	//       float mass                        活塞质量
	//       bool render                       是否渲染物理对象
	void create( vec3_t position1, vec3_t position2, float velocity1, float velocity2, float break1, float break2, LightScene * scene, LightMesh * mesh, vec3_t position, vec3_t box, float mass, bool render=FALSE )
	{
		gVectorCopy( position1, m_position1 );
		gVectorCopy( position2, m_position2 );
		m_velocity1 = velocity1;
		m_velocity2 = velocity2;
		m_break1 = break1;
		m_break2 = break2;
		m_scene = scene;
		m_mesh = mesh;
		gVectorCopy( box, m_box );
		m_mass = mass;
		m_render = render;
		m_distance = gVectorDistance( position1, position2 );		

		// 创建长方体
		LightActorDesc desc;
		memset( &desc, 0, sizeof(desc) );
		desc.type = LIGHT_SHAPE_BOX;
		desc.dynamic = TRUE;
		gVectorCopy( box, desc.box.size );
		gVectorCopy( position, desc.pos );
		VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
		desc.angle = 0.0f;
		desc.mass = m_mass;
		desc.hide = FALSE;	
		actor = m_scene->createActor( desc );

		LightJointDesc jointDesc;		

		// 创建矩形活塞关节
		gVectorSubtract( position2, position1, m_normal );
		gVectorNormalize( m_normal );
		jointDesc.type = LIGHT_JOINT_PRISMATIC; // 矩形活塞关节
		actor->wakeUp( 1e10 );
		jointDesc.actor[0] = actor;
		jointDesc.actor[1] = 0;
		VEC3( jointDesc.localAnchor[0], 0.0f, 0.0f, 0.0f );
		gVectorCopy( m_normal, jointDesc.localAxis[0] );
		joint = scene->createJoint( jointDesc );		

		m_state = 0;
		wakeTime = 0;
	}

	// 更新矩形活塞状态
	void update()
	{
		vec3_t pos;		
		vec3_t velocity, actionless_velocity = { 0.0f, 0.0f, 0.0f };
		float dist;

		// 查询角色位置
		actor->getGlobalPosition( &pos[0], &pos[1], &pos[2] );
		switch( m_state )
		{
		case 0: dist = gVectorDistance( m_position1, pos );
				if( dist > m_distance )
				{
					wakeTime = m_scene->getEngine()->getTickCount() + m_break1*1000;
					actor->setLinearVelocity( actionless_velocity );
					m_state = 1;
				}
				else
				{
					gVectorScale( m_normal, m_velocity1, velocity );
					actor->setLinearVelocity( velocity );
				}
				break;
		case 1: if( m_scene->getEngine()->getTickCount() > wakeTime )
					m_state = 2;
			    break;
		case 2: dist = gVectorDistance( m_position2, pos );
				if( dist > m_distance )
				{
					wakeTime = m_scene->getEngine()->getTickCount() + m_break2*1000;
					actor->setLinearVelocity( actionless_velocity );
					m_state = 3;
				}
				else
				{
					gVectorScale( m_normal, m_velocity2, velocity );
					VEC3( velocity, -velocity[0], -velocity[1], -velocity[2] );
					actor->setLinearVelocity( velocity );
				}
				break;
		case 3: if( m_scene->getEngine()->getTickCount() > wakeTime )
					m_state = 0;
		}
		// 将静态网格绑定到长方体
		m_mesh->setGlobalPose( actor->getGlobalPoseMatrix44() );
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
	float  m_velocity1, m_velocity2;
	float  m_break1, m_break2;
	int    m_state;
	float  m_distance;
	vec3_t m_normal;
	unsigned long wakeTime;
	LightScene    *m_scene;
	LightMesh     *m_mesh;
	vec3_t        m_box;
	float         m_mass;
	bool          m_render;
	LightActor    *actor;
	LightJoint    *joint;
};