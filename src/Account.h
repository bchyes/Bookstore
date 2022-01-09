#ifndef MAIN_1_CPP_BaseAccount_H
#define MAIN_1_CPP_BaseAccount_H

#include "PeopleNode.h"
#include "BookNode.h"
#include "Store.h"
#include "Log.h"
#include "exception.h"
#include "OperationFunction.h"
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

extern std::vector<NodePeople> stk;
extern std::vector<NodeBook> stk_;
extern Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file_people;
extern Store<NodeIndex_<NodeBook>, Block_<NodeBook>> file_book;
extern Store<NodeIndex_<NodeBookName>, Block_<NodeBookName>> file_name;
extern Store<NodeIndex_<NodeBookAuthor>, Block_<NodeBookAuthor>> file_author;
extern Store<NodeIndex_<NodeBookKeyword>, Block_<NodeBookKeyword>> file_keyword;
extern Store<NodeIndex_<EmployeeLog>, Block_<EmployeeLog>> file_employee;

struct ShowMessage {
    char isbn[22];
    char book_name[62];
    char author[62];
    char keyword[62];

    ShowMessage() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
    }
};

class BaseAccount {
public:
    NodeBook select;

    virtual ~BaseAccount();

    virtual void Initialize();

    virtual void Su(std::string id, std::string password);

    virtual void Su(std::string id);

    virtual void Logout();

    virtual void GetSelect();

    virtual void Register(std::string id, std::string password, std::string user_name);

    virtual void Passwd(std::string id, std::string old_passwd, std::string new_passwd);

    virtual void Passwd(std::string id, std::string new_passwd);

    virtual void Useradd(std::string id, std::string password, int priority, std::string user_name);

    virtual void Delete(std::string id);

    virtual void Show(ShowMessage infor);

    virtual void Buy(std::string isbn, int quantity);

    virtual void Select(std::string isbn);

    virtual void ModifyIsbn(std::string isbn);

    virtual void ModifyName(std::string name);

    virtual void ModifyAuthor(std::string author);

    virtual void ModifyKeyword(std::string keyword);

    virtual void ModifyPrice(double price);

    virtual void Import(int quantity, double cost);

    virtual void AddMessage(const EmployeeLog &employee);

    virtual void Report(Block_<EmployeeLog> employee, std::fstream &report, int i);

    virtual void ReportForFinance(Block_<EmployeeLog> employee, std::fstream &report, int i);

    virtual void ReportMyself();

    void FinanceInsert(double finance);

    virtual void ShowFinance(int time);

    virtual void ShowFinance();

    virtual void ReportFinance();

    virtual void ReportEmployee();

    virtual void Log();
};

class Manager : public BaseAccount {
public:
};

class Employee : public BaseAccount {
public:
    virtual void Passwd(std::string id, std::string new_passwd) {
        throw Invalid();
    }

    virtual void Delete(std::string id) {
        throw Invalid();
    }

    virtual void ShowFinance(int time) {
        throw Invalid();
    }

    virtual void ShowFinance() {
        throw Invalid();
    }

    virtual void ReportFinance() {
        return;
    }

    virtual void ReportEmployee() {
        return;
    }

    virtual void Log() {
        return;
    }
};

class Consumer : public BaseAccount {
public:
    virtual void Passwd(std::string id, std::string new_passwd) {
        throw Invalid();
    }

    virtual void Useradd(std::string id, std::string pass_word, int priority, std::string user_name) {
        throw Invalid();
    }

    virtual void Delete(std::string id) {
        throw Invalid();
    }

    virtual void Select(std::string isbn) {
        throw Invalid();
    }

    virtual void ModifyIsbn(std::string isbn) {
        throw Invalid();
    }

    virtual void ModifyName(std::string name) {
        throw Invalid();
    }

    virtual void ModifyAuthor(std::string author) {
        throw Invalid();
    }

    virtual void ModifyKeyword(std::string keyword) {
        throw Invalid();
    }

    virtual void ModifyPrice(double price) {
        throw Invalid();
    }

    virtual void Import(int quantity, double cost) {
        throw Invalid();
    }

    virtual void ReportMyself() {
        return;
    }

    virtual void ShowFinance(int time) {
        throw Invalid();
    }

    virtual void ShowFinance() {
        throw Invalid();
    }

    virtual void ReportFinance() {
        return;
    }

    virtual void ReportEmployee() {
        return;
    }

    virtual void Log() {
        return;
    }
};

class Visitor : public BaseAccount {
public:
    virtual void Logout() {
        throw Invalid();
    }

    virtual void Passwd(std::string id, std::string old_passwd, std::string new_passed) {
        throw Invalid();
    }

    virtual void Passwd(std::string id, std::string new_passwd) {
        throw Invalid();
    }

    virtual void Useradd(std::string id, std::string pass_word, int priority, std::string user_name) {
        throw Invalid();
    }

    virtual void Delete(std::string id) {
        throw Invalid();
    }

    virtual void Show(ShowMessage infor) {
        throw Invalid();
    }

    virtual void Buy(std::string isbn, int quantity) {
        throw Invalid();
    }

    virtual void Select(std::string isbn) {
        throw Invalid();
    }

    virtual void ModifyIsbn(std::string isbn) {
        throw Invalid();
    }

    virtual void ModifyName(std::string name) {
        throw Invalid();
    }

    virtual void ModifyAuthor(std::string author) {
        throw Invalid();
    }

    virtual void ModifyKeyword(std::string keyword) {
        throw Invalid();
    }

    virtual void ModifyPrice(double price) {
        throw Invalid();
    }

    virtual void Import(int quantity, double cost) {
        throw Invalid();
    }

    virtual void ReportMyself() {
        return;
    }

    virtual void ShowFinance(int time) {
        throw Invalid();
    }

    virtual void ShowFinance() {
        throw Invalid();
    }

    virtual void ReportFinance() {
        return;
    }

    virtual void ReportEmployee() {
        return;
    }

    virtual void Log() {
        return;
    }
};

#endif //MAIN_1_CPP_BaseAccount_H
