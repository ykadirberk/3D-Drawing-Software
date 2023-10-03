#pragma once
#include "../Core/DLLBuild.h"
#include "../Shape/Shape.h"

#include "../Core/Transform/Transform.h"

namespace dra {
	class _API Line : public Shape {
		public:
			Line();
			~Line() override;

			Transform& GetTransform();

			void Draw() override;
		private:
			Transform m_Transform;
	};
}