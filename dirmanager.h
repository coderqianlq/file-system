#include<iostream>
using namespace std;

#ifndef DIRMANAGER
#define DIRMANAGER

class dirmanager { 
  public:   
    void manager(); 
    void addnew();  
    void copydir();                     
    void pastedir();                       
    void renamedir();  
	void cdsubdir(); 
	void showdir(); 
	void showdirinfor(); 
	void help();
	~dirmanager() 
	{
	  delete root;
    } 
	
  private:  
    directory *root,*p,*p1,*p2;   
	directory *dir[10];
 }; 
 
 #endif