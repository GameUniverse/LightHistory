

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

LightEngine   *engine;
LightScene    *scene;
LightCamera   *camera;
LightText     *text;
LightTexture  *texture;
LightActor    *a, *b;
LightActor    *plane;

bool collided = FALSE; // ��ײ��־

// ��ɫ�Ӵ������������
void contactReportProc( LightActor * a1, LightActor * a2, unsigned long events )
{
	// ���� a �� b ������ײ�����ݽӴ���־λִ����Ӧ�Ĳ���
	if( (a1 == a && a2 == b) || (a1 == b && a2 == a) )
	{
		// �� a �� b ��ʼ�Ӵ���Ҳ��ֹͣ�Ӵ�֮ǰ�ĵ�һ�νӴ���
		if( events & LIGHT_NOTIFY_ON_START_TOUCH )
			collided = TRUE;
		else
			// �� a �� b �����Ӵ������ֽӴ�״̬��
			if( events & LIGHT_NOTIFY_ON_TOUCH )
				collided = TRUE;
			else
				// �� a �� b ֹͣ�Ӵ����뿪��
				if( events & LIGHT_NOTIFY_ON_END_TOUCH )
					collided = FALSE;
	}
}

// ��ײ�����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );
	
	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������������
	LightCameraDesc cameraDesc;
	camera = engine->createCamera( cameraDesc );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����һ������
	LightSceneDesc sceneDesc;
	memset( &sceneDesc, 0, sizeof(sceneDesc) );	
	scene = engine->createScene( sceneDesc );

	// �������棨һ��ƽ�棩
	LightActorDesc desc;	
	desc.type = LIGHT_SHAPE_PLANE;
	VEC3( desc.plane.normal, 0.0f, 1.0f, 0.0f );
	desc.plane.distance = 0.0f;
	plane = scene->createActor( desc );

	// ���������� a �� b
	LightTextureDesc textureDesc;
	texture = engine->createTexture( textureDesc );
	texture->load( "..\\resource\\image\\wood.jpg" );	
	desc.type = LIGHT_SHAPE_BOX;
	desc.dynamic = TRUE;
	VEC3( desc.box.size, 2.0f, 2.0f, 2.0f );
	VEC3( desc.pos, 0.0f, 10.0f, 0.0f );
	VEC3( desc.rotate, 0.0f, 1.0f, 0.0f );
	desc.angle = 0.0f;
	desc.mass = 0.00001f;
	desc.hide = FALSE;	
	a = scene->createActor( desc );
	desc.type = LIGHT_SHAPE_BOX;
	desc.dynamic = TRUE;
	VEC3( desc.box.size, 2.0f, 2.0f, 2.0f );
	VEC3( desc.pos, 0.0f, 40.0f, 0.0f );
	VEC3( desc.rotate, 1.5f, 1.0f, 0.0f );
	desc.angle = 45.0f;	
	b = scene->createActor( desc );

	// ������ײ�����Ӧ����
	scene->setUserContactReport( contactReportProc );

	// ���������
	camera->lookAt( 0, 10, 15,  0, 2, 0,  0, 1, 0 );

	// ���ǰ����
	texture->active();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );
		
		// ��ײ��־��λ
		//collided = FALSE;

		// ��������״̬
		engine->updatePhysics();
		
		// ��ʾ������ a �� b
		a->render();
		b->render();

		// ��ʾ��ʾ��Ϣ
		text->setTextPos( 40, 368 );
		if( collided )
		{
			text->color( 255, 0, 0 );
			text->drawText( "A �� B ������ײ" );
		}
		else
		{
			text->color( 0, 255, 0 );
			text->drawText( "A �� B û����ײ" );
		}

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseTexture( texture );  // �ͷ��������
	scene->releaseActor( a );           // �ͷ��������
	scene->releaseActor( b );
	scene->releaseActor( plane );
	engine->releaseScene( scene );      // �ͷ�����������
	engine->releaseText( text );        // �ͷ����ֶ���
	engine->releaseCamera( camera );    // �ͷ����������

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );
	
	return 0;
}