#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  class Emboss : public ModelFilter
  {
    public:
      Emboss(tbb::filter::mode);
      void *operator()(void* image);
  };

} // filters
