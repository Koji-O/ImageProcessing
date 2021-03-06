#include "image.hpp"
#include "sharpening.hpp"
#include "remove_noise.hpp"   
#include "extract_object.hpp"
#include "extract_contour.hpp"

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

Image::Image()
{
}

Image::Image(Image *img)
{
    
}

Image::~Image()
{
    
}

void Image::open(char *filename_in)
{
    // 画像を読み込み、imgに保存する。グレースケール化した画像をgray_imgに保存する。
    /*
    std::cout << "Open::" << filename_in << std::endl;
    filename = filename_in;
    img = cv::imread(filename_in);
    cvtColor(img, gray_img, CV_RGB2GRAY);
    if(img.empty())
        exit(1);
    post_img = gray_img.clone();
    */
}

void Image::set_info(char *ifile, string ctype, int copt, string cmessage, string comessage)
{
    inputfile = ifile;
    caltype = ctype;
    calopt = copt;
    cal_message = cmessage;
    calopt_message = comessage;
}

void Image::start()
{
    

}

void Image::show_info()
{
    cout << "==== Information ====" << endl;
    cout << "inputfile: " << inputfile << endl;
    if(!outputfile.empty())
        cout << "outputfile: " << outputfile << endl;        
    cout << "calculation type: " << cal_message << endl;
    cout << "calculation option: " << calopt_message << endl;
    cout << "==== +++++++++++ ====" << endl;    
}
void Image::show(unsigned char f)
{
    // img に保存されている画像をウィンドウに表示する。
    /*
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
    */
}

void Image::extract_contour(int f)
{
    //from coreExtractContour.hpp
    switch(f){
    case 1:
        enum CTYPE{
            GRAD1D, ROVERTS, SOBEL,
        };
        std::cout << "gradient_difference." << std::endl;
        diff_grad(gray_img, post_img, 5, ROVERTS);
        break;
    case 2:
        std::cout << "template_matching." << std::endl;
        template_matching(gray_img, post_img, 2);
        break;
    case 3:
        std::cout << "thinning." << std::endl;
        diff_grad(gray_img, post_img, 5, ROVERTS);
        tmp_img = post_img.clone();
        hilditch(tmp_img, post_img);
        break;
    case 4:
        std::cout << "Laplacian." << std::endl;
        laplacian(gray_img, post_img, 5, 1);
        break;
    case 5:
        std::cout << "Zero_Cross." << std::endl;
        zero_cross(gray_img, post_img);
        break;
    case 6:
        std::cout << "Hough." << std::endl;
        char buf[255];
        tmp_img = post_img.clone();
        hough(gray_img, post_img, tmp_img, 10, buf);
        break;
    default:
        std::cout << "Error arguments in extract_contour. " << std::endl;
        break;
    }
}

void Image::remove_noise(int f)
{
    switch(f){
    case 1:
        std::cout << "Moving_Average_Methods." << std::endl;
        smooth(gray_img, post_img, 7);
        break;
    case 2:
        std::cout << "Add_Nosie." << std::endl;
        noise_rand(gray_img, post_img, 50);
        break;
    case 3:
        std::cout << "Smooth_Weighted." << std::endl;
        smooth_weighted(gray_img, post_img, 1);
        break;
    case 4:
        std::cout << "Median_Filter." << std::endl;
        median(gray_img, post_img);
        break;
    case 5:
        std::cout << "Add_Spike_Noise." << std::endl;
        noise_spike(gray_img, post_img, 50, 50);
    case 6:
        std::cout << "LOF fileter." << std::endl;
        break;
    default:
        break;
    }
}
