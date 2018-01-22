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

void UserMenu::MainMenu()  //欢迎界面
{
	UserMenu usermenu;     //用UserMenu类定义的类型
	string s;
	while (1)
	{
		
		system("cls");         //清屏函数
        cout<<"================================================"<<endl;
        cout<<"                   *请输入以下指令            \n"<<endl;  
        cout<<"                   login 用户登录               "<<endl;
        cout<<"                    exit 退出系统             \n"<<endl;
        cout<<"  学号:201427920214 姓名:钱立清 班级:软工1405   "<<endl;
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

void UserMenu::Login()//用户登录界面
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
			cout << "username：";
			cin >> username;
			if (username == "#BACKTOMAIN")
			{
				menu.MainMenu();
			}
			cout << "password：";
			cin >> password;
			if (password == "#BACKTOMAIN")
			{
				menu.MainMenu();
			}

		}
		ofstream out;//保存用
		out.open("G:\\username_login.txt");
		if (flag)
		{
			out << username << endl;
		}
		out.close();
		inFile.close();

	}

	Sleep(500);
	menu.FunctionMenu();//进入功能界面
}
void UserMenu::FunctionMenu()//功能界面
{
	FileSystem fs;
	UserMenu menu;
	string s;
	time_t t = time(0);      //创建目录时间
	char tmp[64];
	//strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));//存入系统时间
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
				//输出帮助文档
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

			//各指令使用方式
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
				//cout << "注 销(返回欢迎界面): logout " << endl;
			else if (s == "back+?")
				cout << "back: back" << endl;
			else if (s == "exit+?")
				cout << "exit: exit" << endl;
			//else if (s == "back+?")
				//cout << "返回上级菜单: back " << endl;
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
				cout << "找不到对应指令,请重新输入" << endl;
			}
			fs.display();
		}



	}
}

void UserMenu::HelpWord()//帮助文档
{
	cout<<"========================================================\n";
	cout<< "		mkdir		新建目录\n"
		<< "		rmdir		删除目录      \n"
		<< "		renamedir	重命名目录    \n"
		<< "		copydir		复制目录      \n"
		<< "		pastedir	粘贴目录      \n"
		<< "		ls		显示当前路径下的文件夹和文件\n"
		<< "		opendir		打开目录      \n"
		<< "		back	      返回上一级目录      \n"
		<< "		mk		新建文件\n"
		<< "		rm		删除文件\n"
		<< "		renamefile	重命名文件\n"
		<< "		copyfile	复制文件\n"
		<< "		pastefile	粘贴文件\n"
		<< "		read		打开文件\n"
		<< "		vi		编辑文件\n"
		<< "		alertfile	修改文件属性\n"
		<< "		clear		清屏\n"
		//<< "		cancel		注销\n"
		<< "		exit		退出      \n"
		//<< "		back		返回上一级菜单\n"
		<< "             软件工程1405班 钱立清 201427920214\n"; 
    cout<<"========================== ============================\n";
}

