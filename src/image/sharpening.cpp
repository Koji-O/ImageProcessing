#include "image_const.hpp"
#include "sharpening.hpp"

#include <opencv2/opencv.hpp>

/* ********
   画像の明るさを調整する
   in_img  : 入力画像配列
   out_img : 出力画像配列
   fmax : 入力画像の濃度の最大値
   fmin : 入力画像の濃度の最小値
******** */
void amplify(cv::Mat in_img, cv::Mat out_img, double a, double b)
{
    int d;
	for (int i = 0; i < in_img.size().height; i++){
    	for (int j = 0; j < in_img.size().width; j++){
			d = (int)( in_img.at<uchar>(i, j) * a + b);
			if (d < LOW) d = LOW;
			if (d > HIGH) d = HIGH;
			out_img.at<uchar>(i, j) = (unsigned char)d;
		}
	}
}

/* ********
   画像の明るさの範囲を求める
   in_img  : 入力画像配列
   fmax : 入力画像の濃度の最大値
   fmin : 入力画像の濃度の最小値
******** */
void range(cv::Mat in_img, int *fmax, int *fmin)
{
	int n;

	*fmax = LOW;
	*fmin = HIGH;
	for (int i = 0; i < in_img.size().height; i++){
		for (int j = 0; j < in_img.size().width; j++){
			n =(int)in_img.at<uchar>(i, j);
			if (n > *fmax) *fmax = n;
			if (n < *fmin) *fmin = n;
		}
	}
}

/* ********
   濃度を0から255の範囲に拡大する
   in_img  : 入力画像配列
   out_img : 出力画像配列
   fmax : 入力画像の濃度の最大値
   fmin : 入力画像の濃度の最小値
******** */
void expand(cv::Mat in_img, cv::Mat out_img, int fmax, int fmin)
{
	double a, b;

	a = 255.0 / (double)(fmax - fmin);
	b = -255.0 * fmin / (double)(fmax - fmin);
	amplify(out_img, in_img, a, b);
}

/* ********
   濃度ヒストグラムを平坦化する
   in_img  : 入力画像配列
   out_img : 出力画像配列
   hist : 濃度ヒストグラム配列
******** */
void plane(cv::Mat in_img, cv::Mat out_img, long hist[256])
{
    struct xyw buf[BUFF_MAX];
    int height = in_img.size().height;
    int width = in_img.size().width;
    int sum;
	int delt;              /* 周辺画素レベルにより選ばれる画素数 */
	int low, high;         /* 処理レベルの範囲 */
	int av;                /* 平坦化後の１濃度レベルの画素数 */
    cv::Mat buf_img;

	av = (int)((height) * (width) / 256);
	high = 255;
	low = 255;

    out_img = cv::Mat::zeros(in_img.size(), CV_8UC1);
    buf_img = in_img.clone();    

	for (int i = 255; i > 0; i--){
		for (sum = 0; sum < av; low--) sum = sum + hist[low];
		low++;
		delt = hist[low] - (sum - av);
		sort(buf_img, buf, low);
		if (low < high){
			for (int iy = 0; iy < height; iy++){
				for (int jx = 0; jx < width; jx++){
					if (((int)buf_img.at<uchar>(iy, jx) >= low + 1 ) &&
						((int)buf_img.at<uchar>(iy, jx) <= high))
                        out_img.at<uchar>(iy, jx) = (unsigned char)i;
				}
			}
		}
		for (int j = 0; j < delt; j++){
			out_img.at<uchar>(buf[j].y, buf[j].x) =(unsigned char)i;
			buf_img.at<uchar>(buf[j].y, buf[j].x) =(unsigned char)0;
		}
		hist[low] = hist[low] - delt;
		high = low;
	}
}

/* ********
   周りの画素の濃度の高い順に並び変える
   in_img  : 入力画像配列
   data  : 位置及び周辺画素の濃度和の配列
   level : 並び変える画素の濃度
******** */
void sort(cv::Mat in_img, struct xyw data[], int level)
{
    int inum, wt;
	struct xyw temp;

	inum = 0;
	for (int i = 0; i < in_img.size().height; i++ ){
		for (int j = 0; j < in_img.size().width; j++ ){
			if ((int)in_img.at<uchar>(i, j) == level){
				weight(in_img, i, j, &wt);	/* 周辺画素の濃度の和を計算 */
				data[inum].y = i;
				data[inum].x = j;
				data[inum].w = wt;
				inum++;
			}
		}
	}

	for (int i = 0; i < inum - 1; i++ ){         /* 並び変え */
		for (int j = i + 1; j < inum; j++){
			if (data[i].w <= data[j].w){
				temp.y = data[i].y;
				temp.x = data[i].x;
				temp.w = data[i].w;
				data[i].y = data[j].y;
				data[i].x = data[j].x;
				data[i].w = data[j].w;
				data[j].y = temp.y;
				data[j].x = temp.x;
				data[j].w = temp.w;
			}
		}
	}
}

