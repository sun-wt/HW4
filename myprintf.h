#ifndef MYPRINTF_H_INCLUDE
#define MYPRINTF_H_INCLUDE

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

void change( int32_t temp , int32_t carry , int capital);
int myprintf( const char *str ,...);

#endif

