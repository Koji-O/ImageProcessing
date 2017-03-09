#ifndef __SHARPENING_HPP
#define __SHARPENING_HPP

#include <opencv2/opencv.hpp>
#include "image_const.hpp"

struct xyw {
    int x, y, w;
};

void amplify(cv::Mat in_img, cv::Mat out_img, double a, double b);
void range(cv::Mat in_img, int* fmax, int* fmin);
void expand(cv::Mat in_img, cv::Mat out_img, int fmax, int fmin);
void sort(cv::Mat in_img, struct xyw data[], int level);
void weight(cv::Mat in_img, int i, int j, int *wt);
void plane(cv::Mat in_img, cv::Mat out_img, long hist[256]);
void dither_ordered(cv::Mat in_img, cv::Mat out_img);
void dither_minimized(cv::Mat in_img, cv::Mat out_img);
void quantize(cv::Mat in_img, cv::Mat out_img, int nq);
void d_quantize(int in, unsigned char *pout, int nq);
void dither_minimized_multi(cv::Mat in_img, cv::Mat out_img, int nq);

#endif
