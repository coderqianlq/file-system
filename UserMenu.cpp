#include"UserMenu.h"
#include"FileAndDir.h"
#include"FileSystem.h"
#include <windows.h>

UserMenu::UserMenu()
{

}
UserMenu::~UserMenu()
{

}

void UserMenu::MainMenu()  //��ӭ����
{
	UserMenu usermenu;     //��UserMenu�ඨ�������
	string s;
	while (1)
	{
		
		system("cls");         //��������
        cout<<"================================================"<<endl;
        cout<<"                   *����������ָ��            \n"<<endl;  
        cout<<"                   login �û���¼               "<<endl;
        cout<<"                    exit �˳�ϵͳ             \n"<<endl;
        cout<<"  ѧ��:201427920214 ����:Ǯ���� �༶:��1405   "<<endl;
        cout<<"======================= ========================"<<endl;
		cin >> s;
		if (s == "login")
		{
			usermenu.Login();
		}
		if (s == "exit")
		{
			exit(1);
		}
		else if (s == "version")
		{
			cout << "Version 1.0 Ding Chenguang 201326811305\nCopyright(C)dwightding.cn All rights reserve\n";
			system("pause");
		}
	}

}

void UserMenu::Login()//�û���¼����
{
	UserMenu menu;
	string username, password;
	string readusername, readpassword;
	int flag = 0;
	cin >> username;
	if (username == "#BACKTOMAIN")
	{
		menu.MainMenu();
	}
	cin >> password;
	if (password == "#BACKTOMAIN")
	{
		menu.MainMenu();
	}

	while (!flag)
	{
		ifstream inFile;
		inFile.open("G:\\user_info.txt");
		inFile >> readusername >> readpassword;
		while (!inFile.eof())
		{
			if (readusername == username && readpassword == password)
			{
		        system("cls");
				flag++;
				break;
			}
			else
			{
				inFile >> readusername >> readpassword;
			}
		}
		if (!flag)//flag==0
		{
			cout << "login error invalid username or password please try again" << endl;
			cout << "username��";
			cin >> username;
			if (username == "#BACKTOMAIN")
			{
				menu.MainMenu();
			}
			cout << "password��";
			cin >> password;
			if (password == "#BACKTOMAIN")
			{
				menu.MainMenu();
			}

		}
		ofstream out;//������
		out.open("G:\\username_login.txt");
		if (flag)
		{
			out << username << endl;
		}
		out.close();
		inFile.close();

	}

	Sleep(500);
	menu.FunctionMenu();//���빦�ܽ���
}
void UserMenu::FunctionMenu()//���ܽ���
{
	FileSystem fs;
	UserMenu menu;
	string s;
	time_t t = time(0);      //����Ŀ¼ʱ��
	char tmp[64];
	//strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));//����ϵͳʱ��
	//cout << "Welcome To FileSystem Powered By Ding Chenguang|" << tmp << endl;
	while (1)
	{
        
		fs.display();
		while (cin >> s)
		{
			if (s == "mkdir")
				fs.newDir();
			else if (s == "mk")
				fs.newFile();
			else if (s == "ls")
				fs.showDir();
			else if (s == "cd")
				fs.openDir();
			else if (s == "clear")
				system("cls");
			//else if (s == "logout")
				//menu.MainMenu();
			else if (s == "back")
				fs.goback();
			else if (s == "exit")
				exit(0);
			//else if (s == "back")
				//menu.FunctionMenu();
			else  if (s == "help" || s == "h")
			{
				//��������ĵ�
				menu.HelpWord();
				//menu.FunctionMenu();
			}
			else if (s == "rmdir")
				fs.deleteDir();
			else if (s == "rm")
				fs.deleteFile();
			else if (s == "renamedir")
				fs.renameDir();
			else if (s == "renamefile")
				fs.renameFile();
			else if (s == "read")
				fs.readFile();
			else if (s == "vi")
				fs.writeFile();
			else if (s == "copydir")
				fs.copyDir();
			else if (s == "pastedir")
				fs.pasteDir();
			else if (s == "copyfile")
				fs.copyFile();
			else if (s == "pastefile")
				fs.pasteFile();
			else if (s == "alterfile")
				fs.filerw();

			//��ָ��ʹ�÷�ʽ
			else if (s == "mkdir+?")
				cout << "mkdir: mkdir [dirname] (ex:madir dir)" << endl;
			else if (s == "mk+?")
				cout << "mk: [filename] (ex:mk file)" << endl;
			else if (s == "ls+?")
				cout << "ls: ls " << endl;
			else if (s == "cd+?")
				cout << "cd: cd [dirname] (ex:cd dir)" << endl;
			else if (s == "cls+?")
				cout << "cls: cls" << endl;
			//else if (s == "logout+?")
				//cout << "ע ��(���ػ�ӭ����): logout " << endl;
			else if (s == "back+?")
				cout << "back: back" << endl;
			else if (s == "exit+?")
				cout << "exit: exit" << endl;
			//else if (s == "back+?")
				//cout << "�����ϼ��˵�: back " << endl;
			else if (s == "help+?")
				cout << "help: help/h" << endl;
			else if (s == "rmdir+?")
				cout << "rmdir: rmdir [dirname] (ex:rmdir dir)" << endl;
			else if (s == "rm+?")
				cout << "rm: rm [filename] (ex:rm file)" << endl;
			else if (s == "renamedir+?")
				cout << "renamedir: renamedir [olddiranme] [newdirname] (ex:renamedir odir ndir)" << endl;
			else if (s == "renamefile+?")
				cout << "renamefile: renamefile [oldfile] [newfile] (ex:renamefile ofile nfile)" << endl;

			else if (s == "read+?")
				cout << "read: read [filename] (ex:read file)" << endl;
			else if (s == "vi+?")
				cout << "vi: vi [filename] [content] (ex:vi file content)" << endl;

			else if (s == "copydir+?")
				cout << "copydir: copydir [dirname] (ex:copydir dir)" << endl;
			else if (s == "pastedir+?")
				cout << "pastedir: pastedir " << endl;
			else if (s == "copyfile+?")
				cout << "copyfile: copyfile [filename] (ex:copyfile file)" << endl;
			else if (s == "pastfile+?")
				cout << "pastfile: pastfile " << endl;
			else if (s == "alterfile+?")
				cout << "alterfile: alterfile [filename]  (ex:alterfile file)" << endl;
			else
			{
				cout << "�Ҳ�����Ӧָ��,����������" << endl;
			}
			fs.display();
		}



	}
}

