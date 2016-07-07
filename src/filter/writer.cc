#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "writer.hh"


namespace filters
{

  Writer::Writer(tbb::mode mode)
    : ModelFilter(mode, "writer")
  {}

  void* Writer::operator()(void* image)
  {
    cv::Mat* input = (cv::Mat*) image;
    cv::imshow("vidz", *input);
    if (cv::waitKey(30) > 0)
      return 0;

    return nullptr;
  }
}
