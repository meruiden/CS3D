#pragma once

#include <map>
#include <string>

#include <GL/glew.h>

#include <engine/mesh.h>

class ResourceManager
{
public:
	~ResourceManager();

	GLuint getTexture(std::string filePath, bool& succes);
	GLuint getShader(std::string vtShader, std::string fragShader, bool& succes);
	MeshData getMeshData(std::string filePath, bool& succes);

	void addTexture(GLuint texture, std::string filePath);
	void addShader(GLuint program, std::string vtShader, std::string fragShader);
	void addMeshData(MeshData mesh, std::string filePath);
	static ResourceManager* getInstance();
private:
	ResourceManager();
	std::map<std::string, GLuint> loadedTextures;
	std::map<std::string, GLuint> loadedShaders;
	std::map<std::string, MeshData> loadedMeshes;

	static ResourceManager* instance;
};

