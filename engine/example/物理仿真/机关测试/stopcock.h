


// ���λ�����
class stopcock
{

public:

	// ���ܣ��������λ���
	// ������vec3_t position1, position2       ���������˶���������
	//       float velocity1, float velocity2  ���������˶����ٶ�
	//       float break1, float break2        ������������ͣ�ٵ�ʱ��
	//       LightScene * scene                �����û��صĳ���
	//       LightMesh * mesh                  ��������ľ�̬����
	//       vec3_t position                   �����ĳ�ʼλ��
	//       vec3_t box                        �����Ĵ�С��box[0], box[1], box[2] �ֱ��ʾ x��y��z �����᷽��Ĵ�С����̬����Ĵ�С��Ӱ������������С��
	//       float mass                        ��������
	//       bool render                       �Ƿ���Ⱦ�������
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

		// ����������
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

		// �������λ����ؽ�
		gVectorSubtract( position2, position1, m_normal );
		gVectorNormalize( m_normal );
		jointDesc.type = LIGHT_JOINT_PRISMATIC; // ���λ����ؽ�
		actor->wakeUp( 1e10 );
		jointDesc.actor[0] = actor;
		jointDesc.actor[1] = 0;
		VEC3( jointDesc.localAnchor[0], 0.0f, 0.0f, 0.0f );
		gVectorCopy( m_normal, jointDesc.localAxis[0] );
		joint = scene->createJoint( jointDesc );		

		m_state = 0;
		wakeTime = 0;
	}

	// ���¾��λ���״̬
	void update()
	{
		vec3_t pos;		
		vec3_t velocity, actionless_velocity = { 0.0f, 0.0f, 0.0f };
		float dist;

		// ��ѯ��ɫλ��
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
		// ����̬����󶨵�������
		m_mesh->setGlobalPose( actor->getGlobalPoseMatrix44() );
	}

	// ��Ⱦ���λ���
	void render()
	{
		// ��ʾ��̬����
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