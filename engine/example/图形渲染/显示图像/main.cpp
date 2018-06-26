

#include "windows.h"
#include "stdio.h"
#include "..\\..\\..\\include\\light.h"
#pragma comment( lib, "..\\..\\..\\lib\\light.lib" )

// ��ʾͼ����ʾ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightImage *desktop;
	LightImage *image[7];
	LightImage *mask;
	LightText *text;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 640;                // ���ڿ��
	engineDesc.displayMode.window.height  = 480;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

    // ������ʾģʽΪ����ģʽ
	//engine->SetWindowMode(200, 150, 400, 300, 0);

	// ������ֱͬ����ϵͳĬ�ϣ�
	//engine->Enable( LIGHT_SWAP_INTERVAL );
	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �ؼ�ɫ�ֽ�͸��ɫ���йؼ�ɫ�����أ���Ⱦ��ʱ������ȫ͸���ģ���������
	// �����ؼ�ɫ��ͼ��������ļ�������֮ǰ�������ò����ùؼ�ɫ��������֮�����رչؼ�ɫ��
	// �Է�����ͼ�����������ϣ����͸����
	// ÿ��ͼ�������������ò�ͬ�Ĺؼ�ɫ��

	// ���ùؼ�ɫ��ϵͳĬΪ���ùؼ�ɫ��
	engine->enable( LIGHT_KEY_COLOR );
	// ���ùؼ�ɫ��Ĭ��ֵΪ��ɫ 0��0��0 ��	
	engine->setKeyColor( 255, 0, 0 );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ����ͼ�����
	LightImageDesc imageDesc;
	desktop = engine->createImage( imageDesc );
	image[0] = engine->createImage( imageDesc );
	image[1] = engine->createImage( imageDesc );
	image[2] = engine->createImage( imageDesc );
	image[3] = engine->createImage( imageDesc );
	image[4] = engine->createImage( imageDesc );
	image[5] = engine->createImage( imageDesc );
	image[6] = engine->createImage( imageDesc );
	mask = engine->createImage( imageDesc );

	// ��ʹ�ùؼ�ɫ��ͼ���ļ������ڴ�
	image[4]->load("..\\resource\\image\\keycolor.bmp");

	// ��ֹ�ؼ�ɫ
	engine->enable( LIGHT_KEY_COLOR );

	// ��ͼ���ļ������ڴ�
	desktop->load("..\\resource\\image\\sweet_flower.bmp");
	image[0]->load("..\\resource\\image\\a.bmp");
	image[1]->load("..\\resource\\image\\d.bmp");
	image[2]->load("..\\resource\\image\\b.bmp");
	image[3]->load("..\\resource\\image\\c.bmp");	
	image[5]->load("..\\resource\\image\\l.bmp");
	image[6]->load("..\\resource\\image\\g.bmp");
	mask->load("..\\resource\\image\\mask.tga");

	/// ��ʼ��������ȴ��
	float rotate = 0;
	int lasttime = engine->getTickCount();

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾ����
		desktop->render( 0, 0 );

		// ������ʾͼ��
		image[0]->render( 25, 25 );

		// ��תͼ��
		LightImageRenderDesc desc;
		desc.flags = LIGHT_IMAGE_REVERSALX | LIGHT_IMAGE_REVERSALY;
		image[1]->renderDesc( 331, 25, desc );
		
		// ����ͼ��
		desc.flags = LIGHT_IMAGE_DESTRECT;		
		desc.dest_rect.left = 54;
		desc.dest_rect.top = 240;
		desc.dest_rect.right = 150;
		desc.dest_rect.bottom = 336;		
		image[3]->renderDesc( 0, 0, desc );

		// ��ϴ��йؼ�ɫ��͸��ɫ����ͼ��
        desc.flags = LIGHT_IMAGE_BLEND;
		desc.blend = 0.6f;		
		image[2]->renderDesc( 178, 25, desc );
		
		// ��ʾָ�������ͼ��
		desc.flags = LIGHT_IMAGE_SOURRECT;		
		desc.sour_rect.left = 30;
		desc.sour_rect.top = 30;
		desc.sour_rect.right = 90;
		desc.sour_rect.bottom = 90;		
		image[3]->renderDesc( 25, 208, desc );

		// ��ָ��������ʾͼ��
		desc.flags = LIGHT_IMAGE_LIGHTENESS;
		desc.lighteness = 0.5f;		
		image[3]->renderDesc( 484, 25, desc );

		// ��תͼ��
		desc.flags = LIGHT_IMAGE_ROTATE;
		desc.rotate = -16;
		image[5]->renderDesc( 400, 190, desc );

		// �ؼ�ɫ��͸��ɫ��
		// ���ùؼ�ɫ
		engine->enable( LIGHT_KEY_COLOR );
		// ��Ⱦ�ؼ�ɫͼ��		
		image[4]->render( 320, 120 );

		// ��ֹ�ؼ�ɫ
		engine->disable( LIGHT_KEY_COLOR );

