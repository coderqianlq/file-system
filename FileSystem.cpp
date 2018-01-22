#include"FileSystem.h"
#include"FileAndDir.h"
#include"UserMenu.h"

FileSystem::FileSystem()     
{
    //默认一个目录为用户根目录
	root=new Dir();
	root->dirname="";
	//当前目录为根目录
	currentDir=root;
	//默认为0	
	tempfile=0;
	tempdir=0;
}

//析构函数 
FileSystem::~FileSystem()  
{
	delete currentDir;
	delete root;
	delete tempfile;
	delete tempdir;
}

//函数：新建目录
Dir* FileSystem::newDir()   
{
    //创建目录时间
	time_t t=time(0);      
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));
	
    //指针指向新建目录
	Dir *p=new Dir();    
	cin>>p->dirname;    
    //如果该目录链表指针不为空
	if(currentDir!=NULL)
	{
		if(currentDir->dirptr==NULL)
		{
			currentDir->dirptr=p;
			p->preDir=currentDir;

			p->dircreatetime=tmp;
			p->altertime=tmp;
		}
		else//该目录下目录链表指针不为空
		{
		    //该指针用于遍历
			Dir *q;
			q=currentDir->dirptr;
			while(q->nextDir!=NULL)
			{
				if(!strcmp(p->dirname.c_str(),q->dirname.c_str()))//文件夹同名
				{
					cout<<"同级目录不能重名！"<<endl;
				    cout<<"同级目录不能重名999！"<<endl;
					return 0;
				}

				q=q->nextDir;
			}
			if(!strcmp(p->dirname.c_str(),q->dirname.c_str()))
			{
				cout<<"同级目录不能重名！"<<endl;
				return 0;
			}
			q->nextDir=p;
			p->preDir=currentDir;
			p->dircreatetime=tmp;
			p->altertime=tmp;
		}
		cout<<"目录创建成功！"<<endl;
	}
	else
	{
		cout<<"不能在空目录下创建文件!！"<<endl;
	}
	return currentDir;
}
//新建文件
int FileSystem::newFile()
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));
	string ct;

	File *p=new File();
	cin>>p->filename;
	if(currentDir!=NULL)
	{
		//检查有无同名文件
		if(currentDir->fileptr==NULL)
		{
			currentDir->fileptr=p;
			p->fcreatetime=tmp;
			p->altertime=tmp;

		}
		else
		{
			File *q=new File();
			q=currentDir->fileptr;
			while(q->nextFile!=NULL)
			{
				if(!strcmp(p->filename.c_str(),q->filename.c_str()))
				{
					cout<<"该文件已创建，无需重新创建!"<<endl;
					return 0;
				}
				//下一个文件为q所指向文件
				q=q->nextFile;

			}
			if(!strcmp(p->filename.c_str(),q->filename.c_str()))
			{
				cout<<"该文件已创建，无需重新创建!"<<endl;
				return 0;
			}
			q->nextFile=p;
			p->fcreatetime=tmp;
			p->altertime=tmp;
		}
		cout<<"文件创建成功！"<<endl;
	}
	else
	{
		cout<<"不能在空目录下创建文件!"<<endl;
	}
	return 1;
} 

