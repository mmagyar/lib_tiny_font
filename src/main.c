/*main file for tiny_font, tests and utilities*/
#include "main.h"
int main(int argc, char **argv)
{
    printf("hello world\n");
    printf("argument: ");
    for (int i=0; i< argc; i++) {
        printf(argv[i]);
        printf("\n");
    }
    char file_name[]= "/home/matt/ter-u12n.bdf";
    read_file(file_name);



    printf("\nbye bye YOU\n");
    return 0;
}




