#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "writer.hh"


namespace filters
{

  Writer::Writer()
    : tbb::filter(tbb::filter::serial_out_of_order)
  {}

  void* Writer::operator()(void* image)
  {
    cv::Mat* input = (cv::Mat*) image;
    // FIXME
    return nullptr;
  }
}
