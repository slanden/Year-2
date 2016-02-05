#pragma once
#include "stdio.h"
#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gl_core_4_4.h>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Application
{
public:
	int initWindow();
	void update();
	int terminate();

	void draw();

	GLFWwindow *window;

	glm::mat4 view;
	glm::mat4 projection;

};