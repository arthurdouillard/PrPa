#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  using frame_iterator = std::vector<cv::Mat>::iterator;

  class Sharpen : public ModelFilter
  {
    public:
      Sharpen(tbb::filter::mode);
      void *operator()(void* image);
  };

} // filters
