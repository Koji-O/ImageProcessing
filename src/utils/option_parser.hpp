#ifndef __OPTION_PARSER_HPP
#define __OPTION_PARSER_HPP
#include "../image/image.hpp"

int option_parser(int argc, char** argv, Image* img);
void short_help(void);
void long_help(void);

#endif
