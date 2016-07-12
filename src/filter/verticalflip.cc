#include <algorithm>
#include <cmath>
#include "verticalflip.hh"


namespace filters
{
  VerticalFlip::VerticalFlip(tbb::filter::mode mode)
    : ModelFilter(mode, "vflip")
  {}

  void* VerticalFlip::operator()(void* ptr)
  {

    cv::Mat* img = (cv::Mat*) ptr;
    cv::Mat* rotated = new cv::Mat(img->rows, img->cols, img->type());

    for (int i = 0; i < img->cols; i++)
    {
      for (int j = 0; j < img->rows; j++)
      {
        rotated->at<cv::Vec3b>(j, img->cols - 1 - i) = img->at<cv::Vec3b>(j, i);
      }
    }

    return rotated;
  }

}

