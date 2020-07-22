#version 330 core

out vec4 fragColor;

struct Material {
	sampler2D texture_diffuse1;
};

struct DirectionalLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Pointlight {
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

in vec3 fragPos;
in vec2 fragTextureCoords;
in vec3 fragNormals;
in vec3 cameraPosition;

uniform Material material;
uniform NumberOfLights numberOfLights;
uniform Pointlight pointLight[20];
uniform SpotLight spotLight[20];
uniform DirectionalLight directionalLight;

vec3 calculateDirectionalLight(DirectionalLight directionalLight) {
	vec3 ambient = directionalLight.ambient * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 lightDir = normalize(-directionalLight.direction);
	vec3 norm = normalize(fragNormals);

	vec3 toCameraVector = normalize(cameraPosition - fragPos);
	float flipDot = dot(toCameraVector, norm);
	if (flipDot < 0.0f) {
		norm = -norm;
	}

	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuse = directionalLight.diffuse * diff * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	return ambient + diffuse;
}
vec3 calculatePointLight(Pointlight pointLight) {
	vec3 ambient = pointLight.ambient * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 norm = normalize(fragNormals);
	vec3 lightDir = normalize(pointLight.position - fragPos);

	vec3 toCameraVector = normalize(cameraPosition - fragPos);
	float flipDot = dot(toCameraVector, norm);
	if (flipDot < 0.0f) {
		norm = -norm;
	}

	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = pointLight.diffuse * diff * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	float distance = length(pointLight.position - fragPos);
	float attenuation = 1.0 / (pointLight.constantValue + pointLight.linearValue * distance + pointLight.quadraticValue * distance * distance);

	ambient *= attenuation;
	diffuse *= attenuation;

	return ambient + diffuse;
}
vec3 calculateSpotLight(SpotLight spotLight) {
	vec3 ambient = spotLight.ambient * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 norm = normalize(fragNormals);
	vec3 lightDir = normalize(spotLight.position - fragPos);

	vec3 toCameraVector = normalize(cameraPosition - fragPos);
	float flipDot = dot(toCameraVector, norm);
	if (flipDot < 0.0f) {
		norm = -norm;
	}

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	float theta = dot(normalize(spotLight.direction), normalize(fragPos - spotLight.position));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;

	float distance = length(spotLight.position - fragPos);
	float attenuation = 1.0 / (spotLight.constantValue + spotLight.linearValue * distance + spotLight.quadraticValue * distance * distance);
	ambient *= attenuation;
	diffuse *= attenuation;

	return ambient + diffuse;
}

void main() {
	vec4 color = texture(material.texture_diffuse1, fragTextureCoords);
	if (color.a < 0.5) {
		discard;
	}

	vec3 result = calculateDirectionalLight(directionalLight);

	for (int i = 0; i < numberOfLights.numberOfPointLights; i++) {
		result += calculatePointLight(pointLight[i]);
	}

	for (int i = 0; i < numberOfLights.numberOfSpotLights; i++) {
		result += calculateSpotLight(spotLight[i]);
	}

	fragColor = vec4(result, 1.0f);
}