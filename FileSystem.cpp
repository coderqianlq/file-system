#include"FileSystem.h"
#include"FileAndDir.h"
#include"UserMenu.h"

FileSystem::FileSystem()     
{
    //Ĭ��һ��Ŀ¼Ϊ�û���Ŀ¼
	root=new Dir();
	root->dirname="";
	//��ǰĿ¼Ϊ��Ŀ¼
	currentDir=root;
	//Ĭ��Ϊ0	
	tempfile=0;
	tempdir=0;
}

//�������� 
FileSystem::~FileSystem()  
{
	delete currentDir;
	delete root;
	delete tempfile;
	delete tempdir;
}

//�������½�Ŀ¼
Dir* FileSystem::newDir()   
{
    //����Ŀ¼ʱ��
	time_t t=time(0);      
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));
	
    //ָ��ָ���½�Ŀ¼
	Dir *p=new Dir();    
	cin>>p->dirname;    
    //�����Ŀ¼����ָ�벻Ϊ��
	if(currentDir!=NULL)
	{
		if(currentDir->dirptr==NULL)
		{
			currentDir->dirptr=p;
			p->preDir=currentDir;

			p->dircreatetime=tmp;
			p->altertime=tmp;
		}
		else//��Ŀ¼��Ŀ¼����ָ�벻Ϊ��
		{
		    //��ָ�����ڱ���
			Dir *q;
			q=currentDir->dirptr;
			while(q->nextDir!=NULL)
			{
				if(!strcmp(p->dirname.c_str(),q->dirname.c_str()))//�ļ���ͬ��
				{
					cout<<"ͬ��Ŀ¼����������"<<endl;
				    cout<<"ͬ��Ŀ¼��������999��"<<endl;
					return 0;
				}

				q=q->nextDir;
			}
			if(!strcmp(p->dirname.c_str(),q->dirname.c_str()))
			{
				cout<<"ͬ��Ŀ¼����������"<<endl;
				return 0;
			}
			q->nextDir=p;
			p->preDir=currentDir;
			p->dircreatetime=tmp;
			p->altertime=tmp;
		}
		cout<<"Ŀ¼�����ɹ���"<<endl;
	}
	else
	{
		cout<<"�����ڿ�Ŀ¼�´����ļ�!��"<<endl;
	}
	return currentDir;
}
//�½��ļ�
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
		//�������ͬ���ļ�
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
					cout<<"���ļ��Ѵ������������´���!"<<endl;
					return 0;
				}
				//��һ���ļ�Ϊq��ָ���ļ�
				q=q->nextFile;

			}
			if(!strcmp(p->filename.c_str(),q->filename.c_str()))
			{
				cout<<"���ļ��Ѵ������������´���!"<<endl;
				return 0;
			}
			q->nextFile=p;
			p->fcreatetime=tmp;
			p->altertime=tmp;
		}
		cout<<"�ļ������ɹ���"<<endl;
	}
	else
	{
		cout<<"�����ڿ�Ŀ¼�´����ļ�!"<<endl;
	}
	return 1;
} 

//��ʾ��ǰĿ¼������
int FileSystem::showDir()
{
	int dirsize1=0,dirsize2=0;
	Dir *d = new Dir();
	//d��ʾ��ǰĿ¼�µ�Ŀ¼ 
	d=currentDir->dirptr;
	File *f = new File();
	//f��ʾ��ǰĿ¼�µ��ļ� 
	f=currentDir->fileptr;
	char buf[10];
	string str;
	if (d == NULL && f == NULL) { 
		cout << "��Ŀ¼" << endl;
		return 0; 
	}                                                                   
	Dir *d1=new Dir();
	File *d2=new File();

	//������ǰĿ¼
	cout<<endl;

	cout<<" Ŀ¼����      "<<"Ŀ¼��С      "<<"   ����ʱ��";
	cout<<endl;
	while (d != NULL) { 

		d1=d->dirptr;
		d2=d->fileptr;

		while(d1!=NULL)
		{
		    //ָ����Ŀ¼�ĸ���
			dirsize1++;
			d1=d1->nextDir;
		}
		while(d2!=NULL)
		{
		    //ָ�����ļ��ĸ���
			dirsize2++;
			d2=d2->nextFile;
		}
		//��Ŀ¼���ļ���Ŀ¼�ĸ���
		d->dirsize=(dirsize1+dirsize2);
		itoa(d->dirsize,buf,10);
		str=buf;

		cout<<"    "<<d->dirname<<string(14-(d->dirname.length()),' ')<<d->dirsize<<string(10-str.length(),' ')<<d->dircreatetime<<endl;
		d = d->nextDir; 
		dirsize1=0;
		dirsize2=0;
	} 

	cout<<endl;
	cout<<" �ļ�����      "<<"�ļ���С         "<<"�ļ�����           "<<"����ʱ��           "<<"�ļ�����";
	cout<<endl; 

	//������ǰ�ļ�ָ��
	while(f!=NULL)
	{
		itoa(f->filesize,buf,10);
		str=buf;
		if(f->rw)
			cout<<"    "<<f->filename<<string(15-(f->filename.length()),' ')<<f->filesize<<string(18-f->filecontent.length(),' ')<<f->filecontent<<string(10-str.length(),' ')<<f->fcreatetime<<"     ֻ��"<<endl;
		else
			cout<<"    "<<f->filename<<string(15-(f->filename.length()),' ')<<f->filesize<<string(18-f->filecontent.length(),' ')<<f->filecontent<<string(10-str.length(),' ')<<f->fcreatetime<<"    �ɶ���д"<<endl;
		f=f->nextFile;
	}
	return 1;
}

