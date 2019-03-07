#version 330

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec4 v_normal;
varying vec4 v_light_position;

//uniform sampler2D u_texture;
uniform sampler2D texture;
uniform vec3 u_light_pos;

void main()
{
    vec3 norm = normalize(vec3(v_normal));
    vec3 light_dir = normalize(vec3(u_light_pos) - vec3(v_position));
    float diff = max(dot(norm, light_dir), 0.1) + 0.1;
    gl_FragColor = texture2D(texture, v_tex_coord) * vec4(v_color, 1.0) * diff;
}