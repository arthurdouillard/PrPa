#include "options.hh"

namespace bpo = boost::program_options;

struct Options options_parser(int argc, char** argv)
{
  bpo::options_description desc("Options");
  desc.add_options()
    ("help,h", "Display the help")
    ("video,v", bpo::value<std::string>(), "Video file (*.avi)")
    ("filter,f", bpo::value<std::vector<std::string>>()->multitoken(), "Filter to use")
    ("mode,m", bpo::value<std::string>(), "Mode choice: so (serial out-of-order), si (serial in-order), pa (parallel)")
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

  if (!vm.count("video") || !vm.count("filter") || !vm.count("mode"))
  {
    std::cerr << "Video & Filter & Mode options are mandatory !" << std::endl;
    exit(1);
  }

  auto mode = vm["mode"].as<std::string>();
  if (mode != "so" && mode != "si" && mode != "pa")
  {
    std::cerr << "Mode should be either: so | si | pa" << std::endl;
    exit(1);
  }

  Options opt = {
                  vm["video"].as<std::string>(),
                  vm["filter"].as<std::vector<std::string>>(),
                  mode
                };

  return opt;
}


void list_filter()
{
  std::cout << "Filters:"     << std::endl
            << "* grayscale"  << std::endl
            << "* sepia" << std::endl;
  exit(0);
}
