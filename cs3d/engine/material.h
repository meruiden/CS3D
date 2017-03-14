#pragma once

#include <map>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <engine/shader.h>
#include <engine/texture.h>
#include <engine/dylibhandle.h>

class DYLIB Material
{
public:
	Material(Shader* shader);
	Material();
	virtual ~Material();

	void setShader(Shader* shader);
	void passToShader();
	Shader* getShader() { return shader; }

	void addUniform(std::string uniformName, glm::vec4* uniform);
	void addUniform(std::string uniformName, glm::mat4* uniform);
	void addUniform(std::string uniformName, glm::vec3* uniform);
	void addUniform(std::string uniformName, float* uniform);
	void addUniform(std::string uniformName, int* uniform);
	void addUniform(std::string uniformName, Texture* uniform);


	void removeVec3Uniform(std::string uniformName);
	void removeVec4Uniform(std::string uniformName);
	void removeMat4Uniform(std::string uniformName);
	void removeFloatUniform(std::string uniformName);
	void removeIntUniform(std::string uniformName);
	void removeTextureUniform(std::string uniformName);

protected:
	Shader* shader;

private:
	std::map<std::string, glm::vec3*> vec3Uniforms;
	std::map<std::string, glm::vec4*> vec4Uniforms;
	std::map<std::string, glm::mat4*> mat4Uniforms;
	std::map<std::string, float*> floatUniforms;
	std::map<std::string, int*> intUniforms;
	std::map<std::string, Texture*> textureUniforms;
};

