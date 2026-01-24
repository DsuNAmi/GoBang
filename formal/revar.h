#ifndef __REVAR_H__
#define __REVAR_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* formal */
#define IN 
#define OUT 
#define INOUT 


/* var redefine */
typedef bool BOOL_T;
typedef int INT;
typedef unsigned int UINT;
typedef char CHAR;
typedef unsigned char UCHAR;
typedef short SHORT;
typedef unsigned short USHORT;
typedef long LONG;
typedef unsigned long ULONG;
typedef float FLOAT;
typedef double DOUBLE;
typedef void VOID;


/* variable constant */
#define BOOL_TRUE      true
#define BOOL_FALSE     false
#define ZERO_INT      0
#define ZERO_UINT     0U
#define ZERO_CHAR     '\0'
#define CHAR_END      '\n'


#define COMMAND_SUCCEED   0
#define COMMAND_FAILED    1
#define COMMAND_NO_MEMORY  2




/* function */
#define GO_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define GO_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define GO_ABS(a)              (((a) < 0) ? -(a) : (a))
#define GO_SWAP(a,b,temp)     { (temp) = (a); (a) = (b); (b) = (temp); }

#define GO_FOR_EACH(list, index, size, function)    \
    for (index = 0; index < (size); index++) {    \
        function(list[index]);                   \
    }\

#define GO_INIT_STRUC(struc) \
{ \
    memset(&(struc), 0, sizeof(struc)); \
}

#define GO_MALLOC(var, type, size) \
{ \
    (var) = (type *)malloc(size); \
}

#define GO_FGETS(buffer, size, stream) \
    fgets(buffer, size, stream)

#define GO_STRNCMP(str1, str2, n) \
    strncmp((str1), (str2), (n)

#define GO_STRNCPY(dest, src, size) \
    strncpy((dest), (src), (size))

#define GO_FREE(ptr) \
{ \
    if (NULL != (ptr)) { \
        free(ptr); \
        (ptr) = NULL; \
    } \
}

#endif // __REVAR_H__