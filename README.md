

# Bookstore

> 包晨豪

## 文件储存

所有账户与所有图书

每个员工的操作

财务信息 所有员工的操作 日志类

## 代码文件结构

main函数

```c++
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
public:
    virtual void Su(string id, string pass_word);

    virtual void Logout();

    virtual void Register(string id, string pass_word, string user_name);

    virtual void Passwd(string id, string old_passwd, string new_passed);

    virtual void Useradd(string id, string pass_word, int priority, string user_name);

    virtual void Delete(string id);

    virtual void Show(string isbn, string name, string author, string keyword);

    virtual void Buy(string isbn, int quantity);

    virtual void Select(string isbn);

    virtual void Modify(string isbn, string name, string author, string keyword, double price);

    virtual void Import(int quantity, double cost);

    virtual void ReportMyself();

    virtual void ShowFinance(int time);

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

    virtual void Logout();//退出栈

    virtual void Register(string id, string pass_word, string user_name);//以块链维护账户信息

    virtual void Passwd(string id, string old_passwd, string new_passed);//通过块链找到账户信息

    virtual void Useradd(string id, string pass_word, int priority, string user_name);//以块链维护账户信息

    virtual void Delete(string id);//先通过栈寻找是否登陆，再通过块链删除

    virtual void Show(string isbn, string name, string author, string keyword);//图书信息由另一个文件的块链储存

    virtual void Buy(string isbn, int quantity);//通过块链找到信息并修改

    virtual void Select(string isbn);//通过块链找到信息，同时在该类中记录选中的图书

    virtual void Modify(string isbn, string name, string author, string keyword, double price);//通过记录的信息在块链中修改

    virtual void Import(int quantity, double cost);//通过记录的信息在块链中修改

    virtual void ReportMyself();//每一个员工包含一个ASCLL文件信息，在每一次的操作后记录信息于文件之中

    virtual void ShowFinance(int time);

    virtual void ReportFinance();

    virtual void ReportEmployee();

    virtual void Log();//以上三个操作均存一个不同的ASCLL文件
```



