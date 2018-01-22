#ifndef USERMENU_H
#define USERMENU_H
#include "FileAndDir.h"

class UserMenu
{

public:
	UserMenu();
	~UserMenu();
	void Register();      //用户注册界面
	void Login();         //用户登录界面
	void MainMenu();      //欢迎主界面
	void FunctionMenu();  //功能界面
	void HelpWord();      //帮助文档	
};

#endif