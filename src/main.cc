#include <iostream>
#include <boost/program_options.hpp>

#include "options/options.hh"

namespace bpo = boost::program_options;

int main(int argc, char** argv)
{
  Options opt = options_parser(argc, argv);
  std::cout << opt.video  << std::endl;
  for (auto f : opt.filter)
    std::cout << f << std::endl;
}

