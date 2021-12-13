#include<bits/stdc++.h>

using namespace std;
enum Expression {
    su, logout, register_, passwd, useradd, delete_,
    show, buy, select_, modify, import, report_myself, show_finance,
    report_finance, report_employee, log_, quit, exit_
};

class Invaild {
};

class People {
protected:

public:
    virtual void Su(string id, string pass_word);

    virtual void Su(string id);

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

int main() {
    string s;
    //initialze();
    cin >> s;
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