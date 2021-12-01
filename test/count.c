#include <stdio.h>
#include<string.h>
int str_len(char *str);
int main(){
    char str[100];
    printf("please enter a string: \n");
    scanf("%s", str);
    printf("the string length is: %d", str_len(str));
    return 0;
}

int str_len(char *str){
    char *start=str;
    char *final=str;
    while (*final){
        final++;
    }
    return (final-start);
}

