

# Bookstore

> 包晨豪

## 文件储存

所有账户与所有图书 均以二进制文件储存，并用块状链表维护

所有员工的操作 以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

财务信息 日志类 以ASCLL文件直接储存

## 代码文件结构

main函数

```c++
stack<NodePeople> log_in;//登陆栈
enum Expression {
    su, logout, register_, passwd, useradd, delete_,
    show, buy, select_, modify, import, report_myself, show_finance,
    report_finance, report_employee, log_, quit, exit_
};
Expression GetOrder(string s) {
    if (s == "su") return su;
    if (s == "logout") return logout;
    if (s == "register") return register_;
    if (s == "passwd") return passwd;
    if (s == "useradd") return useradd;
    if (s == "delete") return delete_;
    if (s == "show") return show;
    if (s == "buy") return buy;
    if (s == "select") return select_;
    if (s == "modify") return modify;
    if (s == "import") return import;
    if (s == "report myself") return report_myself;
    if (s == "show finance") return show_finance;
    if (s == "report finance") return report_finance;
    if (s == "report employee") return report_employee;
    if (s == "log") return log_;
    if (s == "quit") return quit;
    if (s == "exit") return exit_;
}
int main(){
    Expression exp = GetOrder(s);
    switch (exp) {
        case su:
            break;
        case logout:
            break;
        case register_:
            break;
        case passwd:
            break;
        case useradd:
            break;
        case delete_:
            break;
        case show:
            break;
        case buy:
            break;
        case select_:
            break;
        case modify:
            break;
        case import:
            break;
        case report_myself:
            break;
        case show_finance:
            break;
        case report_finance:
            break;
        case report_employee:
            break;
        case log_:
            break;
        case quit:
            break;
        case exit_:
            break;
    }
}
```

通过如上的算法来调用指令

## 接口与成员说明

账户与图书系统

```c++
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

将功能的实现写于People中

在派生类中实现没有权限就抛出异常

```c++
class Invaild{};
class People {
    virtual void Su(string id,string pass_word);
};

class Visitor : public People {
public:
    virtual void Su(string id,string pass_word){
        throw Invaild();
    }
};
```

任何main函数的指令通过People进行调用

```c++
class People {
protected:
    fstream file_people;//操作账户文件
    fstream file_book;//操作图书文件
    fstream file_index_people;//操作账户索引
    fstream file_index_book;//操作图书索引
    NodeIndexPeople idx_people;//读取账户索引
    NodeIndexBook idx_book;//读取图书索引
    BlockPeople blo_people;//读取账户信息
    BlockBook blo_book;//读取图书信息
    fstream file_operator;//写出员工的操作
    fstream file_finance;//写出财务的记录
    fstream file_finance_math;//以数字的形式写出财务记录，在文件的开头记录交易笔数
    fstream file_diary;//写出日志
public:
    virtual void Su(string id, string pass_word);

    virtual void Su(string id);//特殊处理虚函数

    virtual void Logout();

    virtual void Register(string id, string pass_word, string user_name);

    virtual void Passwd(string id, string old_passwd, string new_passed);

    virtual void Useradd(string id, string pass_word, int priority, string user_name);

    virtual void Delete(string id);

    virtual void Show(string isbn, string name, string author, string keyword);

    virtual void Show();

    virtual void Buy(string isbn, int quantity);

    virtual void Select(string isbn);

    virtual void Modify(string isbn, string name, string author, string keyword, double price);

    virtual void Import(int quantity, double cost);

    virtual void ReportMyself();

    virtual void ShowFinance(int time);

    virtual void ShowFinance();

    virtual void ReportFinance();

    virtual void ReportEmployee();

    virtual void Log();
};

class Manager : public People {
public:
};

class Employee : public People {
public:
    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void ShowFinance(int time) {
        throw Invaild();
    }
    virtual void ShowFinance() {
        throw Invaild();
    }

    virtual void ReportFinance() {
        throw Invaild();
    }

    virtual void ReportEmployee() {
        throw Invaild();
    }

    virtual void Log() {
        throw Invaild();
    }
};

class Custom : public People {
public:
    virtual void Useradd(string id, string pass_word, int priority, string user_name) {
        throw Invaild();
    }

    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void Select(string isbn) {
        throw Invaild();
    }

    virtual void Modify(string isbn, string name, string author, string keyword, double price) {
        throw Invaild();
    }

    virtual void Import(int quantity, double cost) {
        throw Invaild();
    }

    virtual void ReportMyself() {
        throw Invaild();
    }

