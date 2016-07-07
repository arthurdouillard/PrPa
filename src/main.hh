#pragma once

#include "options/options.hh"

void launch_pipeline(std::vector<cv::Mat>& frames, Options& opt);
std::vector<cv::Mat> copy_video(cv::VideoCapture& cap);
