#ifndef __IMAGE_HPP
#define __IMAGE_HPP
#include <string>
#include <opencv2/opencv.hpp>

//#include "coreExtractContour.hpp"
#include "coreExtractObject.hpp"
#include "coreRemoveNoise.hpp"
#include "coreSharpening.hpp"

#define BEFORE 0
#define AFTER 1
#define GRAY 2

class Image
{
private:
    std::string filename;
    cv::Mat img;
    cv::Mat gray_img;
    cv::Mat post_img;
public:
    Image(char *filename_in);
    ~Image();
    
    void show(unsigned char f);
    void extract_contour(int f);
    /*
    void resize(void);
    void cvimg2mat(void);
    void mat2cvimg(unsigned char mat_in[Y_SIZE][X_SIZE]);
    void threshold(int thresh, int type);
    void histgram(void);
    void threshold_mode(int smt, int type);
    void threshold_discrim(int type);
    void threshold_dynamic(int type);
    */
};
#endif

