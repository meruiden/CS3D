#include <stdarg.h>

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include<engine/cs3d.h>

void add_output(const char *format, ...);

class SimpleGL3Window : public Fl_Gl_Window
{
	Renderer* renderer;
	Entity* entity;
	Material* unlit;
	Shader* unlitShader;
	Camera* camera;
	glm::mat4 Projection;
	double deltaTime;

	int gl_version_major;

public:

	SimpleGL3Window(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h)
	{
		mode(FL_RGB8 | FL_DOUBLE | FL_OPENGL3);
		deltaTime = 0;
	}

	~SimpleGL3Window()
	{
		delete camera;
		delete entity;
		delete renderer;
		delete unlit;
		delete unlitShader;
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
        if(firstTime)
            
        {
            firstTime = false;
            init();
        }
		if (!valid())
		{
			valid(1);
			glViewport(0, 0, pixel_w(), pixel_h());

			Projection = glm::perspective(45.0f, (float)pixel_w() / pixel_h(), 0.1f, 2000.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		static float t = 0;
		t += 1.0 * deltaTime;

		glm::mat4 model = Renderer::getModelMatrix(glm::vec3(0), glm::vec3(1), glm::vec3(0, t, t));
		glm::mat4 MVP = Projection * camera->getViewMatrix() * model;

		renderer->renderMesh(entity->getMesh(), MVP, model, entity->getMaterial(), std::vector<Light*>(), camera);
	}
    
    void init(){
        make_current();
        
        renderer = new Renderer(false);
        renderer->initGL();
        
        const uchar *glv = glGetString(GL_VERSION);
        add_output("GL_VERSION=%s\n", glv);
        sscanf((const char *)glv, "%d", &gl_version_major);
        if (gl_version_major < 3) add_output("\nThis platform does not support OpenGL V3\n\n");
        
        entity = new Entity();
        entity->setAndLoadMesh("assets/cube.obj");
        
        unlit = new Material();
        unlitShader = new Shader();
        unlitShader->loadShader("shaders/unlit.vert", "shaders/unlit.frag");
        unlit->setShader(unlitShader);
        entity->setMaterial(unlit);
        camera = new Camera();
        
        camera->rotation += glm::vec3(0, 3.14f, 0);
        camera->position = glm::vec3(0, 0, -7);
    }

};


Fl_Text_Display *output; // shared between output_win() and add_output()

void output_win(SimpleGL3Window *gl)
{
	output = new Fl_Text_Display(900, 0, 500, 800);
	output->buffer(new Fl_Text_Buffer());
}


void add_output(const char *format, ...)
{
	va_list args;
	char line_buffer[10000];
	va_start(args, format);
	vsnprintf(line_buffer, sizeof(line_buffer) - 1, format, args);
	va_end(args);
	output->buffer()->append(line_buffer);
	output->scroll(10000, 0);
	output->redraw();
}


int main(int argc, char **argv)
{
	Fl_Window *topwin = new Fl_Window(1400, 1050);
	SimpleGL3Window *win = new SimpleGL3Window(0, 0, 900, 800);
	win->end();
	output_win(win);
	topwin->end();
	topwin->resizable(win);
	topwin->label("Click GL panel to reshape");
	topwin->show(argc, argv);


	while (topwin->shown())
	{
		Fl::wait(0.0f);
		win->redraw();
	}

	delete topwin;
	delete win;
}