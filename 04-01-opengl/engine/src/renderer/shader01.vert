attribute vec3 a_position;
varying vec4 v_position;

uniform mat4 transform;

void main()
{
    v_position  = transform * vec4(a_position, 1.0);
    //v_position.w = 0.05;
    //v_position  = vec4(a_position, 1.0);
    gl_Position = v_position;
}