#include <engine/mesh.h>
#include <engine/objloader.h>
Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

bool Mesh::loadObj(std::string filePath)
{
	bool succes = false;
	meshData = ObjLoader::loadOBJ(filePath.c_str(), succes);
	return succes;

}