#include"template.h"

class Node_ {
public:
    char index[66];
    int value;

    Node_() {
        index[0] = '\0';
        value = 0;
    }

    Node_(string idx, int val) {
        strcpy(index, idx.c_str());
        value = val;
    }

    friend bool operator>(const Node_ &a, const Node_ &b) {
        return (string(a.index) > string(b.index) || string(a.index) == string(b.index) && a.value > b.value);
    }

    friend bool operator>=(const Node_ &a, const Node_ &b) {
        return (string(a.index) > string(b.index) || string(a.index) == string(b.index) && a.value >= b.value);
    }

    friend bool operator==(const Node_ &a, const Node_ &b) {
        return (string(a.index) == string(b.index) && a.value == b.value);
    }

    Node_ &operator=(const Node_ &nod) {
        strcpy(this->index, nod.index);
        this->value = nod.value;
        return (*this);
    }
};

int main() {
    int n;
    cin >> n;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        if (s == "insert") {
            string index;
            int value;
            cin >> index >> value;
            Store<NodeIndex_<Node_>, Block_<Node_>> file;
            Node_ nod(index, value);
            file.Insert(nod);
        } else if (s == "find") {
            string index;
            cin >> index;
            Store<NodeIndex_<Node_>, Block_<Node_>> file;
            cout << file.Find(index) << '\n';
        } else if (s == "delete") {
            string index;
            int value;
            cin >> index >> value;
            Store<NodeIndex_<Node_>, Block_<Node_>> file;
            Node_ nod(index, value);
            file.Delete(nod);
        }
    }
}
