

// 脚本主函数
int main()
{
    LightImage   image;
    LightInput   input;
    LightMesh    mesh;
    LightCamera  camera;
    LightText    text;
    uint image_handle, input_handle, mesh_handle, camera_handle, text_handle;

    // 创建引擎对象
    image_handle   = light_engine.createImage();
    input_handle   = light_engine.createInput();
    mesh_handle    = light_engine.createMesh();
    camera_handle  = light_engine.createCamera();    
    text_handle    = light_engine.createText();
    
    // 将脚本映射到引擎
    image.hook( image_handle );
    input.hook( input_handle );
    mesh.hook( mesh_handle );
    camera.hook( camera_handle );    
    text.hook( text_handle );
    
    // 将图像文件读入内存
    image.load( "..\\resource\\image\\a.bmp" );
    mesh.load( "..\\resource\\mesh\\digger\\digger.3ds" );
    
    // 设置摄像机参数
    camera.lookAt( 0, 50, 250,  0, 50, 0,  0, 1, 0 );

    do
    {
        // 清除屏幕内容
        light_engine.clear( 16640 );
    
        // 显示图像
        //image.draw( 0, 0 );
        //ZeroMemory( &renderDesc, sizeof(renderDesc) );
        LightImageRenderDesc renderDesc;
        renderDesc.flags = 4;
        renderDesc.rotate = 25;
        image.renderDesc( 135, 80, renderDesc );
        
        // 显示静态网格
        //mesh.setPosition( 0, 0, -10 );
        mesh.render();
       
        // 显示提示信息
        text.color( 0, 255, 0 );
        text.setTextPos( 140, 120 );
        text.drawText( "Hello Script World!" );
        
        // 显示光标位置
        POINT point;
        input.getCursorPos( point );
        text.setTextPos( 140, 160 );
        text.drawText( "当前光标位置 " + point.x + "," + point.y );
    
        // 显示提示信息	    
	    text.setTextPos( 250, 245 );
	    text.drawText( "正在执行脚本文件..." );
    
        // 显示帧速（FPS）
	    text.color( 0, 255, 0 );
	    text.setTextPos( 40, 400 );
	    text.drawText( "帧速: " + light_engine.getFramePerSecond() + " 帧/秒" );
		
        light_engine.swapBuffers();    
    }
	// 配送消息
    while( light_engine.dispatchMessage() );

    light_engine.releaseImage( image_handle );
    light_engine.releaseInput( input_handle );
    light_engine.releaseMesh( mesh_handle );
    light_engine.releaseCamera( camera_handle );
    light_engine.releaseText( text_handle );
    
    return 0;
}