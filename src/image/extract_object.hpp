#ifndef __COREEXTRACTOBJECT_HPP
#define __COREEXTRACTOBJECT_HPP
#include <opencv2/opencv.hpp>

void threshold(cv::Mat in_img, cv::Mat out_img, int fhresh, int type);
void histgram(cv::Mat in_img, long hist[256]);
void histprint(long hist[256], char *buf);



#endif
