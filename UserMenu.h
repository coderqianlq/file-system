#ifndef USERMENU_H
#define USERMENU_H
#include "FileAndDir.h"

class UserMenu
{

public:
	UserMenu();
	~UserMenu();
	void Register();      //�û�ע�����
	void Login();         //�û���¼����
	void MainMenu();      //��ӭ������
	void FunctionMenu();  //���ܽ���
	void HelpWord();      //�����ĵ�	
};

#endif