/* ********
   周辺画素の濃度の和を計算する
   in_img  : 入力画像配列
   i, j : 画素位置
   wt : 濃度和
******** */
void weight(cv::Mat in_img, int i, int j, int *wt)
{
	int dim, djm;
	int dip, djp;
	int k, d[8];

	dim = i - 1;
	djm = j - 1;
	dip = i + 1;
	djp = j + 1;
	if (dim < 0) dim = i;
	if (djm < 0) djm = j;
	if (dip > in_img.size().height-1) dip = i;
	if (djp > in_img.size().width-1) djp = j;

	d[0] = (int)in_img.at<uchar>(dim, djm);
	d[1] = (int)in_img.at<uchar>(dim, j);
	d[2] = (int)in_img.at<uchar>(dim, djp);
	d[3] = (int)in_img.at<uchar>(i, djm);
	d[4] = (int)in_img.at<uchar>(i, djp);
	d[5] = (int)in_img.at<uchar>(dip, djm);
	d[6] = (int)in_img.at<uchar>(dip, j);
	d[7] = (int)in_img.at<uchar>(dip, djp);
	for (k = 0; k < 8; k++) *wt = *wt + d[i];
}

/* ********
   組織的ディザ法
   in_img  : 入力画像配列
   out_img : 出力画像配列
******** */
void dither_ordered(cv::Mat in_img, cv::Mat out_img)
{
	static int thres[4][4] = {{  0,  8,  2, 10},
                              { 12,  4, 14,  6},
							  {  3, 11,  1,  9},
                              { 15,  7, 13,  5}};	/* ディザマトリクス	*/
    
	for (int i = 0 ; i<in_img.size().height/4 ; i++)
		for (int j = 0 ; j<in_img.size().width/4 ; j++)
			for (int m = 0; m < 4; m++)
				for (int n = 0; n < 4; n++)
                    if ((int)in_img.at<uchar>(i*4+m, j*4+n) > thres[m][n]*16+8) 
                        out_img.at<uchar>(i*4+m, j*4+n) = HIGH;
                    else out_img.at<uchar>(i*4+m, j*4+n) = LOW;    
}

/* ********
   平均誤差最小ディザ法
   in_img  : 入力画像配列
   out_img : 出力画像配列
******** */
void dither_minimized(cv::Mat in_img, cv::Mat out_img)
{
    int width = in_img.size().width;
    int height = in_img.size().height;
        
	int	t, d;
	int	error[width], error1[width], error2[width]; 	/* 誤差配列 */

	t = (HIGH+1)/2;		/*　閾値　この例では１２８	*/
	for (int i = 0; i < width; i++) {
		if (in_img.at<uchar>(0, i) > t) out_img.at<uchar>(0, i) = HIGH;
		else		out_img.at<uchar>(0, i) = LOW;
		error1[i] = in_img.at<uchar>(0, i)-out_img.at<uchar>(0, i) ;
	}
	for (int i = 0; i < width; i++) {
		if (in_img.at<uchar>(1, i) > t) out_img.at<uchar>(1, i) = HIGH;
		else		out_img.at<uchar>(1, i) = LOW;
		error2[i] = in_img.at<uchar>(1, i)-out_img.at<uchar>(1, i);
	}
	for (int i = 2; i < height; i++) {
		if (in_img.at<uchar>(i, 0) > t) out_img.at<uchar>(i, 0) = HIGH;
		else	out_img.at<uchar>(i, 0) = LOW;
		error[0] = in_img.at<uchar>(i, 0)-out_img.at<uchar>(i, 0);
		if (in_img.at<uchar>(i, 1) > t) out_img.at<uchar>(i, 1) = HIGH;
		else	out_img.at<uchar>(i, 1) = LOW;
		error[1] = in_img.at<uchar>(i, 1)-out_img.at<uchar>(i, 1);
		for (int j = 2; j < width-2; j++) {
		    d = (error1[j-2]+error1[j-1]*3+error1[j]*5
		    	+error1[j+1]*3+error1[j+2]
		    	+error2[j-2]*3+error2[j-1]*5+error2[j]*7
		    	+error2[j+1]*5+error2[j+2]*3
		    	+error[j-2]*5+error[j-1]*7)/48;
		    if ((int)in_img.at<uchar>(i, j)+d > t) out_img.at<uchar>(i, j) = HIGH;
		    else	out_img.at<uchar>(i, j) = LOW;
		    error[j] = in_img.at<uchar>(i, j)+d-out_img.at<uchar>(i, j);
		}
		if (in_img.at<uchar>(i, width-2) > t) out_img.at<uchar>(i, width-2) = HIGH;
		else	out_img.at<uchar>(i, width-2) = LOW;
		error[width-2] = in_img.at<uchar>(i, width-2)-out_img.at<uchar>(i, width-2);
		if (in_img.at<uchar>(i, width-1) > t) out_img.at<uchar>(i, width-1) = HIGH;
		else	out_img.at<uchar>(i, width-1) = LOW;
		error[width-1] = in_img.at<uchar>(i, width-1)-out_img.at<uchar>(i, width-1);
		for (int j = 0; j < width; j++) {
			error1[j] = error2[j];
			error2[j] = error[j];
		}
	}
}