//显示当前目录的内容
int FileSystem::showDir()
{
	int dirsize1=0,dirsize2=0;
	Dir *d = new Dir();
	//d表示当前目录下的目录 
	d=currentDir->dirptr;
	File *f = new File();
	//f表示当前目录下的文件 
	f=currentDir->fileptr;
	char buf[10];
	string str;
	if (d == NULL && f == NULL) { 
		cout << "空目录" << endl;
		return 0; 
	}                                                                   
	Dir *d1=new Dir();
	File *d2=new File();

	//遍历当前目录
	cout<<endl;

	cout<<" 目录名称      "<<"目录大小      "<<"   创建时间";
	cout<<endl;
	while (d != NULL) { 

		d1=d->dirptr;
		d2=d->fileptr;

		while(d1!=NULL)
		{
		    //指的是目录的个数
			dirsize1++;
			d1=d1->nextDir;
		}
		while(d2!=NULL)
		{
		    //指的是文件的个数
			dirsize2++;
			d2=d2->nextFile;
		}
		//该目录下文件和目录的个数
		d->dirsize=(dirsize1+dirsize2);
		itoa(d->dirsize,buf,10);
		str=buf;

		cout<<"    "<<d->dirname<<string(14-(d->dirname.length()),' ')<<d->dirsize<<string(10-str.length(),' ')<<d->dircreatetime<<endl;
		d = d->nextDir; 
		dirsize1=0;
		dirsize2=0;
	} 

	cout<<endl;
	cout<<" 文件名称      "<<"文件大小         "<<"文件内容           "<<"创建时间           "<<"文件属性";
	cout<<endl; 

	//遍历当前文件指针
	while(f!=NULL)
	{
		itoa(f->filesize,buf,10);
		str=buf;
		if(f->rw)
			cout<<"    "<<f->filename<<string(15-(f->filename.length()),' ')<<f->filesize<<string(18-f->filecontent.length(),' ')<<f->filecontent<<string(10-str.length(),' ')<<f->fcreatetime<<"     只读"<<endl;
		else
			cout<<"    "<<f->filename<<string(15-(f->filename.length()),' ')<<f->filesize<<string(18-f->filecontent.length(),' ')<<f->filecontent<<string(10-str.length(),' ')<<f->fcreatetime<<"    可读可写"<<endl;
		f=f->nextFile;
	}
	return 1;
}

//打开目录
Dir* FileSystem::openDir()
{
	Dir *d=new Dir();
	cin>>d->dirname;
	int flag=0;
	FileSystem *fs=new FileSystem;

	if(currentDir==NULL)
	{
		cout<<"目录为空!"<<endl;
	}
	else
	{
		if(currentDir->dirptr==NULL)
		{
			cout<<"请先创建一个目录!"<<endl;
		}
		else
		{

			Dir *q=new Dir();
			q=currentDir->dirptr;
			while(q!=NULL)
			{
				if(!strcmp(d->dirname.c_str(),q->dirname.c_str()))
				{
					currentDir=q;
					flag++;
					break;
				}
				q=q->nextDir;

			}
			if(!flag)
			{
				cout<<"该目录不存在"<<endl;
			}
		}
	}
	return currentDir;
}

//返回上一级目录
Dir* FileSystem::goback()
{

	int flag=0;
	if(currentDir!=NULL)
	{
		if(currentDir==root)
		{
			cout<<"根目录无法返回!"<<endl;
		}
		else
		{
			currentDir=currentDir->preDir;
		}
	}
	else
	{
		cout<<"无前继目录可以返回!"<<endl;
	}

	return currentDir;
}

//显示当前路径
void  FileSystem::display()
{
	vector<Dir*> v;
	int flag=0;
	ifstream in;
	in.open("G:\\username_login.txt");
	string username;
	in>>username;
	Dir*p=new Dir();
	p=root;
	if(p==currentDir)
	{
		cout << "\nf:\\"<<p->dirname<<">";}
	else
	{
		cout << "\nf:"<<p->dirname;
		Dir *q=new Dir();
		q=currentDir;
		while(q!=NULL)
		{
			v.push_back(q);
			q=q->preDir;
		}
		for(int i=0;i<v.size();i++)
		{
			if(i==0) cout<<v[v.size()-1-i]->dirname;
			else cout<<"\\"<<v[v.size()-1-i]->dirname;
		}
		cout<<">";

	}
	v.clear();
	in.close();
}

//目录删除子函数，删除要删除目录下的目录
int FileSystem::delete_Dir(Dir *dir) 
{
	if(dir->dirptr!=NULL)
	{
        //把该目录删除掉
		delete_Dir(dir->dirptr);
	}
	//下一目录不为空
	if(dir->nextDir!=NULL)
	{
	    //把该目录的下一目录也删除掉，递归
		delete_Dir(dir->nextDir);
	}
	delete dir;
	return 1;
}

//目录删除子函数，删除要删除目录下的文件
int FileSystem::deleteFileInDir(Dir *dir) 
{

	if(dir->fileptr!=NULL)
	{
		dir->fileptr=NULL;
	}

	return 1;
}

