#include <opencv2/opencv>

int main(int argc, char **argv){
    
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat out = cv::Mat::zeros(img.size(), img.depth());
    cv::Mat kernel = cv::Mat::ones(5, 5, img.depth());

    //cv::filter2d(img, out, kernel);

    return 0;
}
