#include "gaussian.hh"

namespace filters
{
  Gaussian::Gaussian(tbb::filter::mode mode,
                     frame_iterator first, frame_iterator last)
    : ModelFilter(mode, "gaussian")
    , first_(first)
    , last_(last)
  {}

  void* Gaussian::operator()(void* ptr)
  {
    // end the pipeline after the last image
    if (first_ == last_)
      return nullptr;

    img_ = (ptr != nullptr) ? *(static_cast<cv::Mat*>(ptr)) : *first_;

    std::vector<std::vector<float>> kernel = {
      { 1, 2, 1 },
      { 2, 4, 2 },
      { 1, 2, 1 }
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

            acc_r += elt * in[0];
            acc_g += elt * in[1];
            acc_b += elt * in[2];
          }
        }

        auto& out = copy.at<cv::Vec3b>(i, j);
        out[0] = acc_r < 0 ? 0 : (acc_r > 255 ? 255 : acc_r);
        out[1] = acc_g < 0 ? 0 : (acc_g > 255 ? 255 : acc_g);
        out[2] = acc_b < 0 ? 0 : (acc_b > 255 ? 255 : acc_b);


        int coef = 9;
        out[0] = (int)(out[0] / coef);
        out[1] = (int)(out[1] / coef);
        out[2] = (int)(out[2] / coef);

      }
    }
    ++first_;

    img_ = copy;

    return &img_;
  }

}
