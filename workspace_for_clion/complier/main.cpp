#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char str[100];
int index1=0;
void E();			//E->TX;
void X();			//X->+TX | e
void T();			//T->FY
void Y();			//Y->*FY | e
void F();			//F->(E) | i
int main()
{
    int len;
    printf("E->TE1\n");
    printf("E1->+TE'|x");
    while(1)
    {
        printf("请输入算数表达式：");
        scanf("%s",str);
        len=strlen(str);
        str[len]='#';
        str[len+1]='\0';
        E();
        printf("正确语句！\n");
        strcpy(str,"");
        index1=0;
    }
    return 0;
}
void E()
{
    printf("E -> TE1\n");
    T();
    X();
}
void X()
{

    if(str[index1]=='+')
    {
        printf("E1->+TE1\n");
        printf("%c匹配\n",str[index1]);
        index1++;

        T();
        X();
    }
    else{
        if(str[index1]!='#'&&str[index1]!=')'){
            printf("分析错误！\n");
            printf("错误位置%d,%c\n",index1+1,str[index1]);
            exit(1);
        }else{
            printf("E1->x\n");
        }
    }
}
void T()
{
    printf("T->FT1\n");
    F();
    Y();
}
void Y()
{

    if(str[index1]=='*')
    {
        printf("T1->*FT1\n");
        printf("%c匹配\n",str[index1]);
        index1++;
        F();
        Y();
    }
    else{
        if(str[index1]!='#'&&str[index1]!=')'&&str[index1]!='+'){
            printf("分析错误！\n");
            printf("错误位置%d,%c\n",index1+1,str[index1]);
            exit(1);
        }else{
            printf("T1->x\n");
        }
    }
}
void F()
{

    if(str[index1]=='i')
    {
        printf("F->i\n");
        printf("%c匹配\n",str[index1]);
        index1++;
    }
    else if (str[index1]=='(')
    {
        printf("F->(E)\n");
        printf("%c匹配\n",str[index1]);
        index1++;
        E();
        if(str[index1]==')')
        {
            printf("%c匹配\n",str[index1]);
            index1++;
        }else{
            printf("\n分析错误!\n");
            printf("错误位置%d,%c\n",index1+1,str[index1]);
            exit(0);
        }
    }
    else{
        printf("分析错误!\n");
        printf("错误位置%d,%c\n",index1+1,str[index1]);
        exit(0);
    }
}