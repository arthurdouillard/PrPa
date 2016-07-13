#pragma once

#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iomanip>
#include <thread>

#include "main.hh"
#include "options/options.hh"
#include "filter/grayscale.hh"
#include "filter/binary.hh"
#include "filter/writer.hh"
#include "filter/false_writer.hh"
#include "filter/true_writer.hh"
#include "filter/modelfilter.hh"
#include "filter/sepia.hh"
#include "filter/sharpen.hh"
#include "filter/gaussian.hh"
#include "filter/verticalflip.hh"
#include "filter/image_overlay.hh"
#include "filter/copy_filter.hh"
#include "filter/emboss.hh"
#include "filter/edge.hh"
#include "filter/invert.hh"
#include "timer.hh"

void
launch_pipeline(std::vector<filters::ModelFilter*> filters, Options& opt);

void
launch_seq(std::vector<filters::ModelFilter*> filters);

std::vector<filters::ModelFilter*>
load_filter(std::vector<cv::VideoCapture*> caps, Options& opt);

void
exec(std::vector<cv::VideoCapture*> cap, Options& opt);