    virtual void ShowFinance(int time) {
        throw Invaild();
    }
    virtual void ShowFinance() {
        throw Invaild();
    }
    virtual void ReportFinance() {
        throw Invaild();
    }

    virtual void ReportEmployee() {
        throw Invaild();
    }

    virtual void Log() {
        throw Invaild();
    }
};

class Visitor : public People {
public:
    virtual void Su(string id, string pass_word) {
        throw Invaild();
    }

    virtual void Passwd(string id, string old_passwd, string new_passed) {
        throw Invaild();
    }

    virtual void Useradd(string id, string pass_word, int priority, string user_name) {
        throw Invaild();
    }

    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void Show(string isbn, string name, string author, string keyword) {
        throw Invaild();
    }
    virtual void Show(){
        throw Invaild();
    }

    virtual void Buy(string isbn, int quantity) {
        throw Invaild();
    }

    virtual void Select(string isbn) {
        throw Invaild();
    }

    virtual void Modify(string isbn, string name, string author, string keyword, double price) {
        throw Invaild();
    }

    virtual void Import(int quantity, double cost) {
        throw Invaild();
    }

    virtual void ReportMyself() {
        throw Invaild();
    }

    virtual void ShowFinance(int time) {
        throw Invaild();
    }
    virtual void ShowFinance() {
        throw Invaild();
    }

    virtual void ReportFinance() {
        throw Invaild();
    }

    virtual void ReportEmployee() {
        throw Invaild();
    }

    virtual void Log() {
        throw Invaild();
    }
};
```

## 具体算法说明

```c++
    virtual void Su(string id, string pass_word);//以栈来维护，登入账号推入栈
    
    virtual void Su(string id);//特殊处理

    virtual void Logout();//退出栈

    virtual void Register(string id, string pass_word, string user_name);//以块链维护账户信息

    virtual void Passwd(string id, string old_passwd, string new_passed);//通过块链找到账户信息

    virtual void Useradd(string id, string pass_word, int priority, string user_name);//以块链维护账户信息

    virtual void Delete(string id);//先通过栈寻找是否登陆，再通过块链删除

    virtual void Show(string isbn, string name, string author, string keyword);//图书信息由另一个文件的块链储存

    virtual void Show();

    virtual void Buy(string isbn, int quantity);//通过块链找到信息并修改

    virtual void Select(string isbn);//通过块链找到信息，同时在该类中记录选中的图书

    virtual void Modify(string isbn, string name, string author, string keyword, double price);//通过记录的信息在块链中修改

    virtual void Import(int quantity, double cost);//通过记录的信息在块链中修改

    virtual void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    virtual void ShowFinance(int time);

    virtual void ShowFinance();

    virtual void ReportFinance();

    virtual void ReportEmployee();

    virtual void Log();//以上三个操作均存一个不同的ASCLL文件
```

## 块状链表

```c++
struct NodePeople {
    char user_id[32];
    char password[32];
    int priority;
};//人节点，储存信息
struct NodeBook{
    char isbn[22];
    char book_name[62];
    char author[62];
    char keyword[62];
    int quantity;
    double price;
};//书节点，储存信息
struct BlockPeople {
    static const int maxn = 320;//一个块记录的节点个数最大值
    NodePeople size[maxn + 2];
    int now = 0;//现在块中储存的节点的个数
};//为块状链表中的块
struct NodeIndexPeople {
    long long next = -1;//记录索引下一个在索引文件中的位置
    NodePeople end;//记录对应的块的最后一个节点
    long long block_begin = 0;//记录对应的块在文件中的位置
};//块状链表的索引
struct BlockBook {
    static const int maxn = 320;//一个块记录的节点个数最大值
    NodeBook size[maxn + 2];
    int now = 0;//现在块中储存的节点的个数
};//为块状链表中的块
struct NodeIndexBook {
    long long next = -1;//记录索引下一个在索引文件中的位置
    NodeBook end;//记录对应的块的最后一个节点
    long long block_begin = 0;//记录对应的块在文件中的位置
};//块状链表的索引
struct Operator{
    char message[502];
    long long next;//记录下一个同一员工的操作
};//记录每一次员工的操作
struct Finance{
    char message[502];
};//财务记录
struct FinanceMath{
  double money;  
};//用于财务的查询
struct diary{
  char message[502];  
};//用于日志指令
```

## 日志系统

report myself输出形式

name:

|did XXX|

|did XX|

......

report finance

|cost XXX to did XXX|

|earn XXX from did XXX|

......

report employee

|XXX did XXX|

......

log

同上述输出
