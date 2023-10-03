#include "Transform.h"

#include "../../ext/glm/gtx/quaternion.hpp"
#include "../../ext/glm/gtc/quaternion.hpp"

namespace dra {
	Transform::Transform() {
		m_Position	= glm::vec3(0.0f, 0.0f, 0.0f);
		m_Rotation	= glm::vec3(0.0f, 0.0f, 0.0f);
		m_Scale		= glm::vec3(1.0f, 1.0f, 1.0f);
	}

	Transform::~Transform() {
	}

	void Transform::SetPosition(float x, float y, float z) {
		m_Position = glm::vec3(x, y, z);
	}

	void Transform::SetRotation(float x, float y, float z) {
		m_Rotation = glm::vec3(x, y, z);
	}

	void Transform::SetScale(float x, float y, float z) {
		m_Scale = glm::vec3(x, y, z);
	}

	glm::vec3 Transform::GetPosition() {
		return m_Position;
	}

	glm::vec3 Transform::GetRotation() {
		return m_Rotation;
	}

	glm::vec3 Transform::GetScale() {
		return m_Scale;
	}

	glm::mat4 Transform::GetTransform() {
		glm::mat4 t_position_matrix = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 t_rotation_matrix = glm::toMat4(glm::quat(m_Rotation));
		glm::mat4 t_scale_matrix	= glm::scale(glm::mat4(1.0f), m_Scale);

		return t_position_matrix * t_rotation_matrix * t_scale_matrix;
	}
}


