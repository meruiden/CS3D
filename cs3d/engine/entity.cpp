#include <engine/entity.h>
#include <engine/scene.h>

Entity::Entity()
{
	this->mesh = NULL;
	this->material = NULL;
	this->position = glm::vec3();
	this->scale = glm::vec3(1, 1, 1);
	this->rotation = glm::vec3();
	this->defaultMaterial = new DefaultMaterial();
}

Entity::~Entity()
{
	if (mesh != NULL)
	{
		delete mesh;
	}

	delete defaultMaterial;
}

void Entity::update(float deltaTime)
{
}

void Entity::setMesh(Mesh * mesh)
{
	this->mesh = mesh;
}

void Entity::setAndLoadMesh(std::string filePath)
{
	if (mesh != NULL)
	{
		delete mesh;
	}

	mesh = new Mesh();
	mesh->loadObj(filePath);
}

void Entity::setMaterial(Material * material)
{
	this->material = material;
}
