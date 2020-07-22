#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;
layout(location = 5) in mat4 instanceMatrix;

out vec3 fragPos;
out vec2 fragTextureCoords;
out vec3 fragNormals;
out vec3 cameraPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	fragPos = vec3(instanceMatrix * vec4(position, 1.0f));
	fragTextureCoords = texCoords;
	fragNormals = mat3(transpose(inverse(instanceMatrix))) * normals;
	cameraPosition = vec3(inverse(view) * vec4(0, 0, 0, 1.0f));

	gl_Position = projection * view * instanceMatrix * vec4(position, 1.0f);
}