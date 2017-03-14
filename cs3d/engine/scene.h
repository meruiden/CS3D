#pragma once
#include <algorithm>
#include <stdarg.h>

#include <engine/light.h>
#include <engine/entity.h>
#include <engine/camera.h>
#include <engine/dylibhandle.h>

class DYLIB Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void update(float deltaTime);
	
	void addEntity(Entity* entity);
	void addEntity(std::vector<Entity*> entities);
	void removeEntity(Entity* entity);
	void removeEntity(std::vector<Entity*> entities);
	void addLight(Light* light);
	void addLight(std::vector<Light*> lights);
	void removeLight(Light* light);
	void removeLight(std::vector<Light*> lights);

	std::vector<Entity*> getEntities() { return entities; }
	std::vector<Light*> getLights() { return lights; }

	Camera* getCamera() { return camera; }
private:
	std::vector<Entity*> entities;
	std::vector <Light*> lights;

protected:
	Camera* camera;
};
