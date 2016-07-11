#include "image_overlay.hh"


namespace filters
{
  ImageOverlay::ImageOverlay(tbb::filter::mode mode,
                                   frame_iterator first, frame_iterator last,
                                   cv::Mat overlay)
    : ModelFilter(mode, "img_overlay")
    , first_(first)
    , last_(last)
    , overlay_(overlay)
  {}

  void* ImageOverlay::operator()(void* ptr)
  {
    // end the pipeline after the last image
    if (first_ == last_)
      return nullptr;
    if (ptr != nullptr)
      img_ = *(static_cast<cv::Mat*>(ptr));
    else
      img_ = *first_;

    float delta_row = overlay_.rows / img_.rows;
    float delta_col = overlay_.cols / img_.cols;
    for (int i = 0; i < img_.rows; i++)
    {
      for (int j = 0; j < img_.cols; j++)
      {
        cv::Vec3b &current_img = img_.at<cv::Vec3b>(i, j);
        cv::Vec3b &overlay_img = overlay_.at<cv::Vec3b>(delta_row * i, delta_col * j);

        current_img += overlay_img;
      }
    }
    ++first_;

    return &img_;
  }

}

