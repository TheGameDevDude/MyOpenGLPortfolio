#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoords;
layout(location = 5) in mat4 instanceMatrix;

out vec3 fragPos;
out vec2 fragTextureCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	fragPos = vec3(instanceMatrix * vec4(position, 1.0f));
	fragTextureCoords = texCoords;

	gl_Position = projection * view * instanceMatrix * vec4(position, 1.0f);
}