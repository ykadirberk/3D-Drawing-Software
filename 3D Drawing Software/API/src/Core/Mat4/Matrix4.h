#pragma once

#include <memory>

#include "../DLLBuild.h"
#include <iostream>
#include <array>
#include <random>

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

		Matrix4<T> operator*(const Matrix4<T>& other) const {
			Matrix4 m;
			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					T elem = 0;
					for (int s = 0; s < 4; ++s) {
						elem += data[row_col_cm(s, r)] *
							other.data[row_col_cm(c, s)];
					}
					m.data[row_col_cm(c, r)] = elem;
				}
			}
			return m;
		}

		Matrix4<T> Translate(const Matrix4<T>& mat, const Vector<T>& translation) {
			Matrix4<T> result = mat;

			result.data[12] += translation.x();
			result.data[13] += translation.y();
			result.data[14] += translation.z();

			return result;
		}

		Matrix4<T> Rotate(const Matrix4<T>& mat, T angle, const Vector<T>& axis) {
			T radians = angle * static_cast<T>(3.14 / 180.0);
			T c = cos(radians);
			T s = sin(radians);

			auto normalized_axis = axis.normalized();// TODO:Write normalize function
			Vector<float> temp = Vector(normalized_axis.x(), normalized_axis.y(), normalized_axis.z());// TODO

			Matrix4<T> rotation;
			rotation.data[0] = c + temp.x() * normalized_axis.x();
			rotation.data[4] = temp.x() * normalized_axis.y() + s * normalized_axis.z();
			rotation.data[8] = temp.x() * normalized_axis.z() - s * normalized_axis.y();

			rotation.data[1] = temp.y() * normalized_axis.x() - s * normalized_axis.z();
			rotation.data[5] = c + temp.y() * normalized_axis.y();
			rotation.data[9] = temp.y() * normalized_axis.z() + s * normalized_axis.x();

			rotation.data[2] = temp.z() * normalized_axis.x() + s * normalized_axis.y();
			rotation.data[6] = temp.z() * normalized_axis.y() - s * normalized_axis.x();
			rotation.data[10] = c + temp.z() * normalized_axis.z();

			return mat * rotation;
		}

		Matrix4<T> Scale(const Matrix4<T>& mat, const Vector<T>& scalingFactors) {
			Matrix4<T> result = mat;

			result.data[0] *= scalingFactors.x();
			result.data[5] *= scalingFactors.y();
			result.data[10] *= scalingFactors.z();

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

		template<typename T, typename... Matrices>
		Matrix4<T> CustomMultiply(const Matrix4<T>& first, const Matrices&... matrices) {
			return (first * ... * matrices);
		};

		

	private:		
		int row_col_cm(int row, int col) const {
			return col * 3 + row;
		};

	};

	
}

