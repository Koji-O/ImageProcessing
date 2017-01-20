#include <opencv2/opencv.hpp>

int main(int argc, char **argv){
    
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat out = cv::Mat::zeros(img.size(), img.depth());
    cv::Mat kernel = cv::Mat::ones(5, 5, img.depth());
    std::cout << kernel << std::endl;    
    kernel.at<float>(0, 1) = 0.02;
    std::cout << kernel << std::endl;    
    cv::filter2D(img, out, img.depth(), kernel);
    cv::namedWindow("smooth weighted", cv::WINDOW_AUTOSIZE);
    cv::imshow("show", out);
    cv::waitKey(0);
    return 0;
}
