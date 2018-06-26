


// ������
class slinger
{

public:

	// ���ܣ���������
	// ������vec3_t position                   ����λ�ã�ָ������Ҫ�����ĸ�λ��
	//       LightEngine * engine              ����ָ��
	//       LightScene * scene                �����û��صĳ���
	//       LightMesh * mesh                  ��������ľ�̬����
	//       LightBrush * brush                ����ָ��
	//       vec3_t homeplace                  ����ĳ�ʼλ��
	//       vec3_t box                        ����Ĵ�С��box[0], box[1], box[2] �ֱ��ʾ x��y��z �����᷽��Ĵ�С����̬����Ĵ�С��Ӱ������������С��
	//       float mass                        ��������
	//       bool render                       �Ƿ���Ⱦ�������
	void create( vec3_t position, LightEngine * engine, LightScene * scene, LightMesh * mesh, LightBrush * brush, vec3_t homeplace, vec3_t box, float mass, bool render=FALSE )
	{
		gVectorCopy( position, m_position );
		m_engine = engine;
		m_scene = scene;
		m_mesh = mesh;
		m_brush = brush;
		gVectorCopy( homeplace, m_homeplace );
		gVectorCopy( box, m_box );
		m_mass = mass;
		m_render = render;

		// ����������
		LightActorDesc desc;
		memset( &desc, 0, sizeof(desc) );
		desc.type = LIGHT_SHAPE_BOX;
		desc.dynamic = TRUE;
		gVectorCopy( m_box, desc.box.size );
		gVectorCopy( m_homeplace, desc.pos );
		VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
		desc.angle = 0.0f;
		desc.mass = m_mass;
		desc.hide = FALSE;	
		actor = m_scene->createActor( desc );

		// �������������ѹؽڣ�Ҳ������ڣ�
		LightJointDesc jointDesc;
		jointDesc.type = LIGHT_JOINT_SPHERICAL; // ���ѹؽ�
		actor->wakeUp( 1e10 );
		jointDesc.actor[0] = actor;
		jointDesc.actor[1] = 0;
		gVectorCopy( m_position, jointDesc.localAnchor[0] );
		joint = scene->createJoint( jointDesc );		
	}

	// ���¾��λ���״̬
	void update()
	{
		// ����̬����󶨵�������
		m_mesh->setGlobalPose( actor->getGlobalPoseMatrix44() );
	}

	// ��Ⱦ���λ���
	void render()
	{
		// ��ʾ���������ѹؽڣ�
		vertex_t line[2];
		VEC3( line[0].normal, 0.0f, 1.0f, 0.0f );
		line[0].texcoord[0] = line[0].texcoord[1] = 0.0f;
		VEC3( line[0].position, m_position[0], m_position[1], m_position[2] );
		VEC3( line[0].normal, 0.0f, 1.0f, 0.0f );
		line[1].texcoord[0] = line[1].texcoord[1] = 0.1f;
		actor->getGlobalPosition( &line[1].position[0], &line[1].position[1], &line[1].position[2] );
		m_engine->disable( LIGHT_TEXTURE );
		m_brush->color( 0, 255, 0 );
		m_brush->lineWidth( 4 );
		m_brush->linesPlus( line, 2 );
		m_engine->enable( LIGHT_TEXTURE );

		// ��ʾ��̬����
		if( m_render )
			actor->render();
		m_mesh->render();
	}

	vec3_t        m_position;
	LightEngine * m_engine;
	LightScene  * m_scene;
	LightMesh   * m_mesh;
	LightBrush  * m_brush;
	vec3_t        m_homeplace;
	vec3_t        m_box;
	float         m_mass;
	bool          m_render;
	vec3_t        m_normal;
	LightActor    *actor;
	LightJoint    *joint;
};