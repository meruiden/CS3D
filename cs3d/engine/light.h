#pragma once

#include <engine/entity.h>

class Light : Entity
{
public:
	Light();
	virtual ~Light();
	
	glm::vec3 position;
	glm::vec3 color;
	float brightness;
};

