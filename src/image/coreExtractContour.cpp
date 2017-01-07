/**
 * @file coreExtractContour.cpp
 * @brief 画像の輪郭を抽出する関数群
 */
#include "coreExtractContour.hpp"

#include <opencv2/opencv.hpp>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cmath>

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

    int TMP = 128;
    
    while (flg){
        flg = false;
        for(int i = 1; i < in_img.size().height - 1 ; ++i){
            for(int j = 1; j < in_img.size().width - 1 ; ++j){
                for(int k = 0; k < 9; ++k)
                    p[k] = in_img.at<uchar>(i + i_idx[k], j + j_idx[k]);

                for(auto &x : p){
                    if (x == 255) x = 1;
                    else if(x == 0) x = 0;
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
    int c[3][9] = {  0, -1,  0, -1,  4, -1,  0, -1,  0,
                    -1, -1, -1, -1,  8, -1, -1, -1, -1,
                     1, -2,  1, -2,  4, -2,  1, -2,  1};

    int d;
    int e[3] = {-1, 0, 1};
    int OFFSET = 128;
    
    type--;
    if(type < 0 ) type = 0;
    if(type > 2 ) type = 2;
    for(int i = 1; i < in_img.size().height + 1 ; i++){
        for(int j = 1; j < in_img.size().width + 1 ; j++){
            d = 0;
            for(int k = 0; k < 3; k++){
                d +=  c[type][k] * in_img.at<uchar>(i - 1, j + e[k])
                    + c[type][k + 3] * in_img.at<uchar>(i, j + e[k])
                    + c[type][k + 6] * in_img.at<uchar>(i + 1, j + e[k]);
            }
            d = (int)(d * amp) + OFFSET;
            if(d < 0) d = 0;
            if(d > 255) d = 255;
            out_img.at<uchar>(i, j) = (unsigned char) d;
        }
    }
}

