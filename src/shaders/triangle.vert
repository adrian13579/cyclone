#version 330 core

layout(location = 0) in vec3 Position;

uniform float scale;
uniform mat4 translation;

void main() {
    gl_Position = translation *vec4( scale* Position.x, Position.y, Position.z, 1.0);
}
