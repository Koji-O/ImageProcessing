#ifndef __COREEXTRACTCONTOUR_HPP
#define __COREEXTRACTCONTOUR_HPP
#include <opencv2/opencv.hpp>
#include <vector>

bool diff_grad(cv::Mat in_img, cv::Mat out_img, int amp, int type);
void gradient(cv::Mat in_img, cv::Mat out_img, int amp, std::vector<int> cx, std::vector<int> cy);
bool template_matching(cv::Mat in_img, cv::Mat out_img, int amp);
void prewitt(cv::Mat in_img, cv::Mat out_img, int amp);
bool hilditch(cv::Mat in_img, cv::Mat out_img);
int ncon(std::vector<int> p);
void laplacian(cv::Mat in_img, cv::Mat out_img, int amp, int type);
void zero_cross(cv::Mat in_img, cv::Mat out_img);
void hough(cv::Mat in_img, cv::Mat out_img, cv::Mat hough_img, int thresh, char *buf);
void hough_line(cv::Mat in_img, cv::Mat out_img, double rho, double theta);
void hough_cross(double theta1, double rho1, double theta2, double rho2, double *x, double *y);

#endif

