#include "gaussian.hh"

namespace filters
{
  Gaussian::Gaussian(tbb::filter::mode mode)
    : ModelFilter(mode, "gaussian")
  {}

  void* Gaussian::operator()(void* ptr)
  {
    cv::Mat* img = (cv::Mat*) ptr;

    std::vector<std::vector<float>> kernel = {
      { 1, 2, 1 },
      { 2, 4, 2 },
      { 1, 2, 1 }
    };

    cv::Mat* copy = new cv::Mat;
    img.copyTo(*copy);

    for (int i = 1; i < img->rows - 1; i++)
    {
      for (int j = 1; j < img->cols - 1; j++)
      {
        int acc_r = 0;
        int acc_g = 0;
        int acc_b = 0;

        int x = (int) (i - kernel.size() / 2);
        int y = (int) (j - kernel.size() / 2);

        for (int row = 0; row < kernel.size(); row++, x++)
        {
          for (int pos = 0; pos < kernel[row].size(); pos++, y++)
          {
            int elt = kernel[row][pos];
            auto in = copy->at<cv::Vec3b>(x, y);

            acc_r += elt * in[0];
            acc_g += elt * in[1];
            acc_b += elt * in[2];
          }
        }

        auto& out = img->at<cv::Vec3b>(i, j);

        int coef = 16;
        acc_r = (int)(acc_r / coef);
        acc_g = (int)(acc_g / coef);
        acc_b = (int)(acc_b / coef);

        out[0] = acc_r < 0 ? 0 : acc_r;
        out[1] = acc_g < 0 ? 0 : acc_g;
        out[2] = acc_b < 0 ? 0 : acc_b;

      }
    }
    ++first_;

    return img;
  }

}
