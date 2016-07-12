#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"

namespace filters
{
  class Edge : public ModelFilter
  {
    public:
      Edge(tbb::filter::mode);
      void *operator()(void* image);
      void *applyX(void* image);
      void *applyY(void* image);
  };

} // filters
