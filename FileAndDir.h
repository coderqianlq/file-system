#ifndef FILEANDDIR_H
#define FILEANDDIR_H

#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include<vector>
#include<time.h>
#include<sstream>

using namespace std;

typedef struct File          //创建文件的结构体     
{
	bool rw;                //false可读可写，true只读
	string fcreatetime;     //创建时间
	string altertime;       //修改时间
	string filename;        //文件名
	int filesize;                 //文件大小
	File * nextFile;              //指向文件表中下一个文件
	string filecontent;           //文件内容
	File(){rw=false;fcreatetime="";altertime="";filesize=0;nextFile=NULL;filecontent="";}  //初始化函数
}File;

typedef struct Dir         //创建目录的结构体
{
	string dircreatetime; //创建时间
	string altertime;     //修改时间
	string dirname;               //目录名
	int dirsize;                  //目录大小
	Dir * nextDir;                //后继目录
	Dir * preDir;                 //前继目录
	File * fileptr;               //该目录下文件链表指针
	Dir * dirptr;                 //该目录下目录链表指针
	Dir()                         //用于初始化的函数
	{
		altertime="";
		dircreatetime="";      
		dirsize=0;
		nextDir=NULL;
		preDir=NULL;
		fileptr=NULL;
		dirptr=NULL;
	}
	Dir(string time,string name,int size,Dir *nextdir,Dir*predir,File *fileptr1,Dir *dirptr1)//赋值函数
	{
		dircreatetime=time;
		dirname=name;
		dirsize=size;
		nextDir=nextdir;
		preDir=predir;
		fileptr=fileptr1;
		dirptr=dirptr1;
	}
}Dir;
#endif