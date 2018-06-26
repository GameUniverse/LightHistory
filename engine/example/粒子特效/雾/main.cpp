

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine  *engine;
	LightCamera  *camera;
	LightInput   *input;
	LightText    *text;
	LightMesh    *mesh;
	LightSky     *sky;	
	LightFog     *fog;	
	char string[100];
	float angle = 0;
	DWORD lasttime = 0;
	bool fog_enable = TRUE;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// ʹ�� 3DSMAX ����ϵͳ(Z->UP��
	engine->coordinateSystem( LIGHT_3DSMAX_COORDINATE_SYSTEM );

	// ���ùؼ�ɫ��Ĭ�Ͻ��ã�
	engine->enable( LIGHT_KEY_COLOR );
	// ���ùؼ�ɫ��͸��ɫ��Ĭ��ֵΪ��ɫ 0��0��0 ��
	engine->setKeyColor( 255, 0, 0 );

	// �رմ�ֱͬ����Ĭ�Ͽ�����
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// ��������ӿ�
	LightInputDesc inputDesc;
	input = engine->createInput( inputDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ������̬�������
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\scene\\hill\\hill.3DS" );

	// ������պ�
	LightSkyDesc skyDesc;
	memset( &skyDesc, 0, sizeof(skyDesc) );
	skyDesc.type = LIGHT_SKY_BOX;                    // �������
	VEC3( skyDesc.box.size, 64, 64, 64 );            // ��պд�С
	LightTextureDesc textureDesc;
	skyDesc.top = engine->createTexture( textureDesc );
	skyDesc.top->load( "..\\resource\\sky\\fine_top.tga" );
	skyDesc.front = engine->createTexture( textureDesc );
	skyDesc.front->load( "..\\resource\\sky\\fine_front.tga" );
	skyDesc.back = engine->createTexture( textureDesc );
	skyDesc.back->load( "..\\resource\\sky\\fine_back.tga" );
	skyDesc.left = engine->createTexture( textureDesc );
	skyDesc.left->load( "..\\resource\\sky\\fine_left.tga" );
	skyDesc.right = engine->createTexture( textureDesc );
	skyDesc.right->load( "..\\resource\\sky\\fine_right.tga" );
	skyDesc.bottom = engine->createTexture( textureDesc );
	skyDesc.bottom->load( "..\\resource\\sky\\fine_bottom.tga" );	
	sky = engine->createSky( skyDesc );

	// ���������
	LightFogDesc fogDesc;
	memset( &fogDesc, 0, sizeof(fogDesc) );
	fogDesc.type = 0;                         // ������
	VEC3( fogDesc.color, 0.88f, 0.51f, 0.06f );  // ����ɫ
	fogDesc.color[3] = 1.0;
	fogDesc.density = 1;                      // ���ܶ�
	fogDesc.start = 50;                       // ����ʼ����
	fogDesc.end = 200;                        // ���������
	fogDesc.quality = 0;                      // ����ʾƷ��
	fogDesc.enable = TRUE;                    // ������
	fog = engine->createFog( fogDesc );

	// ���������λ�úͷ���
	camera->lookAt( 0, 0, 5,  10, 10, 8,  0, 0, 1 );

	do
	{
		// ������������״̬
		engine->updatePhysics();

		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��Ⱦ��պ�
		sky->render();

		// ��Ⱦ��������
		mesh->render();

		// ��ʾ��ʾ��Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 20 );
		if( fog_enable )
			text->drawText( "�ո� = �ر���Ч��" );
		else
			text->drawText( "�ո� = ����Ч��" );

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );		
		text->drawText( string );

		// �������밴��
		unsigned int key = input->getKey();
		// ������¿ո������ر�/����
		if( key == KEY_SPACE )
			fog_enable = !fog_enable;
		if( fog_enable )
			fog->enable();
		else
			fog->disable();

		// ������ʾ
		engine->swapBuffers();		
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷ������	
	engine->releaseFog( fog );

	// �ͷ���ն���
	engine->releaseSky( sky );

	// �ͷž�̬�������
	engine->releaseMesh ( mesh );

	// �ͷ�����ӿ�
	engine->releaseInput( input );

	// �ͷ����ֶ���
	engine->releaseText( text );

	// �ͷ����������
	engine->releaseCamera( camera );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}