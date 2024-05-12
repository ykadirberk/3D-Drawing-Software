#pragma once

#include "../Core/DLLBuild.h"

#include <string>
#include <string_view>
#include <fstream>

namespace dra {
	class _API Video {
		public:
			Video(std::string_view output_file_path, int width, int height, int fps);
			~Video();

			void FeedFrame(unsigned char* frame_image);

		private:
			int m_Width, m_Height;
			int m_Fps;
			int m_FrameNum = 0;
			//char* filename;
			const void* m_AVCodec_codec;
			void* m_AVCodecContext_c = nullptr;
			void* m_AVFrame_frame = nullptr;
			void* m_AVPacket_pkt = nullptr;
			std::ofstream m_OutputFile;

			void Encode(void* tframe);
	};
}