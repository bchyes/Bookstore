#include"PeopleNode.h"
NodePeople::NodePeople() {
    user_id[0] = '\0';
}

NodePeople::NodePeople(std::string id, std::string name, std::string passwd, int prior) {
    strcpy(user_id, id.c_str());
    strcpy(user_name, name.c_str());
    strcpy(password, passwd.c_str());
    priority = prior;
}

bool operator>(const NodePeople &a, const NodePeople &b) {
    return (std::string(a.user_id) > std::string(b.user_id));
}

bool operator>=(const NodePeople &a, const NodePeople &b) {
    return (std::string(a.user_id) >= std::string(b.user_id));
}

bool operator==(const NodePeople &a, const NodePeople &b) {
    return (std::string(a.user_id) == std::string(b.user_id));
}

bool operator>=(const NodePeople &a, const std::string &b) {
    return (std::string(a.user_id) >= b);
}

bool operator==(const NodePeople &a, const std::string &b) {
    return (std::string(a.user_id) == b);
}

NodePeople &NodePeople::operator=(const NodePeople &nod) {
    if (this == &nod) return (*this);
    strcpy(this->user_id, nod.user_id);
    strcpy(this->user_name, nod.user_name);
    strcpy(this->password, nod.password);
    this->priority = nod.priority;
    return (*this);
}

std::ostream &operator<<(std::ostream &os, const NodePeople &nod) {
    os << std::string(nod.user_id) << " " << std::string(nod.user_name) << " " << std::string(nod.password) << " "
       << nod.priority
       << '\n';
    return os;
}