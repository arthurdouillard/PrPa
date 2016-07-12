#include "copy_filter.hh"
#include <iostream>
namespace filters
{
  CopyFilter::CopyFilter(tbb::filter::mode mode, std::vector<cv::VideoCapture*> caps)
    : ModelFilter(mode, "copy")
    , caps_(caps)
  {}


  void* CopyFilter::operator()(void* ptr)
  {
    int alpha = 128;

    cv::Mat* ans = new cv::Mat;

    if (caps_.size() == 1)
    {
      cv::Mat f;
      (*caps_.front()) >> f;
      f.copyTo(*ans);
      return ans;
    }

    cv::Mat f1;
    cv::Mat f2;
    (*caps_.front()) >> f1;
    (*caps_.back())  >> f2;

    if (f1.empty() && f2.empty())
      return nullptr;
    else if (!f1.empty() && f2.empty())
      f1.copyTo(*ans);
    else if (!f2.empty() && f1.empty())
      return nullptr;
    else // none is empty
    {
      f1.copyTo(*ans);
      for (int row = 0; row < ans->rows; row++)
      {
        for (int col = 0; col < ans->cols; col++)
        {
          if (row < f2.rows && col < f2.cols)
          {
            auto& pixel = ans->at<cv::Vec3b>(row, col);
            auto& p2    = f2.at<cv::Vec3b>(row, col);

            int r = pixel[0] * alpha + p2[0] * alpha;
            int g = pixel[1] * alpha + p2[1] * alpha;
            int b = pixel[2] * alpha + p2[2] * alpha;

            r /= 255;
            g /= 255;
            b /= 255;

            pixel[0] = r;
            pixel[1] = g;
            pixel[2] = b;
          }
        }
      }
    }

    return ans;
  }
}
