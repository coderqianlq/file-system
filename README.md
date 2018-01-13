# FileSystem
## 实验目的
    本次实训的总体目的在于通过系统的编程训练，培养学生编写一个具有一定难度的小型系统的能力，培养学生从编写单个程序，实现单个程序功
    能到进行系统开发，整体调试的能力。从知识点的角度来说，目的在于通过本实训项目，让学生对链表或二叉树这一重要数据结构的运用更加熟
    练。 
## 实验内容
    本次实验的题目是多级文件目录管理系统。要求利用数据结构的知识，采用链表的形式或通过将树转换为二叉树的概念，采用孩子兄弟二叉树的
    方式实现文件目录系统。每个树节点表示一个文件（包括目录文件），成员基本信息可包含，文件名、文件属性、文件内容等信息(具体属性自
    己确定)。
## 知识概要
    文件系统是操作系统用于明确存储设备或分区上的文件的方法和数据结构，即在存储设备上组织文件的方法。操作系统中负责管理和存储文件信
    息的软件机构称为文件管理系统，简称文件系统。文件系统由三部分组成：文件系统的接口，对对象操纵和管理的软件集合，对象及属性。从系
    统角度来看，文件系统是对文件存储设备的空间进行组织和分配，负责文件存储并对存入的文件进行保护和检索的系统。具体地说，它负责为用
    户建立文件，存入、读出、修改、转储文件，控制文件的存取，当用户不再使用时刪除文件等。
## 实验要求
    开发工具：word，vc，win32api
    1．设计和实现一个模拟文件系统，要求包括目录、普通文件和文件的存储。必须有自定义的数据结构，不能直接调用windows 的API函数，即
    不能只实现了一个壳。
    2．文件系统的目录结构采用类似Linux的树状结构。
    3．要求模拟的操作包括：
      a) 目录的添加、删除、重命名；
      b) 目录的显示（列表）；
      c) 文件的添加、删除、重命名；
      d) 文件和目录的拷贝；
      e) 文件的读写操作。
    4．用户进入时显示可用命令列表；用户输入help时显示所有命令的帮助文档； 输入某个命令+？时显示该条命令的使用说明。
    5．用户输入exit时退出该系统。
    6．实验实现基于windows平台。
    7．实验开发语言必须选用C/C++，不能选用JAVA。
## 实验建模
    系统流程涉及整个文件系统的操作以及运行的流程，用户可以输入help查看所有命令的帮助文档。
## 设计分析
    1. 存储结构
    采用二叉链表存储方式，即以二叉链表作树的存储结构。链表中节点的两个链域分别指向该节点的第一个孩子结点和下一个兄弟节点，节点可以
    表示目录或文件，目录下面允许有节点，文件下面不允许有其它节点。
    2. 基于二叉表的操作：新建、删除和显示等
      2.1 新建
      传递上级目录节点(父节点)，找到对应子节点为止。
      2.2 删除(销毁)
      单个文件，直接删除节点，释放内存； 
      单个目录，采取简单的删除策略，无论目录下是否有子目录或者文件，都直接删除该目录。
    3. 操作指令
      3.1 用户指令
      3.2 文件、目录指令
## 设计方案与数据结构
**用户界面模块**
```c++
 class user{
 private:
  char username[9];
  char password[9]; 
 public:
  void reg();
  void login();
  void inter();
 };
```
**文件模块**
```c++
class file   
 {   
  private:  
    int size;  	                      //文件大小
    char *text;                        //文件内容

  public:  
    char filename[9];                  //文件名
    bool rw;                         //文件属性
    string fcreatetime;                 //创建文件时间
    file *next;                        
    file();                            //构造函数
    void editfile();                     //编辑文件内容
    char *getfilename()                 //返回文件名
    {
      return filename;
    }  
    void show_text()                   //显示文件信息
    {
      return text;
    }  
    int getsize()                       //返回大小
    {       
      return size;
    }   
    ~file()                            //析构函数
    {
      delete text;
    }
}; 
```
**目录模块**
```c++
class directory  
{ 
  private:  
    char dirname[9];                    //目录名

  public:  
    file  *pfile;          
    directory *nextdir,*subdir,*fatherdir;    //子节点、兄弟节点、父节点
    directory(char *dname)               //复制构造函数
    { 
      strcpy(dirname,dname);
      pfile=NULL;
    }  
    directory()                          //构造函数
    {  
      pfile=NULL;
      cin>>dirname; 
    }  
    void creatfile();                      //创建文件 
    void deletefile();                     //删除文件
    void showfile();                      //显示文件内容
    void renamefile();                    //重命名文件
    void copyfile();                      //复制文件
    void pastefile();                     //粘贴文件
    char *getdname()                    //返回目录名
    {     
      return dirname;
    }  
    ~directory()                         //析构函数
    {
      delete pfile;
    }
};  
```
**主模块**
```c++
class dirmanager { 
  public:   
    void manager();                      //显示界面
    void addnew();                       //新建目录
    void copydir();                       //复制目录
    void pastedir();                       //粘贴目录
    void renamedir();                     //重命名目录
    void cdsubdir();                       //进入子目录
    void showdir();                       //显示目录信息
    void showdirinfor();                   //显示目录、文件信息
    void help();                          //指令帮助文档
    ~dirmanager()                        //析构函数
    {
      delete root;
    } 

  private:  
    directory *root,*p,*p1,*p2;              //定义根目录节点
    directory *dir[10];                     //定义目录的大小
}; 
```
## 实验结果与截图
    略