//��Ŀ¼
Dir* FileSystem::openDir()
{
	Dir *d=new Dir();
	cin>>d->dirname;
	int flag=0;
	FileSystem *fs=new FileSystem;

	if(currentDir==NULL)
	{
		cout<<"Ŀ¼Ϊ��!"<<endl;
	}
	else
	{
		if(currentDir->dirptr==NULL)
		{
			cout<<"���ȴ���һ��Ŀ¼!"<<endl;
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
				cout<<"��Ŀ¼������"<<endl;
			}
		}
	}
	return currentDir;
}

//������һ��Ŀ¼
Dir* FileSystem::goback()
{

	int flag=0;
	if(currentDir!=NULL)
	{
		if(currentDir==root)
		{
			cout<<"��Ŀ¼�޷�����!"<<endl;
		}
		else
		{
			currentDir=currentDir->preDir;
		}
	}
	else
	{
		cout<<"��ǰ��Ŀ¼���Է���!"<<endl;
	}

	return currentDir;
}

//��ʾ��ǰ·��
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

//Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ�Ŀ¼
int FileSystem::delete_Dir(Dir *dir) 
{
	if(dir->dirptr!=NULL)
	{
        //�Ѹ�Ŀ¼ɾ����
		delete_Dir(dir->dirptr);
	}
	//��һĿ¼��Ϊ��
	if(dir->nextDir!=NULL)
	{
	    //�Ѹ�Ŀ¼����һĿ¼Ҳɾ�������ݹ�
		delete_Dir(dir->nextDir);
	}
	delete dir;
	return 1;
}

//Ŀ¼ɾ���Ӻ�����ɾ��Ҫɾ��Ŀ¼�µ��ļ�
int FileSystem::deleteFileInDir(Dir *dir) 
{

	if(dir->fileptr!=NULL)
	{
		dir->fileptr=NULL;
	}

	return 1;
}

//ɾ��Ŀ¼
int FileSystem::deleteDir()
{
	Dir *p=new Dir();
	cin>>p->dirname;
	int flag=0;
	if(currentDir->dirptr==NULL)
	{
		cout<<"��ǰ·���²�����Ŀ¼!"<<endl;
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
				    //ɾ���ļ�
					deleteFileInDir(q);
					currentDir->dirptr=NULL;
				}
				//���Ŀ¼��������Ŀ¼
				else
				{
				    //ɾ���ļ�
					deleteFileInDir(q);
					//ɾ����Ŀ¼
					delete_Dir(q->dirptr);
					q->dirptr=NULL;
					currentDir->dirptr=NULL;
				}
				flag++;
			}
		}
		//��һĿ¼��Ϊ�ա�
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
				    //�����һ������Ŀ¼��==��Ҫɾ����Ŀ¼��
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
			cout<<"Ŀ¼ɾ���ɹ���"<<endl;
		}
		else
		{
			cout<<"������ָ��Ҫɾ����Ŀ¼!"<<endl;
		}
	}
	return 1;

}

//ɾ���ļ�
int FileSystem::deleteFile() 
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	if(currentDir->fileptr==NULL)
		cout<<"��ǰ·���²������ļ�!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		if(q->nextFile==NULL)
		{
		    //�ж��Ƿ�Ϊ��Ҫɾ�����ļ�
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
			cout<<"�ļ�ɾ���ɹ���"<<endl;
		else
			cout<<"������ָ��Ҫɾ�����ļ�!"<<endl;

	}
	return 1;
}

