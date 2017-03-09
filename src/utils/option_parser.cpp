#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include "../image/image.hpp"
#include <boost/program_options.hpp>
#include "option_parser.hpp"

using namespace std;
using namespace boost::program_options;

int option_parser(int argc, char** argv, Image* img){
    options_description option1("Extract Object.");
    options_description option2("Extract Contour.");    
    options_description option3("Remove Noise.");
    options_description option4("Sharpening.");
    options_description option5("Help discription.");        
    
    option1.add_options()
        ("option1, a", "o1")
        ;
    option2.add_options()
        ("option1, a", "o1")
        ;
    option3.add_options()
        ("option1, a", "o1")
        ;
    option4.add_options()
        ("option1, a", "o1")
        ;
    option5.add_options()
        ("help, h", "help");

    option1.add(option2).add(option3).add(option4).add(option5);
    variables_map values;

    try{
        store(parse_command_line(argc, argv, option1), values);
        if(!values.count("option1") && ){
            cout << option1 <<endl;
        }

        
    } catch(exception &e){
        cout << e.what()<< endl;
    }
        
    return 0;
}
