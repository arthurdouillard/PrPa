#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "true_writer.hh"


namespace filters
{

  TrueWriter::TrueWriter(tbb::filter::mode mode,
                         std::string dst,
                         cv::VideoCapture& cap,
                         Options& opt)
    : ModelFilter(mode, "true-writer")
  {
    auto fps = cap.get(CV_CAP_PROP_FPS);
    auto size = cv::Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),
                         (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));

    auto original = opt.video.front();
    auto ext = original.substr(original.find_last_of(".") + 1);

    auto dst_name = dst + "." + ext;

    cv::VideoWriter out_;
    out_.open(dst_name, -1, fps, size, true);
  }

  void* TrueWriter::operator()(void* image)
  {
    cv::Mat* frame = (cv::Mat*) image;
    out_ << (*frame);

    return nullptr;
  }
}
