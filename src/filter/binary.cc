#include <algorithm>
#include <cmath>
#include "binary.hh"


namespace filters
{
  Binary::Binary(tbb::filter::mode mode)
    : ModelFilter(mode, "binary")
  {}

  void* Binary::operator()(void* ptr)
  {
    // end the pipeline after the last image
    cv::Mat* img = (cv::Mat*) ptr;

    for (int i = 0; i < img->rows; i++)
    {
      for (int j = 0; j < img->cols; j++)
      {
        cv::Vec3b &current_img = img->at<cv::Vec3b>(i, j);
        unsigned char red = current_img[0]; // R
        unsigned char green = current_img[1]; // G
        unsigned char blue = current_img[2]; // B

        unsigned char binary = (red + green + blue > 368) * 255;
        for (int t = 0; t < 3; ++t)
          current_img[t] = binary;
      }
    }

    return img;
  }

}

