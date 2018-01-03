#include<iostream>
using namespace std;

#ifndef USER
#define USER 

class user{
  private:
    char username[9];
    char password[9];
    
  public:
    void reg();
    void login();
    void inter();
};

#endif