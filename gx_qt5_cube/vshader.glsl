#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 u_jointMatrix[200];

attribute vec4 a_position;
attribute vec4 a_normal;
attribute vec4 a_joint_0;
attribute vec4 a_weight_0;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
varying vec4 v_color;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    v_color = a_normal * 0.5 + 0.5;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
//! [0]
