#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();
	glm::vec3 position;
	glm::vec3 rotation;
};