//删除目录
int FileSystem::deleteDir()
{
	Dir *p=new Dir();
	cin>>p->dirname;
	int flag=0;
	if(currentDir->dirptr==NULL)
	{
		cout<<"当前路径下不存在目录!"<<endl;
	}
	else
	{
		Dir *q=new Dir();
		q=currentDir->dirptr;
		if(q->nextDir==NULL)
		{
			if(q->dirname==p->dirname)
			{
				if(q->dirptr==NULL)
				{
				    //删除文件
					deleteFileInDir(q);
					currentDir->dirptr=NULL;
				}
				//如果目录里面有子目录
				else
				{
				    //删除文件
					deleteFileInDir(q);
					//删除子目录
					delete_Dir(q->dirptr);
					q->dirptr=NULL;
					currentDir->dirptr=NULL;
				}
				flag++;
			}
		}
		//下一目录不为空。
		else
		{
			if(q->dirname==p->dirname)
			{
				flag++;
				if(q->dirptr==NULL)
				{
					deleteFileInDir(q);
					currentDir->dirptr=q->nextDir;
				}
				else
				{
					deleteFileInDir(q);
					delete_Dir(q->dirptr);
					q->dirptr=NULL;
					currentDir->dirptr=q->nextDir;
				}
			}
			else
			{
				while(q->nextDir!=NULL)
				{
				    //如果下一遍历的目录名==需要删除的目录名
					if(q->nextDir->dirname==p->dirname)
					{
						if(q->nextDir->dirptr==NULL)
						{
							deleteFileInDir(q->nextDir);
							q->nextDir=q->nextDir->nextDir;
						}
						else
						{
							deleteFileInDir(q->nextDir);
							delete_Dir(q->nextDir->dirptr);
							q->nextDir->dirptr=NULL;
							q->nextDir=q->nextDir->nextDir;
						}
						flag++;
						break;
					}
					q=q->nextDir;
				}
			}
		}
		if(flag)
		{
			cout<<"目录删除成功！"<<endl;
		}
		else
		{
			cout<<"不存在指定要删除的目录!"<<endl;
		}
	}
	return 1;

}

//删除文件
int FileSystem::deleteFile() 
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		if(q->nextFile==NULL)
		{
		    //判断是否为需要删除的文件
			if(q->filename==p->filename)
			{
				currentDir->fileptr=NULL;
				flag++;
			}
		}
		else
		{
			if(q->filename==p->filename)
			{
				currentDir->fileptr=q->nextFile;
				flag++;
			}
			else
			{
				while(q->nextFile!=NULL)
				{
					if(q->nextFile->filename==p->filename)
					{
						q->nextFile=q->nextFile->nextFile;
						flag++;
						break;
					}
					q=q->nextFile;
				}
			}
		}
		if(flag)
			cout<<"文件删除成功！"<<endl;
		else
			cout<<"不存在指定要删除的文件!"<<endl;

	}
	return 1;
}

//目录重命名
int FileSystem::renameDir()
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	Dir *p=new Dir();
	cin>>p->dirname;
	Dir *q=new Dir();
	cin>>q->dirname;
	int flag=0,flag1=0;
	if(currentDir->dirptr==NULL)
		cout<<"当前路径下不存在目录!"<<endl;
	else
	{
		Dir *ptr=new Dir();
		ptr=currentDir->dirptr;
		Dir *ptr1=new Dir();
		ptr1=currentDir->dirptr;
		while(ptr!=NULL)
		{
		    //当前路径下存在要重命名的目录
			if(ptr->dirname==p->dirname)
			{
				flag++;
				while(ptr1!=NULL)
				{
				    //重命名后的目录名字与原来存在的目录相同
					if(ptr1->dirname==q->dirname)
					{
						flag1++;
						break;
					}
					ptr1=ptr1->nextDir;
				}
				if(!flag1)
				{
					ptr->dirname=q->dirname;
					ptr->altertime=tmp;
				}
				break;
			}

			ptr=ptr->nextDir;
		}

		if(!flag)
			cout<<"不存在指定要重命名的目录!"<<endl;
		if(flag)
		{
			if(flag1)
				cout<<"无效重命名，新目录名与原有目录名重名!"<<endl;
			else
				cout<<"目录重命名成功！"<<endl;
		}
	}
	return 1;
}

