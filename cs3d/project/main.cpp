#include <engine/renderer.h>
#include <engine/scenemanager.h>
#include <project/mainscene.h>
int main(void)
{
	Renderer* renderer;
	renderer = new Renderer();

	MainScene* mainscene = new MainScene();
	SceneManager::addScene("mainscene", mainscene);
	SceneManager::loadScene("mainscene");

	renderer->run();
	delete renderer;
	delete mainscene;
	return 0;
}