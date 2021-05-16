#include "myprintf.h"

void change( int32_t temp , int32_t carry , int capital) 
{
    int32_t modify = temp;
    int32_t times = 0;
    modify = temp;
    char B[1280];
    int32_t b[1280];
    while( modify > 0 )
    {
        modify /= carry;
        times++;
    }
    modify = temp;
    for(int i=0;i<times;i++)
    {
        modify %= carry;
        b[i] = modify;
        temp /= carry;
        modify = temp;
    }
    for(int i=times-1;i>=0;i--)
    {
        
        if( b[i] >= 10 )
        {
            if( b[i] == 10 )
            {    
                if( capital )
                B[i] = 'A';
                else
                B[i] = 'a';
            }
            if( b[i] == 11 )
            {    
                if( capital )
                B[i] = 'B';
                else
                B[i] = 'b';
            }
            if( b[i] == 12 )
            {    
                if( capital )
                B[i] = 'C';
                else
                B[i] = 'c';
            }
            if( b[i] == 13 )
            {    
                if( capital )
                B[i] = 'D';
                else
                B[i] = 'd';
            }
            if( b[i] == 14 )
            {    
                if( capital )
                B[i] = 'E';
                else
                B[i] = 'e';
            }
            if( b[i] == 15 )
            {    
                if( capital )
                B[i] = 'F';
                else
                B[i] = 'f';
            }
        }
        else
        {
            B[i] = b[i] + 48;
        }
    }   
    for(int i=strlen(B)-1;i>=0;i--)
    {
        fputc( B[i] , stdout );
    }                            
}

int myprintf( const char *str ,...)
{
    va_list ap;
    int32_t temp , modify , res = 0;
    int32_t count , ch;
    char *s = NULL;

    va_start( ap , str );
    while( '\0' != *str )
    {
        switch( *str )
        {
            case '%':
            str++;
            switch( *str )
            {
                case 'd':
                    temp = va_arg(ap, int); 
                    change( temp , 10 , 0 );
                    break;
                case 'x':
                    temp = va_arg(ap, int); 
                    change( temp , 16 , 0 );    break;
                case 'X':
                    temp = va_arg(ap, int); 
                    change( temp , 16 , 1 );  
                    break;
                case 'i':
                    temp = va_arg(ap, int); 
                    change( temp , 10 , 0 );    break;
                case 's':
                    s = va_arg( ap , char *);
                    while( *s != '\0' )
                    {
                        fputc( *s , stdout );
                        s++;
                    }
                break;
            } 
        }
        va_end ( ap );
        return res;
    }
}
