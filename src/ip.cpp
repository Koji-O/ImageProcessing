//#include "gui/IPviewer.hpp"
#include "image/image.hpp"
#include "utils/option_parser.hpp"
#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
    Image img;
    //img.show(BEFORE);

    //img.extract_contour(6);
    //img.remove_noise(2);
    
    //img.show(AFTER);
    //img.show(TEMP);

    /* For GUI */
    //IpApp ipapp;
    //ipapp.start(argc, argv);

    option_parser(argc, argv, &img);
    img.show_info();
    //img.start();
    
    return 0;
}