/* ********
   量子化する
   in_img  : 入力画像配列
   out_img : 出力画像配列
   nq:  階調数
******** */
void quantize(cv::Mat in_img, cv::Mat out_img, int nq)
{
    
	for (int i = 0; i < in_img.size().height; i++)
		for (int j = 0; j < in_img.size().width; j++)
			d_quantize(in_img.at<uchar>(i, j), &out_img.at<uchar>(i, j), nq);
}

/* ********
   量子化（データ）
   in: 入力
   pout: 出力
   nq:  階調数
******** */
void d_quantize(int in, unsigned char *pout, int nq)
{
    int t, i;

	t = (HIGH + 1)/(nq - 1);
	i = (int)((double)in / t + 0.5) * t;
	if (i > HIGH)	*pout = HIGH;
	else *pout = i;
}

/* ********
   平均誤差最小ディザ法(多階調)
   in_img  : 入力画像配列
   out_img : 出力画像配列
   nq:  階調数
******** */
void dither_minimized_multi(cv::Mat in_img, cv::Mat out_img, int nq)
{
    int width = in_img.size().width;
    int height = in_img.size().height;

    int i, j;
	int d;
	int	error[width], error1[width], error2[width]; 	/* 誤差配列 */

	for (i = 0; i < width; i++) {
		d_quantize((int)in_img.at<uchar>(0, i), &out_img.at<uchar>(0, i), nq);
        error1[i] = (int)in_img.at<uchar>(0, i)-(int)out_img.at<uchar>(0, i);
     	}
	for (i = 0; i < width; i++) {
		d_quantize((int)in_img.at<uchar>(1, i), &out_img.at<uchar>(1, i), nq);
        error2[i] = (int)in_img.at<uchar>(1, i)-out_img.at<uchar>(1, i);
	}
	for (i = 2; i < height; i++) {
		d_quantize((int)in_img.at<uchar>(i, 0), &out_img.at<uchar>(i, 0), nq);
		error[0] = (int)in_img.at<uchar>(i, 0)-(int)out_img.at<uchar>(i, 0);
		d_quantize((int)in_img.at<uchar>(i, 1), &out_img.at<uchar>(i, 1), nq);
		error[1] = (int)in_img.at<uchar>(i, 1)-(int)out_img.at<uchar>(i, 1);
		for (j = 2; j < width-2; j++) {
		    d = (error1[j-2]+error1[j-1]*3+error1[j]*5
			+error1[j+1]*3+error1[j+2]
			+error2[j-2]*3+error2[j-1]*5+error2[j]*7
			+error2[j+1]*5+error2[j+2]*3
			+error[j-2]*5+error[j-1]*7)/48;
			d_quantize((int)in_img.at<uchar>(i, j)+d, &out_img.at<uchar>(i, j), nq);
			error[j] = (int)in_img.at<uchar>(i, j)+d-(int)out_img.at<uchar>(i, j);
		}
		d_quantize((int)in_img.at<uchar>(i, width-2), &out_img.at<uchar>(i, width-2), nq);
		error[width-2] = (int)in_img.at<uchar>(i, width-2)
			- (int)out_img.at<uchar>(i, width-2);
		d_quantize((int)in_img.at<uchar>(i, width-1), &out_img.at<uchar>(i, width-1), nq);
		error[width-1] = (int)in_img.at<uchar>(i, width-1)
			- (int)out_img.at<uchar>(i, width-1);
		for (j = 0; j < width; j++) {
			error1[j] = error2[j];
			error2[j] = error[j];
		}
	}
}

