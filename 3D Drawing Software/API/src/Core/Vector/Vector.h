#pragma once

#include <memory>
#include <concepts>
#include <cmath>

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


		T norm() const {
			return std::sqrt(arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2]);
		}

		float length() {
			return std::sqrt(arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2]);
		}

		Vector<T> normalized() const {
			T len = norm();
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

		Vector& operator=(const Vector& v) {
			if (this != &v) {
				arr[0] = v.arr[0];
				arr[1] = v.arr[1];
				arr[2] = v.arr[2];
			}
			return *this;
		}

		struct Quaternion {
			T w, x, y, z;
		};

		Quaternion ToQuaternion() const {
			T cy = std::cos(arr[2] * 0.5);
			T sy = std::sin(arr[2] * 0.5);
			T cp = std::cos(arr[1] * 0.5);
			T sp = std::sin(arr[1] * 0.5);
			T cr = std::cos(arr[0] * 0.5);
			T sr = std::sin(arr[0] * 0.5);

			Quaternion q;
			q.w = cr * cp * cy + sr * sp * sy;
			q.x = sr * cp * cy - cr * sp * sy;
			q.y = cr * sp * cy + sr * cp * sy;
			q.z = cr * cp * sy - sr * sp * cy;

			return q;
		}
		
	private:
		std::array<T, 3> arr;

		};
	}


