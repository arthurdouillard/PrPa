#pragma once

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>

typedef struct Options
{
  std::string              video;
  std::vector<std::string> filter;
} options;

struct Options options_parser(int argc, char** argv);
void list_filter();
