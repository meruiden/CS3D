#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <engine/material.h>
#include <engine/mesh.h>
#include <engine/defaultmaterial.h>

class Scene;

class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void update(float deltaTime);
	
	void setMesh(Mesh* mesh);
	void setAndLoadMesh(std::string filePath);
	void setMaterial(Material* material);

	Scene* getParentScene() { return parentScene; }
	void setParentScene(Scene* scene) { parentScene = scene; }

	Mesh* getMesh() { return mesh; }
	Material* getMaterial() { return material; }
	DefaultMaterial* getDefaultMaterial() { return defaultMaterial; }

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
private:
	Mesh* mesh;
	Scene* parentScene;
	Material* material;
	DefaultMaterial* defaultMaterial;
};

