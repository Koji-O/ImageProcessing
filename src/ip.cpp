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

    option_parser(argc, argv, &img);
    img.start();
    return 0;
}
