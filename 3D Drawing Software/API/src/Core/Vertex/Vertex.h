#pragma once

#include <memory>
#include <vector>

#include "../DLLBuild.h"

#include "../ShaderArena/ShaderArena.h"
#include "../VertexArray/VertexArray.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../VertexBufferLayout/VertexBufferLayout.h"
#include "../Vector/Vector.h"

namespace dra {
	class _API Vertex {
		public:
			Vertex();
			~Vertex();

			[[nodiscard]] Vector<float> GetPosition() const noexcept;
		private:
			Vector<float> m_Center;

			std::vector<float> m_Positions;
			std::vector<unsigned int> m_Indices;

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;

	};
}