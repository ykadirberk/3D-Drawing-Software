#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class VideoCreator {
public:
    VideoCreator(const std::string& filename, int codec, double fps, cv::Size frameSize)
        : filename_(filename), codec_(codec), fps_(fps), frameSize_(frameSize) {
        writer_.open(filename_, codec_, fps_, frameSize_, true);
        if (!writer_.isOpened()) {
            throw std::runtime_error("Could not open video writer.");
        }
    }

    void addFrame(const cv::Mat& frame) {
        if (frame.size() != frameSize_) {
            throw std::invalid_argument("Frame size does not match expected frame size.");
        }
        writer_ << frame;
    }

    void finish() {
        writer_.release();
    }

private:
    std::string filename_;
    int codec_;
    double fps_;
    cv::Size frameSize_;
    cv::VideoWriter writer_;
};

//
//int main() {
//    std::string filename = "output.avi";
//    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');  // Using Motion-JPEG codec
//    double fps = 30.0;
//    cv::Size frameSize(640, 480);
//
//    try {
//        VideoCreator videoCreator(filename, codec, fps, frameSize);
//
//        for (int i = 0; i < 100; ++i) {
//            
//            cv::Mat frame(frameSize, CV_8UC3, cv::Scalar(255, 255, 255));
//            //example
//            cv::circle(frame, cv::Point(320, 240), 50 + i, cv::Scalar(0, 0, 255), -1);
//
//            videoCreator.addFrame(frame);
//        }
//
//        videoCreator.finish();
//    } catch (const std::exception& ex) {
//        std::cerr << "Error: " << ex.what() << std::endl;
//        return -1;
//    }
//
//    return 0;
//}
