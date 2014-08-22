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
int read_file(char*   const file_name)
{
    FILE* f = fopen(file_name,"r");
    int const READ_BUFFER_ELEMENTS = 1000;
    // int const READ_BUFFER_SIZE = READ_BUFFER_ELEMENTS* READ_DATA_SIZE;
    //char * const reader = malloc(READ_DATA_SIZE*READ_BUFFER_ELEMENTS);
    char reader[READ_BUFFER_ELEMENTS];

    while(1) {

        if(fgets(reader,READ_BUFFER_ELEMENTS,f)==NULL) {
            if(feof(f)!= 0) {
                printf("\nEnd of file has been reached\n");
            } else if(ferror(f)!=0) {
                printf("\nAn error occured during  file read");
            }
            break;

        }
        if(strequ_f(reader,"STARTFONT ")) {
            printf(reader);
        } else if(strequ_f(reader,"COMMENT ")) {
            printf(reader);
        } else if(!strncmp(reader,"CONTENTVERSION",12)) {
            printf(reader);
        } else if(!strncmp(reader,"FONT ",5)) {
            printf(reader);
        } else if(!strncmp(reader,"SIZE ",5)) {
            printf(reader);
        } else if(!strncmp(reader,"METRICSSET ",11)) {
            printf(reader);
        }

        else if(!strncmp(reader,"METRICSSET ",11)) {
            printf(reader);
        }

        else if(!strncmp(reader,"METRICSSET ",11)) {
            printf(reader);
        }


        else         if(!strncmp(reader,"FONTBOUNDINGBOX",15)) {        }
        else if(!strncmp(reader,"PIXEL_SIZE",10)) {}
        else if(!strncmp(reader,"STARTCHAR",9)) {}
        else if(!strncmp(reader,"ENCODING",8)) {}
        else if(!strncmp(reader,"BBX",3)) {}
        else if(!strncmp(reader,"BITMAP",6)) {}
        else if(!strncmp(reader,"ENDCHAR",7)) {}
        else {
            //printf("n");
        }
        /*
        switch (lineSplit[0]) {
        case "FONTBOUNDINGBOX":
            // Out.log("FONT: " + lineSplit[1]);
            box = lineSplit[1].split(" ");
            width = Integer.parseInt(box[0]);
            height = Integer.parseInt(box[1]);
            offX = Integer.parseInt(box[2]);
            offY = Integer.parseInt(box[3]);
            break;
        case "PIXEL_SIZE":
            size = Integer.parseInt(lineSplit[1]);
            break;
        case "STARTCHAR":
            if (readingChar || readingCharBitmap)
                Out.error("ERROR char started before previveous enden.");
            readingChar = true;
            // thisCharName = lineSplit[1];
        break;
        case "ENCODING":
        thisCharCode = Integer.parseInt(lineSplit[1]);
        break;
        case "BBX":
        box = lineSplit[1].split(" ");
        cW = Integer.parseInt(box[0]);
        cH = Integer.parseInt(box[1]);
        cX = Integer.parseInt(box[2]);
        cY = Integer.parseInt(box[3]);
        break;
        case "BITMAP":
        if(readingChar)
        {
            readingCharBitmap = true;
        } else
        { Out.error("Error while Parsing, No STARTCHAR before BITMAP"); }
        lineArray = new long[cH];
        lineCounter = 0;
        break;

        case "ENDCHAR":
        if(!(readingChar && readingCharBitmap))
        {
            Out.error("ERROR, char ended before it was started");
        }
        readingChar = false;
        readingCharBitmap = false;
        // Out.log("   " + thisCharName + ": " + (char) thisCharCode + " Size: " + cW + " : " + cH);

            Font newFont = new Font(cW, cH, cX, cY, (char) thisCharCode, lineArray);
            types.put(newFont.charachter, newFont);

            // Out.log(String.format("0x%8s", Long.toHexString(lng)).replace(' ', '0'));

            break;
        default:
            if (readingChar && readingCharBitmap)
                lineArray[lineCounter++] = Long.parseLong(line, 16);
            break
        */
        //        printf(reader);

    }

    fclose(f);
    return 0;
}
