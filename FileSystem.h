#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "FileAndDir.h"

class FileSystem
{
	
public:
	FileSystem();
	~FileSystem();
	
	//Ŀ¼
	Dir* newDir();               //�½�Ŀ¼
	int deleteDir();             //ɾ��Ŀ¼
	Dir* openDir();              //��Ŀ¼
	int renameDir();             //������Ŀ¼
	int copyDir();               //����Ŀ¼    
	int SubPasteDir(Dir *dir1,Dir *dir2);//ճ���Ӻ���
	int pasteDir();                      //ճ��Ŀ¼
	Dir* goback();                       //������һ��Ŀ¼
	int delete_Dir(Dir *dir);            //Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ�Ŀ¼
	int deleteFileInDir(Dir *dir);       //Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ��ļ�

	//�ļ�
	int newFile();                //�½��ļ�
	int deleteFile();             //ɾ���ļ�
	int readFile();               //���ļ�
	int writeFile();              //�༭�ļ�
	int renameFile();             //�������ļ�
	int copyFile();               //�����ļ�
	int pasteFile();              //ճ���ļ�
	int pasteFileInDir(File *file,Dir*dir);//ճ������Ŀ¼�µ��ļ�
	int showDir();                //��ʾ��ǰĿ¼������
	void display();               //��ʾ��ǰ·��
	int filerw();                 //�޸��ļ�����Ϊ�ɶ�
private:
	Dir * root;                 //��Ŀ¼
	Dir * currentDir;           //��ǰĿ¼
	File * tempfile;            //��Ÿ��Ƶ��ļ����Ա�ճ��ʹ��
	Dir * tempdir;              //��Ÿ��Ƶ�Ŀ¼���Ա�ճ��ʹ��
};

#endif