#include "image_overlay.hh"


namespace filters
{
  ImageOverlay::ImageOverlay(tbb::filter::mode mode,
                             cv::Mat overlay)
    : ModelFilter(mode, "img_overlay")
    , overlay_(overlay)
  {}

  void* ImageOverlay::operator()(void* ptr)
  {
    cv::Mat* img = (cv::Mat*) ptr;

    float delta_row = overlay_.rows / img->rows;
    float delta_col = overlay_.cols / img->cols;

    for (int i = 0; i < img->rows; i++)
    {
      for (int j = 0; j < img->cols; j++)
      {
        cv::Vec3b &current_img = img->at<cv::Vec3b>(i, j);
        cv::Vec3b &overlay_img = overlay_.at<cv::Vec3b>(delta_row * i, delta_col * j);

        current_img += overlay_img;
      }
    }

    return img;
  }

}

