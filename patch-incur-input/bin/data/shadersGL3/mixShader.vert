#version 150

in vec4 position;
in vec4  color;
in vec3  normal;
in vec2 texcoord;

uniform mat4 modelViewProjectionMatrix;

out vec4 v_position;
out vec4    v_color;
out vec3    v_normal;
out vec2 v_texcoord;


uniform mat4 u_modelViewProjectionMatrix;

void main() {
    v_position = position;
    v_color = color;
    v_normal = normal;
    v_texcoord = texcoord;

    gl_Position = modelViewProjectionMatrix * position;

}
