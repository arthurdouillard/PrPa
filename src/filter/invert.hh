#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  using frame_iterator = std::vector<cv::Mat>::iterator;

  class Invert : public ModelFilter
  {
    public:
      Invert(tbb::filter::mode);
      // overload of tbb::filter
      void* operator()(void* image);
  };
}

