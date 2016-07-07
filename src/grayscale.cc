#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
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
    if (first_ == last_)
      return nullptr;

    cv::Mat* frame = (cv::Mat*) image;
    if (!frame)
    {
      std::cout << "ERROR" << std::endl;
      return nullptr;
    }

    for (int i = 0; i < frame->rows; i++)
    {
      for (int j = 0; j < frame->cols; j++)
      {
        cv::Vec3b &current_img = frame->at<cv::Vec3b>(j, i);
        unsigned int blue = current_img[0]; // B
        unsigned int green = current_img[1]; // G
        unsigned int red = current_img[2]; // R

        current_img[0] = (blue + red + green) / 3;
        current_img[1] = (blue + red + green) / 3;
        current_img[2] = (blue + red + green) / 3;
      }
    }
    ++first_;
    return frame;
  }

}

