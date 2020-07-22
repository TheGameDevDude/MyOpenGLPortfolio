#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constantValue;
	float linearValue;
	float quadraticValue;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constantValue;
	float linearValue;
	float quadraticValue;
};

struct NumberOfLights {
	int numberOfPointLights;
	int numberOfSpotLights;
};

out VS_OUT{
	vec3 cameraPosition_tangent;
	vec3 fragPosition_tangent;
} vs_out;

out vec3 fragPos;
out vec2 fragTextureCoords;
out vec3 fragNormals;
out vec3 camaraPosition;
out vec3 directionalLightPosition_tangent;
out vec3 pointLightPositionTangent[6];
out vec3 spotLightPositionTangent[6];
out vec3 spotLightDirectionTangent[6];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform PointLight pointLight[6];
uniform SpotLight spotLight[6];
uniform DirectionalLight directionalLight;
uniform NumberOfLights numberOfLights;

void main() {
	fragPos = vec3(model * vec4(position, 1.0f));
	fragTextureCoords = texCoords;
	fragNormals = mat3(transpose(inverse(model))) * normals;
	camaraPosition = vec3(inverse(view) * vec4(0, 0, 0, 1.0f));

	vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(normals, 0.0)));
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	mat3 TBN = transpose(mat3(T, B, N));
	
	vs_out.cameraPosition_tangent = TBN * camaraPosition;
	vs_out.fragPosition_tangent = TBN * fragPos;

	directionalLightPosition_tangent = TBN * directionalLight.direction;

	for (int i = 0; i < numberOfLights.numberOfPointLights; i++) {
		pointLightPositionTangent[i] = TBN * pointLight[i].position;
	}

	for (int i = 0; i < numberOfLights.numberOfSpotLights; i++) {
		spotLightPositionTangent[i] = TBN * spotLight[i].position;
		spotLightDirectionTangent[i] = TBN * spotLight[i].direction;
	}

	gl_Position = projection * view * model * vec4(position, 1.0f);
}