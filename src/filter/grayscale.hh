#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace filters
{
  using frame_iterator = std::vector<cv::Mat>::iterator;

  class GrayscaleFilter : public ModelFilter
  {
    public:
      GrayscaleFilter(tbb::mode, frame_iterator first, frame_iterator last);
      // overload of tbb::filter
      void* operator()(void* image);

    private:
      frame_iterator first_;
      frame_iterator last_;
      cv::Mat img_;
  };
}

