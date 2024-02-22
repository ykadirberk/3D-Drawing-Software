#pragma once
#include "../Core/DLLBuild.h"
#include "../Core/Object/Object.h"
#include "../Camera/Camera.h"
#include <iostream>

namespace dra {
	class _API Shape : public Object {
		public:
			Shape() : Object() {}
			Shape(Object* parent) : Object(parent) {}
			virtual ~Shape() { std::cout << "Shape destroyed." << std::endl; }

			virtual void Update() = 0;
			virtual void Draw(Camera* camera) = 0;
	};
}

