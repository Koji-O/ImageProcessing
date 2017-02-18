#include <random>
#include <vector>

#include "remove_noise.hpp"
#include "extract_contour.hpp"

#define RAND_MAX 32767


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

/* ********************
   重み付き移動平均法
   in_img  : 入力画像配列
   out_img : 出力画像配列
   type    : 重み係数(1, 2, 3)
******************** */
void smooth_weighted(cv::Mat in_img, cv::Mat out_img, int type)
{
    int wsize = in_img.size().width;
    int hsize = in_img.size().height;
    double f;
    double c[3][5][5] = {{{      0,      0,      0,      0,      0},
                          {      0, 1.0/10, 1.0/10, 1.0/10,      0},
                          {      0, 1.0/10, 2.0/10, 1.0/10,      0},    
                          {      0, 1.0/10, 1.0/10, 1.0/10,      0},        
                          {      0,      0,      0,      0,      0}},
                         {{      0,      0,      0,      0,      0},
                          {      0, 1.0/16, 2.0/16, 1.0/16,      0},
                          {      0, 2.0/16, 4.0/16, 2.0/16,      0},    
                          {      0, 1.0/16, 2.0/16, 1.0/16,      0},        
                          {      0,      0,      0,      0,      0}},                         
                         {{ 0.0030, 0.0133, 0.0219, 0.0133, 0.0030},
                          { 0.0133, 0.0596, 0.0983, 0.0596, 0.0133},
                          { 0.0219, 0.0983, 0.1621, 0.0983, 0.0219},
                          { 0.0133, 0.0596, 0.0983, 0.0596, 0.0133},
                          { 0.0030, 0.0133, 0.0219, 0.0133, 0.0030}}};

    
    if (type < 1)  type = 1;
    if (type > 3)  type = 3;
    for(int i=1; i<hsize ;i++){
        for(int j=1; j<wsize ;j++){
            f = 0.0;
            for(int m = -2; m <= 2 ; m++){
                for(int n = -2; n <= 2 ; n++){
                    if((i+m >= 0) && (i+m <= hsize-1) &&
                       (j+n >= 0) && (j+n <= wsize-1))
                        f += in_img.at<uchar>(i+m, j+n) * c[type-1][2+m][2+n];
                }
            }
            if(f < 0) f = 0;
            if(f > 255) f = 255;
            out_img.at<uchar>(i, j) = (unsigned char)f;
        }
    }            
}

/* ********************
   メディアンフィルタ
   in_img  : 入力画像配列
   out_img : 出力画像配列
******************** */
void median(cv::Mat in_img, cv::Mat out_img)
{
    std::vector<uchar> c(9);
    int s[3] = {-1, 0, 1};
    
    for(int i=1 ; i < in_img.size().height-1 ; i++){
        for(int j=1 ; j < in_img.size().width-1 ; j++){
            for(int k=0; k<3 ; k++){
                c[k] = in_img.at<uchar>(i-1, j+s[k]);
                c[k+3] = in_img.at<uchar>(i, j+s[k]);
                c[k+6] = in_img.at<uchar>(i+1, j+s[k]);
                std::sort(c.begin(), c.end());
                in_img.at<uchar>(i, j) = c[4];
                //cをソートして中央値に置き換える。
            }
        }
    }
}

/* ********************
   スパイクノイズ付加
   in_img  : 入力画像配列
   out_img : 出力画像配列
   number  : スパイクノイズの数
   level   : ノイズレベルの付加
******************** */
void noise_spike(cv::Mat in_img, cv::Mat out_img, int number, int level)
{
    std::mt19937_64 mt;
    std::uniform_real_distribution<double> ur(0, 1);
    mt.seed(0);
    
    int x, y;
    int data, noise;

    for(int i = 0; i < number; i++){
        x = (int)(ur(mt) * in_img.size().width);
        y = (int)(ur(mt) * in_img.size().height);
        noise = (int)((ur(mt) - 0.5) * level * 2.0);
        data = in_img.at<uchar>(x, y) + noise;
        if ( data > 255)  out_img.at<uchar>(x, y) = 255;
        else if(data < 0) out_img.at<uchar>(x, y) = 0;
        else              out_img.at<uchar>(x, y) = data;
    }
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

