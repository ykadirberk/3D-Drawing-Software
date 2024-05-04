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

		Matrix4(T a0, T b0, T c0, T d0,
			T a1, T b1, T c1, T d1,
			T a2, T b2, T c2, T d2,
			T a3, T b3, T c3, T d3) {
			data[0] = a0; data[1] = a1; data[2] = a2; data[3] = a3;
			data[4] = b0; data[5] = b1; data[6] = b2; data[7] = b3;
			data[8] = c0; data[9] = c1; data[10] = c2; data[11] = c3;
			data[12] = d0; data[13] = d1; data[14] = d2; data[15] = d3;
		}

		std::array<T, 4> operator[](int col) {
			assert(col >= 0 && col < 4);
			std::array<T, 4> row;

			for (int i = 0; i < 4; ++i) {
				row[i] = data[col + 4 * i];
			}
			return row;
		}

		

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
			Matrix4<T> result = mat;

			result.data[3] = translation.x() * mat.data[0] + translation.y() * mat.data[1] + translation.z() * mat.data[2] + mat.data[3];
			result.data[7] = translation.x() * mat.data[4] + translation.y() * mat.data[5] + translation.z() * mat.data[6] + mat.data[7];
			result.data[11] = translation.x() * mat.data[8] + translation.y() * mat.data[9] + translation.z() * mat.data[10] + mat.data[11];
			result.data[15] = translation.x() * mat.data[12] + translation.y() * mat.data[13] + translation.z() * mat.data[14] + mat.data[15];

			return result;
		}

		Matrix4<T> Rotate(const Matrix4<T>& mat, T angle, const Vector<T>& axis) {
			T radians = angle * static_cast<T>(3.14 / 180.0);
			T c = cos(radians);
			T s = sin(radians);

			Vector<T> normAxis = axis.normalized();
			Vector<T> temp = Vector<T>((1 - c) * normAxis.x(), (1 - c) * normAxis.y(), (1 - c) * normAxis.z());

			Matrix4<T> rotation;
			rotation.data[0] = c + temp.x() * normAxis.x();
			rotation.data[4] = temp.x() * normAxis.y() + s * normAxis.z();
			rotation.data[8] = temp.x() * normAxis.z() - s * normAxis.y();

			rotation.data[1] = temp.y() * normAxis.x() - s * normAxis.z();
			rotation.data[5] = c + temp.y() * normAxis.y();
			rotation.data[9] = temp.y() * normAxis.z() + s * normAxis.x();

			rotation.data[2] = temp.z() * normAxis.x() + s * normAxis.y();
			rotation.data[6] = temp.z() * normAxis.y() - s * normAxis.x();
			rotation.data[10] = c + temp.z() * normAxis.z();

			Matrix4<T> result = rotation * mat;
			result.data[3] = mat.data[3];
			result.data[7] = mat.data[7];
			result.data[11] = mat.data[11];
			result.data[15] = mat.data[15];

			return result;
		}

		Matrix4<T> Scale(const Matrix4<T>& mat, const Vector<T>& scalingFactors) {
			Matrix4<T> result = mat;

			result.data[0] = mat.data[0] * scalingFactors.x();
			result.data[4] = mat.data[4] * scalingFactors.x();
			result.data[8] = mat.data[8] * scalingFactors.x();
			result.data[12] = mat.data[12] * scalingFactors.x();

			result.data[1] = mat.data[1] * scalingFactors.y();
			result.data[5] = mat.data[5] * scalingFactors.y();
			result.data[9] = mat.data[9] * scalingFactors.y();
			result.data[13] = mat.data[13] * scalingFactors.y();

			result.data[2] = mat.data[2] * scalingFactors.z();
			result.data[6] = mat.data[6] * scalingFactors.z();
			result.data[10] = mat.data[10] * scalingFactors.z();
			result.data[14] = mat.data[14] * scalingFactors.z();



			return result;
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
			return row * 4 + col;
		};

	};

	
}

