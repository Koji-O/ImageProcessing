#include "coreRemoveNoise.hpp"
#include "coreExtractContour.hpp"

#include <random>


/* ********************
   移動平均法による雑音除去
   in_img  : 入力画像配列
   out_img : 出力画像配列
   type    : 平滑化範囲 (3 : 3x3, 5: 5x5, 7: 7x7, ...)
 ******************** */
void smooth(cv::Mat in_img, cv::Mat out_img, int type)
{
    int x, y;
    double sum, num;
    int w = type/2;
    int xsize = in_img.size().height;
    int ysize = in_img.size().width;

    num = (double) type * type;
    for(int i = 0; i < in_img.size().height ; i++){
        for(int j = 0; j < in_img.size().width ; j++){
            sum = 0.0;
            for(int k = -w; k <= w ; k++){
                for(int l = -w; l <= w ; l++){
                    x = i + k;
                    y = j + l;
                    if(y < 0) y = 0;
                    if(x < 0) x = 0;
                    if(y > ysize) y = ysize;
                    if(x > xsize) x = ysize;
                    sum += in_img.at<uchar>(x, y);
                }
            }
            sum = sum/num;
            if(sum < 0) sum = 0;
            if(sum > 255) sum = 255;
            out_img.at<uchar>(i, j) = (unsigned char) sum;
        }
    }
}


/* ********************
   ランダムノイズの付加
   in_img  : 入力画像配列
   out_img : 出力画像配列
   level   : ノイズレベルの最大値
 ******************** */
void noise_rand(cv::Mat in_img, cv::Mat out_img, int level)
{
    int data, noise;
    std::mt19937_64 mt;
    std::uniform_real_distribution<double> ur(-0.5, 0.5);
    mt.seed(0);
    

    for(int i = 0; i < in_img.size().height ; i++){
        for(int j = 0; j < in_img.size().width ; j++){
            noise = (int)(ur(mt) * 2.0 * level);
            data = in_img.at<uchar>(i, j) + noise;
            if(data > 255)     out_img.at<uchar>(i, j) = 255;
            else if (data < 0) out_img.at<uchar>(i, j) = 0;
            else               out_img.at<uchar>(i, j) = data;
        }
    }
}

void smooth_weighted(cv::Mat in_img, cv::Mat out_img, int type)
{
}

void median(cv::Mat in_img, cv::Mat out_img)
{
}

void median_value(unsigned char c[9])
{
}

void noise_spike(cv::Mat in_img, cv::Mat out_img, int number, int level)
{
}

void smooth_edge_preserve(cv::Mat in_img, cv::Mat out_img)
{
}
    
void average_minvar(unsigned char p[9][9])
{
}


void log_zero_cross(cv::Mat in_img, cv::Mat out_img, double var)
{
}


void laplacian_of_gaussian(cv::Mat in_img, cv::Mat out_img, double var, double amp)
{
}
    

void dilation(cv::Mat in_img, cv::Mat out_img)
{
}


void erosion(cv::Mat in_img, cv::Mat out_img)
{
}

