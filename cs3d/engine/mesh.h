#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

struct MeshData
{
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint uvBuffer;
	int numVerts;
	MeshData()
	{
		vertexBuffer = -1;
		normalBuffer = -1;
		uvBuffer = -1;
		numVerts = 0;
	}
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	bool loadObj(std::string filePath);

	MeshData getMeshData() { return meshData; }
private:
	MeshData meshData;
};

