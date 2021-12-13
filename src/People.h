#ifndef MAIN_1_CPP_PEOPLE_H
#define MAIN_1_CPP_PEOPLE_H

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

class NodeBook {
public:
    char isbn[22];
    char book_name[62];
    char author[62];
    char keyword[62];
    int quantity;
    double price;

    NodeBook() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    NodeBook(string isbn_, string name, string author_, string key, int quantity_, double price_) {
        strcpy(isbn, isbn_.c_str());
        strcpy(book_name, name.c_str());
        strcpy(author, author_.c_str());
        strcpy(keyword, key.c_str());
        quantity = quantity_;
        price = price_;
    }

    bool operator>(const NodeBook &b) {
        return (string(this->isbn) > string(b.isbn));
    }

    bool operator>=(const NodeBook &b) {
        return (string(this->isbn) >= string(b.isbn));

    }

    bool operator==(const NodeBook &b) {
        return (string(this->isbn) == string(b.isbn));
    }

    bool operator>=(const string &b) {
        return (string(this->isbn) >= b);
    }

    bool operator>(const string &b) {
        return (string(this->isbn) > b);
    }

    bool operator==(const string &b) {
        return (string(this->isbn) == b);
    }

    virtual NodeBook &operator=(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
        return (*this);
    }

    friend ostream &operator<<(ostream &os, const NodeBook &nod) {
        os << string(nod.isbn) << '\t' << string(nod.book_name) << '\t' << string(nod.author) << '\t'
           << string(nod.keyword) << '\t' << fixed << setprecision(2) << nod.price << '\t' << nod.quantity << '\n';
        return os;
    }
};

class NodeBookName : public NodeBook {
public:
    NodeBookName() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    NodeBookName(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookName &b) {
        return (string(this->book_name) > string(b.book_name) ||
                (string(this->book_name) == string(b.book_name) && string(this->isbn) > string(b.isbn)));
    }

    bool operator>=(const NodeBookName &b) {
        return (string(this->book_name) > string(b.book_name) ||
                (string(this->book_name) == string(b.book_name) && string(this->isbn) >= string(b.isbn)));

    }

    bool operator==(const NodeBookName &b) {
        return (string(this->book_name) == string(b.book_name) && string(this->isbn) == string(b.isbn));
    }

    bool operator>=(const string &b) {
        return (string(this->book_name) >= b);
    }

    bool operator>(const string &b) {
        return (string(this->book_name) > b);
    }

    bool operator==(const string &b) {
        return (string(this->book_name) == b);
    }
};

class NodeBookAuthor : public NodeBook {
public:
    NodeBookAuthor() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    NodeBookAuthor(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookAuthor &b) {
        return (string(this->author) > string(b.author) ||
                (string(this->author) == string(b.author) && string(this->isbn) > string(b.isbn)));
    }

    bool operator>=(const NodeBookAuthor &b) {
        return (string(this->author) >= string(b.author) ||
                (string(this->author) == string(b.author) && string(this->isbn) >= string(b.isbn)));

    }

    bool operator==(const NodeBookAuthor &b) {
        return (string(this->author) == string(b.author) && string(this->isbn) == string(b.isbn));
    }

    bool operator>=(const string &b) {
        return (string(this->author) >= b);
    }

    bool operator>(const string &b) {
        return (string(this->author) > b);
    }

    bool operator==(const string &b) {
        return (string(this->author) == b);
    }
};

class NodeBookKeyword : public NodeBook {
public:
    char keyword_[62];

    NodeBookKeyword() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    NodeBookKeyword(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookKeyword &b) {
        return (string(this->keyword_) > string(b.keyword_) ||
                (string(this->keyword_) == string(b.keyword_) && string(this->isbn) > string(b.isbn)));
    }

    bool operator>=(const NodeBookKeyword &b) {
        return (string(this->keyword_) >= string(b.keyword_) ||
                (string(this->keyword_) == string(b.keyword_) && string(this->isbn) >= string(b.isbn)));

    }

    bool operator==(const NodeBookKeyword &b) {
        return (string(this->keyword_) == string(b.keyword_) && string(this->isbn) == string(b.isbn));
    }

    bool operator>=(const string &b) {
        return (string(this->keyword_) >= b);
    }

