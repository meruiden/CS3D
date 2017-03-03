#include <engine/light.h>

Light::Light()
{
	brightness = 2.0f;
	color = glm::vec3(1, 1, 1);
}


Light::~Light()
{
}
