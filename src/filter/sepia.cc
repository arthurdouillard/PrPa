#include <algorithm>
#include <cmath>
#include "sepia.hh"


namespace filters
{
  Sepia::Sepia(tbb::filter::mode mode)
    : ModelFilter(mode, "sepia")
  {}

  void* Sepia::operator()(void* ptr)
  {
    // end the pipeline after the last image
    cv::Mat* img = (cv::Mat*) ptr;

    for (int i = 0; i < img->rows; i++)
    {
      for (int j = 0; j < img->cols; j++)
      {
        cv::Vec3b &current_img = img->at<cv::Vec3b>(i, j);
        unsigned char blue = current_img[2]; // B
        unsigned char green = current_img[1]; // G
        unsigned char red = current_img[0]; // R

        current_img[2] = std::min(255,
              (int) std::lround(red * 0.393 + green * 0.769 + blue * 0.189));
        current_img[1] = std::min(255,
              (int) std::lround(red * 0.349 + green * 0.689 + blue * 0.168));
        current_img[0] = std::min(255,
              (int) std::lround(red * 0.272 + green * 0.534 + blue * 0.131));
      }
    }
    return img;
  }

}

