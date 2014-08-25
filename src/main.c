/*main file for tiny_font, tests and utilities*/
#include "main.h"
int main(int argc, char** argv)
{
    printf("hello world\n");
    printf("argument: ");
    for(int i=0; i< argc; i++) {
        printf(argv[i]);
        printf("\n");
    }
    //char file_name[]= "/home/matt/ter-u12n.bdf";
    char file_name[]= "/home/matt/dejavu-12.bdf";
    font_t* font=    read_file(file_name,128);
    font_type_basic_print_stdout(font->fc,font->types['m']);
    font_type_basic_print_stdout(font->fc,font->types['a']);
    font_type_basic_print_stdout(font->fc,font->types['t']);
    font_type_basic_print_stdout(font->fc,font->types['t']);
    font_t_delete(font);
    printf("\nbye bye YOU\n");
    return 0;
}




