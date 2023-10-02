#include "OpenGL.h"

#include <GL/glew.h>
#include <iostream>

namespace dra {
	bool OpenGL::Initialize() {
		if (glewInit() != GLEW_OK) {
			std::cout << "Error!" << std::endl;
			return false;
		}
		return true;
	}

}