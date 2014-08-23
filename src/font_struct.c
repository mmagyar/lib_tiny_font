#include "font_struct.h"

font_common* font_common_new(size_t width,size_t height)
{
    font_common* fc = malloc(sizeof(font_common));
    fc->width=width;
    fc->height =height;
    fc->pixels_num = width*height;
    return fc;
}
int font_common_delete(font_common* fc)
{
    if(fc ==NULL) {
        return -1;
    }
    free(fc);
    return 0;
}
font_type_basic* font_type_basic_new(font_common* common,const char corr_char)
{
    font_type_basic init = {corr_char,
                            malloc(sizeof(char)*common->pixels_num)
                           };
    font_type_basic* ftb = malloc(sizeof(font_type_basic));
    memcpy(ftb, &init , sizeof(ftb));

    return ftb;
}

int font_type_basic_delete(
    font_common* common, font_type_basic* delete_this)
{
    if(common ==NULL || delete_this==NULL) {
        return -1;
    }
    free(delete_this->lines);
    free(delete_this);
    return 0;
}

int font_bit_get(font_common* common ,font_type_basic* basic,
                 size_t x, size_t y)
{
    if(common->width<= x || common->height <= y) {
        return -1;
    }
    ///Number of bits in char
    int bits = CHAR_BIT * sizeof(unsigned char);
    ///How many pointer are there +1 because there are at least one
    size_t ptr_total = (common->pixels_num / bits)+1;
    size_t px_bit_num = (common->width * y)+x;
    size_t ptr_no = px_bit_num/bits;
    size_t bit_no = px_bit_num%bits;
    if(ptr_total < bit_no) {
        return -2;
    }
    int result = basic->lines[ptr_no] & (1<<bit_no);

    return result ==0 ?0:1;
}
int font_bit_set(font_common* common ,font_type_basic* basic,
                 size_t x, size_t y,bool value)
{
    if(common->width<= x || common->height <= y) {
        return -1;
    }
    int bits = CHAR_BIT * sizeof(unsigned char);
    size_t ptr_total = (common->pixels_num / bits)+1;
    size_t px_bit_num = (common->width * y)+x;
    size_t ptr_no = px_bit_num/bits;
    size_t bit_no = px_bit_num%bits;
    if(ptr_total < bit_no) {
        return -2;
    }
    if(value) {
        basic->lines[ptr_no] |= (1<<bit_no);
    } else {
        basic->lines[ptr_no] &= ~(1<<bit_no);
    }
    return 0;
}
void font_type_basic_print_stdout(font_common* fc , font_type_basic* ftb)
{
    for(int y = 0 ; y < fc->height; y++) {
        for(int x = 0; x< fc->width; x++) {
            printf(font_bit_get(fc,ftb,x,y)==1?"X":"_");
        }
        printf("\n");
    }

}
