#include "MyApplication.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

int Application::initWindow()
{
	if (glfwInit() == false)
		return -1;
	window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//print OpenGL version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf_s("GL: %i.%i\n", major, minor);

	Gizmos::create();
	view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
}



void Application::update()
{
	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST); //enable the depth buffer

		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int Application::terminate()
{
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void Application::draw()
{
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	vec4 sColor(1.f, 0.45f, 0.25f, .8f);
	vec4 pColor(0.25f, 0.4f, 0.71f, 1.f);

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	Gizmos::addSphere(vec3(0, 0, 0), 5, 18, 18, sColor, &mat4(.5f));

	Gizmos::addSphere(vec3(-4,3,6), .25f, 10, 10, pColor, &mat4(1));
	//Gizmos::addDisk(vec3(10, 10, 10), 5, 4, white, tran);

	Gizmos::draw(projection * view);
}