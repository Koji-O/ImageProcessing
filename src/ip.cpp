//#include "gui/IPviewer.hpp"
#include "image/image.hpp"
#include "utils/option_parser.hpp"
#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
<<<<<<< HEAD
    Image img;
=======
    Image img(argv[1]);
>>>>>>> d7c8d614c6f6311da9ee3fbe6464e9593326a3da
    //img.show(BEFORE);
    //img.extract_contour(6);
    img.remove_noise(2);
    img.show(AFTER);
    //img.show(TEMP);

<<<<<<< HEAD
    /* For GUI */
    //IpApp ipapp;
    //ipapp.start(argc, argv);

    option_parser(argc, argv, &img);
    img.show_info();
    //img.start();
=======
    // Under Developing
    //option_parser(argc, argv);
>>>>>>> d7c8d614c6f6311da9ee3fbe6464e9593326a3da
    
    return 0;
}

<<<<<<< HEAD
=======
int option_parser(int argc, char** argv){
    int opt;
    int index;
    // char *arg = NULL;
    string input, output;
    string longopt;
        
    struct option opts[] = {
        {"input", optional_argument, NULL, 'i'},
        {"output", optional_argument, NULL, 'o'},        
        {"counter", optional_argument, NULL, 'c'},
        {"noise", optional_argument, NULL, 'n'},
        {"help", no_argument, NULL, 'h'},                
    };
    
    while((opt = getopt_long(argc, argv, "i::c::o::h::n::", opts, &index)) != -1){
        switch(opt){
        case 'i' :
            printf("Input File::\t%s\n", optarg);
            input = optarg;
            break;
        case 'o' :
            printf("Output File::\t%s\n", optarg);
            output = optarg;
            break;
        case 'c' :
            printf("Extract Counter::\t%s\n", optarg);
            enum copt{
                cDEFUALT, cGRAD, cTEMP, cTHIN, cLAP, cZC, cH
            };
            cout << cGRAD << endl;
            break;
        case 'n' :
            printf("Remove Noise::\t%s\n", optarg);
            break;
        case 'h' :
            longopt = opts[index].name;            
            if(longopt == "help"){
                cout << "\n"
                     << "======= ip (image processing) ==== developed by Koji-O ==\n"                
                     << "This program provide fundamental Image processing tools. \n"
                     << "All source codes are based on the Reference book[ref.1]. \n"
                     << "Codes in this program are just translated from C to C++. \n"
                     << "ref.1: C言語で学ぶ実践画像処理 (井上 誠喜 et al.)          \n"
                     << "========================================================="
                     << endl;
                cout << "\n\nprogram:\n"
                     << "\t\t[-i:--input \"inputfile-path\"]\n"
                     << "\t\t\t:input: image-file(png, jpeg, ...etc)\n"
                     << "\t\t[-o:--output \"inputfile-path\"] \n"
                     << "\t\t\t:output: image-file(png, jpeg, ...etc)\n"                
                     << "\t\t[-c:--counter arg] \n"
                     << "\t\t\tExtract Contour from input Image.\n"                    
                     << "\t\t\t:couter: Argument Lists\n"
                     << "\t\t\t--[GRAD: Gradient Difference]\n"
                     << "\t\t\t--[TEMP: Template Matching]\n"
                     << "\t\t\t--[THIN: Thinning]\n"
                     << "\t\t\t--[LAP: Laplacian]\n"
                     << "\t\t\t--[ZC: Zero Cross]\n"
                     << "\t\t\t--[H: Hough Transform]\n"                    
                     << endl;
                break;
            }
            cout << "program: [-i:--input arg] "
                 << "[-o:--output arg] "
                 << "[-c:--counter arg]" << endl;
            break;
        default:
            printf("error! \'%c\' \'%c\'\n", opt, optopt);
            return 0;
        }
    }
    
    return 0;
}
>>>>>>> d7c8d614c6f6311da9ee3fbe6464e9593326a3da
