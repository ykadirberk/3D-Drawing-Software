#pragma once
#include "../Core/DLLBuild.h"
#include "../Line/Line.h"
#include "../Core/ShaderArena/ShaderArena.h"
#include "../PerspectiveCamera/PerspectiveCamera.h"

#include "../Core/VertexArray/VertexArray.h"
#include "../Core/VertexBuffer/VertexBuffer.h"
#include "../Core/IndexBuffer/IndexBuffer.h"
#include "../Core/VertexBufferLayout/VertexBufferLayout.h"


namespace dra {
	class _API Scene {
		public:
			Scene();
			~Scene();

			void Render();
		private:
			float m_Color_r = 0.0f;
			float m_Change_r = 0.001f;

			std::unique_ptr<VertexArray> m_VAO;
			std::unique_ptr<VertexBuffer> m_VertexBuffer;
			std::unique_ptr<IndexBuffer> m_IndexBuffer;

			PerspectiveCamera m_Camera;
			Line m_Line;
	};
}
