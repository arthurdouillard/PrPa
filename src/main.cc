#include "main.hh"

namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
  Options opt = options_parser(argc, argv);

  // Get input video.
  std::vector<cv::VideoCapture*> caps;
  for (auto& v : opt.video)
  {
    caps.push_back(new cv::VideoCapture(v));

    if (!caps.back()->isOpened())
    {
      std::cerr << "Error when reading video." << std::endl;
      exit(1);
    }
  }

  // If no filter, just show the video.
  if (opt.filter.empty())
  {
    cv::namedWindow("vidz", cv::WINDOW_AUTOSIZE);
    while (true)
    {
      cv::Mat frame;
      (*caps.front()) >> frame;
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
    exec(caps, opt);
  else
  {
    std::cout << "Benchmark... Please wait..." << std::endl;
    std::vector<std::string> modes = { "so", "si", "pa" };
    for (auto mode : modes)
    {
      opt.mode = mode;
      exec(caps, opt);
    }
  }
}


void exec(std::vector<cv::VideoCapture*> caps, Options& opt)
{
  double time;
  {
    scoped_timer t(time);
    if (opt.mode == "se")
      launch_seq(load_filter(caps, opt));
    else
      launch_pipeline(load_filter(caps, opt), opt);
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

void
launch_seq(std::vector<filters::ModelFilter*> filters)
{
  auto frame = filters[0]->operator()(nullptr);

  do
  {
    for (int i = 1; i < filters.size(); ++i)
      frame = filters[i]->operator()(frame);

    frame = filters[0]->operator()(nullptr);
  } while (frame);
}


std::vector<filters::ModelFilter*>
load_filter(std::vector<cv::VideoCapture*> caps, Options& opt)
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
  filters.push_back(new filters::Emboss(mode));

  std::vector<filters::ModelFilter*> filtered_filters;
  filtered_filters.push_back(new filters::CopyFilter(tbb::filter::serial_in_order, caps));
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
