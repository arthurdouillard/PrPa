#include "options.hh"

namespace bpo = boost::program_options;

struct Options options_parser(int argc, char** argv)
{
  bpo::options_description desc("Options");
  desc.add_options()
    ("help,h", "Display the help")
    ("video,v", bpo::value<std::string>(), "Video file (*.avi)")
    ("filter,f", bpo::value<std::vector<std::string>>()->multitoken(), "Filter to use")
    ("mode,m", bpo::value<std::string>()->default_value("so"),
     "Mode choice: so (TBB: serial out-of-order), si (TBB: serial in-order), pa (TBB: parallel)")
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

  if (!vm.count("video"))
  {
    std::cerr << "CMON ! Give me a video !" << std::endl << desc;
    exit(1);
  }

  auto mode = vm["mode"].as<std::string>();
  if (mode != "so" && mode != "si" && mode != "pa" && mode != "se")
  {
    std::cerr << "Mode should be either: so | si | pa" << std::endl;
    exit(1);
  }

  std::vector<std::string> filters;
  if (vm.count("filter"))
    filters = vm["filter"].as<std::vector<std::string>>();

  bool timer_p = vm.count("timer");
  bool benchmark = vm.count("benchmark");

  Options opt = {
                  vm["video"].as<std::string>(),
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
            << "* vflip"       << std::endl;
  exit(0);
}
