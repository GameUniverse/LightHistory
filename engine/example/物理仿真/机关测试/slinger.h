


// 吊物类
class slinger
{

public:

	// 功能：创建吊物
	// 参数：vec3_t position                   机关位置，指定物体要吊在哪个位置
	//       LightEngine * engine              引擎指针
	//       LightScene * scene                创建该机关的场景
	//       LightMesh * mesh                  代表物体的静态网格
	//       LightBrush * brush                画笔指针
	//       vec3_t homeplace                  物体的初始位置
	//       vec3_t box                        物体的大小（box[0], box[1], box[2] 分别表示 x，y，z 三个轴方向的大小，静态网格的大小不影响物体的物理大小）
	//       float mass                        物体质量
	//       bool render                       是否渲染物理对象
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

		// 创建长方体
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

		// 创建绳索（球窝关节，也称万向节）
		LightJointDesc jointDesc;
		jointDesc.type = LIGHT_JOINT_SPHERICAL; // 球窝关节
		actor->wakeUp( 1e10 );
		jointDesc.actor[0] = actor;
		jointDesc.actor[1] = 0;
		gVectorCopy( m_position, jointDesc.localAnchor[0] );
		joint = scene->createJoint( jointDesc );		
	}

	// 更新矩形活塞状态
	void update()
	{
		// 将静态网格绑定到长方体
		m_mesh->setGlobalPose( actor->getGlobalPoseMatrix44() );
	}

	// 渲染矩形活塞
	void render()
	{
		// 显示绳索（球窝关节）
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

		// 显示静态网格
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