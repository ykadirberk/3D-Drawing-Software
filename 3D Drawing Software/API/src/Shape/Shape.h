#pragma once
#include "../Core/DLLBuild.h"
#include <iostream>

namespace dra {
	class _API Shape {
		public:
			Shape() {}
			virtual ~Shape() { std::cout << "Shape destroyed." << std::endl; }

			virtual void Draw() = 0;
	};
}

