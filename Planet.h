#pragma once
#include <glm/glm.hpp>
//#include <glm/ext.hpp>
#include <iostream>

class Planet
{
public:

	glm::vec3 center;
	glm::vec3 position;
	glm::vec4 color;
	float radius;

	Planet(glm::vec3 a_center = glm::vec3(0, 0, 0), glm::vec3 a_pos = glm::vec3(0, 0, 0), glm::vec4 a_col = glm::vec4(0, 0, 0, 0), float a_rad = 0) :
		center(a_center), position(a_pos), color(a_col), radius(a_rad) {};

	//make an object orbit around a parent
	void OrbitAround(Planet parent, float time_value)
	{
		//preserve origin
		//glm::vec3 newPos = position;
		position -= parent.position;

		//position.x = parent.radius * cos(time_value);
		//position.z = parent.radius * sin(time_value);

		//calculate distance from parent to child planet
		float dist = sqrt((position.x + radius) - (parent.position.x + parent.radius) *
						  (position.x + radius) - (parent.position.x + parent.radius) +
						  (position.z + radius) - (parent.position.z + parent.radius) *
						  (position.z + radius) - (parent.position.z + parent.radius));

		//rotate around y-axis, at the distance
		position.x = (parent.radius * (parent.radius - dist)) * cos(time_value);
		position.z = (parent.radius * (parent.radius - dist)) * sin(time_value);

		position += parent.position;
	}
};