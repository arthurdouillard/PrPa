#include <tbb/tbb.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "false_writer.hh"


namespace filters
{

  FalseWriter::FalseWriter(tbb::filter::mode mode)
    : ModelFilter(mode, "false-writer")
  {}

  void* FalseWriter::operator()(void* image)
  {
    return nullptr;
  }
}
