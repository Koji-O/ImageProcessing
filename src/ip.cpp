#include "image/Image.hpp"
#include "gui/IPviewer.hpp"
#include <iostream>


int main(int argc, char** argv){

    std::cout << "argv[1]:" << argv[1] << std::endl;
    if (!argv[1]){
        throw std::invalid_argument("argv[1]: Please Image data.");
    }
    
    Image img(argv[1]);
    img.extract_contour(2);
    
    myApp app;
    app.init(argc, argv);


    
    return 0;
}
