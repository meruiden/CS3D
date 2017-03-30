#version 330 core

#define MAX_POINT_LIGHTS 50

struct PointLight {
    vec3 position;
	vec3 color;
	float brightness;
};

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 FragPos;
in vec3 normalModelSpace;

// Values that stay constant for the whole mesh.
uniform sampler2D mainTexture;
uniform float alpha;
uniform vec3 viewPos;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numLights;
uniform float specular;

out vec4 color;

void main(){
	vec3 norm = normalize(normalModelSpace);
	 
	vec3 ambient = vec3(0.1, 0.1, 0.1) ;

	vec3 result = ambient;
	vec3 spec = vec3(0,0,0);
	for(int i = 0; i < numLights; i++){
		PointLight light = pointLights[i];
		vec3 lightVec = normalize(light.position - FragPos);
		float nDotl = dot(norm, lightVec);
		float brightness = max(nDotl , 0.0);
		
		result += (brightness * light.color) * light.brightness * ambient;
		
		vec3 cameraVec = normalize(light.position - viewPos);
		vec3 reflectedLightDir = reflect(lightVec, norm);
		
		float specFactor = dot(reflectedLightDir, cameraVec);
		specFactor = max(specFactor, 0.0);
		float damped = pow(specFactor, 10);
		
		spec += (damped * specular) * ambient;
	}

	color = vec4(result, 1) * texture(mainTexture, UV) + vec4(spec, 1);
}
