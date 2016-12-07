#include "coreExtractContour.hpp"

#include <opencv2/opencv.hpp>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cmath>

bool diff_grad(cv::Mat in_img, cv::Mat out_img, int amp, int type)
{
    /*
      １次微分を用いて輪郭を抽出する。
      in_img  ::  入力画像配列 
      out_img ::  出力画像配列
      amp     ::  出力画像の比例係数
      type    ::  計算方法の設定(gradient_1d, roverts, sobel)
     */
    enum CTYPE{
        GRAD1D, ROVERTS, SOBEL,
    };
    std::vector<int> g1d_x_op{0, 0, 0, 0, -1, 1, 0, 0, 0};
    std::vector<int> g1d_y_op{0, 0, 0, 0, -1, 0, 0, 1, 0};    
    std::vector<int> roverts_x_op{0, 0, 0, 0, -1, 0, 0, 0, 1};
    std::vector<int> roverts_y_op{0, 0, 0, 0, 0, -1, 0, 1, 0};    
    std::vector<int> sobel_x_op{-1, 0, 1, -2, 0, 2, -1, 0, 1};
    std::vector<int> sobel_y_op{-1, -2, -1, 0, 0, 0, 1, 2, 1};
    
    switch(type){
    case(GRAD1D):
        gradient(in_img, out_img, amp, g1d_x_op, g1d_y_op);
        break;
    case(ROVERTS):
        gradient(in_img, out_img, amp, roverts_x_op,roverts_y_op);
        break;
    case(SOBEL):
        gradient(in_img, out_img, amp, sobel_x_op, sobel_y_op);
        break;
    defualt:
        break;
    }
    
    return true;
}

void gradient(cv::Mat in_img, cv::Mat out_img, int amp, std::vector<int> cx, std::vector<int> cy)
{
    std::vector<int> m(9);
    int d[3] = {-1, 0, 1};
    double xx, yy, zz;
    int ele;

    for(int i = 1; i < in_img.size().height + 1 ; i++){
        for(int j = 1; j < in_img.size().width + 1 ; j++){
            out_img.at<uchar>(i, j) = (unsigned char)0;
            for(int k = 0; k < 3; k++){
                m[k] = in_img.at<uchar>(i - 1, j + d[k]);
                m[k + 3] = in_img.at<uchar>(i, j + d[k]);
                m[k + 6] = in_img.at<uchar>(i + 1, j + d[k]);
            }
            xx = (double)std::inner_product(m.begin(), m.end(), cx.begin(), 0);
            yy = (double)std::inner_product(m.begin(), m.end(), cy.begin(), 0);
            zz = (double)(amp*sqrt(xx*xx + yy*yy));
            ele = (int) zz;
            if( ele > 255) ele = 255;
            out_img.at<uchar>(i, j) = (unsigned char) ele;
        }
    }
}
bool template_matching(cv::Mat in_img, cv::Mat out_img, int amp)
{
    prewitt(in_img, out_img, amp);
    return true;
}

void prewitt(cv::Mat in_img, cv::Mat out_img, int amp)
{
    std::vector<int> d(9), m(9);
    int s[3] = {-1, 0, 1};
    double zz;
    int max, ele;

    for(int i = 1; i < in_img.size().height + 1 ; i++){
        for(int j = 1; j < in_img.size().width + 1 ; j++){
            for(int k = 0; k < 3; k++){
                d[k] = in_img.at<uchar>(i - 1, j + s[k]);
                d[k + 3] = in_img.at<uchar>(i, j + s[k]);
                d[k + 6] = in_img.at<uchar>(i + 1, j + s[k]);
            }
            m[0] = d[0] + d[1] + d[2] + d[3] - 2*d[4] + d[5] - d[6] - d[7] - d[8];
            m[1] = d[0] + d[1] + d[2] + d[3] - 2*d[4] - d[5] + d[6] - d[7] - d[8];
            m[2] = d[0] + d[1] - d[2] + d[3] - 2*d[4] - d[5] + d[6] + d[7] - d[8];
            m[3] = d[0] - d[1] - d[2] + d[3] - 2*d[4] + d[5] + d[6] + d[7] + d[8];
            m[4] = -d[0] - d[1] - d[2] + d[3] - 2*d[4] + d[5] + d[6] + d[7] + d[8];
            m[5] = -d[0] - d[1] + d[2] - d[3] - 2*d[4] + d[5] + d[6] + d[7] + d[8];
            m[6] = -d[0] + d[1] + d[2] - d[3] - 2*d[4] + d[5] - d[6] + d[7] + d[8];
            m[7] = d[0] + d[1] + d[2] - d[3] - 2*d[4] + d[5] - d[6] - d[7] + d[8];
            max = *max_element(m.begin(), m.end());
            zz = amp*(double)(max);
            ele = (int)(zz);
            if( ele > 255) ele = 255;
            out_img.at<uchar>(i, j) = (unsigned char) ele;
        }
    }
}

bool hilditch(cv::Mat in_img, cv::Mat out_img, int amp)
// 細分化をする
{

    return true;
}