    bool operator>(const string &b) {
        return (string(this->keyword_) > b);
    }

    bool operator==(const string &b) {
        return (string(this->keyword_) == b);
    }
};

vector<NodePeople> stk;
Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file_people("file_people", "file_people_index", "file_people_delete");
Store<NodeIndex_<NodeBook>, Block_<NodeBook>> file_book("file_book", "file_book_index", "file_book_delete");
Store<NodeIndex_<NodeBookName>, Block_<NodeBookName>> file_name("file_name", "file_name_index", "file_name_delete");
Store<NodeIndex_<NodeBookAuthor>, Block_<NodeBookAuthor>> file_author("file_author", "file_author_index",
                                                                      "file_author_delete");
Store<NodeIndex_<NodeBookKeyword>, Block_<NodeBookKeyword>> file_keyword("file_keyword", "file_keyword_index",
                                                                         "file_keyword_delete");

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

string GetKey(string &key) {
    for (int i = 0; i < key.length(); i++) {
        if (key[i] == ' ') {
            string s_ = key.substr(0, i);
            key = key.substr(i + 1);
            return s_;
        }
    }
}

string Get(string &s) {
    if (s == "") throw Invaild();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            string s_ = s.substr(0, i);
            s = s.substr(i + 1);
            return s_;
        }
    }
}

long long CheckNum_(string num) {
    long long ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invaild();
        else ans = ans * 10 + (long long) (num[i] - '0');
    }
    return ans;
}

class People {
protected:
    NodeBook select;
public:
    virtual void Initialize() {
        file_people.Initialize<NodePeople>({"root", "", "sjtu", 7});
    }

    virtual void Su(string id, string password) {
        NodePeople people = file_people.Find<NodePeople>(id);
        if (people.password == password) {
            stk.push_back(people);
        } else throw Invaild();
    }

    virtual void Su(string id) {
        if (stk.empty()) throw Invaild();
        NodePeople people = file_people.Find<NodePeople>(id);
        NodePeople peo = stk[stk.size() - 1];
        if (peo.priority >= people.priority) {
            stk.push_back(people);
        } else throw Invaild();
    }

    virtual void Logout() {
        if (stk.empty()) {
            throw Invaild();
        } else
            stk.pop_back();
    }

