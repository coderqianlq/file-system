#include<iostream>
using namespace std;
 
#ifndef DIRECTORY
#define DIRECTORY

class directory  
{ 
  private:  
    char dirname[9];   
  public:  
    file  *pfile; 
    directory *nextdir,*subdir,*fatherdir; 
    directory(char *dname) 
	{ 
	  strcpy(dirname,dname);
	  pfile=NULL;
    }  
	directory()   
	{  
	  pfile=NULL;
	  cin>>dirname; 
    }  
	void creatfile();    
	void deletefile();   
	void showfile();
	void renamefile(); 
	void copyfile();  
	void pastefile();
    char *getdname() 
	{
	  return dirname;
    }  
	~directory() 
	{
	  delete pfile;
    }
};  

#endif