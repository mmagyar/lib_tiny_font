#include "bdf_parser.h"

/** \brief strequ_f checks if the strings front are equal
 *         but only as long as the sorter is.
 *
 * \param string1 const char*
 * \param string2 const char*
 * \return bool returns zero (false) if the are not equal,
 *                         1 (true) otherwise
 *
 */
bool strequ_f(const char* string1, const char* string2)
{
    const size_t size1 = strlen(string1);
    const size_t size2 = strlen(string2);
    const size_t size = size1<size2?size1:size2;

    if(!strncmp(string1,string2,size)) {
        return true;
    }

    return false;
}
#define assign_to_num_check(x,y) if((y) !=NULL){x=atoi(y);}
int parse_desc(font_common* fc,char** parts, size_t parts_size)
{
    if(parts_size <1) {
        return -1;
    }

    if(strequ_f(parts[0],"STARTFONT ")) {
        //Font version number,  number
    } else if(strequ_f(parts[0],"COMMENT ")) {
        //Font comment, string
    } else if(strequ_f(parts[0],"CONTENTVERSION")) {
        //Font version integer
    } else if(strequ_f(parts[0],"FONT ")) {
        //Font name, string
    } else if(strequ_f(parts[0],"SIZE ")) {
        //Point size with X x Y res outputin format of (int int int)
        assign_to_num_check(fc->points, parts[1]);
//        fc->points =  parts[1]!=NULL? atoi(parts[1]):size;
//        res_x = parts[2]!=NULL? atoi(parts[2]):size;
//        res_y = parts[3]!=NULL? atoi(parts[3]):size;

    } else if(strequ_f(parts[0],"FONTBOUNDINGBOX")) {
        //bounding box of the Font w,h, offset w and h (int int int int)
        assign_to_num_check(fc->width, parts[1]);
        assign_to_num_check(fc->height, parts[2]);
        assign_to_num_check(fc->offset_x, parts[3]);
        assign_to_num_check(fc->offset_y, parts[4]);
//        fc->width    = parts[1]!=NULL? atoi(parts[1]):size;
//        fc->height   = parts[2]!=NULL? atoi(parts[2]):size;
//        fc->offset_x = parts[3]!=NULL? atoi(parts[3]):size;
//        fc->offest_y = parts[4]!=NULL? atoi(parts[4]):size;
        printf("parts size %d \n",parts_size);
    } else if(strequ_f(parts[0],"METRICSSET ")) {
        //optional
    } else if(strequ_f(parts[0],"STARTPROPERTIES  ")) {
        //int , noting the number of following lines,properties, optional

    } else if(strequ_f(parts[0],"PIXEL_SIZE")) {
    } else if(strequ_f(parts[0],"ENDPROPERTIES ")) {
        //end of properties list


    }
    return 0;
}
int set_font_line_from_hex_string(
    font_common* fc, font_type_basic* ftb,char* n,int cur_y)
{
    size_t cur_x=0;
    for(size_t cursor = 0; n[cursor]!= '\0'&& n[cursor]!= '\n'; cursor++) {
        char stubb[2] = {n[cursor],'\0'};
        uint8_t bits4 = strtol(stubb,NULL,16);
        int pxs[4]= {bits4>>3 &1,bits4>>2 &1,bits4>>1 &1,bits4 &1};
        for(int i=0; i<4; i++) {
            font_bit_set(fc,ftb,cur_x++,cur_y,pxs[i]);
        }
    }

    return 0;
}
int read_file(char*   const file_name)
{
    FILE* f = fopen(file_name,"r");
    int const READ_BUFFER_ELEMENTS = 1000;
    char reader[READ_BUFFER_ELEMENTS];

    int charnum = 0;
    int processed_charnum = 0;

    int const MAX_PARTS = 10,PARTS_BUFFER_LENGTH=128;
    char** parts = malloc(sizeof(char*)*MAX_PARTS);
    for(int i= 0 ; i< MAX_PARTS; i++) {
        parts[i] = malloc(sizeof(char)*PARTS_BUFFER_LENGTH);
    }

    int const READ_UP_TO=128;
    font_type_basic** basic = malloc(sizeof(font_type_basic)*READ_UP_TO);
     for(int i= 0; i < READ_UP_TO;i++) basic[i]=NULL;
//Parsing state start
    bool parsingBitmap=false;
    size_t cur_y=0;
    bool parsingTypes =false;
    uint32_t current_char = 0;
//Parsing state end
//Font info start
    font_common* fc = font_common_new(12,6);
//Font info end
    int ii=0;
    while(1) {

        if(fgets(reader,READ_BUFFER_ELEMENTS,f)==NULL) {
            if(feof(f)!= 0) {
                printf("\nEnd of file has been reached\n");
            } else if(ferror(f)!=0) {
                printf("\nAn error occurred during  file read");
            }
            break;

        }
        //Break the string into bits
        int parts_num=0;
        for(char* part = strtok(reader," ");
                parts_num<MAX_PARTS && part!=NULL ; parts_num++) {
            strncpy(parts[parts_num],part,PARTS_BUFFER_LENGTH);
            parts[parts_num][PARTS_BUFFER_LENGTH-1]='\0';
            part = strtok(NULL," ");
        }


        if(parsingTypes || (strequ_f(parts[0],"STARTCHAR "))) {
            parsingTypes =true;
            if(parsingBitmap) {
                if(strequ_f(parts[0],"ENDCHAR")) {
                    parsingBitmap=false;
                } else {
                    if(current_char == 109) {
                        set_font_line_from_hex_string(
                            fc,basic[current_char],parts[0],cur_y);
                        cur_y++;

                    }
                }

            } else  if(strequ_f(parts[0],"CHARS ")) {
                //int, The number of characters in this font
            } else if(strequ_f(parts[0],"STARTCHAR ")) {
                charnum++;
                //string, containing the name, start of a character
            } else if(strequ_f(parts[0],"ENCODING ")) {
                //Positive == Adobe standard encoding
                assign_to_num_check(current_char,parts[1]);
                if(current_char < READ_UP_TO) {
                    basic[current_char] = font_type_basic_new(fc,current_char);
                    processed_charnum++;
                }
            } else if(strequ_f(parts[0],"SWIDTH ")) {
                //Scale-able width, not really interesting for us
            } else if(strequ_f(parts[0],"DWIDTH ")) {
                //Mandatory for encoding 0, width in pixels
            } else if(strequ_f(parts[0],"SWIDTH1 ")) {
                //This should be only present with encoding 1 || 2
            } else if(strequ_f(parts[0],"DWIDTH1 ")) {
                //This should be only present with encoding 1 || 2
            } else if(strequ_f(parts[0],"VVECTOR ")) {
                //Optional
            } else if(strequ_f(parts[0],"BBX ")) {
                //(int int int int) width and height of black pixels,
                // and their offsets
            } else if(strequ_f(parts[0],"BITMAP")) {
                //start parsing bitmap
                parsingBitmap=true;
                cur_y=0;
            } else if(strequ_f(parts[0],"ENDCHAR")) {
                //ends the character description
                parsingBitmap=false;
            } else if(strequ_f(parts[0],"ENDFONT")) {
                //Terminates the file
            } else {
                printf("not handled %s",parts [0]);
            }
        } else {
            parse_desc(fc,parts,parts_num);
        }


    }

    fclose(f);
    printf("lines of bitmap: %d",ii);
    printf("parsed %d fonts, processed fonts: %d\n",charnum,processed_charnum);
    font_common_print(fc);
    font_type_basic_print_stdout(fc,basic[109]);

    for(int i =0; i < READ_UP_TO;i++){
            font_type_basic_delete(fc,basic[i]);
    }
    free(basic);
//    printf("target resolution x : %d y : %d\n",res_x,res_y);
    for(int i = 0 ; i <MAX_PARTS; i++) {
        free(parts[i]);
    }
    free(parts);
    font_common_delete(fc);
    return 0;
}
