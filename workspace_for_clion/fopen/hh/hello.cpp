

//
// Created by bruce on 5/10/17.
//
#include<stdio.h>
int strlen(char *string){
    int length=0;
    while(*string)
    {
        length++;
    }
    return length;
}
int  test9(){
    char *hello ="hello world";
    printf("the length of the hello is %d\n",strlen(hello));
    return 0;
}
int main()
{
    test9();
    return 0;

}

