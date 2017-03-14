#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <engine/resourcemanager.h>
#include <engine/dylibhandle.h>

class DYLIB Shader
{
public:
	Shader();
	virtual ~Shader();

	void loadShader(const char * vertex_file_path, const char * fragment_file_path);
	GLuint getProgramId() { return programId; }
private:
	GLuint programId;
};

