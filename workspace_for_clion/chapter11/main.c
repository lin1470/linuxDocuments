

//
// Created by bruce on 5/10/17.
//
#include<stdio.h>
#include <memory.h>
#include <ctype.h>

#define MAXLENTH 100
#define answer "GRANT"
int strleng(char *string){
    int length=0;
    while(*string)
    {
        length++;
        string++;
    }
    return length;
}
char* spaceIndex(char *string){
    while((*string)&&((*string)!=' ')){
        string++;
    }
    if(*string!='\0')
        return string;
    else return NULL;
}
char* toUpper(char *string){
    char *p=string;
    while(*p)
    {
        *p=toupper(*p);
        p++;
    }
    return string;
}
int  test9(){
    char hello[]="hello world";
    printf("the length of the hello is %d\n",strlen(hello));
    return 0;
}
int test10(){
    char *space="hhe sdf";
    printf("the first space of the space is %c\n",*(spaceIndex(space)-1));
    return 0;
}
int test11(){
    char try[40];

    puts("who is buried in grant's tomb");
    gets(try);
    toUpper(try);
    printf("your input string is %s\n",try);
    while(strcmp(try,answer)){
        puts("no,that's wrong. Try again.");
        gets(try);
        toUpper(try);
        printf("your input string is %s\n",try);
    }
    puts("you are right!");
    return 0;
}
char* getLine(char *string){
    char c;
    int count=0;
    while((c=getchar())!=EOF){
        string[count++]=c;
    }
    return string;
}
int test1(){
    char text[MAXLENTH];
    getLine(text);
    printf("this text is %s\n",text);
    printf("hheheh\n");
    return 0;
}
int main()
{
   test1();
   // test11();
    return 0;

}