//Ŀ¼������
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
		cout<<"��ǰ·���²�����Ŀ¼!"<<endl;
	else
	{
		Dir *ptr=new Dir();
		ptr=currentDir->dirptr;
		Dir *ptr1=new Dir();
		ptr1=currentDir->dirptr;
		while(ptr!=NULL)
		{
		    //��ǰ·���´���Ҫ��������Ŀ¼
			if(ptr->dirname==p->dirname)
			{
				flag++;
				while(ptr1!=NULL)
				{
				    //���������Ŀ¼������ԭ�����ڵ�Ŀ¼��ͬ
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
			cout<<"������ָ��Ҫ��������Ŀ¼!"<<endl;
		if(flag)
		{
			if(flag1)
				cout<<"��Ч����������Ŀ¼����ԭ��Ŀ¼������!"<<endl;
			else
				cout<<"Ŀ¼�������ɹ���"<<endl;
		}
	}
	return 1;
}

//�������ļ�
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
		cout<<"��ǰ·���²������ļ�!"<<endl;
	else
	{
		File *ptr=new File();
		ptr=currentDir->fileptr;
		File *ptr1=new File();
		ptr1=currentDir->fileptr;
		while(ptr!=NULL)
		{
		    //��ǰ·���´���Ҫ��������Ŀ¼
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
			cout<<"������ָ��Ҫ���������ļ�!"<<endl;
		if(flag)
		{
			if(flag1)
				cout<<"��Ч�����������ļ�����ԭ���ļ�������!"<<endl;
			else
				cout<<"�ļ��������ɹ���"<<endl;
		}
	}
	return 1;
}

//�����ļ�,��ʾ�ļ�����
int FileSystem::readFile()
{
	File *p=new File();
	cin>>p->filename;
	int flag=0;
	if(currentDir->fileptr==NULL)
		cout<<"��ǰ·���²������ļ�!"<<endl;
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
			cout<<"�ļ�������,��ʧ��!"<<endl;

	}
	return 1;
}

//�༭�ļ����� 
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
		cout<<"��ǰ·���²������ļ�!"<<endl;
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
					cout<<"�ļ�д��ɹ���"<<endl;
					break;
				}
				else
				{
					cout<<"���ļ�Ϊֻ���ļ�������д��!"<<endl;
					return 0;
				}

			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"������ָ��Ҫ�༭���ļ�!"<<endl;

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
		cout<<"��ǰ·���²������ļ�!"<<endl;
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
			cout<<"�ļ����Ƴɹ���"<<endl;
		else
			cout<<"������ָ��Ҫ���Ƶ��ļ�!"<<endl;
	}

	return 1;
}

//ճ���ļ� 
int FileSystem::pasteFile()
{
	int flag=0;
	if(tempfile==NULL)
	{
		cout<<"�����ļ������ڣ�ճ��ʧ��!"<<endl;
		return 0;
	}
    //1.������ 2.��ǰfileptr�յģ�ֱ��paste����
	if(currentDir->fileptr==NULL)
	{
		currentDir->fileptr=new File();
		currentDir->fileptr->fcreatetime=tempfile->fcreatetime;
		currentDir->fileptr->filecontent=tempfile->filecontent;
		currentDir->fileptr->filename=tempfile->filename;
		currentDir->fileptr->filesize=tempfile->filesize;
		cout<<"ճ���ļ��ɹ�!"<<endl;
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
			//���� ��flag
			if(q->nextFile==NULL && q->filename==tempfile->filename)
			{
				flag++;
			}
		}
		//�ж������һ���ļ��Ƿ���Ҫճ����ͬ��
		if(currentDir->fileptr->filename==tempfile->filename)
		{
			flag++;
		}

		if(!flag )
		{
			//���ڵ㽻��temp
			q->nextFile=new File();
			q->nextFile->fcreatetime=tempfile->fcreatetime;
			q->nextFile->filecontent=tempfile->filecontent;
			q->nextFile->filename=tempfile->filename;
			q->nextFile->filesize=tempfile->filesize;
			cout<<"�ļ�ճ���ɹ���"<<endl;

		}
		else
			cout<<"��ǰ�ļ��Ѵ���!"<<endl;
	}


	return 1;
}

