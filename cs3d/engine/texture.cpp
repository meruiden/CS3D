#include "texture.h"



Texture::Texture()
{
	textureBuffer = -1;
}


Texture::~Texture()
{
}

void Texture::loadTexture(std::string imagePath)
{
	bool succes = false;
	this->textureBuffer = ResourceManager::getInstance()->getTexture(imagePath, succes);
	if (succes)
	{
		return;
	}
	glEnable(GL_TEXTURE_2D);

	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	int width;
	int height;
	unsigned char* image = SOIL_load_image(imagePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);


	std::cout << "Width: " << width << ", Height: " << height << std::endl;
	std::cout << "Image ID: " << texture_id << std::endl;

	SOIL_free_image_data(image);

	if (texture_id == -1)
	{
		std::cout << "Failed loading: " << imagePath << std::endl;
	}
	
	textureBuffer = texture_id;
	ResourceManager::getInstance()->addTexture(texture_id, imagePath);
}
