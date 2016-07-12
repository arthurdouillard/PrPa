#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  class VerticalFlip : public ModelFilter
  {
    public:
      VerticalFlip(tbb::filter::mode);
      // overload of tbb::filter
      void* operator()(void* image);
  };
}

