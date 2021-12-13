#include"store_template.h"

class NodePeople {
public:
    char user_id[32];
    char user_name[32];
    char password[32];
    int priority;

    NodePeople() {
        user_id[0] = '\0';
    }

    NodePeople(string id, string name, string passwd, int prior) {
        strcpy(user_id, id.c_str());
        strcpy(user_name, name.c_str());
        strcpy(password, passwd.c_str());
        priority = prior;
    }

    friend bool operator>(const NodePeople &a, const NodePeople &b) {
        return (string(a.user_id) > string(b.user_id));
    }

    friend bool operator>=(const NodePeople &a, const NodePeople &b) {
        return (string(a.user_id) >= string(b.user_id));
    }

    friend bool operator==(const NodePeople &a, const NodePeople &b) {
        return (string(a.user_id) == string(b.user_id));
    }

    friend bool operator>=(const NodePeople &a, const string &b) {
        return (string(a.user_id) >= b);
    }

    friend bool operator==(const NodePeople &a, const string &b) {
        return (string(a.user_id) == b);
    }

    NodePeople &operator=(const NodePeople &nod) {
        strcpy(this->user_id, nod.user_id);
        strcpy(this->user_name, nod.user_name);
        strcpy(this->password, nod.password);
        this->priority = nod.priority;
        return (*this);
    }

    friend ostream &operator<<(ostream &os, const NodePeople &nod) {
        os << string(nod.user_id) << " " << string(nod.user_name) << " " << string(nod.password) << " " << nod.priority
           << '\n';
        return os;
    }
};

int main() {
    int n;
    cin >> n;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        if (s == "insert") {
            string id, name, passwd;
            int prior;
            cin >> id >> name >> passwd >> prior;
            Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file;
            NodePeople nod(id, name, passwd, prior);
            file.Insert(nod);
        } else if (s == "find") {
            string id;
            cin >> id;
            Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file;
            try {
                NodePeople nod = file.Find<NodePeople>(id);
                cout << nod;
            } catch (Invaild) { cout << "NO" << '\n'; }
        } else if (s == "delete") {
            string id;
            cin>>id;
            Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file;
            file.Delete(id);
        }
    }
}

