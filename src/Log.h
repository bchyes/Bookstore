#ifndef MAIN_1_CPP_LOG_H
#define MAIN_1_CPP_LOG_H

#include"BookNode.h"
#include"PeopleNode.h"
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

class EmployeeLog {
public:
    char type[22];
    int time;
    char name[62];
    int priority;
    NodePeople people_last;
    NodePeople people_new;
    NodeBook book_last;
    NodeBook book_new;
    double finance;

    explicit EmployeeLog();

    EmployeeLog(const EmployeeLog &nod);

    bool operator>(const EmployeeLog &b);

    bool operator>=(const EmployeeLog &b);

    bool operator==(const EmployeeLog &b);

    bool operator>=(const std::string &b);

    bool operator>(const std::string &b);

    bool operator==(const std::string &b);

    EmployeeLog &operator=(const EmployeeLog &nod);

    void InsertPeopleLast(const NodePeople &peo) {
        people_last = peo;
    }

    void InsertPeopleNew(const NodePeople &peo) {
        people_new = peo;
    }

    void InsertBookLast(const NodeBook &book) {
        book_last = book;
    }

    void InsertBookNew(const NodeBook &book) {
        book_new = book;
    }

    void PrintPeopleTitle(std::fstream &report);

    void PrintBookTitle(std::fstream &report);

    void PrintPeopleLast(std::fstream &report);

    void PrintPeopleNew(std::fstream &report);

    void PrintBookLast(std::fstream &report);

    void PrintBookNew(std::fstream &report);
};

#endif //MAIN_1_CPP_LOG_H
