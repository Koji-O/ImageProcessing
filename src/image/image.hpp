#ifndef __IMAGE_HPP
#define __IMAGE_HPP
#include <string>
#include <opencv2/opencv.hpp>

#include "extract_contour.hpp"
#include "extract_object.hpp"
#include "remove_noise.hpp"
#include "sharpening.hpp"

#define BEFORE 0
#define AFTER 1
#define GRAY 3

using namespace std;

class Image
{
private:
    string inputfile;
    string outputfile;    
    string caltype;
    string cal_message;
    string calopt_message;    
    int calopt;
    
    cv::Mat img;
    cv::Mat gray_img;
    cv::Mat post_img;
    cv::Mat tmp_img;
    void extract_contour(int f);
    void remove_noise(int f);
    void sharpening(int f);

public:
    Image();
    Image(Image *img);    
    virtual ~Image();

    void open(char *filename_in);
    void set_info(char *ifile, string ctype, int copt, string cmessage, string comessage);
    void show_info();
    void start();
    void show(unsigned char f);

};
#endif

