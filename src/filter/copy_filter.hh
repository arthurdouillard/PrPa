#include "modelfilter.hh"
#include <vector>

namespace filters
{
  class CopyFilter : public ModelFilter
  {
    public:
      CopyFilter(tbb::filter::mode, std::vector<cv::VideoCapture*> caps);

      void* operator()(void* image);

    private:
      std::vector<cv::VideoCapture*> caps_;
  };
}
