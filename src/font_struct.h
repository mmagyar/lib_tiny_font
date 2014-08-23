#ifndef FONT_STRUCT_H_INCLUDED
#define FONT_STRUCT_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

/** \brief Must be used with the supplied constructor and deconstruct method
 */
typedef struct font_common {
    size_t width; /**pixels, means bits*/
    size_t height;
    size_t pixels_num;
} font_common;

/** \brief Must be used with the supplied constructor and deconstruct method
 */
typedef struct font_type_basic {
    const char character;
    /**Start of line, the exact size is set by font_common struct
    The stored data is always raw bits corresponding to pixels*/
    unsigned char* lines;
} font_type_basic;

/** \brief Create and initialize font_common structure
 *
 * \param width size_t  maximum width of any single character
 * \param height size_t maximum height of any single character
 * \return font_common* the created font_common struct,NULL if failed
 *
 */
font_common* font_common_new(size_t width,size_t height);

/** \brief Delete font_common structure
 *
 * \param fc font_common* Pointer to structure to destroy
 * \return int non-zero value on error, 0 otherwise
 *
 */
int font_common_delete(font_common* fc);

/** \brief Create and initialize font_type_basic
 *
 * \param common font_common* The common data for fonts;
 * \param c_char The character this struct will represent
 * \return font_type_basic* the created font_type_basic
 *
 */
font_type_basic* font_type_basic_new(font_common* common, const char c_char);

/** \brief delete and clean up font_type_basic struct
 *
 * \param common font_common* the common file used to create this file
 * \param delete_this font_type_basic* the pointer to the struct to be deleted
 * \return int non-zero on failure , 0 on success
 *
 */
int font_type_basic_delete(font_common* common,font_type_basic* delete_this);


int font_bit_get(font_common* common ,font_type_basic* basic,
                 size_t x, size_t y);
int font_bit_set(font_common* common ,font_type_basic* basic,
                 size_t x, size_t y,bool value);
void font_type_basic_print_stdout(font_common* fc , font_type_basic* ftb);
#endif // FONT_STRUCT_H_INCLUDED
