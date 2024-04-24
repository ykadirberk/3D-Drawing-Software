#pragma once

#include <memory>

#include "../DLLBuild.h"
#include <array>


namespace dra {
	template<typename T>
	class _API Vector {
	public:
		Vector() {
			arr[0] = 0;
			arr[1] = 0;
			arr[2] = 0;
		}
		Vector(T v) {
			arr[0] = v;
			arr[1] = v;
			arr[2] = v;
		}
		Vector(T x, T y) {
			arr[0] = x;
			arr[1] = y;
			arr[2] = 0;
		}
		Vector(T x, T y, T z) {
			arr[0] = x;
			arr[1] = y;
			arr[2] = z;
		}
		~Vector(){}


		T length() const {
			return std::sqrt(arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2]);
		}

		Vector<T> normalized() const {
			T len = length();
			T a=1, b=0, c=0;
			if (len != 0) {
				a = arr[0]/len;
				b = arr[1] / len;
				c = arr[2] / len;
			}
			return Vector<T>(a, b, c);
		}


		T x() const {
			return arr[0];
		}
		T y() const {
			return arr[1];
		}
		T z() const {
			return arr[2];
		}


		void setx(T x) {
			arr[0] = x;
		}
		void sety(T y) {
			arr[1] = y;
		}
		void setz(T z) {
			arr[2] = z;
		}

		Vector& operator=(Vector v) {
			//v.swap(*this);
			return *this;
		}
		
	private:
		std::array<T, 3> arr;

		};
	}


