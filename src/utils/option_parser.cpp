#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include <cstdlib>
#include "../image/image.hpp"
#include "option_parser.hpp"

using namespace std;

int option_parser(int argc, char** argv, Image* img){
    int opt;
    int index;
    char *arg = NULL;
    string input, output;
    string ctype;
    string cmessage, comessage;
    int copt;
    string help;
    
    if ( argc < 2 ){
        short_help();
        exit(0);
    }
    
    struct option opts[] = {
        {"out", optional_argument, NULL, 'o'},        
        {"counter", optional_argument, NULL, 'c'},
        {"noise", optional_argument, NULL, 'n'},
        {"sharpen", optional_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},                
    };

    while((opt = getopt_long(argc, argv, "c::o::h::n::s::", opts, &index)) != -1){
        cout << "while" << endl;
        switch(opt){
        case 'o' :
            printf("%s\n",optarg);o
            break;
        case 'c' :
            ctype = 'c';
            cmessage = "Extract Counter";
            enum ecopt{
                cDEFUALT, cGRAD, cTEMP, cTHIN, cLAP, cZC, cH
            };
            copt = 0;
            break;
        case 'n' :
            cmessage = "Remove Noise";
            printf("Remove Noise::\t%s\n", optarg);
            break;
        case 'h' :
            help = opts[index].name;            
            if(help == "help"){
                long_help();
                break;
            }
            short_help();
            break;
        case '?':
            printf("error! \'%c\' \'%c\'\n", opt, optopt);
            return 0;
        }
    }

    img->set_info(argv[1], ctype, copt, cmessage, comessage);
    
    return 0;
}

void short_help(void){
    cout << "./program:: (input :positional) \n"
         << "\t\t\t[-o:--output arg] \n"
         << "\t\t\t[-c:--counter arg] \n" 
         << "\t\t\t[-n:--noise arg] \n"
         << "\t\t\t[-n:--sharpen arg]" << endl;                        
}

void long_help(void){
    cout << "\n"
         << "======= ip (image processing) ==== developed by Koji-O ==\n"                
         << "This program provide fundamental Image processing tools. \n"
         << "All source codes are based on the Reference book[ref.1]. \n"
         << "Codes in this program are just translated from C to C++. \n"
         << "ref.1: C言語で学ぶ実践画像処理 (井上 誠喜 et al.)          \n"
         << "========================================================="
         << endl;
    cout << "\n\nprogram:\n"
         << "\t\t( \"inputfile-path\" positional) \n"
         << "\t\t\t:input: image-file(png, jpeg, ...etc)\n"                
         << "\t\t[-o:--output \"file-path\" optional] \n"
         << "\t\t\t:output: image-file(png, jpeg, ...etc)\n"                
         << "\t\t[-c:--counter arg optional] \n"
         << "\t\t\tExtract Contour from input Image.\n"                    
         << "\t\t\t:couter: Argument Lists\n"
         << "\t\t\t--[GRAD: Gradient Difference]\n"
         << "\t\t\t--[TEMP: Template Matching]\n"
         << "\t\t\t--[THIN: Thinning]\n"
         << "\t\t\t--[LAP: Laplacian]\n"
         << "\t\t\t--[ZC: Zero Cross]\n"
         << "\t\t\t--[H: Hough Transform]\n"
         << "\t\t[-n:--noise arg optional] \n"
         << "\t\t\tRemove Noise from input Image.\n"                    
         << "\t\t\t:: Argument Lists\n"
         << "\t\t\t--[GRAD: Gradient Difference]\n"
         << "\t\t\t--[TEMP: Template Matching]\n"
         << "\t\t\t--[THIN: Thinning]\n"
         << "\t\t\t--[LAP: Laplacian]\n"
         << "\t\t\t--[ZC: Zero Cross]\n"
         << "\t\t\t--[H: Hough Transform]\n"
         << "\t\t[-s:--sharpen arg optional] \n"
         << "\t\t\tSharpen input Image.\n"                    
         << "\t\t\t:: Argument Lists\n"
         << "\t\t\t--[GRAD: Gradient Difference]\n"
         << "\t\t\t--[TEMP: Template Matching]\n"
         << "\t\t\t--[THIN: Thinning]\n"
         << "\t\t\t--[LAP: Laplacian]\n"
         << "\t\t\t--[ZC: Zero Cross]\n"
         << "\t\t\t--[H: Hough Transform]\n"                    
         << endl;
}
