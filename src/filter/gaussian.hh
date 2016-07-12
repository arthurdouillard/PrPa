#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  class Gaussian : public ModelFilter
  {
    public:
      Gaussian(tbb::filter::mode);
      void *operator()(void* image);
  };

} // filters
