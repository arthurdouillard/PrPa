#pragma once

#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iomanip>

#include "main.hh"
#include "options/options.hh"
#include "filter/grayscale.hh"
#include "filter/binary.hh"
#include "filter/writer.hh"
#include "filter/false_writer.hh"
#include "filter/modelfilter.hh"
#include "filter/sepia.hh"
#include "filter/sharpen.hh"
#include "filter/gaussian.hh"
#include "filter/verticalflip.hh"
#include "filter/image_overlay.hh"
#include "filter/copy_filter.hh"
#include "timer.hh"

void
launch_pipeline(cv::VideoCapture& cap, Options& opt);

std::vector<filters::ModelFilter*>
load_filter(cv::VideoCapture& cap, Options& opt);

void
exec(std::vector<cv::Mat>& frames, Options& opt);
