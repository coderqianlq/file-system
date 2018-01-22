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

typedef struct File          //�����ļ��Ľṹ��     
{
	bool rw;                //false�ɶ���д��trueֻ��
	string fcreatetime;     //����ʱ��
	string altertime;       //�޸�ʱ��
	string filename;        //�ļ���
	int filesize;                 //�ļ���С
	File * nextFile;              //ָ���ļ�������һ���ļ�
	string filecontent;           //�ļ�����
	File(){rw=false;fcreatetime="";altertime="";filesize=0;nextFile=NULL;filecontent="";}  //��ʼ������
}File;

typedef struct Dir         //����Ŀ¼�Ľṹ��
{
	string dircreatetime; //����ʱ��
	string altertime;     //�޸�ʱ��
	string dirname;               //Ŀ¼��
	int dirsize;                  //Ŀ¼��С
	Dir * nextDir;                //���Ŀ¼
	Dir * preDir;                 //ǰ��Ŀ¼
	File * fileptr;               //��Ŀ¼���ļ�����ָ��
	Dir * dirptr;                 //��Ŀ¼��Ŀ¼����ָ��
	Dir()                         //���ڳ�ʼ���ĺ���
	{
		altertime="";
		dircreatetime="";      
		dirsize=0;
		nextDir=NULL;
		preDir=NULL;
		fileptr=NULL;
		dirptr=NULL;
	}
	Dir(string time,string name,int size,Dir *nextdir,Dir*predir,File *fileptr1,Dir *dirptr1)//��ֵ����
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