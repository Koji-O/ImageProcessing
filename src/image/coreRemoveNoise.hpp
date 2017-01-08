#ifndef __COREREMOVENOISE_HPP
#define __COREREMOVENOISE_HPP

#include <opencv2/opencv.hpp>

void smooth(cv::Mat in_img, cv::Mat out_img, int type);
void noise_rand(cv::Mat in_img, cv::Mat out_img, int level);
void smooth_weighted(cv::Mat in_img, cv::Mat out_img, int type);
void median(cv::Mat in_img, cv::Mat out_img);
void median_value(unsigned char c[9]);
void noise_spike(cv::Mat in_img, cv::Mat out_img, int number, int level);
void smooth_edge_preserve(cv::Mat in_img, cv::Mat out_img);
void average_minvar(unsigned char p[9][9]);
void log_zero_cross(cv::Mat in_img, cv::Mat out_img, double var);
void laplacian_of_gaussian(cv::Mat in_img, cv::Mat out_img, double var, double amp);
void dilation(cv::Mat in_img, cv::Mat out_img);
void erosion(cv::Mat in_img, cv::Mat out_img);

#endif
