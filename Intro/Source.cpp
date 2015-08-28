#include "stdio.h"
#include <gl_core_4_4.h> 
#include <GLFW/glfw3.h> 
int main()
{
	if (glfwInit() == false)
		return -1;
	GLFWwindow * window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
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

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf_s("GL: %i.%i\n", major, minor);

	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// our game logic and update code goes here!
		// so does our render code!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// the rest of our code goes here!
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}