#ifndef VIDEO_CREATOR_H
#define VIDEO_CREATOR_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoCreator {
public:
    
    VideoCreator(const std::string& filename, int codec, double fps, cv::Size frameSize);
    void addFrame(const cv::Mat& frame);
    void finish();

private:
    std::string filename_;
    int codec_;
    double fps_;
    cv::Size frameSize_;
    cv::VideoWriter writer_;
};

#endif 
