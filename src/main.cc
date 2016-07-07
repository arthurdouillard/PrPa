#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "options/options.hh"

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
  auto frames = copy_video(cap);

  launch_pipeline(frames, opt);
}


void launch_pipeline(std::vector<cv::Mat>& frames, Options& opt)
{
  // Get filters according to their names.
  //std::vector<tbb::filter> filters = get_filters(opt.filter);

  tbb::pipeline pipe;
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
    frames.push_back(frame);
  }

  return frames;
}
