#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
typedef struct _info
{
    char i[10000000];
}info;
struct option long_options[] = 
{  
     { "size", 1, NULL, 'S' },
     { "help", 0, NULL, 'h' },   
     { "s", 1, NULL, 's' },  
     { "r", 1, NULL, 'r' }, 

     { 0 , 0 , 0 , 0 },  
};  

int main( int argc, char *argv[] )
{
    FILE *output , *input;
    
    puts( "---" );
    
    // getopt_long
    
    int32_t c = 0;
    int32_t index = 0;
    int32_t SFsize = 0;
    int32_t size = 0;
    int32_t times = 0;
    char new_name[1024],old_name[1024];
    while ( ( c = getopt_long( argc, argv, "S:s:r:h", long_options, &index ) ) != -1 )
    {
        switch( c )
        {
            case 's':
                strncpy( old_name , optarg , sizeof(old_name) );
                printf( "%s\n" , old_name );
                break;
            case 'S':
                if( optarg == NULL )
                {
                    SFsize = 1000;
                }
                else
                {
                    input = fopen( argv[2] , "rb+" );
                    fseek( input , 0L , SEEK_END );
                    size = ftell( input );
                    fseek( input , 0L , SEEK_SET );
                    for(int i=0;i<strlen(argv[4]);i++)
                    {
                        SFsize += (argv[4][i] - 48) * pow( 10 , strlen(argv[4])-i-1);
                    }
                }
                times = size / SFsize + 1;
                printf( "%d\n" , times );
                int j = 0;
                for(int i=0;i<times;i++)
                {
                    sprintf(new_name,"%s.%d",old_name,++j);
                    FILE *output = fopen( new_name , "wb");
                    fseek( input , 0L , SFsize*i );
                    //printf("%d",SFsize*i);
                    char m[times][SFsize];
                    if( i != times - 1 )
                    {
                        fread(m[i],SFsize,1,input);
                        fwrite(m[i],SFsize,1,output);
                    }
                    else
                    {
                        fread(m[i],size%SFsize,1,input);
                        fwrite(m[i],size%SFsize,1,output);
                    }
                }
                break;
            case 'h':
                printf("Split:\n");
                printf("./hw0401 -s [file] --size [Small File Size]\n");
                printf("The default small file size is 1000 bytes.\n");
                printf("Recover:\n");
                printf("./hw0401 -r [output file] [small files]:\n");
                printf("The input small files may not be in order.\n");
                return 0;
            case 'r':
                input = fopen( argv[2] , "wb+" );
                int max = 0;
                for(int i=2;i<argc;i++)
                {
                    FILE *output = fopen( argv[i] , "rb+");
                    fseek( output , 0L , SEEK_END );
                    size = ftell( output );
                    if( size > max )
                    {
                        max = size;
                    }
                    fclose( output );
                }
                for(int i=2;i<argc;i++)
                {
                    FILE *output = fopen( argv[i] , "rb+");
                    fseek( output , 0L , SEEK_END );
                    size = ftell( output );
                    char m[argc-2][max];
                    fseek( output , 0L , SEEK_SET );
                    fread( m[i-2] , size , 1 , output );
                    fwrite( m[i-2] , size , 1 , input );
					fclose( output );
                }
                break;
            case '?':
                output = fopen( optarg , "a");
                printf( "option: ?\n" );
                break;
            default:
                printf( "option: unknown\n" ); 
                break;
        }
    }
    fclose( input );
    return 0;
}
