#include "Video.h"
#include <iostream>
extern "C" {
#include <libavcodec/avcodec.h>

#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
}

dra::Video::Video(std::string_view output_file_path, int width, int height, int fps) 
    : m_Width(width), m_Height(height), m_Fps(fps)
{
    int ret;

    m_AVCodec_codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
    if (!m_AVCodec_codec) {
        fprintf(stderr, "Codec vp9 not found\n");
        exit(1);
    }

    m_AVCodecContext_c = avcodec_alloc_context3(static_cast<const AVCodec*>(m_AVCodec_codec));
    if (!m_AVCodecContext_c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        exit(1);
    }

    m_AVPacket_pkt = av_packet_alloc();
    if (!m_AVPacket_pkt)
        exit(1);

    static_cast<AVCodecContext*>(m_AVCodecContext_c)->bit_rate = 400000;

    static_cast<AVCodecContext*>(m_AVCodecContext_c)->width = width;
    static_cast<AVCodecContext*>(m_AVCodecContext_c)->height = height;

    static_cast<AVCodecContext*>(m_AVCodecContext_c)->time_base = { 1, fps };
    static_cast<AVCodecContext*>(m_AVCodecContext_c)->framerate = { fps, 1 };

    static_cast<AVCodecContext*>(m_AVCodecContext_c)->gop_size = 10;
    static_cast<AVCodecContext*>(m_AVCodecContext_c)->max_b_frames = 1;
    static_cast<AVCodecContext*>(m_AVCodecContext_c)->pix_fmt = AV_PIX_FMT_RGBA;

    if (static_cast<const AVCodec*>(m_AVCodec_codec)->id == AV_CODEC_ID_H264)
        av_opt_set(static_cast<AVCodecContext*>(m_AVCodecContext_c)->priv_data, "preset", "slow", 0);

    ret = avcodec_open2(static_cast<AVCodecContext*>(m_AVCodecContext_c), static_cast<const AVCodec*>(m_AVCodec_codec), NULL);

    //m_OutputFile = fopen(filename, "wb");
    m_OutputFile.open(output_file_path.data(), std::ios::binary);
    if (!m_OutputFile.is_open()) {
        std::cerr << "Could not open " << output_file_path.data() << std::endl;
        exit(1);
    }

    m_AVFrame_frame = av_frame_alloc();
    if (!m_AVFrame_frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        exit(1);
    }
    static_cast<AVFrame*>(m_AVFrame_frame)->format = static_cast<AVCodecContext*>(m_AVCodecContext_c)->pix_fmt;
    static_cast<AVFrame*>(m_AVFrame_frame)->width = static_cast<AVCodecContext*>(m_AVCodecContext_c)->width;
    static_cast<AVFrame*>(m_AVFrame_frame)->height = static_cast<AVCodecContext*>(m_AVCodecContext_c)->height;

    ret = av_frame_get_buffer(static_cast<AVFrame*>(m_AVFrame_frame), 0);
    if (ret < 0) {
        fprintf(stderr, "Could not allocate the video frame data\n");
        exit(1);
    }
}

dra::Video::~Video()
{
    Encode(nullptr);

    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    if (static_cast<const AVCodec*>(m_AVCodec_codec)->id == AV_CODEC_ID_MPEG1VIDEO || static_cast<const AVCodec*>(m_AVCodec_codec)->id == AV_CODEC_ID_MPEG2VIDEO) {
        m_OutputFile.write(reinterpret_cast<const char*>(endcode), sizeof(endcode));
    }
    m_OutputFile.close();

    AVCodecContext* c = static_cast<AVCodecContext*>(m_AVCodecContext_c);
    AVFrame* frame = static_cast<AVFrame*>(m_AVFrame_frame);
    AVPacket* pkt = static_cast<AVPacket*>(m_AVPacket_pkt);

    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);
}

void dra::Video::FeedFrame(unsigned char* frame_image)
{
    int ret, x, y;
    AVCodecContext* c = static_cast<AVCodecContext*>(m_AVCodecContext_c);
    AVPacket* pkt = static_cast<AVPacket*>(m_AVPacket_pkt);
    AVFrame* frame = static_cast<AVFrame*>(m_AVFrame_frame);

    ret = av_frame_make_writable(frame);
    if (ret < 0)
        exit(1);

    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x += 4) {
            frame->data[0][y * frame->linesize[0] + x] = frame_image[y * m_Width + x];
            frame->data[0][y * frame->linesize[0] + x + 1] = frame_image[y * m_Width + x + 1];
            frame->data[0][y * frame->linesize[0] + x + 2] = frame_image[y * m_Width + x + 2];
            frame->data[0][y * frame->linesize[0] + x + 3] = frame_image[y * m_Width + x + 3];
        }
    }

    frame->pts = m_FrameNum++;

    Encode(m_AVFrame_frame);
}

void dra::Video::Encode(void* tframe)
{
    int ret;

    AVCodecContext* enc_ctx = static_cast<AVCodecContext*>(m_AVCodecContext_c);
    AVPacket* pkt = static_cast<AVPacket*>(m_AVPacket_pkt);
    AVFrame* frame = static_cast<AVFrame*>(tframe);

    if (frame) {
        std::cout << "Send frame " << frame->pts << std::endl;
    }
        
    ret = avcodec_send_frame(enc_ctx, frame);
    if (ret < 0) {
        std::cerr << "Error sending a frame for encoding" << std::endl;
        exit(1);
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(enc_ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            std::cerr << "Error during encoding" << std::endl;
            exit(1);
        }

        std::cout << "Write packet " << pkt->pts << " (size=" << pkt->size << ")" << std::endl;
        m_OutputFile.write(reinterpret_cast<const char*>(pkt->data), pkt->size);
        av_packet_unref(pkt);
    }
}
