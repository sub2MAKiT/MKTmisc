# Usage

### Program
```C
#include "../../MKTSimpleErrorHandling.h"

int main(int argc,char ** argv)
{
    SETUP_ERROR_HANDLING("./errors.txt") // path to your file with error strings

    // your program

    printf("welcome to the \"a\" program\n");

    if(argc != 2)
        errorCode = 1;

    HANDLE_ERRORS // error handling

    if(!(argv[1][0] == 'a' && argv[1][1] == 0)) // set errorCode to 2, if the input is not 'a'
        errorCode = 2;

    HANDLE_ERRORS // error handling

    return errorCode;
}
```

### Error strings (in this case "errors.txt")
```
0 - No errors
1 - System error
2 - Input not 'a'
```

## Breakdown
1. Include MKTSimpleErrorHandling
```C
#include "../../MKTSimpleErrorHandling.h"
```
2. Setup MKTSimpleErrorHandling, with a path to your error string text file
```C
SETUP_ERROR_HANDLING("./errors.txt") // path to your file with error strings
```
3. use ```HANDLE_ERRORS``` when needed
```C
    if(!(argv[1][0] == 'a' && argv[1][1] == 0)) // set errorCode to 2, if the input is not 'a'
        errorCode = 2;

    HANDLE_ERRORS // error handling
```
4. Create your own error strings file
```
0 - No errors
1 - System error
2 - Input not 'a'
```

### Error strings file
0 - No errors | hardcoded, means no errors

1 - System error | hardcoded, means that a gnu or MKT function failed

2 - Your own error

3 - Your own error

...