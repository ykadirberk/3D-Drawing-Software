#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "../DLLBuild.h"
#include "../Transform/Transform.h"

namespace dra {

	class _API Object {
		public:
			Object() : m_Parent(nullptr) {}
			Object(Object* parent);
			virtual ~Object() { std::cout << "Object::" << ((uint64_t)this) << " is destroyed." << std::endl; }

			[[nodiscard]] virtual Object* GetParent() noexcept;
			[[nodiscard]] virtual Transform& GetTransform() noexcept;
			virtual void SetParent(Object* parent) noexcept;

		protected:
			Transform m_Transform;
			Object* m_Parent;
			std::vector<Object*> m_Children;

			void RecursiveParentLeave(Object* parent);
			void RecursiveParentJoin(Object* parent);

			friend class Object;
	};
}