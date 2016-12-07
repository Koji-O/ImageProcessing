#ifndef __COREEXTRACTCONTOUR_HPP
#define __COREEXTRACTCONTOUR_HPP
#include <opencv2/opencv.hpp>
#include <vector>

bool diff_grad(cv::Mat in_img, cv::Mat out_img, int amp, int type);
void gradient(cv::Mat in_img, cv::Mat out_img, int amp, std::vector<int> cx, std::vector<int> cy);
bool template_matching(cv::Mat in_img, cv::Mat out_img, int amp);
void prewitt(cv::Mat in_img, cv::Mat out_img, int amp);
bool hilditch(cv::Mat in_img, cv::Mat out_img, int amp);


#endif

