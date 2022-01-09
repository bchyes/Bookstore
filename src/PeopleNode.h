#ifndef MAIN_1_CPP_PEOPLENODE_H
#define MAIN_1_CPP_PEOPLENODE_H

#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

//账号的节点
class NodePeople {
public:
    char user_id[32];
    char user_name[32];
    char password[32];
    int priority;

    explicit NodePeople();

    explicit NodePeople(std::string id, std::string name, std::string passwd, int prior);

    friend bool operator>(const NodePeople &a, const NodePeople &b);

    friend bool operator>=(const NodePeople &a, const NodePeople &b);

    friend bool operator==(const NodePeople &a, const NodePeople &b);

    friend bool operator>=(const NodePeople &a, const std::string &b);

    friend bool operator==(const NodePeople &a, const std::string &b);

    NodePeople &operator=(const NodePeople &nod);

    friend std::ostream &operator<<(std::ostream &os, const NodePeople &nod);
};
#endif //MAIN_1_CPP_PEOPLENODE_H
