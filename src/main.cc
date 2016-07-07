#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "main.hh"
#include "options/options.hh"
#include "filter/grayscale.hh"
#include "filter/writer.hh"

namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
  Options opt = options_parser(argc, argv);

  // Get input video.
  cv::VideoCapture cap(opt.video);

  if (!cap.isOpened())
  {
    std::cerr << "Error when reading video." << std::endl;
    exit(1);
  }

  // Get copy.
  cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);
  auto frames = copy_video(cap);

  // Create windows
  cv::namedWindow("w", cv::WINDOW_AUTOSIZE);

  // Fill vector of every filters
  std::vector<filters::ModelFilter> = load_filter(frames, opt);

  launch_pipeline(filters);
}


void launch_pipeline(std::vector<filters::ModelFilter>& filters)
{
  tbb::pipeline pipe;

  for (auto& f : filters)
    pipe.add_filter(f);

  pipe.run(1);
  pipe.clear();
}


std::vector<filters::ModelFilter> load_filter(std::vector<cv::Mat>& frames,
                                              Options& opt)
{
  std::vector<filters::ModelFilter> filters;

  filters::GrayscaleFilter filter(frames.begin(), frames.end());
  filters.push_back(filter);

  for (auto it = filters.begin(); it != filters.end(); it++)
  {
    bool flag = false;
    for (auto& name : opt.filter)
    {
      if (it->name_get() == name)
      {
        flag = true;
        break;
      }
    }

    if (!flag)
      filters.erase(it++);
  }

  filters::Writer writer;
  filters.push_back(writer);

  return filters;
}


std::vector<cv::Mat> copy_video(cv::VideoCapture& cap)
{
  // New video frames.
  std::vector<cv::Mat> frames;

  // Copy origin/al video to the new one.
  cv::Mat frame;
  while (true)
  {
    cap >> frame;
    if (frame.empty())
      break;
    frames.push_back(frame.clone());
  }
  return frames;
}
