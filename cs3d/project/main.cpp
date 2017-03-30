#include <engine/cs3d.h>
#include <project/mainscene.h>

int main(void)
{
	Renderer* renderer = new Renderer();
	MainScene* mainscene = new MainScene();
	SceneManager::addScene("mainscene", mainscene);
	SceneManager::loadScene("mainscene");

	renderer->run();

	delete mainscene;
	delete renderer;
	return 0;
}
