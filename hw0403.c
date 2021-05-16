#include <stdio.h>
#include "myprintf.h"

int main() 
{
    char *t = "iu";
    myprintf("%s\n",t);
    myprintf("%X\n",678900);
    return 0;
}
