#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "FileAndDir.h"

class FileSystem
{
	
public:
	FileSystem();
	~FileSystem();
	
	//目录
	Dir* newDir();               //新建目录
	int deleteDir();             //删除目录
	Dir* openDir();              //打开目录
	int renameDir();             //重命名目录
	int copyDir();               //复制目录    
	int SubPasteDir(Dir *dir1,Dir *dir2);//粘贴子函数
	int pasteDir();                      //粘贴目录
	Dir* goback();                       //返回上一级目录
	int delete_Dir(Dir *dir);            //目录删除子函数，删除要删除目录下的目录
	int deleteFileInDir(Dir *dir);       //目录删除子函数，删除要删除目录下的文件

	//文件
	int newFile();                //新建文件
	int deleteFile();             //删除文件
	int readFile();               //打开文件
	int writeFile();              //编辑文件
	int renameFile();             //重命名文件
	int copyFile();               //复制文件
	int pasteFile();              //粘贴文件
	int pasteFileInDir(File *file,Dir*dir);//粘贴复制目录下的文件
	int showDir();                //显示当前目录的内容
	void display();               //显示当前路径
	int filerw();                 //修改文件属性为可读
private:
	Dir * root;                 //根目录
	Dir * currentDir;           //当前目录
	File * tempfile;            //存放复制的文件，以便粘贴使用
	Dir * tempdir;              //存放复制的目录，以便粘贴使用
};

#endif