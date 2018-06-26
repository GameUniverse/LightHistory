void main( void )
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
        //gl_FrontColor = gl_Color;
	gl_FrontColor = vec4(1.0, 0.5, 0.5, 1.0); // 使图像带暖色调的代码
}
