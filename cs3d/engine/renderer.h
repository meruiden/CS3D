#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <engine/entity.h>
#include <engine/scene.h>
#include <engine/scenemanager.h>
#include <engine/light.h>
#include <engine/texture.h>
#include <engine/material.h>
#include <engine/mesh.h>
#include <engine/input.h>
#include <engine/shader.h>

class Renderer
{
public:
	Renderer(bool autoInit = true);
	~Renderer();

	void createWindow();
	void initGL();

	void renderMesh(Mesh* mesh, glm::mat4 MVP, glm::mat4 model, Material* material, std::vector<Light*> lights, Camera* camera);

	void run();

	static glm::mat4 getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

private:
	void renderLighting(std::vector<Light*> lights, Shader* shader);

	void calculateDeltaTime();
	double deltaTime;
	

	static GLFWwindow* window;

	glm::mat4 Projection;
	GLuint vertexArrayID;
	GLuint shadowFrameBuffer;
	GLuint depthTexture;

	float windowWidth;
	float windowHeight;
};

