#version 330 core

out vec4 fragColor;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_emission1;
};

in vec3 fragPos;
in vec2 fragTextureCoords;

uniform Material material;

void main() {
	vec4 result = texture(material.texture_emission1, fragTextureCoords) + texture(material.texture_diffuse1, fragTextureCoords);
	fragColor = result;
}