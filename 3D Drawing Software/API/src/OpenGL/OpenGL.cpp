#include "OpenGL.h"
#include "../Core/CoreGL.h"

#include <GL/glew.h>
#include <iostream>
 
namespace dra {
	bool OpenGL::Initialize() {
		if (glewInit() != GLEW_OK) {
			std::cout << "Error!" << std::endl;
			return false;
		}

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));

		GLCall(glEnable(GL_CULL_FACE));
		
		return true;
	}

}