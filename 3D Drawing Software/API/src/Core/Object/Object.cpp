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
		RecursiveParentLeave(m_Parent);
		m_Parent = parent;
		RecursiveParentJoin(parent);
		/*m_Transform.Translate(-parent->GetTransform().GetWorldPosition().x, -parent->GetTransform().GetWorldPosition().y, -parent->GetTransform().GetWorldPosition().z);
		m_Transform.Rotate(-parent->GetTransform().GetWorldRotation().x, -parent->GetTransform().GetWorldRotation().y, -parent->GetTransform().GetWorldRotation().z);*/
	}

	void Object::RecursiveParentLeave(Object* parent)
	{
		if (parent == nullptr) {
			return;
		}

		m_Transform.Translate(parent->GetTransform().GetLocalPosition().x, parent->GetTransform().GetLocalPosition().y, parent->GetTransform().GetLocalPosition().z);
		m_Transform.Rotate(parent->GetTransform().GetLocalRotation().x, parent->GetTransform().GetLocalRotation().y, parent->GetTransform().GetLocalRotation().z);

		RecursiveParentLeave(parent->GetParent());
	}

	void Object::RecursiveParentJoin(Object* parent)
	{
		if (parent == nullptr) {
			return;
		}
		RecursiveParentJoin(parent->GetParent());

		m_Transform.Translate(-parent->GetTransform().GetLocalPosition().x, -parent->GetTransform().GetLocalPosition().y, -parent->GetTransform().GetLocalPosition().z);
		m_Transform.Rotate(-parent->GetTransform().GetLocalRotation().x, -parent->GetTransform().GetLocalRotation().y, -parent->GetTransform().GetLocalRotation().z);

		
	}



}