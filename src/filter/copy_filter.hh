#include "modelfilter.hh"
#include <vector>

namespace filters
{
  class CopyFilter : public ModelFilter
  {
    public:
      CopyFilter(tbb::filter::mode, std::vector<cv::VideoCapture*> caps);

      void* operator()(void* image);

      cv::Mat* merge_mat(cv::Mat* f1, cv::Mat f2);

    private:
      std::vector<cv::VideoCapture*> caps_;
  };
}
