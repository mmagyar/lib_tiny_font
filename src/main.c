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
    char file_name[]= "/home/matt/ter-u12n.bdf";
    read_file(file_name);
    font_common* fc = font_common_new(8,16);
    font_type_basic* ftb = font_type_basic_new(fc,'a');
    ftb->lines[0]=0xFF;

    printf("Hello, test start\n");
    fprintf(stdout,"ret %d\n",font_bit_get(fc,ftb,2,0));
    fprintf(stdout,"ret1 %d\n",font_bit_get(fc,ftb,7  ,0));
    font_bit_set(fc,ftb,7,0,false);
    fprintf(stdout,"ret2 %d\n",font_bit_get(fc,ftb,7  ,0));
    fprintf(stdout,"ret %d\n",font_bit_get(fc,ftb,0  ,1));
    fprintf(stdout,"ret1 %d\n",font_bit_get(fc,ftb,2,1));
    font_bit_set(fc,ftb,2,1,true);
    fprintf(stdout,"ret2 %d\n",font_bit_get(fc,ftb,2,1));
    font_type_basic_print_stdout(fc,ftb);
    font_common_delete(fc);
    printf("\nbye bye YOU\n");
    return 0;
}




