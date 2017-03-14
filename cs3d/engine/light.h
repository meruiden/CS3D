#pragma once

#include <engine/entity.h>
#include <engine/dylibhandle.h>

class DYLIB Light : Entity
{
public:
	Light();
	virtual ~Light();
	float intensity;
	
	glm::vec3 position;
	glm::vec3 color;
	float brightness;
};

