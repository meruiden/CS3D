#pragma once

#include <engine/material.h>
#include <engine/texture.h>

class DefaultMaterial : public Material
{
public:
	DefaultMaterial();
	void setTexture(std::string filePath);
	virtual ~DefaultMaterial();
	float alpha;
	float specular;
private:
	Texture* texture;
	Shader* shader;
};

