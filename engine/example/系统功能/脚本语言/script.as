

// �ű�������
int main()
{
    LightImage   image;
    LightInput   input;
    LightMesh    mesh;
    LightCamera  camera;
    LightText    text;
    uint image_handle, input_handle, mesh_handle, camera_handle, text_handle;

    // �����������
    image_handle   = light_engine.createImage();
    input_handle   = light_engine.createInput();
    mesh_handle    = light_engine.createMesh();
    camera_handle  = light_engine.createCamera();    
    text_handle    = light_engine.createText();
    
    // ���ű�ӳ�䵽����
    image.hook( image_handle );
    input.hook( input_handle );
    mesh.hook( mesh_handle );
    camera.hook( camera_handle );    
    text.hook( text_handle );
    
    // ��ͼ���ļ������ڴ�
    image.load( "..\\resource\\image\\a.bmp" );
    mesh.load( "..\\resource\\mesh\\digger\\digger.3ds" );
    
    // �������������
    camera.lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );

    do
    {
        // �����Ļ����
        light_engine.clear( 16640 );
    
        // ��ʾͼ��
        //image.draw( 0, 0 );
        //ZeroMemory( &renderDesc, sizeof(renderDesc) );
        LightImageRenderDesc renderDesc;
        renderDesc.flags = 4;
        renderDesc.rotate = 25;
        image.renderDesc( 135, 80, renderDesc );
        
        // ��ʾ��̬����
        //mesh.setPosition( 0, 0, -10 );
        mesh.render();
       
        // ��ʾ��ʾ��Ϣ
        text.color( 0, 255, 0 );
        text.setTextPos( 140, 120 );
        text.drawText( "Hello Script World!" );
        
        // ��ʾ���λ��
        POINT point;
        input.getCursorPos( point );
        text.setTextPos( 140, 160 );
        text.drawText( "��ǰ���λ�� " + point.x + "," + point.y );
    
        // ��ʾ��ʾ��Ϣ	    
	    text.setTextPos( 250, 245 );
	    text.drawText( "����ִ�нű��ļ�..." );
    
        // ��ʾ֡�٣�FPS��
	    text.color( 0, 255, 0 );
	    text.setTextPos( 40, 400 );
	    text.drawText( "֡��: " + light_engine.getFramePerSecond() + " ֡/��" );
		
        light_engine.swapBuffers();    
    }
	// ������Ϣ
    while( light_engine.dispatchMessage() );

    light_engine.releaseImage( image_handle );
    light_engine.releaseInput( input_handle );
    light_engine.releaseMesh( mesh_handle );
    light_engine.releaseCamera( camera_handle );
    light_engine.releaseText( text_handle );
    
    return 0;
}