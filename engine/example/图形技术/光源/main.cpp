

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )


// ��Դ��ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightCamera *camera;
	LightScene  *scene;
	LightMesh   *mesh;
	LightLight  *point_light;
	LightLight  *orientation_light;
	LightLight  *spotlight;
	LightInput  *input;
	LightText   *text;
	char string[100];
	float rotate = 0;
	DWORD lasttime = 0;
	bool light1 = TRUE, light2 = FALSE, light3 = FALSE;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

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
	engine->setString( LIGHT_MODEL_DIRECTORY,   "" );
	LightMeshDesc meshDesc;
	mesh = engine->createMesh( meshDesc );
	mesh->load( "..\\resource\\mesh\\digger\\digger.3ds" );

	// ������������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// ����һ�����Դ�����õƹ�������򿪵ƹ�
	LightLightDesc lightDesc;
	memset( &lightDesc, 0, sizeof(lightDesc) );
	lightDesc.type = LIGHT_POINT_LIGHTING;
	VEC4( lightDesc.position, -100, 100, 100, 1 );	    // ��Դλ��
	VEC4( lightDesc.diffuse, 1.0f, 1.0f, 1.0f, 1.0f );  // ��Դ��������ɫ
	VEC4( lightDesc.specular, 0.3f, 0.3f, 0.3f, 1.0f ); // ��Դ�߹���ɫ
	VEC4( lightDesc.ambient, 0.3f, 0.3f, 0.3f, 1.0f );  // ��Դ��������ɫ
	lightDesc.enable = TRUE;
	point_light = engine->createLight( lightDesc );
	point_light->setPosition( -100, 100, 100, 1 );                   // ���ù�Դλ��
	point_light->setColor( LIGHT_DIFFUSE, 1.0f, 1.0f, 1.0f, 1.0f );  // ��Դ��������ɫ
	point_light->setColor( LIGHT_SPECULAR, 0.3f, 0.3f, 0.3f, 1.0f ); // ��Դ�߹���ɫ
	point_light->setColor( LIGHT_AMBIENT, 0.3f, 0.3f, 0.3f, 1.0f );  // ��Դ��������ɫ
	point_light->setAttenuation( LIGHT_CONSTANT, 0.0000 );
	point_light->setAttenuation( LIGHT_LINEAR, 0.0000 );
	point_light->setAttenuation( LIGHT_QUADRATIC, 0.000001f );
	point_light->enable(); // �򿪵ƹ�

	// ����һ������⣬���õƹ�������򿪵ƹ�
	orientation_light = engine->createLight( lightDesc );
	orientation_light->setPosition( -50, 200, 50, 0 ); // ���ù�Դλ��
	orientation_light->setColor( LIGHT_DIFFUSE, 1.0f, 1.0f, 1.0f, 1.0f );  // ��Դ��������ɫ
	orientation_light->setColor( LIGHT_SPECULAR, 0.3f, 0.3f, 0.3f, 1.0f ); // ��Դ�߹���ɫ
	orientation_light->setColor( LIGHT_AMBIENT, 0.3f, 0.3f, 0.3f, 1.0f );  // ��Դ��������ɫ
	orientation_light->enable(); // �򿪵ƹ�	

	// ����һ�����Դ�����õƹ�������򿪵ƹ�
	spotlight = engine->createLight( lightDesc );
	spotlight->setPosition( 0, 50, 250, 1 ); // ���ù�Դλ��
	spotlight->setColor( LIGHT_DIFFUSE, 1.0f, 1.0f, 1.0f, 1.0f );  // ��Դ��������ɫ
	spotlight->setColor( LIGHT_SPECULAR, 0.3f, 0.3f, 0.3f, 1.0f ); // ��Դ�߹���ɫ
	spotlight->setColor( LIGHT_AMBIENT, 0.3f, 0.3f, 0.3f, 1.0f );  // ��Դ��������ɫ
	spotlight->setSpotlight( 0, -50, -250, 1, 30 );
	spotlight->enable(); // �򿪵ƹ�

	// ���������
	camera->lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );	

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// �򿪵ƹ�
		engine->enable( LIGHT_LIGHTING );

		// ��ʾ��̬����
		mesh->setGlobalOrientationAngleAxis( rotate, 0, 1, 0 );
		mesh->render();

		// �رյƹ�
		engine->disable( LIGHT_LIGHTING );

		// ��ת��̬����
		DWORD time = engine->getTickCount();
		if( lasttime == 0 )
			lasttime = time;
		if( (time - lasttime) > 10 )
		{
			rotate -= ( time - lasttime ) * 0.02f;
			if( rotate < -360 )
				rotate = 0;
			lasttime = time;
		}
        
		// �������밴��
		unsigned int key = input->getKey();
		// ���ݰ������л��ƹ�״̬
		if( key == KEY_1 )
			light1 = !light1;
		if( key == KEY_2 )
			light2 = !light2;
		if( key == KEY_3 )
			light3 = !light3;
		
		// ���µƹ�״̬
		if( light1 )
			point_light->enable();
		else
			point_light->disable();
		if( light2 )
			orientation_light->enable();
		else
			orientation_light->disable();
		if( light3 )
			spotlight->enable();
		else
			spotlight->disable();

		// ��ʾ��ʾ��Ϣ
		text->color( 0, 255, 0 );
		text->setTextPos( 20, 20 );
		if( light1 )
			text->drawText( "1 = �رյ��Դ" );
		else
			text->drawText( "1 = �򿪵��Դ" );
		text->setTextPos( 20, 40 );
		if( light2 )
			text->drawText( "2 = �رշ����" );
		else
			text->drawText( "2 = �򿪷����" );
		text->setTextPos( 20, 60 );
		if( light3 )
			text->drawText( "3 = �رվ۹��" );
		else
			text->drawText( "3 = �򿪾۹��" );

		// ��ʾ֡�٣�FPS��
		sprintf( string, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );	
		text->drawText( string );

		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseLight( point_light );        // �ͷŵƹ����
	engine->releaseLight( orientation_light );
	engine->releaseLight( spotlight );
	engine->releaseScene( scene );             // �ͷų�������	
	engine->releaseMesh ( mesh );              // �ͷž�̬�������	
	engine->releaseInput( input );             // �ͷ�����ӿ�	
	engine->releaseText( text );               // �ͷ����ֶ���	
	engine->releaseCamera( camera );           // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}