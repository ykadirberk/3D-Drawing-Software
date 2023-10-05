#include "Object.h"

namespace dra {
	Object::Object(Object* parent): m_Parent(parent) {
		m_Transform = Transform(this);
	}

	Object* Object::GetParent() noexcept {
		return m_Parent;
	}

	Transform& Object::GetTransform() noexcept {
		return m_Transform;
	}

	void Object::SetParent(Object* parent) noexcept {
		m_Parent = parent;
		m_Transform.Translate(-parent->GetTransform().GetLocalPosition().x, -parent->GetTransform().GetLocalPosition().y, -parent->GetTransform().GetLocalPosition().z);
		m_Transform.Rotate(-parent->GetTransform().GetLocalRotation().x, -parent->GetTransform().GetLocalRotation().y, -parent->GetTransform().GetLocalRotation().z);
	}



}