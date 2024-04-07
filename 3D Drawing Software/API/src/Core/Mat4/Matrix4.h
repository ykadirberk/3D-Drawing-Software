#pragma once

#include <memory>

#include "../DLLBuild.h"
#include <iostream>
#include <array>
#include <random>

#include "../Vector/Vector.h"


namespace dra {
	template<typename T>
	class _API Matrix4 {

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

			axis.normalize();// TODO:Write normalize function
			Vector<float> temp = Vector(axis.x(), axis.y(), axis.z());// TODO

			Matrix4<T> rotation;
			rotation.data[0] = c + temp.x() * axis.x();
			rotation.data[4] = temp.x() * axis.y() + s * axis.z();
			rotation.data[8] = temp.x() * axis.z() - s * axis.y();

			rotation.data[1] = temp.y() * axis.x() - s * axis.z();
			rotation.data[5] = c + temp.y() * axis.y();
			rotation.data[9] = temp.y() * axis.z() + s * axis.x();

			rotation.data[2] = temp.z() * axis.x() + s * axis.y();
			rotation.data[6] = temp.z() * axis.y() - s * axis.x();
			rotation.data[10] = c + temp.z() * axis.z();

			return mat * rotation;
		}

		Matrix4<T> Scale(const Matrix4<T>& mat, const Vector<T>& scalingFactors) {
			Matrix4<T> result = mat;

			result.data[0] *= scalingFactors.x();
			result.data[5] *= scalingFactors.y();
			result.data[10] *= scalingFactors.z();

			return result;
		}

		

	private:
		
		int row_col_cm(int row, int col) const;
		int row_col_rm(int row, int col) const;

	};

	template<typename T>
	inline int Matrix4<T>::row_col_cm(int row, int col) const
	{
		return 0;
	}

	template<typename T>
	inline int Matrix4<T>::row_col_rm(int row, int col) const
	{
		return 0;
	}


	template<typename T, typename... Matrices>
	Matrix4<T> CustomMultiply(const Matrix4<T>& first, const Matrices&... matrices) {
		return (first * ... * matrices);
	};
}

