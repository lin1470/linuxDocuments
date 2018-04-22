#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 255         //最大串长
typedef char SString[MAXSTRLEN+1];   //串的定长顺序存储表示
int next[MAXSTRLEN];            //KMP算法中用到的next
char inputFileName[20];
void get_next(const SString T,int next[])
{
    int i=1;next[1]=0;int j=0;
    while(i<T[0])
    {
        if(j==0||T[i]==T[j])
        {
            i++;j++;next[i]=j;
        }
        else j=next[j];
    }
}//调用这个方法来初始化这个next这个数组。

int Index(SString S,const SString T,int pos)  //KMP算法,P82
{
	int i=pos,j=1;
	get_next(T,next);//初始化next这个数组
   while(i<=S[0]&&j<=T[0])
   {
	   if(j==0||S[i]==T[j]) {++i;++j;}
	   else
		   j=next[j];
   }
   if (j>T[0]) return (i-T[0]);
   else
	   return 0;
}

int lenth(SString str)    //求串长
{
	int i=1;
	while(str[i]) i++;
	return(i-1);
}

void find(char *name,const SString keys)  //查找函数
{
	SString line;  //用于存放从小说文件读取的一行字符串
	int l=0;//l represents the number of line
    int j=0;
    int count=0;//represents the number you can find
    FILE *fp;
    fp=fopen(name,"r");
    if((fp== NULL)){
        printf("Open the %sfile failed\n",name);
        exit(1);
    }
    printf("这个单词是： %s\n",&keys[1]);
    while(fgets(&line[1],MAXSTRLEN,fp)!=NULL){
        line[0]=char(lenth(line));
        l++;
        while((j=Index(line,keys,j+1))!=0){
            printf("第%d行 第%d列\n",l,j);
            count++;
        }
    }
    printf("这个文本一共有%d行.\n",l);
    printf("这个文本一共有%d个%s\n",count,&keys[1]);
    fclose(fp);
}


int main()
{
    //test();
    //存储输入的小说路径字符串
	SString words[10];   //定义字符串数组，用于存储输入的关键字
    int count=0;
    do{
        printf("================文学研究助手========\n");
        printf("请输入要查询的文本名字：\n");
        scanf("%s",inputFileName);
        printf("你想要查询几个单词？\n");
        scanf("%d",&count);
        for(int i=0;i<count;i++){
            printf("输入你要查询的单词:\n");
            scanf("%s",&words[i][1]);
            words[i][0]=lenth(words[i]);
        }
        for(int i=0;i<count;i++){
            find(inputFileName,words[i]);
        }

    }while(0);
    return 0;
}
