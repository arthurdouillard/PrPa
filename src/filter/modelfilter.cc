#include "modelfilter.hh"

namespace filters
{
  ModelFilter::ModelFilter(tbb::filter::mode mode, std::string name)
    : tbb::filter(mode)
    , name_(name)
  {}

  const std::string ModelFilter::name_get() const
  {
    return name_;
  }
}

