#include "Transform.h"

#include "../../ext/glm/gtx/quaternion.hpp"
#include "../../ext/glm/gtc/quaternion.hpp"

#include "../Object/Object.h"

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
		const float pi = std::acos(-1);
		const float degree = pi / 180.0f;
		m_Rotation = glm::vec3(degree * x, degree * y, degree * z);
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
		const float pi = std::acos(-1);
		const float degree = pi / 180.0f;
		m_Rotation.x = Interval(m_Rotation.x + (degree * x), 360.0f);
		m_Rotation.y = Interval(m_Rotation.y + (degree * y), 360.0f);
		m_Rotation.z = Interval(m_Rotation.z + (degree * z), 360.0f);
	}

	[[nodiscard]] glm::vec3 Transform::GetLocalPosition() const noexcept {
		return m_Position;
	}

	[[nodiscard]] glm::vec3 Transform::GetLocalRotation() const noexcept {
		const float pi = std::acos(-1);
		return (180 / pi) * m_Rotation;
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
		float x, y, z;
		glm::vec3 scale = GetWorldScale();
		glm::mat4 t = ParentOrientationMat4f(m_Owner);
		float t23 = t[1][2] / scale.y;
		float t33 = t[2][2] / scale.z;
		float t13 = t[0][2] / scale.x;
		float t12 = t[0][1] / scale.x;
		float t11 = t[0][0] / scale.x;
		x = std::atan2f(t23, t33);
		auto sy = std::sqrtf(t23 * t23 + t33 * t33);
		y = std::atan2f(-t13, sy);
		z = std::atan2f(t12, t11);

		const float pi = std::acos(-1);

		return glm::vec3(x * 180.0f / pi, y * 180.0f / pi, z * 180.0f / pi);
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

	[[nodiscard]] float Transform::Interval(float current, float max) const noexcept {
		if (current < max) {
			return current;
		}
		return Interval(current - max, max);
	}

	[[nodiscard]] glm::mat4 Transform::AsMat4f() const noexcept {
		glm::mat4 t_position_matrix = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 t_rotation_matrix = glm::toMat4(glm::quat(m_Rotation));
		glm::mat4 t_scale_matrix = glm::scale(glm::mat4(1.0f), m_Scale);
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

	//[[nodiscard]] glm::vec3 Transform::ParentsPositionRecursiveVec3f(Object* obj) const noexcept {
	//	if (!obj) {
	//		return glm::vec3(1.0f);
	//	}
	//	auto parent = obj->GetParent();
	//	auto transform = obj->GetTransform();
	//	return ParentsPositionRecursiveVec3f(parent) + transform.GetLocalPosition();
	//}

	//glm::vec3 Transform::ParentsRotationRecursiveVec3f(Object* obj) const noexcept
	//{
	//	if (!obj) {
	//		return glm::vec3(1.0f);
	//	}
	//	auto parent = obj->GetParent();
	//	auto transform = obj->GetTransform();
	//	return ParentsRotationRecursiveVec3f(parent) + transform.GetLocalRotation();
	//}

	//glm::vec3 Transform::ParentsScaleRecursiveVec3f(Object* obj) const noexcept
	//{
	//	if (!obj) {
	//		return glm::vec3(1.0f);
	//	}
	//	auto parent = obj->GetParent();
	//	auto transform = obj->GetTransform();
	//	return ParentsScaleRecursiveVec3f(parent) * transform.GetLocalScale();
	//}
}