//����Ŀ¼ 
int FileSystem::copyDir()   
{
	Dir *p=new Dir();
	cin>>p->dirname;
	int flag=0;

	if(currentDir->dirptr==NULL)
		cout<<"��ǰ·���²�����Ŀ¼!"<<endl;
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
			cout<<"Ŀ¼���Ƴɹ���"<<endl;
		else
			cout<<"������ָ��Ҫ���Ƶ�Ŀ¼!"<<endl;
	}
	return 1;
}

//ճ��Ŀ¼
int FileSystem::pasteDir()
{

	int flag=0;
	if(tempdir==NULL)
	{
		cout<<"�����ڸ���Ŀ¼������ճ��!"<<endl;
		return 0;
	}

	Dir *ptr=new Dir();
	ptr=currentDir;
	//���Բ��ܸ��Ƶ�����֧����֤����֧�����ڵ㶼����tempdir
	while(ptr!=NULL)
	{
	    //Ŀ�� current�İְֲ�����temp
		if(ptr->dirname==tempdir->dirname)
		{
			cout<<"��ֹ����Ŀ¼���Ƶ���Ŀ¼��!"<<endl;
			return 0;
		}
		//����
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
			//----�Լ����ֽ���
			//��current ptr��ptr��temp��ptr ������Ŀ¼�Խ�
			//��Ŀ¼��ʼλ�ÿ�ʼճ��
			currentDir->dirptr->dirptr=new Dir();
			currentDir->dirptr->dirptr->dircreatetime=tempdir->dirptr->dircreatetime;
			currentDir->dirptr->dirptr->dirname=tempdir->dirptr->dirname;
			currentDir->dirptr->dirptr->dirsize=tempdir->dirptr->dirsize;
			//���ļ�����
			currentDir->dirptr->dirptr->preDir=currentDir->dirptr;
			//��Ŀ¼
			pasteFileInDir(tempdir->dirptr->fileptr,currentDir->dirptr->dirptr);
			//��ǰ��������Ŀ���ַ
			SubPasteDir(tempdir->dirptr,currentDir->dirptr->dirptr);
		}
		cout<<"Ŀ¼ճ���ɹ���"<<endl;
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
			//�ж�����������һ��Ŀ¼�Ƿ���Ҫճ����ͬ��
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
				cout<<"ճ��Ŀ¼�ɹ�!"<<endl;
			}
		}
		else
			cout<<"��ǰĿ¼�Ѵ���!"<<endl;

	}

	return 1;
}

//ճ���Ӻ���  1�Ǹ����˵�Ŀ¼     2��Ҫ���Ƶ���Ŀ¼
int FileSystem::SubPasteDir(Dir *dir1,Dir *dir2)
{

	if(dir1->dirptr!=NULL)
	{
		dir2->dirptr=new Dir();
		dir2->dirptr->dircreatetime=dir1->dirptr->dircreatetime;
		dir2->dirptr->dirname=dir1->dirptr->dirname;
		dir2->dirptr->dirsize=dir1->dirptr->dirsize;
		dir2->dirptr->preDir=dir2;
		//�ļ�����
		pasteFileInDir(dir1->dirptr->fileptr,dir2->dirptr);
		//�ݹ�
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

//�޸��ļ�����
int FileSystem::filerw()
{
	time_t t=time(0);
	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y/%m/%d %X",localtime(&t));

	File *p=new File();
	cin>>p->filename;
	int flag=0;

	if(currentDir->fileptr==NULL)
		cout<<"�ļ�������!"<<endl;
	else
	{
		File *q=new File();
		q=currentDir->fileptr;
		while(q!=NULL)
		{
			if(q->filename==p->filename)
			{
 
				cout<<"0 ��д  |  1 ֻ��"<<endl;
				int flag1=0; 
				bool a;
				cin>>a;
				while(q->rw==a)
				{
					if(a==0) cout<<"���ļ���Ϊ�ɶ���д!"<<endl;
					if(a==1) cout<<"���ļ���Ϊֻ��!"<<endl;
					flag1=1;
					break; 
				}
                if(flag1==0){
				if(q->rw==false)
				{
					q->altertime=tmp;
					q->rw=a;
					cout<<"�ļ����޸�Ϊֻ��!"<<endl;
				}
				else
				{
					q->altertime=tmp;
					q->rw=a;
					cout<<"�ļ����޸�Ϊ�ɶ���д!"<<endl;
				}
                }
				flag++;
				break;
			}
			q=q->nextFile;
		}
		if(!flag)
			cout<<"������ָ��Ҫ�༭���ļ�!"<<endl;

	}
	return 1;
}