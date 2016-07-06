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
  // New video frames.
  std::vector<cv::Mat> frames;

  if (!cap.isOpened())
  {
    std::cerr << "Error when reading video." << std::endl;
    exit(1);
  }

  // Copy original video to the new one.
  cv::Mat frame;
  while (true)
  {
    cap >> frame;
    frames.push_back(frame);
  }
}

