/* strcnvt.c -- try strtol()  */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char sign='s';
    printf("the store room for 's' is %d\n",sizeof('$'));
    printf("the store room for sign is %d\n",sizeof(sign));
    printf("the store room for \"s\"is %d", sizeof("$"));

    return 0;
}