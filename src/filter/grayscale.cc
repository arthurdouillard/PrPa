#include "grayscale.hh"


namespace filters
{
  GrayscaleFilter::GrayscaleFilter(tbb::mode mode,
                                   frame_iterator first, frame_iterator last)
    : ModelFilter(mode, "grayscale")
    , first_(first)
    , last_(last)
  {}

  void* GrayscaleFilter::operator()(void* ptr)
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
        unsigned char blue = current_img[0]; // B
        unsigned char green = current_img[1]; // G
        unsigned char red = current_img[2]; // R

        current_img[0] = (blue + red + green) / 3;
        current_img[1] = (blue + red + green) / 3;
        current_img[2] = (blue + red + green) / 3;
      }
    }
    ++first_;

    return &img_;
  }

}

