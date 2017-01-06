#include "gui/IPviewer.hpp"
#include <getopt.h>
#include <iostream>

int main(int argc, char** argv){
    std::cout << "argv[1]:" << argv[1] << std::endl;
    if (!argv[1]){
        throw std::invalid_argument("argv[1]: Please Image data.");
    }
    
    IpApp ipapp;
    ipapp.init(argc, argv);
    
    return 0;
}
