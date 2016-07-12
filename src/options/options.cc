#include "options.hh"

namespace bpo = boost::program_options;

struct Options options_parser(int argc, char** argv)
{
  bpo::options_description desc("Options");
  desc.add_options()
    ("help,h", "Display the help")
    ("video,v", bpo::value<std::vector<std::string>>()->multitoken(), "Video file (*.avi)")
    ("filter,f", bpo::value<std::vector<std::string>>()->multitoken(), "Filter to use")
    ("mode,m", bpo::value<std::string>()->default_value("pa"),
     "Mode choice: pa (TBB: parallel) | se (sequential)")
    ("timer,t", "Enable timer")
    ("benchmark,b", "Benchmark video for the three modes (so, si, pa)")
    ("list-filter,l", "List of available filter (or other FX)");

  bpo::variables_map vm;
  try
  {
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);
  }
  catch (std::exception& e)
  {
    std::cerr << desc;
    exit(1);
  }

  if (vm.count("help"))
  {
    std::cout << desc;
    exit(0);
  }
  else if (vm.count("list-filter"))
    list_filter();

  std::vector<std::string> videos;
  if (!vm.count("video"))
  {
    std::cerr << "CMON ! Give me a video !" << std::endl << desc;
    exit(1);
  }
  else
    videos = vm["video"].as<std::vector<std::string>>();

  auto mode = vm["mode"].as<std::string>();
  if (mode != "pa" && mode != "se")
  {
    std::cerr << "Mode should be either: pa | se" << std::endl;
    exit(1);
  }

  std::vector<std::string> filters;
  if (vm.count("filter"))
    filters = vm["filter"].as<std::vector<std::string>>();

  bool timer_p = vm.count("timer");
  bool benchmark = vm.count("benchmark");

  Options opt = {
                  videos,
                  filters,
                  mode,
                  timer_p,
                  benchmark
                };

  return opt;
}


void list_filter()
{
  std::cout << "Filters:"      << std::endl
            << "* img_overlay" << std::endl
            << "* grayscale"   << std::endl
            << "* binary"      << std::endl
            << "* sepia"       << std::endl
            << "* sharpen"     << std::endl
            << "* gaussian"    << std::endl
            << "* emboss"      << std::endl
            << "* vflip"       << std::endl;
  exit(0);
}
