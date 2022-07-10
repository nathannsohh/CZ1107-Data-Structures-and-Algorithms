#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 80 //The size of the array


int main()
{
    char hello[10] = "9999abc123";
    int hi[SIZE] = "";
    int i = 0;
    int j = 0;
    while(hello[i] != '\0'){
        int total = 0;
        if(hello[i] != 'a' && hello[i] != 'b' && hello[i] != 'c'){
            total = total*10 + (hello[i] - '0');
            if(hello[i+1] == 'a' && hello[i+1] == 'b' && hello[i+1] == 'c'){
                hi[j] = 
            }
        }
    }
    printf("%d", atoi(hello));
}