//重命名文件
int FileSystem::renameFile()
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	File *p=new File();
	cin>>p->filename;
	File *q=new File();
	cin>>q->filename;
	int flag=0,flag1=0;
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *ptr=new File();
		ptr=currentDir->fileptr;
		File *ptr1=new File();
		ptr1=currentDir->fileptr;
		while(ptr!=NULL)
		{
		    //当前路径下存在要重命名的目录
			if(ptr->filename==p->filename)
			{
				flag++;
				while(ptr1!=NULL)
				{
					if(ptr1->filename==q->filename)
					{
						flag1++;
						break;
					}
					ptr1=ptr1->nextFile;
				}
				if(!flag1)
				{
					ptr->filename=q->filename;
					ptr->altertime=tmp;
				}
				break;
			}

			ptr=ptr->nextFile;
		}

		if(!flag)
			cout<<"不存在指定要重命名的文件!"<<endl;
		if(flag)
		{
			if(flag1)
				cout<<"无效重命名，新文件名与原有文件名重名!"<<endl;
			else
				cout<<"文件重命名成功！"<<endl;
		}
	}
	return 1;
}

//读出文件,显示文件内容
int FileSystem::readFile()
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{
				cout<<q->filecontent<<endl;
				flag++;
				break;
			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"文件名错误,打开失败!"<<endl;

	}
	return 1;
}

//编辑文件内容 
int FileSystem::writeFile()
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	File *p=new File();
	cin>>p->filename;
	string s;
	int flag=0;
	getline(cin,s);
	if(currentDir->fileptr==NULL)
		cout<<"当前路径下不存在文件!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{

				if(q->rw==false)
				{

					q->filecontent=s;
					q->filesize=s.length()-1;
					q->altertime=tmp;
					flag++;
					cout<<"文件写入成功！"<<endl;
					break;
				}
				else
				{
					cout<<"该文件为只读文件，不能写入!"<<endl;
					return 0;
				}

			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"不存在指定要编辑的文件!"<<endl;

	}
	return 1;
}

int FileSystem::copyFile()
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	tempfile=new File();
	if(currentDir->fileptr==NULL)     
		cout<<"当前路径下不存在文件!"<<endl;
	else					
	{
		File *q=new File();
		q=currentDir->fileptr;

		while(q->nextFile!=NULL)
		{
			if(q->nextFile->filename==p->filename)
			{
				tempfile=q->nextFile;

				flag++;
				break;
			}
			else{}
			q=q->nextFile;
		}
		if(currentDir->fileptr->filename==p->filename)
		{
			tempfile=currentDir->fileptr;
			flag++;
		}
		if(flag)
			cout<<"文件复制成功！"<<endl;
		else
			cout<<"不存在指定要复制的文件!"<<endl;
	}

	return 1;
}

//粘贴文件 
int FileSystem::pasteFile()
{
	int flag=0;
	if(tempfile==NULL)
	{
		cout<<"复制文件不存在，粘贴失败!"<<endl;
		return 0;
	}
    //1.复制了 2.当前fileptr空的，直接paste进来
	if(currentDir->fileptr==NULL)
	{
		currentDir->fileptr=new File();
		currentDir->fileptr->fcreatetime=tempfile->fcreatetime;
		currentDir->fileptr->filecontent=tempfile->filecontent;
		currentDir->fileptr->filename=tempfile->filename;
		currentDir->fileptr->filesize=tempfile->filesize;
		cout<<"粘贴文件成功!"<<endl;
	}
	else  
	{

		File *q=new File();
		q=currentDir->fileptr;

		while(q->nextFile!=NULL)
		{
			if(q->filename==tempfile->filename)
			{
				flag++;
				break;
			}
			q=q->nextFile;
			//检验 给flag
			if(q->nextFile==NULL && q->filename==tempfile->filename)
			{
				flag++;
			}
		}
		//判断链表第一个文件是否与要粘贴的同名
		if(currentDir->fileptr->filename==tempfile->filename)
		{
			flag++;
		}

		if(!flag )
		{
			//最后节点交给temp
			q->nextFile=new File();
			q->nextFile->fcreatetime=tempfile->fcreatetime;
			q->nextFile->filecontent=tempfile->filecontent;
			q->nextFile->filename=tempfile->filename;
			q->nextFile->filesize=tempfile->filesize;
			cout<<"文件粘贴成功！"<<endl;

		}
		else
			cout<<"当前文件已存在!"<<endl;
	}


	return 1;
}

