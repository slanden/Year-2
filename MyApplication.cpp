#include "MyApplication.h"
#include "Planet.h"
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

#define PI 3.14159265

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
	view = glm::lookAt(vec3(6, 25, 25), vec3(0), vec3(0, 1, 0));
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
	GLfloat fTime = glfwGetTime();


	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	Planet sun, mercury, venus, earth, earthMoon, mars,
		   jupiter, saturn, uranus, neptune, pluto;

	/*
	--volumetric mean radii for solar system objects (kilometers)--
	scale: sun = 

	/radius(km)\			/avg distance from earth(km)\

	sun = 696,000.0					  149,604,618
	mercury = 2439.7				  149,600,000
	venus = 6051.8					  149,600,000
	earth = 6,371.0
	earthMoon = 1737.1					  378,000
	mars = 3389.5					  228,500,000
	jupiter = 69,911				  778,300,000
	saturn = 58,232					1,427,000,000
	uranus = 25,362					2,869,600,000
	neptune = 24,622				4,496,600,000
	pluto = 1185					5,906,350,000

	*/

	sun.position = vec3(-20, 0, 1);
	sun.color = vec4(1.f, 0.45f, 0.25f, .8f);
	sun.radius = 10;

	mercury.position = vec3(-9, 0, 1);
	mercury.color = vec4(1.f, 0.55f, 0.15f, .8f);
	//mercury.radius = 0.0035053161f;
	mercury.radius = 0.035f;

	venus.position = vec3(-8, 0, 1);
	venus.color = vec4(.10f, 0.80f, 0.10f, .8f);
	//venus.radius = 0.0086951149f;
	venus.radius = 0.087f;

	earth.position = vec3(-7, 0, 1);
	earth.color = vec4(0.25f, 0.4f, 0.71f, 1.f);
	//earth.radius = 0.0091537356f;
	earth.radius = 0.092f;

	earthMoon.position = vec3(-6.5, 0, 1);
	earthMoon.color = vec4(0.70f, 0.70f, 0.70f, 1.f);
	earthMoon.radius = 0.025f;
	//earthMoon.radius = 0.0024958333f;

	mars.position = vec3(-5, 0, 1);
	mars.color = vec4(0.80f, 0.5f, 0.15f, 1.f);
	//mars.radius = 0.0048699713f;
	mars.radius = 0.049f;

	jupiter.position = vec3(-3.5, 0, 1);
	jupiter.color = vec4(0.80f, 0.5f, 0.15f, 1.f);
	//jupiter.radius = 0.1004468391f;
	jupiter.radius = 1.004;

	saturn.position = vec3(-1, 0, 1);
	saturn.color = vec4(0.80f, 0.5f, 0.15f, 1.f);
	//saturn.radius = 0.083667f;
	saturn.radius = 0.837f;

	uranus.position = vec3(0.5, 0, 1);
	uranus.color = vec4(0.80f, 0.5f, 0.15f, 1.f);
	//uranus.radius = 0.0364396552f;
	uranus.radius = 0.364f;

	neptune.position = vec3(1, 0, 1);
	neptune.color = vec4(0.80f, 0.5f, 0.15f, 1.f);
	//neptune.radius = 0.0353764368f;
	neptune.radius = 0.354f;
	

	pluto.position = vec3(1.5, 0, 1);
	pluto.color = vec4(0.20f, 0.10f, 0.70f, 1.f);
	//pluto.radius = 0.1017025862f;
	pluto.radius = 0.017f;

	//glm::mat4 otherMat(
	//cos(angle), 0, sin(angle), 0,
	//0, 1, 0, 0,
	//-sin(angle), 0, cos(angle), 0,
	//0, 0, 0, 1);

	//glm::mat4 otherMat(cos(angle,1,
	//					0,0,0,0,
	//					0,0,0,0,
	//					0,0,0,0)

	//std::cout << pos.x << " , " << pos.y << std::endl;
	//std::cout << angle << std::endl;

	//glm::mat4 rot = glm::toMat4(ori);
	//glm::mat4 rot = glm::rotateY()
	//glm::mat4 trans = glm::translate(glm::mat4(1.0f),earth.position);
	//glm::mat4 fmat = trans * rot;

	mercury.OrbitAround(sun, fTime*.35f);
	venus.OrbitAround(sun, fTime*.35f);
	earth.OrbitAround(sun, fTime*.35f);
	earthMoon.OrbitAround(earth, fTime*1.35f);
	mars.OrbitAround(sun, fTime*.35f);
	jupiter.OrbitAround(sun, fTime*.35f);
	saturn.OrbitAround(sun, fTime*.35f);
	uranus.OrbitAround(sun, fTime*.35f);
	neptune.OrbitAround(sun, fTime*.35f);
	pluto.OrbitAround(sun, fTime*.35f);

	Gizmos::addSphere(sun.position, sun.radius, 18, 18, sun.color, &mat4(1));

	Gizmos::addSphere(mercury.position, mercury.radius, 10, 10, mercury.color, &mat4(1));
	Gizmos::addSphere(venus.position, venus.radius, 10, 10, venus.color, &mat4(1));
	Gizmos::addSphere(earth.position, earth.radius, 10, 10, earth.color, &mat4(1));
	Gizmos::addSphere(earthMoon.position, earthMoon.radius, 10, 10, earthMoon.color, &mat4(1));
	Gizmos::addSphere(mars.position, mars.radius, 10, 10, mars.color, &mat4(1));
	Gizmos::addSphere(jupiter.position, jupiter.radius, 10, 10, jupiter.color, &mat4(1));
	Gizmos::addSphere(saturn.position, saturn.radius, 10, 10, saturn.color, &mat4(1));
	Gizmos::addSphere(uranus.position, uranus.radius, 10, 10, uranus.color, &mat4(1));
	//Gizmos::addSphere(neptune.position, neptune.radius, 10, 10, neptune.color, &mat4(1));
	//Gizmos::addSphere(pluto.position, pluto.radius, 10, 10, pluto.color, &mat4(1));


	Gizmos::draw(projection * view);
}

