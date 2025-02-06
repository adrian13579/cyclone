#version 330 core

layout(location = 0) in vec3 Position;

uniform float scale;

void main() {
    gl_Position = vec4( scale * Position.x, scale * Position.y, scale * Position.z, 1.0);
}
