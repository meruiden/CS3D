#include <engine/scenemanager.h>

std::map<std::string, Scene*> SceneManager::scenes = std::map<std::string, Scene*>();
Scene* SceneManager::currentScene = NULL;
void SceneManager::addScene(std::string sceneName, Scene* scene)
{
	SceneManager::scenes.emplace(sceneName, scene);
}


void SceneManager::loadScene(std::string sceneName)
{

	Scene* scene = NULL;
	
	bool found = false;
	std::map<std::string, Scene*>::iterator sIt = SceneManager::scenes.find(sceneName);
	if (sIt != SceneManager::scenes.end())
	{
		scene = sIt->second;
		SceneManager::currentScene = scene;
	}
	
}
