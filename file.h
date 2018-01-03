#include<iostream>
using namespace std;

#ifndef File
#define File

class file   
{ 
  private:  
  
  public:  
    int size;  	 
	char *text;
    char filename[9]; 
	file *next;  
	file();  
	file(int n);
	void editfile();
	char *getfilename() 
	{
	  return filename;
    }  
	void show_text() 
	{
	  cout<<"文件名    文件大小   文件内容"<<endl;
	  cout<<filename<<"          "<<strlen(text)<<"       "<<text;
	  cout<<endl;
    }  
	int getsize() 
	{ 
	  return size;
    }   
	~file() 
	{
	  delete text;
    }
}; 

#endif