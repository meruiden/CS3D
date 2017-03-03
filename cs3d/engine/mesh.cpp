#include <engine/mesh.h>
#include <engine/objloader.h>
Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	glDeleteBuffers(1, &meshData.vertexBuffer);
	glDeleteBuffers(1, &meshData.uvBuffer);
	glDeleteBuffers(1, &meshData.normalBuffer);
}

bool Mesh::loadObj(std::string filePath)
{

	if (meshData.vertexBuffer != -1)
	{
		glDeleteBuffers(1, &meshData.vertexBuffer);
	}
	if (meshData.uvBuffer != -1)
	{
		glDeleteBuffers(1, &meshData.uvBuffer);
	}
	if (meshData.normalBuffer != -1)
	{
		glDeleteBuffers(1, &meshData.normalBuffer);
	}

	bool succes = false;
	meshData = ObjLoader::loadOBJ(filePath.c_str(), succes);
	return succes;

}