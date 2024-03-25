#pragma once

#include <memory>

#include "../DLLBuild.h"


namespace dra {
	class _API Vector {
	public:
		Vector();
		Vector(float v);
		Vector(float x, float y);
		Vector(float x, float y, float z);
		~Vector();


		float x();
		float y();
		float z();
		
	private:
		float pos_x, pos_y, pos_z;

		};
	}


