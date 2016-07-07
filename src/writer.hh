#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace filters
{
  using frame_iterator = std::vector<cv::Mat>::iterator;

  class Writer : public tbb::filter
  {
    public:
      Write();
      // overload of tbb::filter
      void* operator()(void* image);

    private:
      cv::Mat img_;

  };
}

