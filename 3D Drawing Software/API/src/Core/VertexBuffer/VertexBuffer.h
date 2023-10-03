#pragma once

#include "../DLLBuild.h"

namespace dra {
	class _API VertexBuffer {
		public:
			VertexBuffer(const void* data, unsigned int size);
			~VertexBuffer();

			void Bind() const;
			void Unbind() const;
		private:
			unsigned int m_RendererID;
	};
}

