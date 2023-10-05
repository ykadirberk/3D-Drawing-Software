#pragma once

#include <memory>
#include <vector>

#include "../DLLBuild.h"
#include "../Transform/Transform.h"

namespace dra {

	class _API Object {
		public:
			Object(Object* parent);
			virtual ~Object() {}

			[[nodiscard]] virtual Object* GetParent() noexcept;
			[[nodiscard]] virtual Transform& GetTransform() noexcept;
			virtual void SetParent(Object* parent) noexcept;

		protected:
			Transform m_Transform;
			Object* m_Parent;
			std::vector<std::weak_ptr<Object>> m_Children;
	};
}