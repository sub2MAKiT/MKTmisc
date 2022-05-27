#define MKT_ERROR_HANDLING_IMPLEMENTATION
#include "../../MKTSimpleErrorHandling.h"

int main(int argc,char ** argv)
{
    SETUP_ERROR_HANDLING("./errors.txt") // path to your file with error strings

    // your program

    printf("welcome to the \"a\" program\n");

    if(argc == 1)
        errorCode = 1;

    HANDLE_ERRORS // error handling

    if(argc > 2)
        errorCode = 3;

    HANDLE_ERRORS // error handling
    
    if(!(argv[1][0] == 'a' && argv[1][1] == 0)) // set errorCode to 2, if the input is not 'a'
        errorCode = 2;

    HANDLE_ERRORS // error handling

    return errorCode;
}