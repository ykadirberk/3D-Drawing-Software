#include "Line.h"
#include <iostream>


namespace dra {
	Line::Line() {
		std::cout << "Line is created." << std::endl;
	}

	Line::~Line() {
		std::cout << "Line is destroyed." << std::endl;
	}

	void Line::Draw() {
		std::cout << "Line Draw() is called." << std::endl;
	}
}