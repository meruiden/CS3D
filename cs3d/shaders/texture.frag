#version 330 core

precision highp float;

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
	 
	vec3 ambient = vec3(0.05, 0.05, 0.05);
	
	vec4 tex = texture(mainTexture, UV);
	
	vec4 result = vec4(tex.rgb * ambient, tex.a);
	
	for(int i = 0; i < numLights; i++){
		vec3 norm = normalize(normalModelSpace);
		vec3 lightDir = normalize(pointLights[i].position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * pointLights[i].brightness * pointLights[i].color;
		
		float specularStrength = specular;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * pointLights[i].brightness * pointLights[i].color;
		
		float distanceToLight = length(pointLights[i].position - FragPos);
		
		float attenuation = 1.0 / (1.1 * pow(distanceToLight, 2));
		
		result += vec4(tex.rgb * (ambient + attenuation *( diffuse + specular)), tex.a);
	}

	color = result;
}
