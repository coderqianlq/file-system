#include"user.h" 
#include"file.h"
#include"directory.h"
#include"dirmanager.h"
#include<iostream.h> 
#include<iomanip.h> 
#include<stdlib.h> 
#include<stdio.h> 
#include<string.h> 

user fileuser[100];

void user::reg(){
	static int i = 0;
	char username[9];
	char password[9];
	while(i<99){
		cout<<"username��";
		cin>>username;
		cout<<"password��";
		cin>>password;
		strcpy(fileuser[i].username,username);
		strcpy(fileuser[i].password,password);
		i++;
		break;
	}
}

void user::login(){
    char username[9];
	char password[9];
	cout<<"username��";
	cin>>username;
	cout<<"password��";
	cin>>password;
	for(int i=0; i<100; i++){
		if(strcmp(fileuser[i].username,username)==0){
			if(strcmp(fileuser[i].password,password)==0){
                system("cls");
                dirmanager admin;  
                admin.manager();
			}
			cout<<"password error.\n";
			break;
		}
		cout<<"error username.\n";
		break;
	}
}

void user::inter(){
  string s;
  char ch;
  cout<<"================================================"<<endl;
  cout<<"                   *����������ָ��            \n"<<endl;  
  cout<<"                     reg �û�ע��               "<<endl;
  cout<<"                   login �û���¼               "<<endl;
  cout<<"                    exit �˳�ϵͳ             \n"<<endl;
  cout<<"  ѧ��:201427920214 ����:Ǯ���� �༶:��1405   "<<endl;
  cout<<"======================= ========================"<<endl;
  for(int i=0;i<200;i++)  
  {   
    cout<<"\n";     
	cin>>s; 
	if(s=="reg") ch = '1';
	if(s=="login") ch = '2';
	if(s=="exit") ch = '3'; 
	//else ch = '4'; 
	switch(ch)        
	{    
	  case '1': 
	    reg();
		break;  
	  case '2':
        login();
        break;
	  case '3':
        exit(1);
	  default: 
	    cout<<"error."<<endl;
		break;        
    }  
    ch='4';
  }  
}


file::file() 
{ 
  char edit; 
  cin>>filename; 
  cout<<endl; 
  cout<<"edit?(y/n)��";  
  cin>>edit;  
  if(edit=='y'||edit=='Y')  
    editfile();  
  else 
    size=0; 
} 

file::file(int n){
   next=NULL;
}

void file::editfile() 
{  
  text=new char[1024];  
  //cout<<"�������ļ����ݣ�"<<endl;
  cin>>text;  
  //gets(text);  
  size=strlen(text); 
} 
void directory::creatfile()  
{     
  file *pf,*p1;  
  if(pfile==NULL) 
  {
    pf=new file; 
	pfile=pf;
	pf->next=NULL;
  }  
  else 
  {  
    p1=pfile;
	while(p1->next!=NULL) 
	  p1=p1->next;    
    pf=new file;             
    p1->next=pf; 
	pf->next=NULL;                 
  } 
} 

void directory::renamefile(){
  char name[9]; 
  int findfile=-1; 
  int findfile1=-1;
  file *pt,*pt1;  
  if(pfile!=NULL)   
  { 
    pt=pfile; 
	cin>>name;  
	while(pt!=NULL) 
	{ 
	  findfile=strcmp(name,pt->getfilename());  
	  if(findfile==0)    
	  { 
	    cin>>pfile->filename;
	    pt1=pfile;
        while(pt1!=NULL){
          findfile1=strcmp(pfile->filename,pt1->getfilename());
	      if(findfile1==0 && (pt->next!=pt1->next)){
    		cout<<"�ļ����Ѵ��ڣ�"; 
    		strcpy(pfile->filename,name);
			//findfile1=-1; 
    		break;
    	  }
    	  pt1=pt1->next;
	    }
		break;    
	  }   
      pt=pt->next;    
    } 
    if(findfile!=0) 
      cout<<"�ļ��������Ҳ������ļ�!"<<endl;  
  } 
  else cout<<"��ǰĿ¼���ļ���"<<endl; 
}
//static file* cpyfile = new file(1);

