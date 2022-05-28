#include <stdio.h>
#include <stdlib.h>
#define ERRORVARIABLE unsigned short
#define NUMBEROFSTEPS unsigned short

void printErrors(ERRORVARIABLE *, char *);

#define SETUP_ERROR_HANDLING(x) char * charArray = x;size_t sizeOfMKTErrorFP = 0;\
for(int i=0;charArray[i]!=0;i++)sizeOfMKTErrorFP=i+2;char*filePath=malloc(sizeOfMKTErrorFP);\
for(int i=0;i<sizeOfMKTErrorFP;i++)filePath[i]=charArray[i];ERRORVARIABLE errorCode = 0;\
NUMBEROFSTEPS step = 0;

#define HANDLE_ERRORS printf("\033[90;40mSTEP: \033[93;40m%d\n",step); \
step++;if(errorCode != 0){printErrors(&errorCode, filePath);return errorCode;}

void printErrors(ERRORVARIABLE * errorCode, char * filePath);



#ifdef MKT_ERROR_HANDLING_IMPLEMENTATION

void printErrors(ERRORVARIABLE * errorCode, char * filePath)
{
    FILE *MKTFILE;
    ERRORVARIABLE ogErrorCode = *errorCode;
    if( fopen_s( &MKTFILE, filePath, "rb" ) == 0 )
    {
        char *charArray;
        fseek(MKTFILE, 0L, SEEK_END);
        long sizeOfFile = ftell(MKTFILE);
        rewind(MKTFILE);
        charArray = (char*)malloc(sizeOfFile);
        if(charArray == NULL)
        {*errorCode = 1;printf("\033[31;40mERROR\033[93;40m[1]\033[31;40m - \033[97;40mSystem error (malloc failure) \033[39;49m");return;}
        sizeOfFile = fread( charArray,1, sizeOfFile, MKTFILE );
        fclose( MKTFILE );
        // now it's time for some simple file reading shenanigans
        long long positionOfError = 0;
        char foundError = 0;
        ERRORVARIABLE errorCodeC;
        char * errorNumber;
        while(foundError == 0)
        {
            positionOfError++;
            if(positionOfError > sizeOfFile)
            {*errorCode = 1;printf("\033[31;40mERROR\033[93;40m[1]\033[31;40m - \033[97;40mSystem error ( in file \"%s\" error %d is missing) \033[39;49m",filePath,ogErrorCode);return;}
            if(charArray[positionOfError] == '\n')
            {
                positionOfError++;
                long long endOfNumber = positionOfError;
                while (charArray[endOfNumber]>47&&charArray[endOfNumber]<58)
                    endOfNumber++;
                endOfNumber--;
                errorNumber = (char*)malloc(endOfNumber - positionOfError+1);
                for(long long i = positionOfError; i <= endOfNumber;i++)
                    errorNumber[i-positionOfError] = charArray[i];
                errorNumber[endOfNumber-positionOfError+1] = 0;
                sscanf(errorNumber,"%d", &errorCodeC);
                if(errorCodeC == *errorCode)
                    foundError = 1;
            }
        }
        for(0;charArray[positionOfError] != '-';positionOfError++)
            0;
        positionOfError++;positionOfError++;
        // simple
        printf("\033[31;40mERROR\033[93;40m[%d]\033[31;40m - \033[97;40m",*errorCode);
        for(int i = positionOfError; charArray[i] != '\n' && i < sizeOfFile;i++)
            printf("%c",charArray[i]);
        printf("\033[39;49m\n");
    }
    else
        *errorCode = 1;
    if(*errorCode == 1)
    {
        printf("\033[31;40mERROR\033[93;40m[1]\033[31;40m - \033[97;40mSystem error \033[39;49m");
    }
    return;
}
#endif // MKT_ERROR_HANDLING_IMPLEMENTATION