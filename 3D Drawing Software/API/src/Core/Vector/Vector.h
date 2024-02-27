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


		float x() const;
		float y() const;
		float z() const;


		void setx(float x);
		void sety(float y);
		void setz(float z);
		
	private:
		float pos_x, pos_y, pos_z;

		};
	}


