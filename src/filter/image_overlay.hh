#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  class ImageOverlay : public ModelFilter
  {
    public:
      ImageOverlay(tbb::filter::mode, cv::Mat overlay);
      // overload of tbb::filter
      void* operator()(void* image);

    private:
      cv::Mat overlay_;
  };
}

