#include "Transform.h"

#include "../../ext/glm/gtx/quaternion.hpp"
#include "../../ext/glm/gtc/quaternion.hpp"

#include "../Object/Object.h"

#include <numbers>

namespace dra {
	Transform::Transform() : m_Owner(nullptr) {
		m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}
	Transform::Transform(Object* owner) : m_Owner(owner) {
		m_Position	= glm::vec3(0.0f, 0.0f, 0.0f);
		m_Rotation	= glm::vec3(0.0f, 0.0f, 0.0f);
		m_Scale		= glm::vec3(1.0f, 1.0f, 1.0f);
	}

	Transform::~Transform() {
	}

	void Transform::SetLocalPosition(float x, float y, float z) noexcept {
		m_Position = glm::vec3(x, y, z);
	}

	void Transform::SetLocalRotation(float x, float y, float z) noexcept {
		const float pi = std::numbers::pi;
		const float degree = pi / 180.0f;
		//m_Rotation = glm::vec3(degree * x, degree * y, degree * z);
		m_Rotation.x = Interval(x, -180, 180);
		m_Rotation.y = Interval(y, -180, 180);
		m_Rotation.z = Interval(z, -180, 180);
	}

	void Transform::SetLocalScale(float x, float y, float z) noexcept {
		m_Scale = glm::vec3(x, y, z);
	}

	void Transform::Translate(float x, float y, float z) noexcept {
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
	}

	void Transform::Rotate(float x, float y, float z) noexcept {
		const float pi = std::numbers::pi;
		const float degree = pi / 180.0f;
		/*m_Rotation.x = Interval(m_Rotation.x + (degree * x), 0.0f, 2 * pi);
		m_Rotation.y = Interval(m_Rotation.y + (degree * y), 0.0f, 2 * pi);
		m_Rotation.z = Interval(m_Rotation.z + (degree * z), 0.0f, 2 * pi);*/
		/*m_Rotation.x = Interval(m_Rotation.x + (degree * x), -pi, pi);
		m_Rotation.y = Interval(m_Rotation.y + (degree * y), -pi, pi);
		m_Rotation.z = Interval(m_Rotation.z + (degree * z), -pi, pi);*/
		m_Rotation.x = Interval(m_Rotation.x + x, -180, 180);
		m_Rotation.y = Interval(m_Rotation.y + y, -180, 180);
		m_Rotation.z = Interval(m_Rotation.z + z, -180, 180);
	}

	[[nodiscard]] glm::vec3 Transform::GetLocalPosition() const noexcept {
		return m_Position;
	}

	[[nodiscard]] glm::vec3 Transform::GetLocalRotation() const noexcept {
		const float pi = std::numbers::pi;
		//return (180 / pi) * m_Rotation;
		return m_Rotation;
	}

	[[nodiscard]] glm::vec3 Transform::GetLocalScale() const noexcept {
		return m_Scale;
	}

	[[nodiscard]] glm::vec3 Transform::GetWorldPosition() const noexcept
	{
		glm::mat4 t = ParentOrientationMat4f(m_Owner);
		return glm::vec3(t[3][0], t[3][1], t[3][2]);
	}

	[[nodiscard]] glm::vec3 Transform::GetWorldRotation() const noexcept {
		auto t = ParentOrientedRotationVec3f(this->m_Owner, glm::vec3(0.0f));
		glm::vec3 rot = glm::vec3();
		rot.x = Interval(t.x, -180.0f, 180.0f);
		rot.y = Interval(t.y, -180.0f, 180.0f);
		rot.z = Interval(t.z, -180.0f, 180.0f);
		return rot;
	}

	[[nodiscard]] glm::vec3 Transform::GetWorldScale() const noexcept {
		glm::mat4 temp = ParentOrientationMat4f(m_Owner);
		glm::vec3 first = glm::vec3(temp[0][0], temp[0][1], temp[0][2]);
		glm::vec3 second = glm::vec3(temp[1][0], temp[1][1], temp[1][2]);
		glm::vec3 third = glm::vec3(temp[2][0], temp[2][1], temp[2][2]);
		glm::vec3 sizes;
		sizes.x = std::sqrtf(first.x * first.x + first.y * first.y + first.z * first.z);
		sizes.y = std::sqrtf(second.x * second.x + second.y * second.y + second.z * second.z);
		sizes.z = std::sqrtf(third.x * third.x + third.y * third.y + third.z * third.z);
		return sizes;
	}

	[[nodiscard]] glm::mat4 Transform::GetLocalAsMat4f() const noexcept {
		return AsMat4f();
	}
	 
	[[nodiscard]] glm::mat4 Transform::GetWorldAsMat4f() const noexcept {
		return ParentOrientationMat4f(m_Owner);
	}

	[[nodiscard]] float Transform::Interval(float current, float min, float max) const noexcept {
		if (current <= max && current >= min) {
			return current;
		}

		if (current < min) {
			return Interval(current + (max - min), min, max);
		}
		return Interval(current - (max - min), min, max);
	}

	[[nodiscard]] glm::mat4 Transform::AsMat4f() const noexcept {
		glm::mat4 t_position_matrix = glm::translate(glm::mat4(1.0f), m_Position);
		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << t_position_matrix[i][j] << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "-------------" << std::endl;*/
		glm::quat t_rotx = glm::normalize(glm::angleAxis(glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)));
		glm::quat t_roty = glm::normalize(glm::angleAxis(glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)));
		glm::quat t_rotz = glm::normalize(glm::angleAxis(glm::radians(m_Rotation.z), glm::vec3(0, 0, 1)));

		glm::quat fin = t_roty * t_rotx * t_rotz;

		/*glm::mat4 t_rotation_matrix = glm::toMat4(glm::quat(
			glm::vec3((180.0f / std::numbers::pi) * m_Rotation.x, (180.0f / std::numbers::pi) * m_Rotation.y, (180.0f / std::numbers::pi) * m_Rotation.z)
		)
		);*/
		glm::mat4 t_rotation_matrix = glm::toMat4(fin);
		//float len = std::sqrt(m_Rotation.x * m_Rotation.x + m_Rotation.y * m_Rotation.y + m_Rotation.z * m_Rotation.z);
		//t_rotation_matrix = glm::rotate(,);
		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << t_rotation_matrix[i][j] << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "-----rotate^--------" << std::endl;*/
		glm::mat4 t_scale_matrix = glm::scale(glm::mat4(1.0f), m_Scale);
		/*for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << t_scale_matrix[i][j] << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << "-------------" << std::endl;*/
		return t_position_matrix * t_rotation_matrix * t_scale_matrix;
	}
	[[nodiscard]] glm::mat4 Transform::ParentOrientationMat4f(Object* obj) const noexcept {
		if (!obj) {
			return glm::mat4(1.0f);
		}
		auto parent = obj->GetParent();
		auto transform = obj->GetTransform();


		return ParentOrientationMat4f(parent) * transform.GetLocalAsMat4f();
	}

	[[nodiscard]] glm::vec3 Transform::ParentOrientedRotationVec3f(Object* obj, glm::vec3 current) const noexcept
	{
		if (!obj) {
			return current;
		}
		auto rotation = obj->GetTransform().GetLocalRotation();
		float x, y, z;
		x = current.x + rotation.x;
		y = current.y + rotation.y;
		z = current.z + rotation.z;
		return ParentOrientedRotationVec3f(obj->GetParent(), glm::vec3(x, y, z));
	}

}