#ifdef LIGHT_CORPORATION_EDITION

		// ͼ������
		desc.flags = LIGHT_IMAGE_MASK;
		desc.mask.image = mask;
		image[6]->renderDesc( 180, 190, desc );

		// ͼ����������
		desc.flags = LIGHT_IMAGE_MASK | LIGHT_IMAGE_MASKRECT;
		desc.mask.image = mask;
		desc.mask.rect.left = 0;
		desc.mask.rect.top = 0;
		desc.mask.rect.right = 64;
		desc.mask.rect.bottom = 64;
		image[6]->renderDesc( 90, 125, desc );

		// ������Ӱ
		desc.flags = LIGHT_IMAGE_SECTOR;
		desc.sector.angle = rotate;
		VEC3( desc.sector.shadow_color, 128, 150, 128 );		
		image[1]->renderDesc( 355, 295, desc );

		// ���¼�����ȴ��
		int time = engine->getTickCount();
		if( (time - lasttime) > 16 )
		{
			rotate += ( time - lasttime ) * 0.005f;
			if( rotate > 360.0f )
				rotate = 0.0f;
			lasttime = time;
		}

#endif

		// ��ʾ��ʾ��Ϣ
		text->color( 255, 0, 0 );
		text->setTextPos( 69, 80 );
		text->drawText( "������ʾ" );
		text->setTextPos( 385, 80 );
		text->drawText( "��ת" );
		text->setTextPos( 92, 280 );
		text->drawText( "����" );
		text->setTextPos( 490, 255 );
		text->drawText( "��ת" );
		text->setTextPos( 233, 80 );
		text->drawText( "���" );
		text->setTextPos( 45, 232 );
		text->drawText( "����" );
		text->setTextPos( 535, 80 );
		text->drawText( "����" );
		text->setTextPos( 365, 175 );
		text->drawText( "�ؼ�ɫ" );

#ifdef LIGHT_CORPORATION_EDITION

		text->setTextPos( 185, 205 );
		text->drawText( "��������" );
		text->setTextPos( 290, 265 );
		text->drawText( "ͼ������" );		
		text->setTextPos( 398, 352 );
		text->drawText( "������Ӱ" );

#endif

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 255, 255, 0 );
		text->setTextPos( 40, 400 );
		text->drawText( fps );
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// �ͷŷ���Ķ���
	engine->releaseText( text );      // �ͷ�����ʵ��
	engine->releaseImage( desktop );  // �ͷ�ͼ���ļ�
	engine->releaseImage( image[0] );
	engine->releaseImage( image[1] );
	engine->releaseImage( image[2] );
	engine->releaseImage( image[3] );
	engine->releaseImage( image[4] );
	engine->releaseImage( image[5] );
	engine->releaseImage( image[6] );
	engine->releaseImage( mask );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}
