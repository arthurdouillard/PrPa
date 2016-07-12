#include "grayscale.hh"


namespace filters
{
  GrayscaleFilter::GrayscaleFilter(tbb::filter::mode mode)
    : ModelFilter(mode, "grayscale")
  {}

  void* GrayscaleFilter::operator()(void* ptr)
  {
    // end the pipeline after the last image
    cv::Mat* img = (cv::Mat*) ptr;

    for (int i = 0; i < img->rows; i++)
    {
      for (int j = 0; j < img->cols; j++)
      {
        cv::Vec3b &current_img = img->at<cv::Vec3b>(i, j);
        unsigned char blue = current_img[0]; // R
        unsigned char green = current_img[1]; // G
        unsigned char red = current_img[2]; // B

        current_img[0] = (blue + red + green) / 3;
        current_img[1] = (blue + red + green) / 3;
        current_img[2] = (blue + red + green) / 3;
      }
    }

    return img;
  }

}