void UserMenu::HelpWord()//�����ĵ�
{
	cout<<"========================================================\n";
	cout<< "		mkdir		�½�Ŀ¼\n"
		<< "		rmdir		ɾ��Ŀ¼      \n"
		<< "		renamedir	������Ŀ¼    \n"
		<< "		copydir		����Ŀ¼      \n"
		<< "		pastedir	ճ��Ŀ¼      \n"
		<< "		ls		��ʾ��ǰ·���µ��ļ��к��ļ�\n"
		<< "		opendir		��Ŀ¼      \n"
		<< "		back	      ������һ��Ŀ¼      \n"
		<< "		mk		�½��ļ�\n"
		<< "		rm		ɾ���ļ�\n"
		<< "		renamefile	�������ļ�\n"
		<< "		copyfile	�����ļ�\n"
		<< "		pastefile	ճ���ļ�\n"
		<< "		read		���ļ�\n"
		<< "		vi		�༭�ļ�\n"
		<< "		alertfile	�޸��ļ�����\n"
		<< "		clear		����\n"
		//<< "		cancel		ע��\n"
		<< "		exit		�˳�      \n"
		//<< "		back		������һ���˵�\n"
		<< "             �������1405�� Ǯ���� 201427920214\n"; 
    cout<<"========================== ============================\n";
}

