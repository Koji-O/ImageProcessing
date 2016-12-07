#include "Image.hpp"
#include "coreSharpening.hpp"
#include "coreRemoveNoise.hpp"   
#include "coreExtractObject.hpp"
#include "coreExtractContour.hpp"

#include <string>
#include <opencv2/opencv.hpp>

Image::Image(char *filename_in)
{
    // 画像を読み込み、imgに保存する。グレースケール化した画像をgray_imgに保存する。
    std::cout << "Open::" << filename_in << std::endl;
    filename = filename_in;
    img = cv::imread(filename_in);
    cvtColor(img, gray_img, CV_RGB2GRAY);
    if(img.empty())
        exit(1);
    post_img = gray_img.clone();
}

Image::~Image()
{
    
}

void Image::show(unsigned char f)
{
    // img に保存されている画像をウィンドウに表示する。
    if( f == BEFORE){
        cv::namedWindow(filename, cv::WINDOW_AUTOSIZE);
        cv::imshow(filename, gray_img);
        cv::waitKey(0);
    }else if(f == AFTER){
        cv::namedWindow(filename, cv::WINDOW_AUTOSIZE);
        cv::imshow(filename, post_img);
        cv::waitKey(0);
    }else if(f == GRAY){
        cv::namedWindow(filename, cv::WINDOW_AUTOSIZE);
        cv::imshow(filename, gray_img);
        cv::waitKey(0);
    }
}

void Image::extract_contour(int f)
{
    switch(f){
    case 1:
        enum CTYPE{
            GRAD1D, ROVERTS, SOBEL,
        };
        std::cout << "gradient_difference." << std::endl;
        diff_grad(gray_img, post_img, 4, SOBEL);
        break;
    case 2:
        std::cout << "template_matching." << std::endl;
        template_matching(gray_img, post_img, 2);
        break;
    case 3:
        break;
    default:
        std::cout << "Error arguments in extract_contour. " << std::endl;
        break;
    }
}

