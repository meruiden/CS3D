#include <engine/resourcemanager.h>

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	std::map<std::string, GLuint>::iterator itt;
	int textureIndex = 0;
	for (itt = loadedTextures.begin(); itt != loadedTextures.end(); itt++)
	{
		glDeleteTextures(1, &itt->second);
	}
}

GLuint ResourceManager::getTexture(std::string filePath, bool& succes)
{
	succes = false;
	std::map<std::string, GLuint>::iterator it;
	it = loadedTextures.find(filePath);
	if (it == loadedTextures.end())
	{
		return -1;
	}
	else
	{
		succes = true;
		return it->second;
	}

}

GLuint ResourceManager::getShader(std::string vtShader, std::string fragShader, bool& succes)
{
	std::string shaderKey = vtShader + "," + fragShader;
	succes = false;
	std::map<std::string, GLuint>::iterator it;
	it = loadedShaders.find(shaderKey);
	if (it == loadedShaders.end())
	{
		return -1;
	}
	else
	{
		succes = true;
		return it->second;
	}
}

MeshData ResourceManager::getMeshData(std::string filePath, bool& succes)
{
	succes = false;
	std::map<std::string, MeshData>::iterator it;

	it = loadedMeshes.find(filePath);
	if (it == loadedMeshes.end())
	{
		return MeshData();
	}
	else
	{
		succes = true;
		return it->second;
	}
}

void ResourceManager::addTexture(GLuint texture, std::string filePath)
{
	loadedTextures.emplace(filePath, texture);
}

void ResourceManager::addShader(GLuint program, std::string vtShader, std::string fragShader)
{
	loadedShaders.emplace((vtShader + "," + fragShader), program);
}

void ResourceManager::addMeshData(MeshData mesh, std::string filePath)
{
	loadedMeshes.emplace(filePath, mesh);
}

ResourceManager * ResourceManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ResourceManager();
	}

	return instance;
}
