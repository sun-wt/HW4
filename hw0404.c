#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

typedef struct _local_file_header
{
    char Signature[4];
    uint16_t Version;
    uint16_t Bit_Flag;
    uint16_t Method;
    uint16_t Time;
    uint16_t Date;
    uint32_t CRC_32;
    uint32_t Compressed_Size;
    uint32_t Uncompressed_Size;
    uint16_t Filename_Length;
    uint16_t Extra_Field_Length;
}__attribute__((__packed__)) Local;

void printer( Local *header)
{
    printf( "Signature         :%s\n" , header->Signature );
    printf( "Version           :%d\n" , header->Version );
    printf( "Bit_Flag          :%d\n" , header->Bit_Flag );
    printf( "Method            :%d\n" , header->Method );
    printf( "Time              :%d\n" , header->Time );
    printf( "Date              :%d\n" , header->Date );
    printf( "CRC_32            :%d\n" , header->CRC_32 );
    printf( "Compressed_Size   :%d\n" , header->Compressed_Size );
    printf( "Uncompressed_Size :%d\n" , header->Uncompressed_Size );
    printf( "Filename_Length   :%d\n" , header->Filename_Length );
    printf( "Extra_Field_Length:%d\n" , header->Extra_Field_Length);
    printf( "\n" );
}

void printer1( char Name[1000][1024] ,int32_t count )
{
    printf("+-- ");
    char *token = NULL;
    token = strtok( Name[0] , "/" );
    int32_t times = 4;
    printf("%s/\n",token);
    token = strtok( NULL , "/" );
    for(int i=0;i<times;i++)
    {
        printf(" ");
    }
    printf( "+-- %s\n" , token );
    for(int i=1;i<count-1;i++)
    {
        for(int i=0;i<times;i++)
        {
            printf( " " );
        }
        token = strtok( Name[i] , "/" );
        token = strtok( NULL , "/" );
        int32_t need = strlen(token);
        if( i == count-1 )
        {
            
        }
        if( token )
        {
            if( token[strlen(token)-1] == '@')
            {
                need -= 2;
            }
            printf( "+-- " );
            for(int i=0;i<need;i++)
            {
                printf( "%c" , token[i] );
            }
            printf( "\n" );
        }
    }
    printf( "+-- /\n" );
}


int main(  int argc, char *argv[] ) 
{
    FILE *fp = fopen( argv[1] , "rb" );
    if( fp == NULL )
    {
        printf("The file does not exist!\n");
        return 0;
    }     

    fseek( fp , 0L , SEEK_END );
    int32_t size = ftell( fp );
    fseek( fp , 0L , SEEK_SET );
    char Name[1000][1024];
    int32_t count = 0;
    while(!feof(fp))
    {
        Local header;
        fread( &header , sizeof(header) , 1 , fp );
        char name[header.Filename_Length];
        char name1[header.Extra_Field_Length];
        char name2[header.Compressed_Size];
        fread( name , header.Filename_Length , 1 ,fp);
        fread( name1 , header.Extra_Field_Length , 1 , fp );
        //printer( &header );
        //printf("%s\n",name);
        strcpy( Name[count] , name );
        fread( name2 , header.Compressed_Size , 1 , fp );
        count++;
    }
    
    for(int i=0;i<count;i++)
    {
        //printf( "%s\n" , Name[i] );
    }
    printer1( Name , count );
    /*FILE *fp1 = fopen( "HW1_40947013S" , "rb");
    if( fp1 == NULL )
    {
        printf("The file does not exist!\n");
        return 0;
    }*/
    fclose( fp );
    return 0;
}

