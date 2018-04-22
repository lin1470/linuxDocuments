#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc,char *argv[]) {
    int ch;
    FILE *fp;

    if (argc < 2) {
        exit(2);
    }
    if ((fp = fopen(argv[1], "rb")) == NULL) {
        exit(1);
    }
    while((ch=getc(fp))!=EOF)
        if(isdigit(ch))
            putchar(ch);
    printf("\n");
    fclose(fp);
    return 0;
}
