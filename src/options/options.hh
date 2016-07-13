#pragma once

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>

typedef struct Options
{
  std::vector<std::string> video;
  std::vector<std::string> filter;
  std::string              mode;
  bool                     timer;
  bool                     benchmark;
  std::string              dst;
} options;

struct Options options_parser(int argc, char** argv);
void list_filter();
