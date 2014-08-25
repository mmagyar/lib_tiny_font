#ifndef BDF_PARSER_H
#define BDF_PRASER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../font_struct.h"
bool strequ_f(const char*,const char*);
font_t* read_file(char* const filename,int const UP_TO_CHAR);

#endif

