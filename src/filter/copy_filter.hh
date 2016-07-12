#include "modelfilter.hh"

namespace filters
{
  class CopyFilter : public ModelFilter
  {
    public:
      CopyFilter(tbb::filter::mode, cv::VideoCapture& cap);

      void* operator()(void* image);

    private:
      cv::VideoCapture cap_;
  };
}
