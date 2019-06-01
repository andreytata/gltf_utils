#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec4 v_color;

//! [0]
void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(texture, v_texcoord);
    //gl_FragColor = (v_color.rgbr + texture2D(texture, v_texcoord))/2.0; // (1,0,0,0.5) ; //(v_normal.x, v_normal.y, v_normal.z ) ;
}
//! [0]

