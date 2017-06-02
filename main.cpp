#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
using namespace std;

char*Key[10]={"const","main","int","if","while","else","return","for"};
char ch;                   // 存储识别出的单词流
int IsAlpha(char c) {                //判断是否为字母
	if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A'))) return 1;
	else return 0;
}
int IsNum(char c){                //判断是否为数字
	if(c>='0'&&c<='9') return 1;
	else return 0;
}
int IsKey(char *Word){          //识别关键字函数
	int m,i;
	for(i=0;i<8;i++){
		if((m=strcmp(Word,Key[i]))==0)
			return 1;

	}
	  return 0;
}

void scanner(FILE *fp){        //扫描函数
	char Word[20]={'\0'};

	char ch;
	int i,c;
	ch=fgetc(fp);                //获取字符，指针fp并自动指向下一个字符
	if(IsAlpha(ch)) {            //判断该字符是否是字母
		Word[0]=ch;
		ch=fgetc(fp);
		i=1;
		while(IsNum(ch)||IsAlpha(ch)) {   //判断该字符是否是字母或数字
			Word[i]=ch;
			i++;
			ch=fgetc(fp);
		}
		Word[i]='\0';       //'\0' 代表字符结束(空格)
		fseek(fp,-1,1);                              //回退一个字符
		c=IsKey(Word);                              //判断是否是关键字
		if(c==0) cout<<"(2,"<<Word<<')'<<endl;//不是关键字
		else     cout<<"(1,"<<Word<<')'<<endl;      //输出关键字
	} else                          //开始判断的字符不是字母
		if(IsNum(ch)) {                //判断是否是数字
			Word[0]=ch;
			ch=fgetc(fp);
			i=1;
			while(IsNum(ch)) {
				Word[i]=ch;
				i++;
				ch=fgetc(fp);
			}
			Word[i]='\0';
			fseek(fp,-1,1);                    //回退
			cout<<"(3,"<<Word<<')'<<endl;
		} else {        //开始判断的字符不是字母也不是数字
				Word[0]=ch;
				switch(ch){                                   //分界符
				case'[':
				case']':
				case'(':
				case')':
				case'{':
				case'}':
				case',':
				case'"':
				case';':
                case'#':
                case'.':
					cout<<"(5,"<<Word<<')'<<endl;
					break;
				case'+':ch=fgetc(fp);                          //运算符
					if(ch=='='||ch=='+') {
						Word[1]=ch;
						cout<<"(4,"<<Word<<')'<<endl;//运算符"+="或判断结果为"++"
					} else {
						fseek(fp,-1,1);
						cout<<"(4,"<<Word<<')'<<endl;//判断结果为"+"
					}
					break;
			   case'-':
					ch=fgetc(fp);
					if(ch=='='||ch=='-') {
						Word[1]=ch;
						cout<<"(4,"<<Word<<')'<<endl;
					} else {
						fseek(fp,-1,1);
						cout<<"(4,"<<Word<<')'<<endl; //判断结果为"-"
					}
					break;
			   case'*':
			   case'/':
			   case'!':
			   case'=':
					ch=fgetc(fp);
					if(ch=='=') {
						Word[1]=ch;
						cout<<"(4,"<<Word<<')'<<endl;
					} else {
					   fseek(fp,-1,1);
					   cout<<"(4,"<<Word<<')'<<endl;
					   }
					   break;
			   case'<':ch=fgetc(fp);

					   if(ch=='='||ch=='<'){
						   Word[1]=ch;
						   cout<<"(4,"<<Word<<')'<<endl;
					   }
					   else {
					   fseek(fp,-1,1);
					   cout<<"(4,"<<Word<<')'<<endl; //判断结果为"<"
					   }
					   break;
               case'>':ch=fgetc(fp);
					   if(ch=='='||ch=='>')
					   {
						   Word[1]=ch;cout<<"(4,"<<Word<<')'<<endl;
					   }
					   else {
						  fseek(fp,-1,1);
						 cout<<"(4,"<<Word<<')'<<endl;
					   }
					   break;
			   default:
				   cout<<"(无法识别字符,"<<Word<<')'<<endl; break;
			   }
		   }
}
int main()
{
	FILE *fp;
	char in_fn[30];
    cout<<"请输入源文件名（包括路径和后缀名）:";
    for(;;)
    {
        cin>>in_fn;
        if((fp=fopen(in_fn,"r"))!=NULL) break;
        else cout<<"文件路径错误！请输入源文件名（包括路径和后缀名）:";
    }
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		if(ch==' '||ch=='\t'||ch=='\n'){} //忽略空格，空白，和换行
		else {
			fseek(fp,-1,1);           //回退一个字节开始识别单词流
			scanner(fp);
		}
	}
	getchar();
}
