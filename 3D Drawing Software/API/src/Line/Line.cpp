#include "Line.h"
#include <iostream>


namespace dra {
	Line::Line() {
		std::cout << "Line is created." << std::endl;
	}

	Line::~Line() {
		std::cout << "Line is destroyed." << std::endl;
	}

	Transform& Line::GetTransform() {
		return m_Transform;
	}

	void Line::Draw() {
		std::cout << "Line Draw() is called." << std::endl;
	}
}