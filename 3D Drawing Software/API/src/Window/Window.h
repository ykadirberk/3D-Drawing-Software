#pragma once

#include "../Core/DLLBuild.h"
#include "../Scene/Scene.h"

#include <GLFW/glfw3.h>
#include <memory>
#include <functional>
#include <vector>

namespace dra {
	enum class MultiSampling {
		x2 = 2,
		x4 = 4,
		x8 = 8,
		x16 = 16
	}; 

	class _API Window {
		public:
			Window(int width, int height, double fps_limit, MultiSampling msaa);
			~Window();

			void Run(const Scene& scene);

		private:
			int m_Width, m_Height;
			double								m_FpsLimit;
			MultiSampling m_MSAA;
			std::shared_ptr<GLFWwindow>			m_Window;
			std::vector<std::function<void()>>	m_Updates;
	};
}