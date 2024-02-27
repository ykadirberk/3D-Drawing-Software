#include "Transform.h"

#include "../../ext/glm/gtx/quaternion.hpp"
#include "../../ext/glm/gtc/quaternion.hpp"

#include "../Object/Object.h"

namespace dra {
	Transform::Transform() : m_Owner(nullptr) {
		m_Position = Vector(0.0f, 0.0f, 0.0f);
		m_Rotation = Vector(0.0f, 0.0f, 0.0f);
		m_Scale = Vector(1.0f, 1.0f, 1.0f);
	}
	Transform::Transform(Object* owner) : m_Owner(owner) {
		m_Position	= Vector(0.0f, 0.0f, 0.0f);
		m_Rotation	= Vector(0.0f, 0.0f, 0.0f);
		m_Scale		= Vector(1.0f, 1.0f, 1.0f);
	}

	Transform::~Transform() {
	}

	void Transform::SetLocalPosition(float x, float y, float z) noexcept {
		m_Position = Vector(x, y, z);
	}

	void Transform::SetLocalRotation(float x, float y, float z) noexcept {
		const float pi = std::acos(-1);
		const float degree = pi / 180.0f;
		m_Rotation = Vector(degree * x, degree * y, degree * z);
	}

	void Transform::SetLocalScale(float x, float y, float z) noexcept {
		m_Scale = Vector(x, y, z);
	}

	void Transform::Translate(float x, float y, float z) noexcept {
		m_Position.setx(m_Position.x() + x);
		m_Position.sety(m_Position.y() + y);
		m_Position.setz(m_Position.z() + z);
	}

	void Transform::Rotate(float x, float y, float z) noexcept {
		const float pi = std::acos(-1);
		const float degree = pi / 180.0f;
		/*m_Rotation.x = Interval(m_Rotation.x + (degree * x), 0.0f, 2 * pi);
		m_Rotation.y = Interval(m_Rotation.y + (degree * y), 0.0f, 2 * pi);
		m_Rotation.z = Interval(m_Rotation.z + (degree * z), 0.0f, 2 * pi);*/
		m_Rotation.setx(Interval(m_Rotation.x() + (degree * x), -pi, pi));
		m_Rotation.sety(Interval(m_Rotation.y() + (degree * y), -pi, pi));
		m_Rotation.setz(Interval(m_Rotation.z() + (degree * z), -pi, pi));
	}

	[[nodiscard]] Vector Transform::GetLocalPosition() const noexcept {
		return m_Position;
	}

	[[nodiscard]] Vector Transform::GetLocalRotation() const noexcept {
		const float pi = std::acos(-1);
		return Vector((180 / pi) * m_Rotation.x(), (180 / pi) * m_Rotation.y(), (180 / pi) * m_Rotation.z());
	}

	[[nodiscard]] Vector Transform::GetLocalScale() const noexcept {
		return m_Scale;
	}

	[[nodiscard]] Vector Transform::GetWorldPosition() const noexcept
	{
		glm::mat4 t = ParentOrientationMat4f(m_Owner);
		return Vector(t[3][0], t[3][1], t[3][2]);
	}

	[[nodiscard]] Vector Transform::GetWorldRotation() const noexcept {
		auto t = ParentOrientedRotationVec3f(this->m_Owner, Vector(0.0f));
		Vector rot = Vector();
		rot.setx(Interval(t.x(), -180.0f, 180.0f));
		rot.sety(Interval(t.y(), -180.0f, 180.0f));
		rot.setz(Interval(t.z(), -180.0f, 180.0f));
		return rot;
	}

	[[nodiscard]] Vector Transform::GetWorldScale() const noexcept {
		glm::mat4 temp = ParentOrientationMat4f(m_Owner);
		Vector first = Vector(temp[0][0], temp[0][1], temp[0][2]);
		Vector second = Vector(temp[1][0], temp[1][1], temp[1][2]);
		Vector third = Vector(temp[2][0], temp[2][1], temp[2][2]);
		Vector sizes;
		sizes.setx(std::sqrtf(first.x() * first.x() + first.y() * first.y() + first.z() * first.z()));
		sizes.sety(std::sqrtf(second.x() * second.x() + second.y() * second.y() + second.z() * second.z()));
		sizes.setz(std::sqrtf(third.x() * third.x() + third.y() * third.y() + third.z() * third.z()));
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
		glm::vec3 pos = glm::vec3(m_Position.x(), m_Position.y(), m_Position.z());
		glm::vec3 rot = glm::vec3(m_Rotation.x(), m_Rotation.y(), m_Rotation.z());
		glm::vec3 sca = glm::vec3(m_Scale.x(), m_Scale.y(), m_Scale.z());
		glm::mat4 t_position_matrix = glm::translate(glm::mat4(1.0f), pos);
		glm::mat4 t_rotation_matrix = glm::toMat4(glm::quat(rot));
		glm::mat4 t_scale_matrix = glm::scale(glm::mat4(1.0f), sca);
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

	[[nodiscard]] Vector Transform::ParentOrientedRotationVec3f(Object* obj, Vector current) const noexcept
	{
		if (!obj) {
			return current;
		}
		auto rotation = obj->GetTransform().GetLocalRotation();
		float x, y, z;
		x = current.x() + rotation.x();
		y = current.y() + rotation.y();
		z = current.z() + rotation.z();
		return ParentOrientedRotationVec3f(obj->GetParent(), Vector(x, y, z));
	}

}


