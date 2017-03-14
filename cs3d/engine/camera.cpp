#include "camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	float halfPI = 1.57079632679f;
	glm::vec3 direction = glm::vec3(
		cos(rotation.x) * sin(rotation.y + 3.14159265359f),
		sin(rotation.x),
		cos(rotation.x) * cos(rotation.y + 3.14159265359f)
	);
	
	glm::vec3 right = glm::vec3(
		sin(rotation.y + 3.14159265359f - halfPI),
		0,
		cos(rotation.y + 3.14159265359f - halfPI)
	);
	right = glm::rotateZ(right, rotation.z*57.2957795f );

	glm::vec3 up = glm::cross(right, direction);

	glm::vec3 pos = glm::vec3(position.x, position.y, position.z);

	return glm::lookAt(
		pos,
		pos + direction,
		up
	);
}