void directory::copyfile(){
  char name[9]; 
  int findfile=-1; 
  file *pt;   
  //directory *p3=p; 
  if(pfile!=NULL)   
  { 
    pt=pfile; 
	cin>>name;  
	while(pt!=NULL) 
	{ 
	  findfile=strcmp(name,pt->getfilename());  
	  if(findfile==0)    
	  { 
         //strcpy(cpyfile->filename,pt->filename);
         //strcpy(cpyfile->text,pt->text);
         //cpyfile->next=NULL;
         break;
	  }   
      pt=pt->next;    
    } 
    if(findfile!=0) 
      cout<<"�ļ��������Ҳ������ļ�!"<<endl;  
  } 
  else cout<<"��ǰĿ¼���ļ���"<<endl; 
}

void directory::pastefile(){
  file *pt,*pf;
  //pf=cpyfile;
  if(pfile==NULL) 
  {
	pfile=pf;
    //pf->next=NULL;	
  } 
  else if(pfile!=NULL){
  	pt=pfile;
    while(pt->next!=NULL)
    {
      pt=pt->next; 
    }
    //pt->next=pf;
    //pf->next=NULL;
  }
}

void directory::showfile() { 
  char name[9],ch1; 
  int findfile=-1; 
  file *pt;  
  if(pfile!=NULL)   
  { 
    pt=pfile; 
	cin>>name;  
	while(pt!=NULL) 
	{ 
	  findfile=strcmp(name,pt->getfilename());  
	  if(findfile==0)    
	  { 
	    if(pt->getsize()!=0) 
		  pt->show_text();      
	    else 
		{
		  cout<<"������!"<<endl;   
		  cout<<"edit?(y/n)��";     
		  cin>>ch1;     
		  if(ch1=='y'||ch1=='Y') 
		    pt->editfile();     
        }   
		break;    
	  }   
      pt=pt->next;    
    } 
    if(findfile!=0) 
      cout<<"�ļ��������Ҳ������ļ�!"<<endl;  
  } 
  else cout<<"��ǰĿ¼���ļ���"<<endl; 
} 

void directory::deletefile() 
{ 
  char filename[9],choice;  
  file *p1,*p2;  
  int findfile=-1;  
  if(pfile!=NULL)  
  { 
    p1=pfile; 
	cin>>filename;  
	while(p1!=NULL)
	{ 
      findfile=strcmp(filename,p1->getfilename()); 
	  if(findfile==0)    
	  { 
	    cout<<"sure?(y/n)��";  
		cin>>choice;  
		if(choice=='y'||choice=='Y') 
		{
		  if(p1==pfile) 
		    pfile=p1->next; 
		  else 
		    p2->next=p1->next;          
		  break;
		}    
	  }    
	  p2=p1;
	  p1=p1->next;    
	}  
	if(findfile!=0) 
	  cout<<"�ļ��������Ҳ������ļ���"<<endl;  
	} 
    else 
	  cout<<"��ǰĿ¼���ļ���"<<endl; 
}   

void dirmanager::addnew() {    
  p1=new directory; 
  p1->fatherdir=p;
  p1->subdir=NULL;
  p1->nextdir=NULL;  
  if(p->subdir==NULL) 
    p->subdir=p1; 
  else 
  {
    p2=p->subdir;   
	while(p2->nextdir!=NULL) 
	  p2=p2->nextdir;         
    p2->nextdir=p1;
  } 
} 

void dirmanager::cdsubdir(){  
  char dname[9];  
  int find;  
  directory *p3=p;   
  cin>>dname;  
  if(p->subdir!=NULL){ 
    p3=p3->subdir;   
	while(p3!=NULL)
	{  
	  find=strcmp(dname,p3->getdname());   
	  if(find==0) 
  	  {
	    p=p3;
		break;
	  }    
	  p3=p3->nextdir; 
    } 
    if(find!=0) 
	  cout<<"Ŀ¼�������Ҳ�����Ŀ¼��"<<endl;     
  } 
  else 
    cout<<"Ŀ¼Ϊ�գ�"<<endl; 
} 

void dirmanager::showdir() {   
  int i=0,j;  
  directory *pd;  
  dir[i++]=p; 
  pd=p->fatherdir;  
  while(pd!=NULL)
  { 
    dir[i]=pd;
	pd=pd->fatherdir;
	i++;
  }  
  for(j=i-1;j>=0;j--)  
  {
    cout<<dir[j]->getdname();
	if(j!=0||i==1)
	  cout<<"\\";
  }  
  cout<<">"; 
} 

