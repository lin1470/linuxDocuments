#include<stdio.h>
#include<stdlib.h>
#include <string.h>


typedef struct{//建立哈夫曼树的结构
    int weight;//表示这个结点的权值
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;//动态分配数组存储哈弗曼树
typedef char **HuffmanCode;//后面利用动态二维数组的办法来存储这个哈弗曼的编码
HuffmanTree HTree;
HuffmanCode HCode;
int word[2][50];
int numberofcharcter;//一共有几个字符
char *w;//用来存储输入的字符串的。
void Select(const HuffmanTree HT,const int n,int &s1,int &s2){
    //注意在HT【1..n]中选择parent为0而且weight最小的两个结点，并且返回的是两个序列号s1和s2。
    int r1;
    for(int i=1;i<=n;i++) {
        if (HT[i].parent == 0)
        {
            r1 = i;
            break;
        }

    }//避免这个老是会选择的是第一个的。
    for(int i=2;i<=n;i++)
        if(HT[i].parent==0&&HT[i].weight<HT[r1].weight)
            r1=i;
    int r2;
    for(int i=1;i<=n;i++){
        if(i!=r1&&HT[i].parent==0) {
            r2 = i;
            break;
        }
    }
    for(int i=2;i<=n;i++)
        if(HT[i].parent==0&&i!=r1&&HT[i].weight<HT[r2].weight)
            r2=i;
    s1=r1;
    s2=r2;
    return;

}
void codingByTree(HuffmanTree &HT,HuffmanCode &HC,int n){
    int i=0;
    HC=(HuffmanCode)malloc((n+1)*sizeof(char *));//分配n个字符编码的头指针向量，注意了这零号的单元是没有用到的。
    char *cd=(char*)malloc(n*sizeof(char));
    cd[n-1]='\0';
    for(i=1;i<=n;i++){
        int start=n-1;
        int c,f;//两个引索值,c代表就是child，f代表的是双亲的值
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
            if(HT[f].lchild==c) cd[--start]='0';
            else cd[--start]='1';
        HC[i]=(char*)malloc((n-start)*sizeof(char));//为第i个字符编码分配空间
        strcpy(HC[i],&cd[start]);
    }
    free(cd);//释放工作空间哈哈。
}
void Huffmancoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
    //w存放n个字符的权值（均>0），构造哈弗曼树HT,并求出n个字符的哈弗曼编码HC.
    //w进来之前是有n个权值的数组来的,但是这个huffmanTree和FuffmanCode都是没有赋值的，需要在这个函数里面给他分配空间并且赋值的。

    if(n<=1)
        return;
    int m=n*2-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元并没有用到的
    HuffmanTree p; int i=0;
    for(p=HT+1,i=1;i<=n;++i,++p,++w)
        *p={*w,0,0,0}; //1～n这n个的元素中都给赋值权值，其余部分为0
    for(;i<=m;++i,++p) *p={0,0,0,0};//剩余的部分全部都赋值是0，这样最后的没有双亲的话就是默认的0，就是这里设置的了
    for(i=n+1;i<=m;i++){
        //在HT【1..n-1]中选择parent为0而且weight最小的两个结点，并且返回的是两个序列号s1和s2。
        int s1,s2;
        Select(HT,i-1,s1,s2);
        HT[s1].parent=i;HT[s2].parent=i;
        HT[i].lchild=s1;HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }//这个过程就是建立哈弗曼树的过程来的，注意这个过程并不是这么难的吧，只要的就是我们看到书本的代码就能够编写这个什么鬼的相信书本就是了
    //这里最大的错误就是这个Select的函数是要我们自己来编写的，但是也不是很难的吧，只要符合就行了吧。
    codingByTree(HT,HC,n);
}
void printfHuffmanTree(HuffmanTree &HT,HuffmanCode &HC,int *w,int n) {
    printf("哈弗曼树的结构是多少呢？\n");
    printf("个数\t\t权值\t\t双亲\t\t左孩子\t右孩子\t\n");
    for (int i = 1; i <= 2 * n - 1; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    printf("哈弗曼编码表值\n");
    printf("个数\t\t字符\t\t权值\t\t编码\n");
    for (int i = 1; i <= n; i++)
        printf("%d\t\t%c\t\t%d\t\t%s\t\t\n", i,word[0][i-1], w[i - 1], HC[i]);
}

void test(){
    int w[]={5,29,7,8,14,23,3,11};//一个权值的数组
    HuffmanTree HT;
    HuffmanCode HC;
    int n=sizeof(w)/sizeof(int);
    Huffmancoding(HT,HC,w,n);
    printfHuffmanTree(HT,HC,w,n);
}
void initialization(){
    printf("一共有几个字符呢？\n");
    scanf("%d",&numberofcharcter);getchar();//读取一个数字还要后面的那个换行符
    w=(char*)malloc(numberofcharcter);
    printf("请输入n个字符和它的权值\n");
    for(int i=0;i<numberofcharcter;i++)
    {
        printf("请输入第%d个字符：",i+1);
        w[i]=(char)getchar();
        word[0][i]=w[i];
        getchar();//读取掉多余的回车换行符
        printf("请输入该字符%c的权值：",word[0][i]);
        scanf("%d",&word[1][i]);
        getchar();
    }
    Huffmancoding(HTree,HCode,word[1],numberofcharcter);
    printfHuffmanTree(HTree,HCode,word[1],numberofcharcter);
    //这一段是用来存储这个字符串在文本中的。
    FILE *fwp;
    if((fwp=fopen("word","w"))==NULL)
    {
        printf("打开文件错误!\n");
        exit(1);
    }
    fwrite(w,numberofcharcter,1,fwp);
    if(fclose(fwp)!=0)
    {
        printf("写入字符不成功\n");
        exit(1);
    }
    else printf("写入字符文件成功\n");
    //
    printf("我们要存储Huffman树的文件是hfmtree");
    FILE *fop;
    if((fop=fopen("hfmtree","w"))==NULL)
    {
        printf("打开文件错误!\n");
        exit(1);
    }
    fwrite(HTree+1,sizeof(HTNode),2*numberofcharcter-1,fop);
    if(fclose(fop)!=0)
        printf("写入不成功!");
    else printf("写入成功!");
}
void initializatiedFromFile(){
    printf("内存中还没有哈弗曼树，正在从文件hfmtree中读入哈弗曼树\n");
    FILE *fip=fopen("hfmtree","r");
    FILE *fwp=fopen("word","r");
    HTree=(HuffmanTree)malloc(sizeof(HTNode)*50);
    int n=0;//n代表的是这里面有多少个节点来的。
    while(fread(HTree+1,sizeof(HTNode),1,fip)!=0)
        n++;
    printf("文件中一共有%d个树节点\n",n);
    numberofcharcter=(n+1)/2;
    w=(char*)malloc(numberofcharcter);
    fread(w,numberofcharcter,1,fwp);//获取到所有的的单词
    fclose(fwp);
    fclose(fip);
    fip=fopen("hfmtree","r");
    fread(HTree+1,sizeof(HTNode),2*numberofcharcter-1,fip);
//    printf("从文件中读取出来的Huffman树是这样的\n");
//    printf("个数\t\t权值\t\t双亲\t\t左孩子\t右孩子\t\n");
//    for(int i=1;i<=2*numberofcharcter-1;i++){
//        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\n", i, HTree[i].weight, HTree[i].parent, HTree[i].lchild, HTree[i].rchild);
//    }
    codingByTree(HTree,HCode,numberofcharcter);//获得HCode
    for(int i=0;i<numberofcharcter;i++) {
        word[1][i] = HTree[i+1].weight;
        word[0][i]=w[i];
    }
}
void coding(){
    if(HTree==NULL){
        initializatiedFromFile();
        printfHuffmanTree(HTree,HCode,word[1],numberofcharcter);
    }

}
void decoding_from_file(const int number,const char character){
    int index=0;
    for(int i=0;i<numberofcharcter;i++){
        if(word[0][i]==character)
        {
            index=i;
            break;
        }
    }
    printf("%d\t\t%c\t\t%s\n",number,word[0][index],HCode[index+1]);
}
void decoding(){
    int number=0;
    if(HCode==NULL){
        printf("内存中还没有哈弗曼树，请初始化!\n");
        return;
    }
    printf("请输入你要翻译的文件名字:");
    char fileName[20];
    scanf("%s",fileName);
    FILE *fip;
    if((fip=fopen(fileName,"r"))==NULL){
        printf("打开翻译文件失败!\n");
        exit(1);
    }
    char character;
    printf("序列\t\t字符\t\t编码\n");
    while((character=fgetc(fip))!=EOF){
        number++;
        decoding_from_file(number,character);
    }
    fclose(fip);
}
void printfTree(){
    if(HCode==NULL)
    {
        printf("内存中并没有哈弗曼树!\n");
        return;
    }
    printfHuffmanTree(HTree,HCode,word[1],numberofcharcter);
}
void mainInterface(){

    int choice;
    int not_exit=1;

    do{
        printf("=====``===========\n\n");
        printf("1.初始化哈弗曼树\n2.编码\n3.译码\n4.打印哈弗曼树\n5.退出\n");
        printf("================\n");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:{initialization();break;}
            case 2:{coding();break;}
            case 3:{decoding();break;}
            case 4:{printfTree();break;}
            case 5:{not_exit=0;break;}
            default:break;
        }
    }while(not_exit);
}
void test01(){
    int a;
    printf("请输入一个字符:");
    a=(int)getchar();
    getchar();
    printf("%c",a);

}
int main()
{
    mainInterface();
    //initialization();
   // initializatiedFromFile();
   // test01();
    //test();
   //coding();
    return 0;

}