#include "Transform.h"

#include "../Object/Object.h"

namespace dra {
	Transform::Transform() : m_Owner(nullptr) {
		m_Position = Vector<float>(0.0f, 0.0f, 0.0f);
		m_Rotation = Vector<float>(0.0f, 0.0f, 0.0f);
		m_Scale = Vector<float>(1.0f, 1.0f, 1.0f);
	}
	Transform::Transform(Object* owner) : m_Owner(owner) {
		m_Position	= Vector<float>(0.0f, 0.0f, 0.0f);
		m_Rotation	= Vector<float>(0.0f, 0.0f, 0.0f);
		m_Scale		= Vector<float>(1.0f, 1.0f, 1.0f);
	}

	Transform::~Transform() {
	}

	void Transform::SetLocalPosition(float x, float y, float z) noexcept {
		m_Position.setx(x);
		m_Position.sety(y);
		m_Position.setz(z);
	}

	void Transform::SetLocalRotation(float x, float y, float z) noexcept {
		const float pi = std::acos(-1);
		const float degree = pi / 180.0f;
		m_Rotation.setx(degree * x);
		m_Rotation.sety(degree * y);
		m_Rotation.setz(degree * z);
	}

	void Transform::SetLocalScale(float x, float y, float z) noexcept {
		m_Scale.setx(x);
		m_Scale.sety(y);
		m_Scale.setz(z);
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
		return Vector<float>((180 / pi) * m_Rotation.x(), (180 / pi) * m_Rotation.y(), (180 / pi) * m_Rotation.z());
		//burada belki bir sorun olabilir
	}

	[[nodiscard]] Vector<float> Transform::GetLocalScale() const noexcept {
		return m_Scale;
	}

	[[nodiscard]] Vector<float> Transform::GetWorldPosition() const noexcept
	{
		Matrix4<float> t = ParentOrientationMat4f(m_Owner);
		return Vector<float>(t[3][0], t[3][1], t[3][2]); //11111111111
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
		Vector first = Vector(temp[0][0], temp[0][1], temp[0][2]);
		Vector second = Vector(temp[1][0], temp[1][1], temp[1][2]);
		Vector third = Vector(temp[2][0], temp[2][1], temp[2][2]);
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
		Matrix4 t_position_matrix = Matrix4(1.0f);
		t_position_matrix = Matrix4<float>::Translate(t_position_matrix, pos);

		
		

		Vector rot = Vector(m_Rotation.x(), m_Rotation.y(), m_Rotation.z());
		Matrix4 t_rotation_matrix = Matrix4(1.0f);
		t_rotation_matrix = Matrix4<float>::Rotate(t_rotation_matrix, rot.length(), rot.normalized());

		Vector sca = Vector(m_Scale.x(), m_Scale.y(), m_Scale.z());
		Matrix4 t_scale_matrix = Matrix4(1.0f);
		t_scale_matrix = Matrix4<float>::Scale(t_scale_matrix, sca);

		/*Matrix4 res = t_position_matrix
			* Matrix4<float>::Rotate(Matrix4(1.0f), rot.length(), rot.normalized()) 
			* Matrix4<float>::Scale(Matrix4(1.0f), Vector(1.0f, 1.0f, 1.0f));
		for (int i = 0; i < 16; i++) {
			std::cout << res.data[i] << ", ";
		}
		std::cout << std::endl;
		std::cout << m_Position.x() << ", " << m_Position.y() << ", " << m_Position.z() << std::endl;*/
		//__debugbreak();

		return t_position_matrix * t_rotation_matrix * t_scale_matrix;
		//return t_scale_matrix * t_rotation_matrix * t_position_matrix;
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
		return ParentOrientedRotationVec3f(obj->GetParent(), Vector<float>(x, y, z));
	}

}


