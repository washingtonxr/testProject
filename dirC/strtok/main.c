#include <stdio.h>  
#include <string.h>  
void split(char str[],char delims[])
{
    char *result = NULL; 
    result = strtok( str, delims );  
    while( result != NULL ) {  
    printf( "result is \"%s\"\n", result );  
    result = strtok( NULL, delims );  
    }  
}
int main()  
{  
    char str[] = "11:22:33:44:55:88,11:22:33:44:55:22,11:22:33:44:55:00,11:22:33:44:55:33";  
    char delims[] = ",";  
    split(str,delims);

}
