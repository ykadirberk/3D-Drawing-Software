#pragma once

#include <functional>
#include <vector>

#include "../Core/DLLBuild.h"
#include "../Camera/Camera.h"

namespace dra {
	class _API Video;

	class _API Scene {
		public:
			Scene();
			~Scene();

			void SetCamera(std::shared_ptr<Camera> camera);
			void SetProjectionCamera(float field_of_view, float width, float height);

			void InsertUpdateFunction(std::function<void()> t);
			void InsertRenderFunction(std::function<void(Camera*)> t);

		private:
			std::shared_ptr<Camera> m_MainCamera;
			std::shared_ptr<Camera> m_Camera;
			
			std::vector<std::function<void()>> m_Updates;
			std::vector<std::function<void(Camera*)>> m_Renders;

			void RunUpdates() const;
			void RunRenders(Camera* camera) const;

			friend class Window;
			friend class Video;
	};
}