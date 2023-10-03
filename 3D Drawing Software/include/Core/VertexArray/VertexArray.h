#pragma once

#include "../VertexBuffer/VertexBuffer.h"

namespace dra {

	class _API VertexBufferLayout;

	class _API VertexArray {
		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

			void Bind() const;
			void Unbind() const;
		private:
			unsigned int m_RendererID;
	};
}

