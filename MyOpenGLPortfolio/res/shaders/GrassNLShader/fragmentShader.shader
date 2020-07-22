#version 330 core

out vec4 fragColor;

struct Material {
	sampler2D texture_diffuse1;
};

in vec3 fragPos;
in vec2 fragTextureCoords;

uniform Material material;


void main() {
	vec4 color = texture(material.texture_diffuse1, fragTextureCoords);
	if (color.a < 0.5) {
		discard;
	}

	fragColor = color;
}