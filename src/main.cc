#include "main.hh"

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

  // Create windows
  if (!opt.benchmark)
    cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);

  if (!opt.benchmark)
    exec(cap, opt);
  else
  {
    std::cout << "Benchmark... Please wait..." << std::endl;
    std::vector<std::string> modes = { "so", "si", "pa" };
    for (auto mode : modes)
    {
      opt.mode = mode;
      exec(cap, opt);
    }
  }
}


void exec(cv::VideoCapture& cap, Options& opt)
{
  double time;
  {
    scoped_timer t(time);
    launch_pipeline(load_filter(cap, opt), opt);
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
launch_pipeline(std::vector<filters::ModelFilter*> filters, Options& opt)
{
  tbb::pipeline pipe;

  for (auto& f : filters)
    pipe.add_filter(*f);

  pipe.run(std::thread::hardware_concurrency());
  pipe.clear();
}


std::vector<filters::ModelFilter*>
load_filter(cv::VideoCapture& cap, Options& opt)
{
  tbb::filter::mode mode;
  if (opt.mode == "so")
    mode = tbb::filter::serial_out_of_order;
  else if (opt.mode == "si")
    mode = tbb::filter::serial_in_order;
  else
    mode = tbb::filter::parallel;

  std::vector<filters::ModelFilter*> filters;

  cv::Mat overlay = cv::imread("tests/overlay.png", CV_LOAD_IMAGE_COLOR);

  // Load all filters
  filters.push_back(new filters::ImageOverlay(mode, overlay));
  filters.push_back(new filters::GrayscaleFilter(mode));
  filters.push_back(new filters::Binary(mode));
  filters.push_back(new filters::Sepia(mode));
  filters.push_back(new filters::Sharpen(mode));
  filters.push_back(new filters::Gaussian(mode));
  filters.push_back(new filters::VerticalFlip(mode));

  std::vector<filters::ModelFilter*> filtered_filters;
  filtered_filters.push_back(new filters::CopyFilter(tbb::filter::serial_in_order, cap));
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
    filtered_filters.push_back(new filters::Writer(tbb::filter::serial_in_order));
  else
    filtered_filters.push_back(new filters::FalseWriter(tbb::filter::serial_in_order));

  return filtered_filters;
}
