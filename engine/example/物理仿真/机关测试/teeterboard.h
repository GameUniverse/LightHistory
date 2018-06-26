


// ���ΰ���
class teeterboard
{

public:

	// ���ܣ��������ΰ�
	// ������vec3_t position1, position2       ���ΰ����������ڵ�������
	//       LightScene * scene                �����û��صĳ���
	//       LightMesh * mesh                  ��������ľ�̬����
	//       vec3_t box                        ���ΰ�Ĵ�С��box[0], box[1], box[2] �ֱ��ʾ x��y��z �����᷽��Ĵ�С����̬����Ĵ�С��Ӱ�����ΰ�������С��
	//       float mass                        ���ΰ�����
	//       vec3_t position                   �����ΰ�ʩ������λ�ã��ֲ����꣬������Ϊ [0,0,0] ��
	//       vec3_t force                      �����ΰ�ʩ�����Ĵ�С
	//       bool render                       �Ƿ���Ⱦ�������
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

		// ����������
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

		// �������λ����ؽ�
		gVectorSubtract( position2, position1, m_normal );
		gVectorNormalize( m_normal );
		jointDesc.type = LIGHT_JOINT_REVOLUTE; // ���λ����ؽ�
		actor->wakeUp( 1e10 );
		jointDesc.actor[0] = actor;
		jointDesc.actor[1] = 0;
		gVectorCopy( m_normal, jointDesc.localAxis[0] );
		gVectorCopy( m_position, jointDesc.localAnchor[0] );		
		joint = scene->createJoint( jointDesc );

		m_state = 0;
		wakeTime = 0;
	}

	// ���¾��λ���״̬
	void update()
	{
		vec3_t pos;

		// ��ѯ��ɫλ��
		actor->getGlobalPosition( &pos[0], &pos[1], &pos[2] );		
		// ����̬����󶨵�������
		m_mesh->setGlobalPose( actor->getGlobalPoseMatrix44() );
		// �����ΰ�һ���´�
		actor->AddForceAtPos( m_force[0], m_force[1], m_force[2], m_barycenter[0], m_barycenter[1], m_barycenter[2] );
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