void dirmanager::showdirinfor() 
{ 
  int length;  
  file *pfi; 
  directory *pdi;  
  if(p->pfile!=NULL)  
  { 
    pfi=p->pfile;  
	while(pfi!=NULL)  
	{  
	  length=strlen(pfi->getfilename()); 
      cout<<pfi->getfilename()<<setw(30-length)<<"<�ļ�>"<<endl;  
	  pfi=pfi->next;
    }  
  }  
  if(p->subdir!=NULL)  
  {   
    pdi=p->subdir;   
	while(pdi!=NULL)   
	{ 
	  length=strlen(pdi->getdname());   
	  cout<<pdi->getdname()<<setw(30-length)<<"<Ŀ¼>"<<endl;   
	  pdi=pdi->nextdir;
    }  
  }  
  if(p->pfile==NULL&&p->subdir==NULL)   
    cout<<"��Ŀ¼��"<<endl; 
} 

void dirmanager::help(){
  cout<<"================================================"<<endl;
  cout<<"                                                "<<endl;  
  cout<<"                  mkdir �½�Ŀ¼                "<<endl;
  cout<<"                   back �����ϼ�Ŀ¼            "<<endl;
  cout<<"                     cd ������Ŀ¼              "<<endl;
  cout<<"                     mk �½��ļ�                "<<endl;
  cout<<"                     rm ɾ���ļ�                "<<endl;
  cout<<"                   read ��ʾ�ļ�����            "<<endl;
  cout<<"                     Is ��ʾĿ¼��Ϣ            "<<endl;
  cout<<"                 rename �������ļ�              "<<endl;
  cout<<"                   help ����                    "<<endl; 
  cout<<"                  clear ����                    "<<endl;
  cout<<"                   exit �˳�ϵͳ                "<<endl;
  cout<<"                                                "<<endl; 
  cout<<"  ѧ��:201427920214 ����:Ǯ���� �༶:��1405   "<<endl;
  cout<<"======================= ========================"<<endl;
}

void dirmanager::manager() 
{  
  string s;
  char ch;  
  /*
  cout<<"================================================"<<endl;
  cout<<"                   *����������ָ��            \n"<<endl;  
  cout<<"                  mkdir �½�Ŀ¼                "<<endl;
  cout<<"                   back �����ϼ�Ŀ¼            "<<endl;
  cout<<"                     cd ������Ŀ¼              "<<endl;
  cout<<"                     mk �½��ļ�                "<<endl;
  cout<<"                     rm ɾ���ļ�                "<<endl;
  cout<<"                   read ��ʾ�ļ�����            "<<endl;
  cout<<"                     Is ��ʾĿ¼��Ϣ            "<<endl;
  cout<<"                 rename �������ļ�              "<<endl;
  cout<<"                   help ����                    "<<endl; 
  cout<<"                   exit �˳�ϵͳ              \n"<<endl;
  cout<<"  ѧ��:201427920214 ����:Ǯ���� �༶:��1405   "<<endl;
  cout<<"======================= ========================"<<endl;
  */
  root=new directory("f:"); 
  root->fatherdir=NULL;  
  root->subdir=NULL;
  root->nextdir=NULL;
  p=root;  
  for(int i=0;i<200;i++)  
  {   
    cout<<"\n";   
	showdir();
	cin>>s;
    if(s=="mkdir") ch='1';
    if(s=="back") ch='2';
    if(s=="cd") ch='3';
    if(s=="mk") ch='4';
    if(s=="rm") ch='5';
    if(s=="read") ch='6';
    if(s=="Is") ch='7';
    if(s=="rename") ch='8';
    if(s=="help") ch='9'; 
	if(s=="exit") ch='0';  
	if(s=="clear") ch='b'; 
	if(s=="copyfile") ch='c';
	if(s=="pastefile") ch='d';
	switch(ch)        
	{    
	  case '1': 
	    addnew();
		break;  
	  case '2': 
      {
	    if(p->fatherdir!=NULL) 
		p=p->fatherdir;
		break;
	  }       
	  case '3': 
	    cdsubdir();
		break;        
	  case '4': 
	    p->creatfile();
		break; 
      case '5':
	    p->deletefile();
		break;   	
      case '6': 
	    p->showfile();
		break; 
      case '7': 
	    showdirinfor();
		break;  
      case '8': 
	    p->renamefile();
		break;  
      case '9': 
	    help();
	    break;
      case '0': 
	    exit(1);
      case 'b':
        system("cls");
        break;
      case 'c':
        p->copyfile();
        break;
      case 'd':
        p->pastefile();
        break;
      default: 
	    cout<<"ָ����Ч��"<<endl;
		break;        
    }  
    ch='a';
  }  
}  

int main() 
{  
  system("color F0");
  user User;
  User.inter();   
} 
