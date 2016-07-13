#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "modelfilter.hh"
#include "../options/options.hh"

namespace filters
{
  class TrueWriter : public ModelFilter
  {
    public:
      TrueWriter(tbb::filter::mode mode,
                 std::string dst,
                 cv::VideoCapture& cap,
                 Options& opt);
      // overload of tbb::filter
      void* operator()(void* image);

    private:
      cv::VideoWriter out_;
  };
}

