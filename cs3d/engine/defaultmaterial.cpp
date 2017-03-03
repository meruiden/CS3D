#include <engine/defaultmaterial.h>

DefaultMaterial::DefaultMaterial() : Material()
{
	shader = new Shader();
	shader->loadShader("shaders/vertex.vert", "shaders/texture.frag");
	this->setShader(shader);
	alpha = 1.0f;
	specular = 0.8f;
	texture = new Texture();
	addUniform("mainTexture", texture);
	addUniform("alpha", &alpha);
	addUniform("specular", &specular);
}

void DefaultMaterial::setTexture(std::string filePath)
{
	texture->loadTexture(filePath);
}

DefaultMaterial::~DefaultMaterial()
{
	delete shader;
	delete texture;
}
