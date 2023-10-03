#pragma once
#include "../Core/DLLBuild.h"
#include "../Line/Line.h"
#include "../Core/ShaderArena/ShaderArena.h"
#include "../PerspectiveCamera/PerspectiveCamera.h"

namespace dra {
	class _API Scene {
		public:
			Scene();
			~Scene();

			void Render();
		private:

			PerspectiveCamera m_Camera;
			Line m_Line;
	};
}
