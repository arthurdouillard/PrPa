#include <algorithm>
#include <cmath>
#include "invert.hh"


namespace filters
{
  Invert::Invert(tbb::filter::mode mode)
    : ModelFilter(mode, "invert")
  {}

  void* Invert::operator()(void* ptr)
  {
    // end the pipeline after the last image
    cv::Mat* img = (cv::Mat*) ptr;

    for (int i = 0; i < img->rows; i++)
    {
      for (int j = 0; j < img->cols; j++)
      {
        cv::Vec3b &current_img = img->at<cv::Vec3b>(i, j);
        unsigned char blue = 255 - current_img[2]; // B
        unsigned char green = 255 - current_img[1]; // G
        unsigned char red = 255 - current_img[0]; // R

        current_img[2] = blue;
        current_img[1] = green;
        current_img[0] = red;
      }
    }
    return img;
  }

}

