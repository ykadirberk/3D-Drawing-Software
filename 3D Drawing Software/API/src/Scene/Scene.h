#pragma once

#include <functional>
#include <vector>

#include "../Core/DLLBuild.h"
#include "../Camera/Camera.h"
#include "../ext/glm/glm.hpp"

namespace dra {
	class _API Video;

	class _API Scene {
		public:
			Scene();
			~Scene();

			void SetCamera(std::shared_ptr<Camera> camera, float focus_x, float focus_y, float focus_z);
			void SetProjectionCamera(float field_of_view, float width, float height);
			void SetOrthogonalCamera(float width, float height);

			void InsertUpdateFunction(std::function<void()> t);
			void InsertRenderFunction(std::function<void(Camera*)> t);

			void SendMousePosition(float x, float y);

			void RotateMainCameraAroundFocus();
			void ZoomMainCamera(float zoom_direction);

		private:
			float m_PrevMousePositionX = 0;
			float m_PrevMousePositionY = 0;
			float m_MousePositionX = 0;
			float m_MousePositionY = 0;

			float m_ScreenWidth = 0;
			float m_ScreenHeight = 0;

			std::shared_ptr<Camera> m_MainCamera;
			std::shared_ptr<Object> m_focusPoint;
			std::shared_ptr<Camera> m_Camera;
			
			std::vector<std::function<void()>> m_Updates;
			std::vector<std::function<void(Camera*)>> m_Renders;

			void RunUpdates() const;
			void RunRenders() const;

			friend class Window;
			friend class Video;
	};
}