/**
 * @file coreExtractContour.cpp
 * @brief 画像の輪郭を抽出する関数群
 */
#include "imageConst.hpp"
#include "coreExtractContour.hpp"

#include <opencv2/opencv.hpp>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cmath>

#define PI 3.141592
#define DMAX 1000


/* *****************************
  １次微分を用いて輪郭を抽出する。
  in_img  ::  入力画像配列 
  out_img ::  出力画像配列
  amp     ::  出力画像の比例係数
  type    ::  計算方法の設定(GRAD1D, ROVERTS, SOBEL)
  ***************************** */
bool diff_grad(cv::Mat in_img, cv::Mat out_img, int amp, int type)
{
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

/*
  １次微分を用いて輪郭を抽出する。
  in_img  ::  入力画像配列 
  out_img ::  出力画像配列
  amp     ::  出力画像の比例係数
  cx,cy   ::  微分オペレータ
*/
void gradient(cv::Mat in_img, cv::Mat out_img, int amp, std::vector<int> cx, std::vector<int> cy)
{
    std::vector<int> m(9);
    int d[3] = {-1, 0, 1};
    double xx, yy, zz;
    int ele;

    for(int i = 1; i < in_img.size().height - 1 ; i++){
        for(int j = 1; j < in_img.size().width - 1 ; j++){
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


/* *****************************
  テンプレートマッチングを用いて輪郭を抽出する。
  in_img  ::  入力画像配列 
  out_img ::  出力画像配列
  amp     ::  出力画像の比例係数
 ***************************** */
bool template_matching(cv::Mat in_img, cv::Mat out_img, int amp)
{
    prewitt(in_img, out_img, amp);
    return true;
}

void prewitt(cv::Mat in_img, cv::Mat out_img, int amp)
{
    std::vector<int> d(9), m(8);
    int s[3] = {-1, 0, 1};
    double zz;
    int max, ele;

    for(int i = 1; i < in_img.size().height - 1 ; i++){
        for(int j = 1; j < in_img.size().width - 1 ; j++){
            for(int k = 0; k < 3; k++){
                d[k] = in_img.at<uchar>(i - 1, j + s[k]);
                d[k + 3] = in_img.at<uchar>(i, j + s[k]);
                d[k + 6] = in_img.at<uchar>(i + 1, j + s[k]);
            }
            m[0] = d[0] + d[1] + d[2] + d[3] - 2*d[4] + d[5] - d[6] - d[7] - d[8];
            m[1] = d[0] + d[1] + d[2] + d[3] - 2*d[4] - d[5] + d[6] - d[7] - d[8];
            m[2] = d[0] + d[1] - d[2] + d[3] - 2*d[4] - d[5] + d[6] + d[7] - d[8];
            m[3] = d[0] - d[1] - d[2] + d[3] - 2*d[4] - d[5] + d[6] + d[7] + d[8];
            m[4] = -d[0] - d[1] - d[2] + d[3] - 2*d[4] + d[5] + d[6] + d[7] + d[8];
            m[5] = -d[0] - d[1] + d[2] - d[3] - 2*d[4] + d[5] + d[6] + d[7] + d[8];
            m[6] = -d[0] + d[1] + d[2] - d[3] - 2*d[4] + d[5] - d[6] + d[7] + d[8];
            m[7] = d[0] + d[1] + d[2] - d[3] - 2*d[4] + d[5] - d[6] - d[7] + d[8];
            max = 0;
            for(auto &x : m) if(max < x) max = x;
            zz = amp*(double)(max);
            ele = (int)(zz);
            if( ele > 255) ele = 255;
            out_img.at<uchar>(i, j) = (unsigned char) ele;
        }
    }
}


/* *****************************
   hilditch法用いて２値画像線形化する 
   in_img  :   入力画像配列（２値画像配列）
   out_img :   出力画像配列
   ***************************** */
bool hilditch(cv::Mat in_img, cv::Mat out_img)
{
    bool flg = true;
    std::vector<int> p(9); /* 図形: 1, 背景: 0, 背景候補: -1 */
    int i_idx[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    /* pの配列を反時計回りに操作するための行のインデックス */
    int j_idx[] = {0, 1, 1, 0, -1, -1, -1, 0, 1};
    /* pの配列を反時計回りに操作するための列のインデックス */
    int n; 

    int TMP = OFFSET;
    
    while (flg){
        flg = false;
        for(int i = 1; i < in_img.size().height - 1 ; ++i){
            for(int j = 1; j < in_img.size().width - 1 ; ++j){
                for(int k = 0; k < 9; ++k)
                    p[k] = in_img.at<uchar>(i + i_idx[k], j + j_idx[k]);

                for(auto &x : p){
                    if (x == HIGH) x = 1;
                    else if(x == LOW) x = 0;
                    else x = -1;
                }
                /* 条件１：図形の一部である */
                if(p[0] != 1) continue;
                /* 条件2：境界画素である(4近傍のうち1個以上が背景) */
                if(p[1] * p[3] * p[5] * p[7] != 0) continue;
                /* 条件3：端点を保存する(8近傍のうち2個以上が図形) */
                n = 0;
                for(auto &x : p) if(x != 0) n++;
                if(n < 2) continue;
                /* 条件4:孤立点を保存する(8近傍のうち1個以上が図形) */
                n = 0;
                for(auto &x : p) if(x == 1) n++;
                if(n < 1) continue;
                /* 条件5:連結性保存する(8連結数が1である) */
                if(ncon(p) != 1) continue;
                /* 条件6:線幅が2のとき片方だけ除去する(8近傍全てにおいて、
                   -1でないか,-1の時この値を0とした場合の8連結数が1である) */
                n = 0;
                for(auto &x : p){
                    if(x != -1) n++;
                    else if(x == -1){
                        x = 0;
                        if(ncon(p) == 1) n++;
                        x = -1;
                    }
                }
                if(n < 8) continue;
                /* 条件1〜6のすべてを満たす場合が削除対象 */
                out_img.at<uchar>(i, j) = (unsigned char) TMP;
                flg = true;
            }
        }
        for(int i = 1; i < in_img.size().height - 1 ; i++)
            for(int j = 1; j < in_img.size().width - 1 ; j++)
                if(out_img.at<uchar>(i, j) == (unsigned char) TMP)
                    out_img.at<uchar>(i, j) = (unsigned char) 0;
    }
    return true;
}

/*
  連結数を計算する。
  Hildich法で使用する関数.
*/
int ncon(std::vector<int> p)
{
    int q[9];
    int n;
    int i1, i2;
    
    for(int i = 0; i < 9; ++i){
        if(( p[i] == 1) || (p[i] == -1)) q[i] = 0;
        else q[i] = 1;
    }
    for(int i = 1; i < 9; i+=2){
        i1 = i + 1;
        i2 = i + 2;
        if( i2 == 9 ) i2 = 1;
        n = n + q[i] - q[i] * q[i1] * q[i2];
    }
    return n;
}

/* ********************
  ラプラシアン法(２次微分)を用いて輪郭線を抽出する。
  in_img  :   入力画像配列（２値画像配列）
  out_img :   出力画像配列
  amp     ::  出力画像の比例係数
  type    ::  計算方法の設定(1, 2, 3) 微分オペレータの指定
  ******************** */
void laplacian(cv::Mat in_img, cv::Mat out_img, int amp, int type)
{
    int c[3][9] = {{  0, -1,  0, -1,  4, -1,  0, -1,  0},
                   { -1, -1, -1, -1,  8, -1, -1, -1, -1},
                   {  1, -2,  1, -2,  4, -2,  1, -2,  1}};
    int d;
    int e[3] = {-1, 0, 1};
    
    type--;
    if(type < 0 ) type = 0;
    if(type > 2 ) type = 2;
    for(int i = 1; i < in_img.size().height - 1 ; i++){
        for(int j = 1; j < in_img.size().width - 1 ; j++){
            d = 0;
            for(int k = 0; k < 3; k++){
                d +=  c[type][k] * in_img.at<uchar>(i - 1, j + e[k])
                    + c[type][k + 3] * in_img.at<uchar>(i, j + e[k])
                    + c[type][k + 6] * in_img.at<uchar>(i + 1, j + e[k]);
            }
            d = (int)(d * amp) + OFFSET;
            if(d < LOW) d = LOW;
            if(d > HIGH) d = HIGH;
            out_img.at<uchar>(i, j) = (unsigned char) d;
        }
    }
}

/* ********************
  ゼロ交差法を用いて輪郭線を抽出する。
  in_img  :   入力画像配列（２値画像配列）
  out_img :   出力画像配列
  ******************** */
void zero_cross(cv::Mat in_img, cv::Mat out_img)
{
    out_img = cv::Mat::zeros(out_img.size(), CV_8UC1);
    
    for(int i = 1; i < in_img.size().height - 1 ; i++){
        for(int j = 1; j < in_img.size().width - 1 ; j++){
            if((int)in_img.at<uchar>(i, j) == OFFSET){
                if(((int)in_img.at<uchar>(i, j+1) - OFFSET)
                   * ((int)in_img.at<uchar>(i, j-1) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
                if(((int)in_img.at<uchar>(i+1, j) - OFFSET)
                   * ((int)in_img.at<uchar>(i-1, j) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
                if(((int)in_img.at<uchar>(i+1, j+1) - OFFSET)
                   * ((int)in_img.at<uchar>(i-1, j-1) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
                if(((int)in_img.at<uchar>(i+1, j-1) - OFFSET)
                   * ((int)in_img.at<uchar>(i-1, j+1) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
            }else{
                if(((int)in_img.at<uchar>(i, j) - OFFSET)
                   * ((int)in_img.at<uchar>(i, j-1) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
                if(((int)in_img.at<uchar>(i, j) - OFFSET)
                   * ((int)in_img.at<uchar>(i-1, j) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
                if(((int)in_img.at<uchar>(i, j) - OFFSET)
                   * ((int)in_img.at<uchar>(i+1, j) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
                if(((int)in_img.at<uchar>(i, j) - OFFSET)
                   * ((int)in_img.at<uchar>(i, j+1) - OFFSET) < 0)
                    out_img.at<uchar>(i, j) = HIGH;
            }
        }
    }
}


/* ********************
  Hough変換による直線抽出
  in_img    :   入力画像配列 (2値画像)
  out_img   :   出力画像配列
  hough_img :   出力画像配列 (Hough変換)
  thresh    :   閾値
  buf       :   メッセージ用バッファ
 ******************** */
void hough(cv::Mat in_img, cv::Mat out_img, cv::Mat hough_img, int thresh, char *buf)
{
    double rho, theta, d, a;
    double p[DMAX][2];
    int posi, m, v, n;
    int xsize = in_img.size().width;
    int ysize = in_img.size().height;
    
    d = PI / xsize;
    a = ysize/2/sqrt(xsize/2 * xsize/2 + ysize/2 * ysize/2);
    
    hough_img = cv::Mat::zeros(in_img.size(), CV_8UC1);    

    for(int i = 1; i < ysize - 1 ; i++){
        for(int j = 1; j < xsize - 1 ; j++){
            if(in_img.at<uchar>(i, j) != HIGH) continue;
            for(int k = 0; k < xsize ; k++){
                theta = k * d;
                rho = (j - xsize/2) * cos(theta) + (ysize/2 - i) * sin(theta);
                v = (int)(rho * a + ysize/2 + 0.5);
                std::cout << v << std::endl;
                if (v >= 0 && v < ysize)
                    if( hough_img.at<uchar>(v, k) < 255) hough_img.at<uchar>(v, k) += 1;
            }
        }
    }
    
    n = 0;
    posi = 0;
    for(int i = 1; i < ysize - 1 ; i++){
        for(int j = 1; j < xsize - 1 ; j++){
            if(hough_img.at<uchar>(i, j) < thresh) continue;
            if(i != 0 && j != 0 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i-1, j-1)) continue;
            if(i != 0 && 
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i-1, j)) continue;
            if(i != 0 && j != xsize-1 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i-1, j+1)) continue;
            if(j != 0 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i, j-1)) continue;
            if(j != xsize-1 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i, j+1)) continue;
            if(i != ysize-1 && j != 0 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i+1, j-1)) continue;
            if(i != ysize-1 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i+1, j)) continue;
            if(i != ysize-1 && j != xsize-1 &&
               hough_img.at<uchar>(i, j) < hough_img.at<uchar>(i+1, j+1)) continue;

            theta = j * d;
            rho = (i - ysize/2) / a;
            p[n][0] = rho;
            p[n][1] = theta;
            n++;
            //m = sprintf(&buf[posi], "theta = %10.3lf, rho = %10.3lf, value = %5d\n", theta * 180/PI, rho, hough_img.at<uchar>(i, j));
            //posi += m;
            if(n == DMAX) return;
        }
    }
    out_img = in_img.clone();

    for(int i = 0; i < n; i++)
        hough_line(in_img, out_img, p[i][0], p[i][1]);
}

void hough_line(cv::Mat in_img, cv::Mat out_img, double rho, double theta)
{
    int xsize = in_img.size().width;
    int ysize = in_img.size().height;
    int i, j;
    
    if((theta >= 0 && theta < PI/4 ) || theta >= 3*PI / 4){
        for( int i = 0; i < ysize ; i++){
            j = (int)((rho - (ysize/2 - i) * sin(theta))
                      /cos(theta) + xsize/2 + 0.5);
            if(j >= 0 && j < xsize)
                in_img.at<uchar>(i, j) = 255;
        }
    } else {
        for( int j = 0; j < ysize ; j++){
            i = (int)((-rho + (j - xsize/2) * cos(theta))
                      /sin(theta) + ysize/2 + 0.5);
            if(i >= 0 && i < xsize)
                in_img.at<uchar>(i, j) = 255;
        }
    }
}


/* ********************
   rho1, theta1 : 直線1
   rho2, theta2 : 直線2   
   x, y         : 交点
******************** */ 
void hough_cross(double theta1, double rho1, double theta2, double rho2, double *x, double *y)
{
    double d, t1, t2;
    
    t1 = theta1 * PI / 180.0;
    t2 = theta2 * PI / 180.0;    

    d = sin(t1 - t2);
    if(d == 0) return;
    *x = (rho2 * sin(t1) - rho2 * sin(t2)) / d;
    *y = (rho1 * cos(t2) - rho2 * cos(t1)) / d;
}
    