    virtual void Register(string id, string password, string user_name) {
        NodePeople people(id, user_name, password, 1);
        try {
            file_people.Insert(people);
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Passwd(string id, string old_passwd, string new_passwd) {
        try {
            NodePeople people = file_people.Find<NodePeople>(id);
            if (people.password == old_passwd) {
                strcpy(people.password, new_passwd.c_str());
                file_people.Delete(id);
                file_people.Insert(people);
            } else throw Invaild();
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Passwd(string id, string new_passwd) {
        try {
            NodePeople people = file_people.Find<NodePeople>(id);
            strcpy(people.password, new_passwd.c_str());
            file_people.Delete(id);
            file_people.Insert(people);
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Useradd(string id, string password, int priority, string user_name) {
        NodePeople now_people = stk[stk.size() - 1];
        if (priority >= now_people.priority) throw Invaild();
        NodePeople people(id, user_name, password, priority);
        try {
            file_people.Insert(people);
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Delete(string id) {
        for (int i = 0; i < stk.size(); i++)
            if (stk[i].user_id == id)
                throw Invaild();
        try {
            file_people.Delete(id);
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Show(ShowMessage infor) {
        try {
            Select(select.isbn);
            if (infor.isbn[0] != '\0') {
                NodeBook book = file_book.Find<NodeBook>(string(infor.isbn));
                if (infor.book_name[0] != '\0') {
                    if (string(book.book_name) != string(infor.book_name))
                        throw Invaild();
                }
                if (infor.author[0] != '\0') {
                    if (string(book.author) != string(infor.author))
                        throw Invaild();
                }
                if (infor.keyword[0] != '\0') {
                    string keyword = string(book.keyword);
                    keyword += " ";
                    while (keyword != "") {
                        string keyword_ = GetKey(keyword);
                        if (keyword_ == string(infor.keyword)) {
                            cout << book;
                            return;
                        }
                    }
                    throw Invaild();
                }
            } else if (infor.book_name[0] != '\0') {
                string ans = file_name.FindMore(string(infor.book_name));
                bool ok = 0;
                fstream file;
                while (ans != "") {
                    file.open("file_name");
                    Block_<NodeBookName> block;
                    long long locate = CheckNum_(Get(ans));
                    file.seekg(locate);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBookName>));
                    for (int i = 1; i <= block.now; i++) {
                        if (string(block.size[i].book_name) != string(infor.book_name))
                            continue;
                        if (infor.author[0] != '\0')
                            if (string(block.size[i].author) != string(infor.author))
                                continue;
                        if (infor.keyword[0] != '\0') {
                            string keyword = string(block.size[i].keyword);
                            keyword += " ";
                            while (keyword != "") {
                                string keyword_ = GetKey(keyword);
                                if (keyword_ == string(infor.keyword)) {
                                    cout << block.size[i];
                                    ok = 1;
                                }
                            }
                        }
                    }
                }
                file.close();
                if (!ok) throw Invaild();
            } else if (infor.author[0] != '\0') {
                string ans = file_author.FindMore(string(infor.author));
                bool ok = 0;
                fstream file;
                while (ans != "") {
                    file.open("file_author");
                    Block_<NodeBookAuthor> block;
                    long long locate = CheckNum_(Get(ans));
                    file.seekg(locate);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBookAuthor>));
                    for (int i = 1; i <= block.now; i++) {
                        if (string(block.size[i].author) != string(infor.author))
                            continue;
                        if (infor.keyword[0] != '\0') {
                            string keyword = string(block.size[i].keyword);
                            keyword += " ";
                            while (keyword != "") {
                                string keyword_ = GetKey(keyword);
                                if (keyword_ == string(infor.keyword)) {
                                    cout << block.size[i];
                                    ok = 1;
                                }
                            }
                        }
                    }
                }
                file.close();
                if (!ok) throw Invaild();
            } else if (infor.keyword[0] != '\0') {
                string ans = file_keyword.FindMore(string(infor.keyword));
                bool ok = 0;
                fstream file;
                while (ans != "") {
                    file.open("file_keyword");
                    Block_<NodeBookKeyword> block;
                    long long locate = CheckNum_(Get(ans));
                    file.seekg(locate);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBookKeyword>));
                    for (int i = 1; i <= block.now; i++) {
                        if (string(block.size[i].keyword) == string(infor.keyword))
                            cout << block.size[i];
                    }
                }
                file.close();
                if (!ok) throw Invaild();
            } else {
                fstream file, file_index;
                file.open("file_book");
                file_index.open("file_book_index");
                NodeIndex_<NodeBook> idx;
                Block_<NodeBook> block;
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_<NodeBook>));
                if (idx.next == -1) {
                    file.close();
                    file_index.close();
                    throw Invaild();
                }
                file_index.seekg(idx.next, ios::beg);
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_<NodeBook>));
                while (1) {
                    file.seekg(idx.block_begin);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBook>));
                    for (int i = 1; i <= block.now; i++)
                        cout << block.size[i];
                    if (idx.next == -1) {
                        file.close();
                        file_index.close();
                        return;
                    }
                    file_index.seekg(idx.next, ios::beg);
                    file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_<NodeBook>));
                }
            }
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Buy(string isbn, int quantity) {
        try {
            if (string(select.isbn) != isbn) {
                NodeBook find_book = file_book.Find<NodeBook>(isbn);
                file_book.Delete(isbn);
                find_book.quantity += quantity;
                file_book.Insert(find_book);
            } else select.quantity += quantity;
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Select(string isbn) {
        try {
            if (select.isbn[0] != '\0') {
                NodeBook book = file_book.Find<NodeBook>(string(select.isbn));
                file_book.Delete(string(select.isbn));
                file_book.Insert(select);
                NodeBookName book_name = book;
                file_name.Delete(book_name);
                book_name = select;
                file_name.Insert(book_name);
                cout << file_name.Find<NodeBookName>(string(book_name.book_name));
                NodeBookAuthor book_author = book;
                file_author.Delete(book_author);
                book_author = select;
                file_author.Insert(book_author);
                cout << file_author.Find<NodeBookAuthor>(string(book_author.author));
                NodeBookKeyword book_key = book;
                string keyword = string(book.keyword);
                keyword += " ";
                while (keyword != "") {
                    string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Delete(book_key);
                }
                book_key = select;
                keyword = string(select.keyword);
                keyword += " ";
                while (keyword != "") {
                    string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Insert(book_key);
                }
                cout << file_keyword.Find<NodeBookKeyword>(string(book_key.keyword_));
            }
        } catch (Invaild) {
            file_book.Insert(select);
            NodeBookName book_name = select;
            file_name.Insert(book_name);
            cout << file_name.Find<NodeBookName>(string(book_name.book_name));
            NodeBookAuthor book_author = select;
            file_author.Insert(book_author);
            cout << file_author.Find<NodeBookAuthor>(string(book_author.author));
            NodeBookKeyword book_key = select;
            string keyword = string(select.keyword);
            keyword += " ";
            while (keyword != "") {
                string keyword_ = GetKey(keyword);
                strcpy(book_key.keyword, keyword_.c_str());
                file_keyword.Insert(book_key);
            }
            cout << file_keyword.Find<NodeBookKeyword>(string(book_key.keyword_));
            try {
                select = file_book.Find<NodeBook>(isbn);
            } catch (Invaild) {
                NodeBook new_book;
                select = new_book;
                strcpy(select.isbn, isbn.c_str());
            }
        }
        try {
            select = file_book.Find<NodeBook>(isbn);
        } catch (Invaild) {
            NodeBook new_book;
            select = new_book;
            strcpy(select.isbn, isbn.c_str());
        }
    }

    virtual void ModifyIsbn(string isbn) {
        if (select.isbn[0] == '\0')
            throw Invaild();
        strcpy(select.isbn, isbn.c_str());
    }

    virtual void ModifyName(string name) {
        if (select.isbn[0] == '\0')
            throw Invaild();
        strcpy(select.book_name, name.c_str());
    }

    virtual void ModifyAuthor(string author) {
        if (select.isbn[0] == '\0')
            throw Invaild();
        strcpy(select.author, author.c_str());
    }

    virtual void ModifyKeyword(string keyword) {
        if (select.isbn[0] == '\0')
            throw Invaild();
        strcpy(select.keyword, keyword.c_str());
    }

    virtual void ModifyPrice(double price) {
        if (select.isbn[0] == '\0')
            throw Invaild();
        select.price = price;
    }

    virtual void Import(int quantity, double cost) {
        if (select.isbn[0] == '\0')
            throw Invaild();
        select.quantity += quantity;
    }

    virtual void ReportMyself() {

    }

    virtual void ShowFinance(int time) {

    }

    virtual void ShowFinance() {

    }

    virtual void ReportFinance() {

    }

    virtual void ReportEmployee() {

    }

    virtual void Log() {

    }
};

class Manager : public People {
public:
};

class Employee : public People {
public:
    virtual void Passwd(string id, string new_passwd) {
        throw Invaild();
    }

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

class Consumer : public People {
public:
    virtual void Passwd(string id, string new_passwd) {
        throw Invaild();
    }

    virtual void Useradd(string id, string pass_word, int priority, string user_name) {
        throw Invaild();
    }

    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void Select(string isbn) {
        throw Invaild();
    }

    virtual void ModifyIsbn(string isbn) {
        throw Invaild();
    }

    virtual void ModifyName(string name) {
        throw Invaild();
    }

    virtual void ModifyAuthor(string author) {
        throw Invaild();
    }

    virtual void ModifyKeyword(string keyword) {
        throw Invaild();
    }

    virtual void ModifyPrice(double price) {
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
    virtual void Passwd(string id, string old_passwd, string new_passed) {
        throw Invaild();
    }

    virtual void Passwd(string id, string new_passwd) {
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

    virtual void ModifyIsbn(string isbn) {
        throw Invaild();
    }

    virtual void ModifyName(string name) {
        throw Invaild();
    }

    virtual void ModifyAuthor(string author) {
        throw Invaild();
    }

    virtual void ModifyKeyword(string keyword) {
        throw Invaild();
    }

    virtual void ModifyPrice(double price) {
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

#endif //MAIN_1_CPP_PEOPLE_H
