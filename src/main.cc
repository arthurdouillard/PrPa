#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "main.hh"
#include "options/options.hh"
#include "filter/grayscale.hh"
#include "filter/writer.hh"
#include "filter/modelfilter.hh"
#include "filter/sepia.hh"

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

  // Create windows
  cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);

  // Fill vector of every filters
  auto filters = load_filter(frames, opt);

  launch_pipeline(filters);
}


void
launch_pipeline(std::vector<std::shared_ptr<filters::ModelFilter>> filters)
{
  tbb::pipeline pipe;

  for (auto& f : filters)
    pipe.add_filter(*f);

  int par = filters.size() == 1 ? filters.size() - 1 : 1;
  pipe.run(par);
  pipe.clear();
}


std::vector<std::shared_ptr<filters::ModelFilter>>
load_filter(std::vector<cv::Mat>& frames, Options& opt)
{
  tbb::filter::mode mode;
  if (opt.mode == "so")
    mode = tbb::filter::serial_out_of_order;
  else if (opt.mode == "si")
    mode = tbb::filter::serial_in_order;
  else
    mode = tbb::filter::parallel;

  std::vector<std::shared_ptr<filters::ModelFilter>> filters;

  // Load all filters
  auto gray = std::make_shared<filters::GrayscaleFilter>(mode, frames.begin(), frames.end());
  filters.push_back(gray);
  auto sepia = std::make_shared<filters::Sepia>(mode, frames.begin(), frames.end());
  filters.push_back(sepia);

  for (auto it = filters.begin(); it != filters.end();)
  {
    bool flag = false;
    for (auto& name : opt.filter)
    {
      if ((*it)->name_get() == name)
      {
        flag = true;
        break;
      }
    }

    if (!flag)
      filters.erase(it++);
    else
      it++;
  }

  auto writer = std::make_shared<filters::Writer>(mode);
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
