#include <engine/material.h>

Material::Material(Shader* shader)
{
	this->shader = shader;
}

Material::Material()
{
	this->shader = NULL;
}


Material::~Material()
{
	std::map<std::string, Texture*>::iterator itt;
	int textureIndex = 0;
	for (itt = textureUniforms.begin(); itt != textureUniforms.end(); itt++)
	{
		GLuint id = glGetUniformLocation(shader->getProgramId(), itt->first.c_str());
		glDeleteTextures(1, &id);
	}
}

void Material::setShader(Shader* shader)
{
	this->shader = shader;
}

void Material::passToShader()
{
	std::map<std::string, glm::vec3*>::iterator itv3;
	for (itv3 = vec3Uniforms.begin(); itv3 != vec3Uniforms.end(); itv3++)
	{
		glm::vec3* vec = itv3->second;
		glUniform3f(glGetUniformLocation(shader->getProgramId(), itv3->first.c_str()), vec->x, vec->y, vec->z);
	}

	std::map<std::string, glm::vec4*>::iterator itv4;
	for (itv4 = vec4Uniforms.begin(); itv4 != vec4Uniforms.end(); itv4++)
	{
		glm::vec4* vec = itv4->second;
		glUniform4f(glGetUniformLocation(shader->getProgramId(), itv4->first.c_str()), vec->x, vec->y, vec->z, vec->w);
	}

	std::map<std::string, glm::mat4*>::iterator itm4;
	for (itm4 = mat4Uniforms.begin(); itm4 != mat4Uniforms.end(); itm4++)
	{
		glm::mat4 mat = *itm4->second;
		glUniformMatrix4fv(glGetUniformLocation(shader->getProgramId(), itm4->first.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	std::map<std::string, float*>::iterator itf;
	for (itf = floatUniforms.begin(); itf != floatUniforms.end(); itf++)
	{
		glUniform1f(glGetUniformLocation(shader->getProgramId(), itf->first.c_str()), *itf->second);
	}

	std::map<std::string, int*>::iterator iti;
	for (iti = intUniforms.begin(); iti != intUniforms.end(); iti++)
	{
		glUniform1f(glGetUniformLocation(shader->getProgramId(), iti->first.c_str()), *iti->second);
	}


	std::map<std::string, Texture*>::iterator itt;
	int textureIndex = 0;
	for (itt = textureUniforms.begin(); itt != textureUniforms.end(); itt++)
	{
		glActiveTexture(GL_TEXTURE0 + textureIndex);
		glBindTexture(GL_TEXTURE_2D, itt->second->getTextureBuffer());
		glUniform1i(glGetUniformLocation(shader->getProgramId(), itt->first.c_str()), textureIndex);
		textureIndex++;
	}

}

void Material::addUniform(std::string uniformName, glm::vec4* uniform)
{
	vec4Uniforms.emplace(uniformName, uniform);
}

void Material::addUniform(std::string uniformName, glm::mat4* uniform)
{
	mat4Uniforms.emplace(uniformName, uniform);
}

void Material::addUniform(std::string uniformName, glm::vec3* uniform)
{
	vec3Uniforms.emplace(uniformName, uniform);
}

void Material::addUniform(std::string uniformName, float* uniform)
{
	floatUniforms.emplace(uniformName, uniform);
}

void Material::addUniform(std::string uniformName, int* uniform)
{
	intUniforms.emplace(uniformName, uniform);
}

void Material::addUniform(std::string uniformName, Texture * uniform)
{
	textureUniforms.emplace(uniformName, uniform);
}

void Material::removeVec3Uniform(std::string uniformName)
{
	std::map<std::string, glm::vec3*>::iterator it;
	it = vec3Uniforms.find(uniformName);
	if (it != vec3Uniforms.end())
	{
		vec3Uniforms.erase(it);
	}
}

void Material::removeVec4Uniform(std::string uniformName)
{
	std::map<std::string, glm::vec4*>::iterator it;
	it = vec4Uniforms.find(uniformName);
	if (it != vec4Uniforms.end())
	{
		vec4Uniforms.erase(it);
	}
}

void Material::removeMat4Uniform(std::string uniformName)
{
	std::map<std::string, glm::mat4*>::iterator it;
	it = mat4Uniforms.find(uniformName);
	if (it != mat4Uniforms.end())
	{
		mat4Uniforms.erase(it);
	}
}

void Material::removeFloatUniform(std::string uniformName)
{
	std::map<std::string, float*>::iterator it;
	it = floatUniforms.find(uniformName);
	if (it != floatUniforms.end())
	{
		floatUniforms.erase(it);
	}
}

void Material::removeIntUniform(std::string uniformName)
{
	std::map<std::string, int*>::iterator it;
	it = intUniforms.find(uniformName);
	if (it != intUniforms.end())
	{
		intUniforms.erase(it);
	}
}

void Material::removeTextureUniform(std::string uniformName)
{
	std::map<std::string, Texture*>::iterator it;
	it = textureUniforms.find(uniformName);
	if (it != textureUniforms.end())
	{
		textureUniforms.erase(it);
	}
}
