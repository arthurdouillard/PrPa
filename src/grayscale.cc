#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "grayscale.hh"


namespace filters
{
  GrayscaleFilter::GrayscaleFilter(frame_iterator first, frame_iterator last)
    : tbb::filter(tbb::filter::serial_out_of_order)
    , first_(first)
    , last_(last)
  {}

  void* GrayscaleFilter::operator()(void* image)
  {
    // end the pipeline after the last image
    if (first == last)
      return nullptr;

    cv::Mat& frame = (cv::Mat) image;
    int cn = frame.channels();
    Scalar_<uint8_t> bgrPixel;

    for (int i = 0; i < frame.rows; i++)
    {
      uint8_t* rowPtr = frames_.row(i);
      for (int j = 0; j < frames_.cols; j++)
      {
        unsigned int blue = rowPtr[j*cn + 0]; // B
        unsigned int green = rowPtr[j*cn + 1]; // G
        unsigned int red = rowPtr[j*cn + 2]; // R

        Vec3b &current_img = frames_.at<Vec3b>(j, i);
        current_img = (blue + red + green) / 3;
    }
    ++first;
    return &frame;
  }

}

