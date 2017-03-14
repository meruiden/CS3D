#include <engine/scenemanager.h>

SceneManager* SceneManager::instance = NULL;

void SceneManager::addScene(std::string sceneName, Scene* scene)
{
	SceneManager::getInstance()->scenes.emplace(sceneName, scene);
}

SceneManager * SceneManager::getInstance()
{
	if (instance == NULL) {
		instance = new SceneManager();
	}

	return instance;
}


void SceneManager::loadScene(std::string sceneName)
{

	Scene* scene = NULL;
	
	bool found = false;
	std::map<std::string, Scene*>::iterator sIt = SceneManager::getInstance()->scenes.find(sceneName);
	if (sIt != SceneManager::getInstance()->scenes.end())
	{
		scene = sIt->second;
		SceneManager::getInstance()->currentScene = scene;
	}
	
}
