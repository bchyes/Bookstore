#ifndef MAIN_1_CPP_PEOPLENODE_H
#define MAIN_1_CPP_PEOPLENODE_H
class NodePeople {
public:
    char user_id[32];
    char user_name[32];
    char password[32];
    int priority;

    explicit NodePeople() {
        user_id[0] = '\0';
    }

    explicit NodePeople(std::string id, std::string name, std::string passwd, int prior) {
        strcpy(user_id, id.c_str());
        strcpy(user_name, name.c_str());
        strcpy(password, passwd.c_str());
        priority = prior;
    }

    friend bool operator>(const NodePeople &a, const NodePeople &b) {
        return (std::string(a.user_id) > std::string(b.user_id));
    }

    friend bool operator>=(const NodePeople &a, const NodePeople &b) {
        return (std::string(a.user_id) >= std::string(b.user_id));
    }

    friend bool operator==(const NodePeople &a, const NodePeople &b) {
        return (std::string(a.user_id) == std::string(b.user_id));
    }

    friend bool operator>=(const NodePeople &a, const std::string &b) {
        return (std::string(a.user_id) >= b);
    }

    friend bool operator==(const NodePeople &a, const std::string &b) {
        return (std::string(a.user_id) == b);
    }

    NodePeople &operator=(const NodePeople &nod) {
        if (this == &nod) return (*this);
        strcpy(this->user_id, nod.user_id);
        strcpy(this->user_name, nod.user_name);
        strcpy(this->password, nod.password);
        this->priority = nod.priority;
        return (*this);
    }

    friend std::ostream &operator<<(std::ostream &os, const NodePeople &nod) {
        os << std::string(nod.user_id) << " " << std::string(nod.user_name) << " " << std::string(nod.password) << " "
           << nod.priority
           << '\n';
        return os;
    }
};
#endif //MAIN_1_CPP_PEOPLENODE_H
