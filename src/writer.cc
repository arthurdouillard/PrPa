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
    std::cerr << "to" << std::endl;
    cv::Mat* input = (cv::Mat*) image;
    // FIXME
    cv::imshow("w", *input);
    if (cv::waitKey(30) > 0)
      return 0;

    return nullptr;
  }
}