//复制目录 
int FileSystem::copyDir()   
{
	Dir *p=new Dir();
	cin>>p->dirname;
	int flag=0;

	if(currentDir->dirptr==NULL)
		cout<<"当前路径下不存在目录!"<<endl;
	else
	{
		Dir *q=new Dir();
		q=currentDir->dirptr;
		while(q!=NULL)
		{
			if(q->dirname==p->dirname)
			{
				tempdir=q;
				flag++;
				break;
			}
			q=q->nextDir;
		}
		if(flag)
			cout<<"目录复制成功！"<<endl;
		else
			cout<<"不存在指定要复制的目录!"<<endl;
	}
	return 1;
}

//粘贴目录
int FileSystem::pasteDir()
{

	int flag=0;
	if(tempdir==NULL)
	{
		cout<<"不存在复制目录，不能粘贴!"<<endl;
		return 0;
	}

	Dir *ptr=new Dir();
	ptr=currentDir;
	//绝对不能复制到本分支，保证本分支各个节点都不是tempdir
	while(ptr!=NULL)
	{
	    //目标 current的爸爸不能是temp
		if(ptr->dirname==tempdir->dirname)
		{
			cout<<"禁止将父目录复制到子目录下!"<<endl;
			return 0;
		}
		//回溯
		ptr=ptr->preDir;
	}

	if(currentDir->dirptr==NULL)
	{

		currentDir->dirptr=new Dir();

		if(tempdir->dirptr==NULL )
		{
			currentDir->dirptr->dircreatetime=tempdir->dircreatetime;
			currentDir->dirptr->dirname=tempdir->dirname;
			currentDir->dirptr->dirsize=tempdir->dirsize;
			currentDir->dirptr->preDir=currentDir;

			pasteFileInDir(tempdir->fileptr,currentDir->dirptr);
		}
		else	
		{
			currentDir->dirptr->dircreatetime=tempdir->dircreatetime;
			currentDir->dirptr->dirname=tempdir->dirname;
			currentDir->dirptr->dirsize=tempdir->dirsize;
			currentDir->dirptr->preDir=currentDir;

			pasteFileInDir(tempdir->fileptr,currentDir->dirptr);
			//----自己部分结束
			//把current ptr的ptr给temp的ptr 两边子目录对接
			//子目录起始位置开始粘贴
			currentDir->dirptr->dirptr=new Dir();
			currentDir->dirptr->dirptr->dircreatetime=tempdir->dirptr->dircreatetime;
			currentDir->dirptr->dirptr->dirname=tempdir->dirptr->dirname;
			currentDir->dirptr->dirptr->dirsize=tempdir->dirptr->dirsize;
			//子文件复制
			currentDir->dirptr->dirptr->preDir=currentDir->dirptr;
			//子目录
			pasteFileInDir(tempdir->dirptr->fileptr,currentDir->dirptr->dirptr);
			//把前面给后面的目标地址
			SubPasteDir(tempdir->dirptr,currentDir->dirptr->dirptr);
		}
		cout<<"目录粘贴成功！"<<endl;
	}
	else
	{
		Dir *q=new Dir();
		q=currentDir->dirptr;

		while(q->nextDir!=NULL)
		{
			if(q->nextDir->dirname==tempdir->dirname)
			{
				flag++;
				break;
			}
			q=q->nextDir;
			//判断最后链表最后一个目录是否与要粘贴的同名
			if(q->nextDir==NULL && q->dirname==tempdir->dirname)
			{
				flag++;
			}
		}
		if(currentDir->dirptr->dirname==tempdir->dirname)
		{
			flag++;
		}
		if(!flag)
		{
			q->nextDir=new Dir();
			if(tempdir->dirptr==NULL)
			{
				q->nextDir->dircreatetime=tempdir->dircreatetime;
				q->nextDir->dirname=tempdir->dirname;
				q->nextDir->dirptr->dirsize=tempdir->dirsize;
				q->nextDir->preDir=currentDir;
				pasteFileInDir(tempdir->fileptr,q->nextDir);

			}
			else
			{
				q->nextDir->dircreatetime=tempdir->dircreatetime;
				q->nextDir->dirname=tempdir->dirname;
				q->nextDir->dirsize=tempdir->dirsize;
				q->nextDir->preDir=currentDir;
				pasteFileInDir(tempdir->fileptr,q->nextDir);

				q->nextDir->dirptr=new Dir();
				q->nextDir->dirptr->dircreatetime=tempdir->dirptr->dircreatetime;
				q->nextDir->dirptr->dirname=tempdir->dirptr->dirname;
				q->nextDir->dirptr->dirsize=tempdir->dirptr->dirsize;
				q->nextDir->dirptr->preDir=q->nextDir;
				pasteFileInDir(tempdir->dirptr->fileptr,q->nextDir->dirptr);
				SubPasteDir(tempdir->dirptr,q->nextDir->dirptr);
				cout<<"粘贴目录成功!"<<endl;
			}
		}
		else
			cout<<"当前目录已存在!"<<endl;

	}

	return 1;
}

