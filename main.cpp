#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
using namespace std;

char*Key[10]={"const","main","int","if","while","else","return","for"};
char ch;                   // �洢ʶ����ĵ�����
int IsAlpha(char c) {                //�ж��Ƿ�Ϊ��ĸ
	if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A'))) return 1;
	else return 0;
}
int IsNum(char c){                //�ж��Ƿ�Ϊ����
	if(c>='0'&&c<='9') return 1;
	else return 0;
}
int IsKey(char *Word){          //ʶ��ؼ��ֺ���
	int m,i;
	for(i=0;i<8;i++){
		if((m=strcmp(Word,Key[i]))==0)
			return 1;

	}
	  return 0;
}

void scanner(FILE *fp){        //ɨ�躯��
	char Word[20]={'\0'};

	char ch;
	int i,c;
	ch=fgetc(fp);                //��ȡ�ַ���ָ��fp���Զ�ָ����һ���ַ�
	if(IsAlpha(ch)) {            //�жϸ��ַ��Ƿ�����ĸ
		Word[0]=ch;
		ch=fgetc(fp);
		i=1;
		while(IsNum(ch)||IsAlpha(ch)) {   //�жϸ��ַ��Ƿ�����ĸ������
			Word[i]=ch;
			i++;
			ch=fgetc(fp);
		}
		Word[i]='\0';       //'\0' �����ַ�����(�ո�)
		fseek(fp,-1,1);                              //����һ���ַ�
		c=IsKey(Word);                              //�ж��Ƿ��ǹؼ���
		if(c==0) cout<<"(2,"<<Word<<')'<<endl;//���ǹؼ���
		else     cout<<"(1,"<<Word<<')'<<endl;      //����ؼ���
	} else                          //��ʼ�жϵ��ַ�������ĸ
		if(IsNum(ch)) {                //�ж��Ƿ�������
			Word[0]=ch;
			ch=fgetc(fp);
			i=1;
			while(IsNum(ch)) {
				Word[i]=ch;
				i++;
				ch=fgetc(fp);
			}
			Word[i]='\0';
			fseek(fp,-1,1);                    //����
			cout<<"(3,"<<Word<<')'<<endl;
		} else {        //��ʼ�жϵ��ַ�������ĸҲ��������
				Word[0]=ch;
				switch(ch){                                   //�ֽ��
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
				case'+':ch=fgetc(fp);                          //�����
					if(ch=='='||ch=='+') {
						Word[1]=ch;
						cout<<"(4,"<<Word<<')'<<endl;//�����"+="���жϽ��Ϊ"++"
					} else {
						fseek(fp,-1,1);
						cout<<"(4,"<<Word<<')'<<endl;//�жϽ��Ϊ"+"
					}
					break;
			   case'-':
					ch=fgetc(fp);
					if(ch=='='||ch=='-') {
						Word[1]=ch;
						cout<<"(4,"<<Word<<')'<<endl;
					} else {
						fseek(fp,-1,1);
						cout<<"(4,"<<Word<<')'<<endl; //�жϽ��Ϊ"-"
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
					   cout<<"(4,"<<Word<<')'<<endl; //�жϽ��Ϊ"<"
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
				   cout<<"(�޷�ʶ���ַ�,"<<Word<<')'<<endl; break;
			   }
		   }
}
int main()
{
	FILE *fp;
	char in_fn[30];
    cout<<"������Դ�ļ���������·���ͺ�׺����:";
    for(;;)
    {
        cin>>in_fn;
        if((fp=fopen(in_fn,"r"))!=NULL) break;
        else cout<<"�ļ�·������������Դ�ļ���������·���ͺ�׺����:";
    }
	while(ch!=EOF)
	{
		ch=fgetc(fp);
		if(ch==' '||ch=='\t'||ch=='\n'){} //���Կո񣬿հף��ͻ���
		else {
			fseek(fp,-1,1);           //����һ���ֽڿ�ʼʶ�𵥴���
			scanner(fp);
		}
	}
	getchar();
}
