#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "main.hh"
#include "options/options.hh"
#include "filter/grayscale.hh"
#include "filter/binary.hh"
#include "filter/writer.hh"
#include "filter/modelfilter.hh"
#include "filter/sepia.hh"
#include "filter/sharpen.hh"
#include "filter/gaussian.hh"
#include "filter/verticalflip.hh"
#include "timer.hh"
#include <iomanip>

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

  // If no filter, just show the video.
  if (opt.filter.empty())
  {
    cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);
    while (true)
    {
      cv::Mat frame;
      cap >> frame;
      if (frame.empty())
        exit(0);
      cv::imshow("vidz", frame);
      cv::waitKey(20);
    }
  }
  // Get copy.
  auto frames = copy_video(cap);

  // Create windows
  if (!opt.benchmark)
    cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);

  if (!opt.benchmark)
    exec(frames, opt);
  else
  {
    std::cout << "Benchmark... Please wait..." << std::endl;
    std::vector<std::string> modes = { "so", "si", "pa" };
    for (auto mode : modes)
    {
      opt.mode = mode;
      exec(frames, opt);
    }
  }
}


void exec(std::vector<cv::Mat>& frames, Options& opt)
{
  double time;
  {
    scoped_timer t(time);
    launch_pipeline(load_filter(frames, opt));
  }

  if (opt.timer || opt.benchmark)
  {
    std::cout << " -----------------------------------------." << std::endl;
    std::cout << "/     TIME : " << std::setfill(' ') << std::setw(22)
                                 << time << " sec   |" << std::endl;
    std::cout << "|     MODE : " << std::setfill(' ') << std::setw(26)
                                 << opt.mode << "   /" << std::endl;
    std::cout << " ----------------------------------------- " << std::endl;
  }
}

void
launch_pipeline(std::vector<filters::ModelFilter*> filters)
{
  tbb::pipeline pipe;

  for (auto& f : filters)
    pipe.add_filter(*f);

  int par = filters.size() == 1 ? filters.size() - 1 : 1;
  pipe.run(par);
  pipe.clear();
}


std::vector<filters::ModelFilter*>
load_filter(std::vector<cv::Mat>& frames, Options& opt)
{
  tbb::filter::mode mode;
  if (opt.mode == "so")
    mode = tbb::filter::serial_out_of_order;
  else if (opt.mode == "si")
    mode = tbb::filter::serial_in_order;
  else
    mode = tbb::filter::parallel;

  std::vector<filters::ModelFilter*> filters;

  // Load all filters
  filters.push_back(new filters::GrayscaleFilter(mode, frames.begin(), frames.end()));
  filters.push_back(new filters::Binary(mode, frames.begin(), frames.end()));
  filters.push_back(new filters::Sepia(mode, frames.begin(), frames.end()));
  filters.push_back(new filters::Sharpen(mode, frames.begin(), frames.end()));
  filters.push_back(new filters::Gaussian(mode, frames.begin(), frames.end()));
  filters.push_back(new filters::VerticalFlip(mode, frames.begin(), frames.end()));

  std::vector<filters::ModelFilter*> filtered_filters;
  for (auto& name : opt.filter)
  {
    for (auto it = filters.begin(); it != filters.end(); it++)
    {
      if ((*it)->name_get() == name)
      {
        filtered_filters.emplace_back(*it);
        break;
      }
    }
  }

  if (filtered_filters.size() == 0)
  {
    std::cerr << "No valid filters were given." << std::endl;
    exit(1);
  }

  if (!opt.benchmark)
    filtered_filters.push_back(new filters::Writer(mode));

  return filtered_filters;
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
