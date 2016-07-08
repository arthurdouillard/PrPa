#include <algorithm>
#include <cmath>
#include "binary.hh"


namespace filters
{
  Binary::Binary(tbb::filter::mode mode,
               frame_iterator first, frame_iterator last)
    : ModelFilter(mode, "binary")
    , first_(first)
    , last_(last)
  {}

  void* Binary::operator()(void* ptr)
  {
    // end the pipeline after the last image
    if (first_ == last_)
      return nullptr;
    if (ptr != nullptr)
      img_ = *(static_cast<cv::Mat*>(ptr));
    else
      img_ = *first_;

    for (int i = 0; i < img_.rows; i++)
    {
      for (int j = 0; j < img_.cols; j++)
      {
        cv::Vec3b &current_img = img_.at<cv::Vec3b>(i, j);
        unsigned char red = current_img[0]; // R
        unsigned char green = current_img[1]; // G
        unsigned char blue = current_img[2]; // B

        unsigned char binary = (red + green + blue > 368) * 255;
        for (int t = 0; t < 3; ++t)
          current_img[t] = binary;
      }
    }
    ++first_;

    return &img_;
  }

}

