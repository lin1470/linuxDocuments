#include <iostream>
#include <string.h>

int main() {
    char string[20];
    fgets(string,20,stdin);
    int length=strlen(string);
    string[length-1]='\0';
    printf("%s",string);
}