uniform sampler2D testTexture;

void main( void )
{
    // NOTE:
    //
    // The gl_Color variable used here is not the same one used in the vertex 
    // shader. Each shader gets it own.
    //
    // For a fragment shader, the values in gl_Color and gl_SecondaryColor 
    // will be derived automatically by the system from gl_FrontColor, 
    // gl_BackColor, gl_FrontSecondaryColor, and gl_BackSecondaryColor based 
    // on which face is visible.

	gl_FragColor = texture2D( testTexture, gl_TexCoord[0] ) * gl_Color; // Modulate texel color with vertex color
	//gl_FragColor = texture2D( testTexture, gl_TexCoord[0].xy ) + gl_Color; // Add texel color to vertex color
}
