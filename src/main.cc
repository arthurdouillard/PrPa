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

  cv::namedWindow("w", cv::WINDOW_AUTOSIZE);
  // Get copy.
  cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);
  auto frames = copy_video(cap);

  launch_pipeline(frames, opt);

/*
  for (auto& f : frames)
  {
    cv::imshow("w", f);
    cv::waitKey(20);
  }
*/
}


void launch_pipeline(std::vector<cv::Mat>& frames, Options& opt)
{
  // Get filters according to their names.
  //std::vector<tbb::filter> filters = get_filters(opt.filter);
  tbb::pipeline pipe;

  filters::GrayscaleFilter filter(frames.begin(), frames.end());
  filters::Writer writer;

  pipe.add_filter(filter);
  pipe.add_filter(writer);
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
    if (frame.empty())
      break;
    frames.push_back(frame.clone());
  }
  return frames;
}
