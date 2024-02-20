#pragma once

#include "../Core/DLLBuild.h"
#include "../Scene/Scene.h"

#include <GLFW/glfw3.h>
#include <memory>
#include <functional>
#include <vector>

namespace dra {
	class _API Window {
		public:
			Window();
			~Window();

			void Run(const Scene& scene);

		private:
			double								m_FpsLimit;
			std::shared_ptr<GLFWwindow>			m_Window;
			std::vector<std::function<void()>>	m_Updates;
	};
}