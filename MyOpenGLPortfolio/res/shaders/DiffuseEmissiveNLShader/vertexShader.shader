#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoords;

out vec3 fragPos;
out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	fragPos = vec3(model * vec4(position, 1.0f));
	fragTextureCoords = texCoords;

	gl_Position = projection * view * model * vec4(position, 1.0f);
}