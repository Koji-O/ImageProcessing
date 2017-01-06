#include "gui/IPviewer.hpp"
#include "image/Image.hpp"
#include <getopt.h>
#include <iostream>

int main(int argc, char** argv){
    std::cout << "argv[1]:" << argv[1] << std::endl;
    if (!argv[1]){
        throw std::invalid_argument("argv[1]: Please Image data.");
    }
    //IpApp app;
    //app.start(argc, argv);
    Image img(argv[1]);
    img.show(BEFORE);

    img.extract_contour(3);

    img.show(TEMP);    
    img.show(AFTER);
    //IpApp ipapp;
    //ipapp.init(argc, argv);
    
    return 0;
}
