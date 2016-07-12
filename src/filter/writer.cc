#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "writer.hh"


namespace filters
{

  Writer::Writer(tbb::filter::mode mode)
    : ModelFilter(mode, "writer")
  {}

  void* Writer::operator()(void* image)
  {
    cv::Mat* input = (cv::Mat*) image;
    cv::imshow("vidz", *input);

    cv::waitKey(30);

    return nullptr;
  }
}
