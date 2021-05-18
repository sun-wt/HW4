#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>

struct option long_options[] = 
{  
    { "l", 1, NULL, 'l' },
    { "i", 1, NULL, 'i' },
    { "o", 1, NULL, 'o' },
    { "help", 0, NULL, 'h' },   
    { 0 , 0 , 0 , 0 },  
};  

int main(  int argc , char *argv[] ) 
{
    FILE *input ,*output ,*t ,*t1;
    int32_t c = 0;
    int32_t index = 0;
    int32_t option = 0;
    srand(time(NULL));
    t = fopen( "temp.c" , "w+" );
    t1 = fopen( "temp1.c" , "w+" );
    while ( ( c = getopt_long( argc, argv, "l:i:o:h", long_options, &index ) ) != -1 )
    {
        switch( c )
        {
            case 'h':
                printf( "./hw0402 -l [options] -i [input file] -o [output file]\n" );
                printf( "./hw0402 -h\n" );
                printf( "./hw0402 --help\n" );
                printf( "Display this help manual.\n" );
                ;
            case 'l':
                option = argv[2][0] -48;
                //printf( "%d\n" , option );
                break;
            case 'i':
                input = fopen( optarg , "r+" );
                //printf( "%s\n" , optarg );
                break;
            case 'o':
                output = fopen( optarg , "w+" );
                //printf( "%s\n" , optarg );
                break; 
        }
    }

    if( input == NULL )
    {
        printf("The file does not exist!1\n");
        return 0;
    }

    if( output == NULL )
    {
        printf("The file does not exist!\n");
        return 0;
    }
    fseek( input , 0L , SEEK_END );
    int32_t size = ftell( input );
    fseek( input , 0L , SEEK_SET );
    char original[2];
    if( option == 1 )
    {
        for(int i=0;i<size;i++)
        {
            fread( original , 1 , 1 , input );
            //printf("%c",original[0]);
            int32_t a;
            if ( original[0] == 32 )
            {
                a=(rand()%10)+1;   
                if(a == 10 )
                {
                    char *p = "\n";
                    fwrite( p , 1 , 1 , output );
                }
                //printf("%d\n",a);
                else
                {
                    for(int i=0;i<a;i++)
                    {
                        fwrite( original , 1 , 1 , output );
                    }
                }
            }
            fwrite( original , 1 , 1 , output );
        }
    }
    if( option == 2 )
    {
        char buf[6] ;
        char store[size];
        fread( store , size , 1 , input );
        fseek( input , 0L , SEEK_SET );

        int32_t memory[100];
        int32_t count = 0;
        int32_t kind [100];
        for(int i=1;fgets(buf,6,input)!=NULL;i++)
        {
            fseek( input , i , SEEK_SET );
            if( strncmp( buf , " int " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory[count] = i;
                kind[i] = 1;
                count++;
            }
            if( strncmp( buf , "char " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory[count] = i;
                kind[i] = 2;
                count++;
            }
        }
        
        fseek( input , 0L , SEEK_SET );
        char change[count][16];
        char check[count][16];
        int32_t length[count];
        int32_t Size = size;
        for(int i=0;i<count;i++)
        {
            fseek( input , memory[i]+3 , SEEK_SET );
            fscanf( input , "%s" , change[i] );
            strcpy( check[i] , change[i] );
            char *token =strtok( check[i] , "(" );
            if( strcmp( token , change[i] ) != 0 )
            {
                //printf("%s\n",token);
                memory[i] = -Size * 2;
            }
            strcpy( change[i] , token );
            length[i] = strlen( change[i] );
            Size = Size - length[i] + 16;
            //printf("%d ",length[i]);
            //printf( "%s\n" , change[i] );
        }
        
        int32_t times = 0;
        fseek( input , 0L , SEEK_SET );
        for(int i=0;i<Size;i++)
        {
            fread( original , 1 , 1 , input );
            
            if( i == memory[times] + times * 16 + 4 )
            {
                
                char modify[16];
                for(int j=0;j<16;j++)
                {
                    modify[j] =(rand()%100)+48;
                }
                //printf("%s",modify);
                fwrite( modify , 16 , 1 , t );
                i = i -length[times] +16;
                times++;
            }
            else
            {
                //printf("%c",original[0]);
                fwrite( original , 1 , 1 , t );
            }
        }
        fseek( t , 0L , SEEK_SET );
        for(int i=0;i<Size;i++)
        {
            fread( original , 1 , 1 , t );
            //printf("%c",original[0]);
            int32_t a;
            if ( original[0] == 32 )
            {
                a=(rand()%10)+1;   
                if(a == 10 )
                {
                    char *p = "\n";
                    fwrite( p , 1 , 1 , output );
                }
                //printf("%d\n",a);
                else
                {
                    for(int i=0;i<a;i++)
                    {
                        fwrite( original , 1 , 1 , output );
                    }
                }
            }
            fwrite( original , 1 , 1 , output );
        }   
    }
    if( option == 3 )
    {
        char buf[6] , buf1[6];
        char store[size];
        fread( store , size , 1 , input );
        fseek( input , 0L , SEEK_SET );

        int32_t memory[100];
        int32_t count = 0;
        int32_t kind [100];
        for(int i=1;fgets(buf,6,input)!=NULL;i++)
        {
            fseek( input , i , SEEK_SET );
            if( strncmp( buf , " int " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory[count] = i;
                kind[i] = 1;
                count++;
            }
            if( strncmp( buf , "char " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory[count] = i;
                kind[i] = 2;
                count++;
            }
        }
        
        fseek( input , 0L , SEEK_SET );
        char change[count][16];
        char check[count][16];
        int32_t length[count];
        int32_t Size = size;
        int32_t t3 = 0;
        for(int i=0;i<count;i++)
        {
            fseek( input , memory[i]+3 , SEEK_SET );
            fscanf( input , "%s" , change[i] );
            strcpy( check[i] , change[i] );
            char *token =strtok( check[i] , "(" );
            if( strcmp( token , change[i] ) != 0 )
            {
                //printf("%s\n",token);
                kind[i] = 3;
                t3++;
            }
            strcpy( change[i] , token );
            
            length[i] = strlen( change[i] );
            Size = Size - length[i] + 16;
            //printf("%d ",length[i]);
            //printf( "%s\n" , change[i] );
        }
        
        int32_t times = 0;
        fseek( input , 0L , SEEK_SET );
        for(int i=0;i<Size;i++)
        {
            fread( original , 1 , 1 , input );
            
            if( i == memory[times] + times * 16 + 3 )
            {
                
                char modify[16];
                for(int j=0;j<16;j++)
                {
                    modify[j] =(rand()%100)+48;
                }
                //printf("%s",modify);
                fwrite( modify , 16 , 1 , t );
                i = i -length[times] +16;
                //i++;
                char *j ="(";
                if( kind[times] == 3 )
                {
                    fwrite( j , 1 , 1 , t );
                }
                times++;
            }
            else
            {
                //printf("%c",original[0]);
                fwrite( original , 1 , 1 , t );
            }
        }
        fseek( t , 0L , SEEK_SET );
        for(int i=0;i<Size;i++)
        {
            fread( original , 1 , 1 , t );
            //printf("%c",original[0]);
            int32_t a;
            if ( original[0] == 32 )
            {
                a=(rand()%10)+1;   
                if(a == 10 )
                {
                    char *p = "\n";
                    fwrite( p , 1 , 1 , output );
                }
                //printf("%d\n",a);
                else
                {
                    for(int i=0;i<a;i++)
                    {
                        fwrite( original , 1 , 1 , output );
                    }
                }
            }
            fwrite( original , 1 , 1 , output );
        }   
    }

    if( option == 4 )
    {
        char buf2[6];
        fseek( input , 0L , SEEK_SET );

        int32_t memory0[100];
        int32_t count0 = 0;
        for(int i=1;fgets(buf2,6,input)!=NULL;i++)
        {
            fseek( input , i , SEEK_SET );
            if( strncmp( buf2 , " int " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory0[count0] = i;
                count0++;
            }
            
        }
        
        fseek( input , 0L , SEEK_SET );
        char change0[count0][5];
        char middle0[count0][5];
        char number0[count0][5];
        char check0[count0][5];
        int32_t length0[count0];
        int32_t Size0 = size;
        for(int i=0;i<count0;i++)
        {
            fseek( input , memory0[i]+3 , SEEK_SET );
            fscanf( input , "%s" , change0[i] );
            fscanf( input , "%s" , middle0[i] );
            if ( strcmp( middle0[i] , "=" ) == 0 )
            {
                fscanf( input , "%s" , number0[i] );
                printf("%s\n",number0[i]);
            }
            
            strcpy( check0[i] , change0[i] );
            char *token =strtok( check0[i] , "(" );
            if( strcmp( token , change0[i] ) != 0 )
            {
                //printf("%s\n",token);
                memory0[i] = -Size0 * 2;
            }
            strcpy( change0[i] , token );
            length0[i] = strlen( number0[i] );
            Size0 = Size0 - length0[i] + 5;
        
        }
        
        int32_t times0 = 0;
        fseek( input , 0L , SEEK_SET );
        for(int i=0;i<size;i++)
        {
            fread( original , 1 , 1 , input );
            
            if( i == memory0[times0] + times0 * 16 + 8 )
            {
                
                char modify[5] = "3+2/4";
                
                fwrite( modify , 5 , 1 , t1 );
                //i = i -length[times] +5;
                //i++;
                
                times0++;
            }
            else
            {
                //printf("%c",original[0]);
                fwrite( original , 1 , 1 , t1 );
            }
        }
        //
        
        char buf[6] , buf1[6];
        
        fseek( t1 , 0L , SEEK_END );
        size = ftell( t1 );
        fseek( t1 , 0L , SEEK_SET );
        int32_t memory[100];
        int32_t count = 0;
        int32_t kind [100];
        for(int i=1;fgets(buf,6,t1)!=NULL;i++)
        {
            fseek( t1 , i , SEEK_SET );
            if( strncmp( buf , " int " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory[count] = i;
                kind[i] = 1;
                count++;
            }
            if( strncmp( buf , "char " , 5 ) == 0 )
            {
                //printf("%d\n",i);
                memory[count] = i;
                kind[i] = 2;
                count++;
            }
        }
        
        fseek( t1 , 0L , SEEK_SET );
        char change[count][16];
        char check[count][16];
        int32_t length[count];
        int32_t Size = size;
        int32_t t3 = 0;
        for(int i=0;i<count;i++)
        {
            fseek( t1 , memory[i]+3 , SEEK_SET );
            fscanf( t1 , "%s" , change[i] );
            strcpy( check[i] , change[i] );
            char *token =strtok( check[i] , "(" );
            if( strcmp( token , change[i] ) != 0 )
            {
                //printf("%s\n",token);
                kind[i] = 3;
                t3++;
            }
            strcpy( change[i] , token );
            
            length[i] = strlen( change[i] );
            Size = Size - length[i] + 16;
            //printf("%d ",length[i]);
            //printf( "%s\n" , change[i] );
        }
        
        int32_t times = 0;
        fseek( t1 , 0L , SEEK_SET );

        for(int i=0;i<Size;i++)
        {
            fread( original , 1 , 1 , t1 );
            
            if( i == memory[times] + times * 16 + 3 )
            {
                
                char modify[16];
                for(int j=0;j<16;j++)
                {
                    modify[j] =(rand()%100)+48;
                }
                //printf("%s",modify);
                fwrite( modify , 16 , 1 , t );
                i = i -length[times] +16;
                //i++;
                char *j ="(";
                if( kind[times] == 3 )
                {
                    fwrite( j , 1 , 1 , t );
                }
                times++;
            }
            else
            {
                //printf("%c",original[0]);
                fwrite( original , 1 , 1 , t );
            }
        }
        fseek( t , 0L , SEEK_SET );
        for(int i=0;i<=Size;i++)
        {
            fread( original , 1 , 1 , t );
            //printf("%c",original[0]);
            int32_t a;
            if ( original[0] == 32 )
            {
                a=(rand()%10)+1;   
                if(a == 10 )
                {
                    char *p = "\n";
                    fwrite( p , 1 , 1 , output );
                }
                //printf("%d\n",a);
                else
                {
                    for(int i=0;i<a;i++)
                    {
                        fwrite( original , 1 , 1 , output );
                    }
                }
            }
            fwrite( original , 1 , 1 , output );
        }
        
    }

    fclose( t );
    fclose( t1 );
    remove( "temp.c" );
    remove( "temp1.c" );
    fclose( input );
    fclose( output );
    return 0;
}
