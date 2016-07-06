#pragma once

#include <iostream>
#include <boost/program_options.hpp>

typedef struct Options
{
  std::string video;
  std::string filter;
} options;

struct Options options_parser(int argc, char** argv);
