#include <editor/editorrenderer.h>


int main(int argc, char **argv)
{
	EditorRenderer* renderer = new EditorRenderer();

	renderer->run();

	delete renderer;
	return 0;
}