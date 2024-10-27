#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>

class Object {
	public:

		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);


};

#endif