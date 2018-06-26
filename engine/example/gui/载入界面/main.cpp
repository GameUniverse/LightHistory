

#include "main.h"


// �������!��GUI��
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LightEngine *engine;
	LightText *text;	
	CEGUI::Renderer* d_renderer;
	POINT last;
	
	last.x = last.y = 0;

	// ������������ʵ��
	LightEngineDesc engineDesc;
	engineDesc.displayMode.mode           = LIGHT_WINDOW_MODE;  // ������ʾģʽ
	engineDesc.displayMode.window.x       = 200;                // �������Ͻ� x ����
	engineDesc.displayMode.window.y       = 150;                // �������Ͻ� y ����
	engineDesc.displayMode.window.width   = 800;                // ���ڿ��
	engineDesc.displayMode.window.height  = 600;                // ���ڸ߶�
	engine = LightEngineCreate( engineDesc );

	// �رմ�ֱͬ��
	engine->disable( LIGHT_SWAP_INTERVAL );

	// �������ֶ���
	LightTextDesc textDesc;
	text = engine->createText( textDesc );

	// ��ʼ�� GUI ϵͳ	
    d_renderer = new CEGUI::OpenGLRenderer(1024);
    new CEGUI::System(d_renderer);

    // initialise the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
        (CEGUI::System::getSingleton().getResourceProvider());

    rp->setResourceGroupDirectory("schemes", "../example/gui/datafiles/schemes/");
    rp->setResourceGroupDirectory("imagesets", "../example/gui/datafiles/imagesets/");
    rp->setResourceGroupDirectory("fonts", "../example/gui/datafiles/fonts/");
    rp->setResourceGroupDirectory("layouts", "../example/gui/datafiles/layouts/");
    rp->setResourceGroupDirectory("looknfeels", "../example/gui/datafiles/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", "../example/gui/datafiles/lua_scripts/");
#if defined(CEGUI_WITH_XERCES) && (CEGUI_DEFAULT_XMLPARSER == XercesParser)
    rp->setResourceGroupDirectory("schemas", "../example/gui/XMLRefSchema/");
#endif

	// ����ʹ�õ�ȱʡ��Դ��
	// set the default resource groups to be used
    CEGUI::Imageset::setDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
#ifdef CEGUI_WITH_XERCES
    CEGUI::XercesParser::setSchemaDefaultResourceGroup("schemas");
#endif

	// ���� GUI �ؼ�
	using namespace CEGUI;

    // Get window manager which we wil use for a few jobs here.
    WindowManager& winMgr = WindowManager::getSingleton();
    // Load the scheme to initialse the VanillaSkin which we use in this sample
    SchemeManager::getSingleton().loadScheme("VanillaSkin.scheme");
    // set default mouse image
    System::getSingleton().setDefaultMouseCursor("Vanilla-Images", "MouseArrow");

    // load an image to use as a background
    ImagesetManager::getSingleton().createImagesetFromImageFile("BackgroundImage", "GPN-2000-001437.tga");

    // here we will use a StaticImage as the root, then we can use it to place a background image
    Window* background = winMgr.createWindow("Vanilla/StaticImage");
    // set area rectangle
    background->setArea(URect(cegui_reldim(0), cegui_reldim(0), cegui_reldim(1), cegui_reldim(1)));
    // disable frame and standard background
    background->setProperty("FrameEnabled", "false");
    background->setProperty("BackgroundEnabled", "false");
    // set the background image
    background->setProperty("Image", "set:BackgroundImage image:full_image");
    // install this as the root GUI sheet
    System::getSingleton().setGUISheet(background);

    FontManager::getSingleton().createFont("simsun.font");

    // load some demo windows and attach to the background 'root'
    background->addChildWindow(winMgr.loadWindowLayout("menu.layout"));

    // create an instance of the console class.
    //d_console = new DemoConsole("Demo");

    // listen for key presses on the root window.
    //background->subscribeEvent(Window::EventKeyDown, Event::Subscriber(&FalagardDemo1Sample::handleRootKeyDown, this));

    // activate the background window
    background->activate();

	// ע�ᴰ����Ϣ��������
	engine->registerMessageProc( &CEGUIWindowMessageProc );

	do
	{
		// �����Ļ����
		engine->clear( LIGHT_COLOR_BUFFER_BIT | LIGHT_DEPTH_BUFFER_BIT );

		// ��ʾͼ��
		//image.Draw( 50, 50 );

		// ��ʾ GUI
		CEGUI::System& guiSystem = CEGUI::System::getSingleton();
		// inject the time pulse
		//guiSystem.injectTimePulse(elapsed / 1000.0f);
		
		// ��ʾ GUI
		guiSystem.renderGUI();

		// ��ʾ֡�٣�FPS��
		char fps[100];
		sprintf( fps, "֡��: %d ֡/��", engine->getFramePerSecond() );
		text->color( 0, 255, 0 );
		text->setTextPos( 30, 530 );
		text->drawText( fps );
        
		// ������ʾ
		engine->swapBuffers();
	}
	// ������Ϣ
	while( engine->dispatchMessage() );

	// ע��������Ϣ��������
	engine->removeMessageProc( &CEGUIWindowMessageProc );

	// ��� GUI ϵͳ
	delete CEGUI::System::getSingletonPtr();
    delete d_renderer;

	// �ͷ�����ʵ��
	engine->releaseText( text );

	// �ͷŹ�������ʵ��
	LightEngineRelease( engine );

	return 0;
}