//粘贴子函数  1是复制了的目录     2是要复制到的目录
int FileSystem::SubPasteDir(Dir *dir1,Dir *dir2)
{

	if(dir1->dirptr!=NULL)
	{
		dir2->dirptr=new Dir();
		dir2->dirptr->dircreatetime=dir1->dirptr->dircreatetime;
		dir2->dirptr->dirname=dir1->dirptr->dirname;
		dir2->dirptr->dirsize=dir1->dirptr->dirsize;
		dir2->dirptr->preDir=dir2;
		//文件复制
		pasteFileInDir(dir1->dirptr->fileptr,dir2->dirptr);
		//递归
		SubPasteDir(dir1->dirptr,dir2->dirptr);
	}

	if(dir1->nextDir!=NULL)
	{
		dir2->nextDir=new Dir();
		dir2->nextDir->dircreatetime=dir1->nextDir->dircreatetime;
		dir2->nextDir->dirname=dir1->nextDir->dirname;
		dir2->nextDir->dirsize=dir1->nextDir->dirsize;
		dir2->nextDir->preDir=dir2->preDir;
		pasteFileInDir(dir1->nextDir->fileptr,dir2->nextDir);


		SubPasteDir(dir1->nextDir,dir2->nextDir);
	}

	return 1;
}

int FileSystem::pasteFileInDir(File *file,Dir *dir)
{
	File *file1=new File();
	file1=file;
	Dir *dir1=new Dir();
	dir1=dir;
	if(dir1->fileptr!=NULL)
	{
		File *ptr=new File();
		ptr=dir1->fileptr;
		while(ptr->nextFile!=NULL)
		{
			ptr=ptr->nextFile;
		}
		ptr->nextFile=new File();
		ptr->nextFile->fcreatetime=file1->fcreatetime;
		ptr->nextFile->filecontent=file1->filecontent;
		ptr->nextFile->filename=file1->filename;
		ptr->nextFile->filesize=file->filesize;

	}
	else 
	{
		if (file == NULL){
			dir->fileptr = file1;
		}
		else{
		File *ptr = new File();
		ptr = file1;
		File *tempfile = new File();
		tempfile->fcreatetime = file1->fcreatetime;
		tempfile->filecontent = file1->filecontent;
		tempfile->filename = file1->filename;
		tempfile->filesize = file1->filesize;
		ptr = tempfile;
		while (file1->nextFile!=NULL)
		{
			File *tempfile2 = new File();
			tempfile->fcreatetime = file1->fcreatetime;
			tempfile->filecontent = file1->filecontent;
			tempfile->filename = file1->filename;
			tempfile->filesize = file1->filesize;
			ptr->nextFile = tempfile2;
			ptr = ptr->nextFile;
			
		}
		dir->fileptr=tempfile;
		}
	}
	return 1;

}

//修改文件属性
int FileSystem::filerw()
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	File *p=new File();
	cin>>p->filename;
	int flag=0;

	if(currentDir->fileptr==NULL)
		cout<<"文件不存在!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{
 
				cout<<"0 读写  |  1 只读"<<endl;
				int flag1=0; 
				bool a;
				cin>>a;
				while(q->rw==a)
				{
					if(a==0) cout<<"该文件已为可读可写!"<<endl;
					if(a==1) cout<<"该文件已为只读!"<<endl;
					flag1=1;
					break; 
				}
                if(flag1==0){
				if(q->rw==false)
				{
					q->altertime=tmp;
					q->rw=a;
					cout<<"文件已修改为只读!"<<endl;
				}
				else
				{
					q->altertime=tmp;
					q->rw=a;
					cout<<"文件已修改为可读可写!"<<endl;
				}
                }
				flag++;
				break;
			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"不存在指定要编辑的文件!"<<endl;

	}
	return 1;
}