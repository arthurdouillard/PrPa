#pragma once

#include "options/options.hh"
#include "filter/modelfilter.hh"

void
launch_pipeline(std::vector<filters::ModelFilter*> filters);

std::vector<cv::Mat>
copy_video(cv::VideoCapture& cap);

std::vector<filters::ModelFilter*>
load_filter(std::vector<cv::Mat>& frames, Options& opt);
