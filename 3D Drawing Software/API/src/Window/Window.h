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
		private:
			class WindowEvents {
				public:
					static void SetResolution(int width, int height) {
						s_Reschange = true;
						s_Width = width;
						s_Height = height;
					}
					static inline int s_ScrollOffset = 0;
					static inline int s_Width = 0;
					static inline int s_Height = 0;
					static inline bool s_Reschange = 0;
			};

		public:
			Window(int width, int height, double fps_limit, MultiSampling msaa);
			~Window();

			void EnableVideoOutput(std::string_view output_folder_path, float video_fps);

			void Run(Scene& scene);

		private:
			int			m_VideoCount = 0;
			bool		m_VideoOutputEnabled = false;
			bool		m_IsRecording = false;
			float		m_VideoFps = 0.0f;
			int			m_Width, m_Height;
			double		m_FpsLimit;
			MultiSampling m_MSAA;
			std::shared_ptr<GLFWwindow>			m_Window;
			std::vector<std::function<void()>>	m_Updates;
			std::string m_VideoOutputFolderPath = "";
	};
}