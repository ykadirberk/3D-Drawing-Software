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
						elem += data[row_col_cm(s, r)] *
							other.data[row_col_cm(c, s)];
					}
					m.data[row_col_cm(c, r)] = elem;
				}
			}
			return m;
		}

		static Matrix4<T> multiplyByRow(Matrix4<T>& one, const Matrix4<T>& two) {
			Matrix4 m;
			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					T elem = 0;
					for (int s = 0; s < 4; ++s) {
						elem += one.data[getValue(s, r)] *
							two.data[getValue(c, s)];
					}
					m.data[getValue(c, r)] = elem;
				}
			}
			return m;
		}

		/*Matrix4& operator=(const Matrix4& other) {
			if (this != &other) {
				data = other.data;
			}
			return *this;
		}*/

		static Matrix4<T> Translate(const Matrix4<T>& mat, const Vector<T>& translation) {
			Matrix4<T> result = mat;

			result.data[3] = translation.x() * mat.data[0] + translation.y() * mat.data[1] + translation.z() * mat.data[2] + mat.data[3];
			result.data[7] = translation.x() * mat.data[4] + translation.y() * mat.data[5] + translation.z() * mat.data[6] + mat.data[7];
			result.data[11] = translation.x() * mat.data[8] + translation.y() * mat.data[9] + translation.z() * mat.data[10] + mat.data[11];
			result.data[15] = translation.x() * mat.data[12] + translation.y() * mat.data[13] + translation.z() * mat.data[14] + mat.data[15];
			/*result.data[3] = translation.x();
			result.data[7] = translation.y();
			result.data[11] = translation.z();*/


			return result;
		}//calisti


		static Matrix4<T> Rotation(const Vector<T>& v) {
			T cx = cos(v.x() * T(0.5));
			T cy = cos(v.y() * T(0.5));
			T cz = cos(v.z() * T(0.5));
			T sx = sin(v.x() * T(0.5));
			T sy = sin(v.y() * T(0.5));
			T sz = sin(v.z() * T(0.5));

			T w = cx * cy * cz + sx * sy * sz;
			T x = sx * cy * cz - cx * sy * sz;
			T y = cx * sy * cz + sx * cy * sz;
			T z = cx * cy * sz - sx * sy * cz;

			T qxx(x * x);
			T qyy(y * y);
			T qzz(z * z);
			T qxz(x * z);
			T qxy(x * y);
			T qyz(y * z);
			T qwx(w * x);
			T qwy(w * y);
			T qwz(w * z);

			Matrix4<float> result;

			result.data[0] = T(1) - T(2) * (qyy + qzz);
			result.data[1] = T(2) * (qxy + qwz);
			result.data[2] = T(2) * (qxz - qwy);
			result.data[3] = 0;
			result.data[4] = T(2) * (qxy - qwz);
			result.data[5] = T(1) - T(2) * (qxx + qzz);
			result.data[6] = T(2) * (qyz + qwx);
			result.data[7] = 0;
			result.data[8] = T(2) * (qxz + qwy);
			result.data[9] = T(2) * (qyz - qwx);
			result.data[10] = T(1) - T(2) * (qxx + qyy);
			result.data[11] = 0;
			result.data[12] = 0;
			result.data[13] = 0;
			result.data[14] = 0;
			result.data[15] = 1;

			return Matrix4<float>::Transpose(result);
		}//calisti

		static Matrix4<T> Scale(const Matrix4<T>& mat, const Vector<T>& scalingFactors) {
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
		}//calisti

		static Matrix4<T> Ortho(T left, T right, T bottom, T top, T zNear, T zFar) {
			Matrix4<T> result(1.0f);

			result.data[0] = static_cast<T>(2) / (right - left);
			result.data[5] = static_cast<T>(2) / (top - bottom);
			result.data[10] = -static_cast<T>(2) / (zFar - zNear);
			result.data[3] = -(right + left) / (right - left);
			result.data[7] = -(top + bottom) / (top - bottom);
			result.data[11] = -(zFar + zNear) / (zFar - zNear);

			return result;
		}//calisti

		static Matrix4<T> Perspective(T fovy, T aspect, T zNear, T zFar) {
			assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

			//T fovy = fovy_wr * static_cast<T>(3.14 / 180.0);

			T const tanHalfFovy = std::tan(fovy / static_cast<T>(2));

			Matrix4<T> result(0.0f);
			result.data[0] = static_cast<T>(1) / (aspect * tanHalfFovy);
			result.data[5] = static_cast<T>(1) / (tanHalfFovy);
			result.data[10] = -(zFar + zNear) / (zFar - zNear);
			result.data[14] = -static_cast<T>(1);
			result.data[11] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);


			/*std::cout << "result bizim" << std::endl;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					std::cout << result[i][j] << " ";
				}
				std::cout << std::endl;
			}*/
			return result;
		}//calisti

		static Matrix4<T> Inverse(const Matrix4<T>& mat) {
			Matrix4<T> result = mat;
			Matrix4<T> identity(T(1));

			for (int i = 0; i < 4; ++i) {
				T diag = result.data[getValue(i, i)];
				if (diag == 0) {
					for (int j = i + 1; j < 4; ++j) {
						if (result.data[getValue(j, i)] != 0) {
							for (int k = 0; k < 4; ++k) {
								std::swap(result.data[getValue(i, k)], result.data[getValue(j, k)]);
								std::swap(identity.data[getValue(i, k)], identity.data[getValue(j, k)]);
							}
							break;
						}
					}
					diag = result.data[getValue(i, i)];
					if (diag == 0) {
						throw std::runtime_error("Non-inversible matrix");
					}
				}
				for (int j = 0; j < 4; ++j) {
					result.data[getValue(i, j)] /= diag;
					identity.data[getValue(i, j)] /= diag;
				}

				for (int j = 0; j < 4; ++j) {
					if (i != j) {
						T factor = result.data[getValue(j, i)];
						for (int k = 0; k < 4; ++k) {
							result.data[getValue(j, k)] -= factor * result.data[getValue(i, k)];
							identity.data[getValue(j, k)] -= factor * identity.data[getValue(i, k)];
						}
					}
				}
			}
			return identity;
		}//calisti

		static Matrix4<T> FromQuaternion(const typename Vector<T>::Quaternion& q) {
			Matrix4<T> result(1);

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

			result.data[3] = result.data[7] = result.data[11] = 0;
			result.data[15] = 1;

			return result;
		}

		static Matrix4<T> Transpose(const Matrix4<T>& mat) {
			Matrix4<T> result = mat;

			result.data[1] = mat.data[4];
			result.data[2] = mat.data[8];
			result.data[3] = mat.data[12];

			result.data[4] = mat.data[1];
			result.data[6] = mat.data[9];
			result.data[7] = mat.data[13];

			result.data[8] = mat.data[2];
			result.data[9] = mat.data[6];
			result.data[11] = mat.data[14];

			result.data[12] = mat.data[3];
			result.data[13] = mat.data[7];
			result.data[14] = mat.data[11];

			return result;
		}//calisti



	private:
		T row_col_cm(T row, T col) const {
			return col * 4 + row;
		}


		T row_col_rm(T row, T col) const {
			return row * 4 + col;
		}

		static T getValue(T row, T col) {
			return row * 4 + col;
		}

	};


}

