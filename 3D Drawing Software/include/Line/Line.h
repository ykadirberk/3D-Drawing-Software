#pragma once
#include "../Core/DLLBuild.h"
#include "../Shape/Shape.h"

namespace dra {
	class _API Line : public Shape {
		public:
			Line();
			~Line() override;

			void Draw() override;
	};
}