#pragma once

#include <memory>

#include "../DLLBuild.h"
#include <iostream>
#include <array>
#include <random>
#include <cassert>

#include "../Vector/Vector.h"


namespace dra {
	template<typename T>
	class Matrix4 {

	public:
		std::array<T, 16> data;

		Matrix4() {
			int i = 0;
			while (i < 16) {
				data[i++] = 0;
			}
		
		}

		Matrix4(T v) {
			int i = 0;
			while (i < 16) {
				data[i++] = 0;
			}
			data[0] = v;
			data[5] = v;
			data[10] = v;
			data[15] = v;
		}
		
		Matrix4(std::initializer_list<T> values) {
			int i = 0;
			for (T value : values) {
				if (i < 16) {
					data[i++] = value;
				}
			}
		}

		T* operator[](int row) {
			assert(row >= 0 && row < 4);
			return &data[row * 4];
		}

		/*const T& operator[](int row) const {
			assert(row >= 0 && row < 4);
			return &data[row * 4];
		}*/

		Matrix4<T> operator*(const Matrix4<T>& other) const {
			Matrix4 m;
			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					T elem = 0;
					for (int s = 0; s < 4; ++s) {
						elem += data[getI(s, r)] *
							other.data[getI(c, s)];
					}
					m.data[getI(r, c)] = elem;
				}
			}
			return m;
		}

		Matrix4& operator=(const Matrix4& other) {
			if (this != &other) {
				data = other.data;
			}
			return *this;
		}

		Matrix4<T> Translate(const Matrix4<T>& mat, const Vector<T>& translation) {
			Matrix4<T> identity(1.0f);

			identity.data[12] += translation.x();
			identity.data[13] += translation.y();
			identity.data[14] += translation.z();

			return identity* mat;
		}

		Matrix4<T> Rotate(const Matrix4<T>& mat, T angle, const Vector<T>& axis) {
			T radians = angle * static_cast<T>(3.14 / 180.0);
			T c = cos(radians);
			T s = sin(radians);

			auto normalized_axis = axis.normalized();
			Vector<float> temp = Vector(normalized_axis.x(), normalized_axis.y(), normalized_axis.z());

			Matrix4<T> rotation;
			rotation.data[0] = c + temp.x() * normalized_axis.x();
			rotation.data[1] = temp.x() * normalized_axis.y() + s * normalized_axis.z();
			rotation.data[2] = temp.x() * normalized_axis.z() - s * normalized_axis.y();

			rotation.data[4] = temp.y() * normalized_axis.x() - s * normalized_axis.z();
			rotation.data[5] = c + temp.y() * normalized_axis.y();
			rotation.data[6] = temp.y() * normalized_axis.z() + s * normalized_axis.x();

			rotation.data[8] = temp.z() * normalized_axis.x() + s * normalized_axis.y();
			rotation.data[9] = temp.z() * normalized_axis.y() - s * normalized_axis.x();
			rotation.data[10] = c + temp.z() * normalized_axis.z();

			return mat * rotation;
			/*glm::vec3 a = glm::normalize(axis);
			float s = sin(angle);
			float c = cos(angle);
			float oc = 1.0f - c;

			glm::mat4 rotationMatrix(1.0f); 

			
			rotationMatrix[0] = oc * a.x * a.x + c;
			rotationMatrix[0][1] = oc * a.x * a.y - a.z * s;
			rotationMatrix[0][2] = oc * a.z * a.x + a.y * s;
			rotationMatrix[1][0] = oc * a.x * a.y + a.z * s;
			rotationMatrix[1][1] = oc * a.y * a.y + c;
			rotationMatrix[1][2] = oc * a.y * a.z - a.x * s;
			rotationMatrix[2][0] = oc * a.z * a.x - a.y * s;
			rotationMatrix[2][1] = oc * a.y * a.z + a.x * s;
			rotationMatrix[2][2] = oc * a.z * a.z + c;

			
			return m * rotationMatrix;*/
		}//22222222222222222222

		Matrix4<T> Scale(const Matrix4<T>& mat, const Vector<T>& scalingFactors) {
			Matrix4<T> result = mat;
			Matrix4<T> identity(1.0f);

			identity.data[0] *= scalingFactors.x();
			identity.data[5] *= scalingFactors.y();
			identity.data[10] *= scalingFactors.z();

			return mat * identity;
		}

		Matrix4<T> Ortho(T left, T right, T bottom, T top, T near, T far) {
			Matrix4<T> result(0);
			result.data[0] = 2.0f / (right - left);
			result.data[5] = 2.0f / (top - bottom);
			result.data[10] = -2.0f / (far - near);
			result.data[15] = 1.0f;
			result.data[3] = -(right + left) / (right - left);
			result.data[7] = -(top + bottom) / (top - bottom);
			result.data[11] = -(far + near) / (far - near);

			return result;
		}

		Matrix4<T> Perspective(T fov, T aspect, T zNear, T zFar){
			Matrix4<T> result(0);
			const T tanHalfFovy = std::tan(fov / 2.0f);
			result.data[0] = 1.0f / (aspect * tanHalfFovy);
			result.data[5] = 1.0f / tanHalfFovy;
			result.data[10] = -(zFar + zNear) / (zFar - zNear);
			result.data[14] = 1.0f;
			result.data[11] = -(2.0f * zFar * zNear) / (zFar - zNear);

			return result;
		}

		static Matrix4<T> FromQuaternion(const typename Vector<T>::Quaternion& q) {
			Matrix4<T> result(1);  // Identity matrix initially

			T qxx(q.x * q.x);
			T qyy(q.y * q.y);
			T qzz(q.z * q.z);
			T qxz(q.x * q.z);
			T qxy(q.x * q.y);
			T qyz(q.y * q.z);
			T qwx(q.w * q.x);
			T qwy(q.w * q.y);
			T qwz(q.w * q.z);

			result.data[0] = 1 - 2 * (qyy + qzz);
			result.data[1] = 2 * (qxy + qwz);
			result.data[2] = 2 * (qxz - qwy);

			result.data[4] = 2 * (qxy - qwz);
			result.data[5] = 1 - 2 * (qxx + qzz);
			result.data[6] = 2 * (qyz + qwx);

			result.data[8] = 2 * (qxz + qwy);
			result.data[9] = 2 * (qyz - qwx);
			result.data[10] = 1 - 2 * (qxx + qyy);

			// The last column
			result.data[3] = result.data[7] = result.data[11] = 0;
			result.data[15] = 1;

			return result;
		}

		

	private:		
		int getI(int row, int col) const {
			return col * 4 + row;
		};

	};

	
}

