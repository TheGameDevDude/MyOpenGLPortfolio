#version 330 core

out vec4 fragColor;

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	float shininess;
};

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

in VS_OUT{
	vec3 cameraPosition_tangent;
	vec3 fragPosition_tangent;
} vs_in;

in vec3 fragPos;
in vec2 fragTextureCoords;
in vec3 fragNormals;
in vec3 camaraPosition;

in vec3 directionalLightPosition_tangent;
in vec3 pointLightPositionTangent[6];
in vec3 spotLightPositionTangent[6];
in vec3 spotLightDirectionTangent[6];

uniform PointLight pointLight[6];
uniform SpotLight spotLight[6];
uniform DirectionalLight directionalLight;
uniform NumberOfLights numberOfLights;

uniform Material material;

vec3 calculateDirectionalLight(DirectionalLight directionalLight) {
	vec3 ambient = directionalLight.ambient * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 normal = texture(material.texture_normal1, fragTextureCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = directionalLight.diffuse * diff * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 toCamaraVector = normalize(vs_in.cameraPosition_tangent - vs_in.fragPosition_tangent);
	vec3 reflectedLight = reflect(-lightDir, normal);
	float spec = pow(max(dot(toCamaraVector, reflectedLight), 0.0f), material.shininess);
	vec3 specular = directionalLight.specular * spec * texture(material.texture_specular1, fragTextureCoords).rgb;

	return ambient + diffuse + specular;
}
vec3 calculatePointLight(PointLight pointLight) {
	vec3 ambient = pointLight.ambient * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 normal = texture(material.texture_normal1, fragTextureCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 lightDir = normalize(pointLight.position - vs_in.fragPosition_tangent);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = pointLight.diffuse * diff * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 toCamaraVector = normalize(vs_in.cameraPosition_tangent - vs_in.fragPosition_tangent);
	vec3 reflectedLight = reflect(-lightDir, normal);
	float spec = pow(max(dot(toCamaraVector, reflectedLight), 0.0f), material.shininess);
	vec3 specular = pointLight.specular * spec * texture(material.texture_specular1, fragTextureCoords).rgb;

	float distance = length(pointLight.position - vs_in.fragPosition_tangent);
	float attenuation = 1.0 / (pointLight.constantValue + pointLight.linearValue * distance + pointLight.quadraticValue * distance * distance);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}
vec3 calculateSpotLight(SpotLight spotLight) {
	vec3 ambient = spotLight.ambient * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 normal = texture(material.texture_normal1, fragTextureCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 lightDir = normalize(spotLight.position - vs_in.fragPosition_tangent);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = spotLight.diffuse * diff * texture(material.texture_diffuse1, fragTextureCoords).rgb;

	vec3 toCamaraVector = normalize(vs_in.cameraPosition_tangent - vs_in.fragPosition_tangent);
	vec3 reflectedLight = reflect(-lightDir, normal);
	float spec = pow(max(dot(toCamaraVector, reflectedLight), 0.0), material.shininess);
	vec3 specular = spotLight.specular * spec * texture(material.texture_specular1, fragTextureCoords).rgb;

	float theta = dot(normalize(spotLight.direction), normalize(vs_in.fragPosition_tangent - spotLight.position));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	float distance = length(spotLight.position - vs_in.fragPosition_tangent);
	float attenuation = 1.0 / (spotLight.constantValue + spotLight.linearValue * distance + spotLight.quadraticValue * distance * distance);
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

void main() {
	DirectionalLight directionalLight_tangent;
	directionalLight_tangent.direction = directionalLightPosition_tangent;
	directionalLight_tangent.ambient = directionalLight.ambient;
	directionalLight_tangent.diffuse = directionalLight.diffuse;
	directionalLight_tangent.specular = directionalLight.specular;

	vec3 result = calculateDirectionalLight(directionalLight_tangent);

	for (int i = 0; i < numberOfLights.numberOfPointLights; i++) {
		PointLight pointLight_tangent = pointLight[i];
		pointLight_tangent.position = pointLightPositionTangent[i];
		result += calculatePointLight(pointLight_tangent);
	}

	for (int i = 0; i < numberOfLights.numberOfSpotLights; i++) {
		SpotLight spotLight_tangent = spotLight[i];
		spotLight_tangent.position = spotLightPositionTangent[i];
		spotLight_tangent.direction = spotLightDirectionTangent[i];
		result += calculateSpotLight(spotLight_tangent);
	}

	fragColor = vec4(result, 1.0f);
}