#include <engine/scene.h>

Scene::Scene()
{
	camera = new Camera();
}

Scene::~Scene()
{
	delete camera;
}

void Scene::update(float deltaTime)
{
	
}

void Scene::addEntity(Entity * entity)
{
	for (Entity* e : entities)
	{
		if (e == entity)
		{
			return;
		}
	}
	entities.push_back(entity);
}

void Scene::addEntity(std::vector<Entity*> entities)
{
	for (int i = 0; i < entities.size(); i++)
	{
		addEntity(entities[i]);
	}
}

void Scene::removeEntity(Entity * entity)
{
	std::vector<Entity*>::iterator entityIterator = entities.begin();
	while (entityIterator != entities.end())
	{
		if ((*entityIterator) == entity)
		{
			entityIterator = entities.erase(entityIterator);
			return;
		}
		else
		{
			entityIterator++;
		}
	}
}

void Scene::removeEntity(std::vector<Entity*> entities)
{
	for (int i = 0; i < entities.size(); i++)
	{
		removeEntity(entities[i]);
	}
}

void Scene::addLight(Light * light)
{
	for (Light* l : lights)
	{
		if (l == light)
		{
			return;
		}
	}
	lights.push_back(light);
}

void Scene::addLight(std::vector<Light*> lights)
{
	for (int i = 0; i < lights.size(); i++)
	{
		addLight(lights[i]);
	}
}

void Scene::removeLight(Light * light)
{
	std::vector<Light*>::iterator lightIterator = lights.begin();
	while (lightIterator != lights.end())
	{
		if ((*lightIterator) == light)
		{
			lightIterator = lights.erase(lightIterator);
			return;
		}
		else
		{
			lightIterator++;
		}
	}
}

void Scene::removeLight(std::vector<Light*> lights)
{
	for (int i = 0; i < lights.size(); i++)
	{
		removeLight(lights[i]);
	}
}
