#pragma once

#include <vector>

#include "../Core/DLLBuild.h"
#include "../Shape/Shape.h"

#include "../PerspectiveCamera/PerspectiveCamera.h"

#include "../Core/ShaderArena/ShaderArena.h"
#include "../Core/Transform/Transform.h"
#include "../Core/VertexArray/VertexArray.h"
#include "../Core/VertexBuffer/VertexBuffer.h"
#include "../Core/IndexBuffer/IndexBuffer.h"
#include "../Core/VertexBufferLayout/VertexBufferLayout.h"

namespace dra {
	class _API Line : public Shape{
		public:
			Line(Object* parent);
			~Line() override;

			void Update() override;
			void Draw(Camera* camera) override;
		private:			
			std::vector<float> m_Positions;
			std::vector<unsigned int> m_Indices;

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}