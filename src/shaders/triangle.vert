#version 330 core

layout(location = 0) in vec3 Position;

uniform mat4 transformation;

void main() {
    gl_Position = transformation * vec4( Position.x, Position.y, Position.z, 1.0);
}
