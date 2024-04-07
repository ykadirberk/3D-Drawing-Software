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

	[[nodiscard]] Vector<float> Transform::GetLocalPosition() const noexcept {
		return m_Position;
	}

	[[nodiscard]] Vector<float> Transform::GetLocalRotation() const noexcept {
		const float pi = std::acos(-1);
		return Vector((180 / pi) * m_Rotation.x(), (180 / pi) * m_Rotation.y(), (180 / pi) * m_Rotation.z());
	}

	[[nodiscard]] Vector<float> Transform::GetLocalScale() const noexcept {
		return m_Scale;
	}

	[[nodiscard]] Vector<float> Transform::GetWorldPosition() const noexcept
	{
		Matrix4<float> t = ParentOrientationMat4f(m_Owner);
		return Vector(t.data[3], t.data[7], t.data[11]);
	}

	[[nodiscard]] Vector<float> Transform::GetWorldRotation() const noexcept {
		auto t = ParentOrientedRotationVec3f(this->m_Owner, Vector(0.0f));
		Vector rot = Vector<float>();
		rot.setx(Interval(t.x(), -180.0f, 180.0f));
		rot.sety(Interval(t.y(), -180.0f, 180.0f));
		rot.setz(Interval(t.z(), -180.0f, 180.0f));
		return rot;
	}

	[[nodiscard]] Vector<float> Transform::GetWorldScale() const noexcept {
		Matrix4<float> temp = ParentOrientationMat4f(m_Owner);
		Vector first = Vector(temp.data[0], temp.data[4], temp.data[8]);
		Vector second = Vector(temp.data[1], temp.data[5], temp.data[9]);
		Vector third = Vector(temp.data[2], temp.data[6], temp.data[10]);
		Vector<float> sizes;
		sizes.setx(std::sqrtf(first.x() * first.x() + first.y() * first.y() + first.z() * first.z()));
		sizes.sety(std::sqrtf(second.x() * second.x() + second.y() * second.y() + second.z() * second.z()));
		sizes.setz(std::sqrtf(third.x() * third.x() + third.y() * third.y() + third.z() * third.z()));
		return sizes;
	}

	[[nodiscard]] Matrix4<float> Transform::GetLocalAsMat4f() const noexcept {
		return AsMat4f();
	}
	 
	[[nodiscard]] Matrix4<float> Transform::GetWorldAsMat4f() const noexcept {
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

	[[nodiscard]] Matrix4<float> Transform::AsMat4f() const noexcept {
		Vector pos = Vector(m_Position.x(), m_Position.y(), m_Position.z());
		Vector rot = Vector(m_Rotation.x(), m_Rotation.y(), m_Rotation.z());
		Vector sca = Vector(m_Scale.x(), m_Scale.y(), m_Scale.z());
		Matrix4 t_position_matrix = Matrix4(1.0f);
		t_position_matrix = t_position_matrix.Translate(t_position_matrix, pos);
		//Matrix4 t_position_matrix = Matrix4.translate(Matrix4(1.0f), pos);


		Matrix4 t_rotation_matrix = Matrix4(1.0f);
		t_rotation_matrix = t_rotation_matrix.Rotate(t_rotation_matrix, 6, rot);
		//glm::mat4 t_rotation_matrix = glm::toMat4(glm::quat(rot));




		Matrix4 t_scale_matrix = Matrix4(1.0f);
		t_scale_matrix = t_scale_matrix.Scale(t_scale_matrix, sca);
		//glm::mat4 t_scale_matrix = glm::scale(glm::mat4(1.0f), sca);
		return t_position_matrix * t_rotation_matrix * t_scale_matrix;
	}
	[[nodiscard]] Matrix4<float> Transform::ParentOrientationMat4f(Object* obj) const noexcept {
		if (!obj) {
			return Matrix4(1.0f);
		}
		auto parent = obj->GetParent();
		auto transform = obj->GetTransform();


		return ParentOrientationMat4f(parent) * transform.GetLocalAsMat4f();
	}

	[[nodiscard]] Vector<float> Transform::ParentOrientedRotationVec3f(Object* obj, Vector<float> current) const noexcept
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


