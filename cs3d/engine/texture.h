#pragma once
#include <string>
#include <iostream>
#include <SOIL.h>
#include <GL/glew.h>

#include <engine/resourcemanager.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();

	void loadTexture(std::string imagePath);
	GLuint getTextureBuffer() { return textureBuffer; }
private:
	GLuint textureBuffer;
};

