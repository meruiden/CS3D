#include <stdarg.h>
#include <sstream>

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/fl_ask.H>

#include<engine/cs3d.h>

void add_output(std::string text);

class SimpleGL3Window : public Fl_Gl_Window
{
	Renderer* renderer;
	Entity* entity;
	Camera* camera;
	glm::mat4 Projection;
	double deltaTime;

	GLint glMajor;
	GLint glMinor;

	std::vector<Entity*> entities;
	std::vector <Light*> lights;

public:
	bool quit;

	bool validGL() { return (glMajor >= 3 && glMinor >= 3); }
	SimpleGL3Window(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h)
	{
		end();
		mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
		deltaTime = 0;

		quit = false;
	}

	~SimpleGL3Window()
	{
		delete renderer;
		if (!validGL()) { return; }

		delete camera;
		for (int i = 0; i < entities.size(); i++)
		{
			delete entities[i];
		}

		for (int i = 0; i < lights.size(); i++)
		{
			delete lights[i];
		}
	}

	void calculateDeltaTime()
	{
		double milis = CS3DTime::getMiliSeconds() / 1000.0f;

		static double lastTime = milis;
		double startTime = milis;
		deltaTime = startTime - lastTime;
		lastTime = startTime;
	}

	void draw()
	{
		calculateDeltaTime();

		static bool firstTime = true;

		if (firstTime)
		{
			firstTime = false;
			init();
		}

		if (!validGL()) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); return; }

		if (!valid())
		{
			valid(1);
			glViewport(0, 0, pixel_w(), pixel_h());

			Projection = glm::perspective(45.0f, (float)pixel_w() / pixel_h(), 0.1f, 2000.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < entities.size(); i++)
		{
			Entity* e = entities[i];
			glm::mat4 model = Renderer::getModelMatrix(e->position, e->scale, e->rotation);
			glm::mat4 MVP = Projection * camera->getViewMatrix() * model;

			renderer->renderMesh(entity->getMesh(), MVP, model, entity->getMaterial(), lights, camera);
		}

		entity->rotation += glm::vec3(0, 0, deltaTime);
	}

	void init()
	{
		make_current();

		renderer = new Renderer(false);
		renderer->initGL();


		glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
		glGetIntegerv(GL_MINOR_VERSION, &glMinor);

		std::stringstream glVersionString;
		glVersionString << (const unsigned char*)glGetString(GL_VERSION);
		glVersionString << "\n" << (const unsigned char*)glGetString(GL_RENDERER);

		add_output(glVersionString.str());

		if (!validGL())
		{
			std::stringstream message;
			message << "OpenGL version: " << glMajor << "." << glMinor << " is not supported. Minimum is: 3.3.\nTry updating your videocard drivers.";
			fl_alert(message.str().c_str());
			quit = true;
			return;
		}

		entity = new Entity();
		entity->setAndLoadMesh("assets/dragon.obj");
		entities.push_back(entity);

		Light* l = new Light();
		entity->getDefaultMaterial()->specular = 2;
		l->position = glm::vec3(-4, 0, 3);
		entity->position = glm::vec3(2, 0, -3);
		lights.push_back(l);
		l->brightness = 10;

		entity->getDefaultMaterial()->setTexture("assets/white.png");

		camera = new Camera();

		camera->rotation += glm::vec3(0, 0, 0);
		camera->position = glm::vec3(0, 5, 14);

	}

};

Fl_Text_Display *output;

void output_win(SimpleGL3Window *gl)
{
	output = new Fl_Text_Display(900, 0, 500, 800);
	output->buffer(new Fl_Text_Buffer());
}


void add_output(std::string text)
{

	output->buffer()->append((text + "\n").c_str());
	output->scroll(10000, 0);
	output->redraw();
}


int main(int argc, char **argv)
{
	Fl_Window *topwin = new Fl_Window(1400, 1050);
	SimpleGL3Window *win = new SimpleGL3Window(0, 0, 900, 800);
	output_win(win);
	topwin->end();
	topwin->resizable(win);
	topwin->label("Click GL panel to reshape");
	topwin->show(argc, argv);


	while (topwin->shown() && !win->quit)
	{
		Fl::wait(0.0f);

		win->redraw();
	}

	delete topwin;
}