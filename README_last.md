# Bookstore

> 包晨豪

## 文件储存

所有账户与所有图书 均以二进制文件储存，并用块状链表维护

财务收支用二进制，顺序储存

所有员工的操作 以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

财务信息 日志类 以ASCLL文件直接储存

## 代码文件结构

main函数

```C++
int main() {
   
    char *command;
    while (running) {
        std::string s;
        if (getline(std::cin, s)) {
                JudgeConditionAndRunCommand(s);
            }
        } else exit(0);
    }
    delete command;
    return 0;
}

```

```C++
string token;
        token = Get(s);
 People *account = new Visitor;
    account->Initialize();
        if (token == "su") {
          
        } else if (token == "logout") {
            
        } else if (token == "useradd") {
           
        } else if (token == "register") {
           
        } else if (token == "delete") {
           
        } else if (token == "passwd") {
           
        } else if (token == "select") {
            
        } else if (token == "show") {
          
        } else if (token == "buy") {
            
        } else if (token == "modify") {
           
        } else if (token == "import") {
           
        } else if (token == "exit") {
            
        } else if (token == "quit") {
           
        }
    }
    delete account;
}
```

通过如上的算法来调用指令

## 接口与成员说明

账户与图书系统

```c++
struct bookInfo {
    char name[70];
    char author[70];
    char ISBN[30];
    char keyword[70][70];
    int number = 0;
    double price = 0;
};
class book {
public:
    bookInfo info;

    book();

};
class People {

};

class Manager : public People {

};

class Employee : public People {

};

class Custom : public People {

};

class Visitor : public People {

};
```

定义如上的类

将功能的实现写于People中，任何main函数的指令通过People进行调用

## 具体算法说明

```C++
public:
    People();

    ~People();//析构账号的时候，如果还有修改没写进文件就写进去

     virtual initialize();

   virtual accountInfo GetInfo() = 0;

    virtual void InputInfo(accountInfo &tmp) = 0;


    virtual void Su(char *id, char *pass_word) = 0;//密码不对就抛出异常，否则存入vector

     virtual void Logout() {//vector pop_back

     virtual void Register(char *id, char *pass_word, char *user_name) = 0;//用insert存进文件（文件里如果重名就要throw）

    virtual void Passwd(char *id, char *passwd1, char *passwd2) = 0;//通过块链找到账户信息

    virtual void Useradd(char *id, char *pass_word, int priority, char *user_name) = 0;//以块链维护账户信息

    virtual void Delete(char *id) = 0;//先find找到，再delete，再insert（文件里如果重名就要throw）//遍历vector，若在登陆栈，则throw

    virtual void Show(char *isbn, char *name, char *author, char *keyword) = 0;//图书信息由另一个文件的块链储存

    virtual void Buy(char *isbn, int quantity) = 0;//通过块链找到信息并修改

    virtual void Select(char *isbn) = 0;//将上次select的存进所有文件中，共四个文件，再将select从文件中读出来

    virtual void Modify(char *isbn, char *name, char *author, char *keyword, double price) = 0;//修改ISBN，不能修改成已有的或是自己
    virtual void Import(int quantity, double cost) = 0;//通过记录的信息在块链中修改

    virtual void ReportMyself() = 0;//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    virtual void ShowFinance(int time) = 0;//finance 存进一个文件，开头存笔数，之后每次交易收入就是正，支出就是负，show就将最后time笔读出来加起来

    virtual void ShowFinance() = 0;

    virtual void ReportFinance() = 0;

    virtual void ReportEmployee() = 0;

    virtual void Log() = 0;
```

在派生类中实现没有权限就输出异常

## 块状链表

```C++
bool compare_char(const char *lhs, const char *rhs);
class BlockList {
    std::string FileName;
    long Start = 0;
public:
    struct Block {
        int CurrentSize = 0;
        const int MaxSize = 5000;
        char first_array[5000][length];
        int second_array[5000]; //maybe you need bigger array, to do
        char MaxValue[length];
        char MinValue[length];
        long Next = -100000;
        long MyLocation = -100000;
    };

    BlockList(const std::string &fn) : FileName(fn) {};

    void InsertPair(char *first_, int second_);

    void DeletePair(char *first_, int second_);

    int FindPairs(char *first_);

    std::vector<int> FindAllPairs(char *first_);

    void ShowAllBooks();

};

```



## 日志系统

report myself输出形式

name:

------------------------------------//分割线

|did XXX|

|did XX|

......

report finance

|did XXX cost XXX |··

|did XXX earn XXX|

......

report employee

|XXX did XXX|

......

log

同上述输出