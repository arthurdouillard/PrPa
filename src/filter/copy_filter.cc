#include "copy_filter.hh"

namespace filters
{
  CopyFilter::CopyFilter(tbb::filter::mode mode, cv::VideoCapture& cap)
    : ModelFilter(mode, "copy")
    , cap_(cap)
  {}


  void* CopyFilter::operator()(void* ptr)
  {
    cv::Mat* ans = new cv::Mat;
    cv::Mat frame;
    cap_ >> frame;

    if (frame.empty())
      return nullptr;
    else
    {
      frame.copyTo(*ans);
      return ans;
    }
  }
}
