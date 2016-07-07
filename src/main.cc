#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "options/options.hh"
#include "grayscale.hh"

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

  cv::namedWindow("w", 1);
  for (auto f : frames)
  {
    imshow("w", f);
    waitKey(50);
  }

  waitKey(0);
}


void launch_pipeline(std::vector<cv::Mat>& frames, Options& opt)
{
  // Get filters according to their names.
  //std::vector<tbb::filter> filters = get_filters(opt.filter);

  tbb::pipeline pipe;

  GrayscaleFilter filter(frames.begin(), frames.end());

  pipe.add_filter(filter)
  pipe.run(1);
  pipe.clear();
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
