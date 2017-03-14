#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <engine/dylibhandle.h>

class DYLIB Camera
{
public:
	Camera();
	virtual ~Camera();
	glm::vec3 position;
	glm::vec3 rotation;

	glm::mat4 getViewMatrix();
};

