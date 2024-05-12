#pragma once
#include "../DLLBuild.h"
#include <GL/glew.h>

namespace dra {
	class _API FrameBufferTexture
	{
		public:
			FrameBufferTexture(int width, int height);
			~FrameBufferTexture();

			unsigned char* GetPixelArray();
			void BindTexture();
			void UnbindTexture();
			void BindFrameBuffer();
			void UnbindFrameBuffer();
		private:
			int m_Width, m_Height;
			unsigned char* m_LastPixelArray = nullptr;
			unsigned int m_TextureId;
			unsigned int m_FrameBufferId;
	};
}