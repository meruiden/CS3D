#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <map>

#include <glm/glm.hpp>

#include <engine/resourcemanager.h>
#include <engine/mesh.h>
#include <engine/dylibhandle.h>

class DYLIB ObjLoader
{
public:

	static MeshData loadOBJ(std::string filePath, bool &succes);
};


#endif