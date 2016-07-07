#include <algorithm>
#include <cmath>
#include "verticalflip.hh"


namespace filters
{
  VerticalFlip::VerticalFlip(tbb::filter::mode mode,
               frame_iterator first, frame_iterator last)
    : ModelFilter(mode, "vflip")
    , first_(first)
    , last_(last)
  {}

  void* VerticalFlip::operator()(void* ptr)
  {
    // end the pipeline after the last image
    if (first_ == last_)
      return nullptr;
    if (ptr != nullptr)
      img_ = *(static_cast<cv::Mat*>(ptr));
    else
      img_ = *first_;

    cv::Mat rotated(img_.rows, img_.cols, img_.type());

    for (int i = 0; i < img_.cols; i++)
    {
      for (int j = 0; j < img_.rows; j++)
      {
        rotated.at<cv::Vec3b>(j, img_.cols - 1 - i) = img_.at<cv::Vec3b>(j, i);
      }
    }
    ++first_;
    img_ = rotated;
    return &img_;
  }

}

