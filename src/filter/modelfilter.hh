#pragma once

#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace filters
{
  using frame_iterator = std::vector<cv::Mat>::iterator;

  class ModelFilter : public tbb::filter
  {
    public:
      ModelFilter(tbb::filter::mode mode, std::string name);
      // overload of tbb::filter
      virtual void* operator()(void* image) = 0;

      const std::string name_get() const;

    private:
      std::string name_;
  };
}

