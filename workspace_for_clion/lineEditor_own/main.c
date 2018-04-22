#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>

//文学研究助手的代码
#define MAXSTRLEN 255         //最大串长
typedef char SString[MAXSTRLEN+1];   //串的定长顺序存储表示
int next[MAXSTRLEN];
//

#define NAMELEN 20//名字最多的个数
#define MAXCHARLENGH 81//一行中最对读取的字符的个数
char activeArea[100][MAXCHARLENGH];//活区的大小，一般我们存取的字符都在这个数组里面的。
const int MaxLineNumber=80;//最多可以读取的行数
int areaLineCount=0;//表示了活区中有多少行
int displayLineCount=0;//表示了已经显示了多少的行
int readLineCount=0;
char inputFileName[NAMELEN];
char outputFileName[NAMELEN];

//以下是补充进来的文学研究助手
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
        line[0]=(char)(lenth(line));
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
void literrature(){
    SString words[10];   //定义字符串数组，用于存储输入的关键字
    int count=0;
    int not_exit=0;
    do{
        printf("================文学研究助手========\n");
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
    printf("还想要继续查询单词吗？yes(1)\tno(0)");
        scanf("%d",&not_exit);
        getchar();
    }while(not_exit);
    return;
}

//到这里为止


void initializeFile()
{

    printf("请编辑文件名称：\n");
    scanf("%s",inputFileName);
    getchar();
    printf("请输入保存文件名称：\n");
    scanf("%s",outputFileName);
    getchar();
    FILE *fip,*fop;
    if(strcmp(inputFileName,outputFileName)==0)
    {
        printf("error! The file conflict!\n");
        exit(1);
    }
    if((fip=fopen(inputFileName,"r"))==NULL){
        printf("not this inputting file!\n");
        exit(1);
    }
    if((fop=fopen(outputFileName,"a"))==NULL){
        printf("open outputting file failed!\n");
        exit(1);
    }
    while(areaLineCount<MaxLineNumber&&(fgets(activeArea[areaLineCount],MAXCHARLENGH,fip)!=NULL)){
        areaLineCount++;
        readLineCount++;
    }
    fclose(fip);
    fclose(fop);

}
void displayActiveArea(int count){
    printf("活区显示（最多显示20行）\n");
    int i=count+20;//利用I来保证可以显示20行的内容。
    while(count<i&&count<areaLineCount){
        printf("%-4d %s",count+1,activeArea[count]);
        count++;
    }
    putchar('\n');
}
void writeFile(){
    FILE *fop;
    fop=fopen(outputFileName,"a");
    if(fop==NULL)
    {
        printf("打开文件错误！\n");
        exit(1);
    }
    int writeLineNumber=1;
    while(writeLineNumber<=areaLineCount)
    {
        fputs(activeArea[writeLineNumber-1],fop);
        writeLineNumber++;
    }
    printf("保存完毕！\n");
    fclose(fop);
}
void deleteLine(){
    int is_deleted=0;
    int choice=0;
    char *end;
    printf("行删除有两种格式：\n1.d< 行号 1><回车>\n2.d< 行号 1> <行号2><回车>\n");
    printf("请选择删除方式：\n");
    scanf("%d",&choice);
    //fflush(stdin);
    getchar();
    if(choice==1){
        int lineNumber;
        char command[NAMELEN];
        printf("请输入命令：");
        fgets(command,NAMELEN,stdin);
        command[strlen(command)-1]='\0';
        lineNumber=(int)strtol(&command[1],&end,10);
        if(command[0]!='d'||strcmp(end,"")!=0){
            printf("命令的格式错误！\n");
            return;
        }
        while(lineNumber<1||lineNumber>areaLineCount){
            printf("你输入的行号错误！,请重新输入：\n");
            scanf("%d",&lineNumber);
        }
        printf("是否确认删除？yes(1)no(0)\n");
        scanf("%d",&is_deleted);
        getchar();
        if(is_deleted){
            for(int i=lineNumber-1;i<areaLineCount-1;i++)
                strcpy(activeArea[i],activeArea[i+1]);//这个语句是后面的数据覆盖前面的数据.
            areaLineCount--;
            displayActiveArea(displayLineCount);
        }
    }
    else if(choice==2){
        int is_deleted=0;
        int lineNumber1,lineNumber2;
        char command[NAMELEN];
        printf("请输入命令：\n");
        fgets(command,NAMELEN,stdin);
        command[strlen(command)-1]='\0';
        if(command[0]!='d'){
            printf("命令格式错误！\n");
            return;
        }
        lineNumber1=atoi(&command[1]);
        lineNumber2=atoi(strchr(command,' ')+1);
        if(lineNumber1<1||lineNumber1>areaLineCount||lineNumber2<1||lineNumber2>areaLineCount){
            printf("输入的命令行数不正确！\n");
            return;
        }
        int spaceLineNumber=lineNumber2-lineNumber1+1;//需要删除的2行数
        printf("确定是否要删除吗？yes(1)no(0)\n");
        scanf("%d",&is_deleted);
        getchar();
        if(is_deleted){
            for(int i=lineNumber1-1;i<areaLineCount-spaceLineNumber;i++)//注意这个删除算法有一定的问题。
                strcpy(activeArea[i],activeArea[i+spaceLineNumber]);
            areaLineCount-=spaceLineNumber;
            printf("剩下的行数为：%d\n",areaLineCount);
            displayActiveArea(displayLineCount);
        }



    }



    //system("clear");
}
void insertLine(){
    int is_added=0;
    char command[NAMELEN];
    char textLine[MAXCHARLENGH];
    int lineNumber;
    printf("请输入插入命令：(格式为：i< 行号 >< 回车 >< 文本 >< 回车 >\n");
    fgets(command,NAMELEN,stdin);
    command[strlen(command)-1]='\0';
    printf("命令是：%s\n",command);
    fgets(textLine,MAXCHARLENGH,stdin);
    printf("输入的文本是：%s\n",textLine);
    lineNumber=atoi(&command[1]);
    if(command[0]!='i')
    {
        printf("格式命令不正确\n");
        return;
    }
    if(lineNumber<0||lineNumber>areaLineCount){
        printf("行数不符合!\n");
        return;
    }
    printf("确认添加吗?yes(1)no(0)\n");
    scanf("%d",&is_added);
    getchar();
    if(is_added){
        for(int i=areaLineCount;i>lineNumber;i--)
            strcpy(activeArea[i],activeArea[i-1]);//行数后移给移出位置。
        strcpy(activeArea[lineNumber],textLine);
        areaLineCount++;
        displayActiveArea(displayLineCount);
    }

}
void readFile(int areadyReadLine){
    FILE *fip=fopen(inputFileName,"r");
    for(int i=0;i<areadyReadLine;i++)
        fgets(activeArea[0],MAXCHARLENGH,fip);
    while(areaLineCount<MaxLineNumber&&(fgets(activeArea[areaLineCount],MAXCHARLENGH,fip)!=NULL)){
        areaLineCount++;
        readLineCount++;
    }
    fclose(fip);
}
void mainEditor(){
    printf("===========文本编辑器==========\n");
    displayActiveArea(displayLineCount);
    int not_exit=1;
    do{
        char choice;
        printf("请选择你的操作：\n");
        printf("d.删除行\ni.插入行\np.显示下一页(p< 回车 >)\nn.活区切换并写入文件(n< 回车 >)\ne.退出\n");
        scanf("%c",&choice);
        getchar();
        switch(choice){
            case 'd':deleteLine();break;
            case 'i':insertLine();break;
            case 'p':{
                displayLineCount+=20;
                if(displayLineCount>80)
                {
                    printf("已经是活页的最后一页了\n");
                    displayLineCount-=20;
                }
                else{
                    displayActiveArea(displayLineCount);
                }
                break;
            }
            case 'n':{
                writeFile();
                displayLineCount=0;
                areaLineCount=0;
                readFile(readLineCount);
                displayActiveArea(displayLineCount);
                break;
            }
            case 'e':{not_exit=0;break;}
            default:
                break;
        }

    }while(not_exit);

}
void mainInterface(){
    int choice=0;
    int not_exit=1;

    do{
        printf("===========主界面================\n");
        putchar('\n');
        printf("1.文学研究助手\t2.文本编辑器\t3.退出\n");
        putchar('\n');
        printf("=================================\n");
        printf("请输入你的选择：");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:{
                literrature();
                break;}
            case 2:{mainEditor();break;}
            case 3:not_exit=0;
            default:break;
        }
    }while(not_exit);

}
int main() {
    initializeFile();
    mainInterface();

    return 0;

}