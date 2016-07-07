#include "sharpen.hh"

namespace filters
{
  Sharpen::Sharpen(tbb::filter::mode mode,
                   frame_iterator first, frame_iterator last)
    : ModelFilter(mode, "sharpen")
    , first_(first)
    , last_(last)
  {}

  void* Sharpen::operator()(void* ptr)
  {
    // end the pipeline after the last image
    if (first_ == last_)
      return nullptr;

    img_ = (ptr != nullptr) ? *(static_cast<cv::Mat*>(ptr)) : *first_;

    std::vector<std::vector<float>> kernel = {
      { 0, -1, 0 },
      { -1, 5, -1 },
      { -1, 0, -1 }
    };

    cv::Mat copy = img_.clone();

    for (int i = 1; i < img_.rows - 1; i++)
    {
      for (int j = 1; j < img_.cols - 1; j++)
      {
        int acc_r = 0;
        int acc_g = 0;
        int acc_b = 0;

        for (int row = 0; row < kernel.size(); row++)
        {
          for (int pos = 0; pos < kernel[row].size(); pos++)
          {
            int elt = kernel[row][pos];
            int x = i - row < 0 ? 0 : i - row;
            int y = j - pos < 0 ? 0 : j - pos;
            auto in = img_.at<cv::Vec3b>(x, y);

            acc_r += elt * in[2];
            acc_g += elt * in[1];
            acc_b += elt * in[0];
          }
        }

        auto& out = copy.at<cv::Vec3b>(i, j);
        out[2] = acc_r < 0 ? 0 : acc_r;
        out[1] = acc_g < 0 ? 0 : acc_g;
        out[0] = acc_b < 0 ? 0 : acc_b;
      }
    }
    ++first_;

    img_ = copy;

    return &img_;
  }

}
