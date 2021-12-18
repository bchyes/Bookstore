

# Bookstore

> 包晨豪

## 文件储存

所有账户与所有图书 均以二进制文件储存，并用块状链表维护

财务收支用二进制，顺序储存

所有员工的操作 以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

财务信息 日志类 以ASCLL文件直接储存

## 代码文件结构

main函数

```c++
vector<NodePeople> stk;//登陆栈
Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file_people("file_people", "file_people_index", "file_people_delete");
Store<NodeIndex_<NodeBook>, Block_<NodeBook>> file_book("file_book", "file_book_index", "file_book_delete");
Store<NodeIndex_<NodeBookName>, Block_<NodeBookName>> file_name("file_name", "file_name_index", "file_name_delete");
Store<NodeIndex_<NodeBookAuthor>, Block_<NodeBookAuthor>> file_author("file_author", "file_author_index",
                                                                      "file_author_delete");
Store<NodeIndex_<NodeBookKeyword>, Block_<NodeBookKeyword>> file_keyword("file_keyword", "file_keyword_index",
                                                                         "file_keyword_delete");
//模板类储存文件，储存形式及节点内容于块状链表内
string GetKey(string &key) {//得到一个keyword中的一个关键词
    for (int i = 0; i < key.length(); i++) {
        if (key[i] == '|') {
            string s_ = key.substr(0, i);
            key = key.substr(i + 1);
            return s_;
        }
    }
}

string Get(string &s) {//得到一个以空格分开的一个字符串
    if (s == "") throw Invaild();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            string s_ = s.substr(0, i);
            int j;
            for (j = i + 1; j < s.length(); j++)
                if (s[j] != ' ') break;
            s = s.substr(j);
            return s_;
        }
    }
}

long long CheckNum_(string num) {//判断是否是long long，否则throw
    long long ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invaild();
        else ans = ans * 10 + (long long) (num[i] - '0');
    }
    return ans;
}
int CheckNum(string num) {//判断是否是int，否则throw
    int ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invaild();
        else ans = ans * 10 + int(num[i] - '0');
    }
    return ans;
}

double CheckDouble(string num) {//判断是否是double，否则throw
    bool dot = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '.' && !dot) {
            dot = 1;
            continue;
        } else if (num[i] == '.' && dot) throw Invaild();
        if (num[i] > '9' || num[i] < '0')
            throw Invaild();
    }
    return stod(num);
}

void CheckNull(string s) {//判断字符串是否为空，用来检查鲁棒性
    if (s != "") throw Invaild();
}

void Getop(const string &op, string &type, string &infor) {//处理modify和show后面所跟的信息，返回处理的type和内容infor，我忘记有什么必要了，感觉下面这个就好了qwq，我之后再看看，感觉没什么用
    if (op[0] != '-') throw Invaild();
    int i;
    for (i = 1; i < op.length(); i++)
        if (op[i] != '=') type += op[i];
        else break;
    if (type != "name" && type != "ISBN" && type != "author" && type != "keyword" && type != "price")
        throw Invaild();
    if (type == "price") {
        bool dot = 0;
        for (i++; i < op.length(); i++) {
            if (op[i] == '.' && !dot) {
                dot = 1;
                infor += op[i];
                continue;
            } else if (op[i] == '.' && dot) throw Invaild();
            if (op[i] > '9' || op[i] < '0')
                throw Invaild();
            infor += op[i];
        }
    } else if (type == "ISBN") {
        for (i++; i < op.length(); i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127) throw Invaild();
            infor += op[i];
        }
    } else
        for (i += 2; i < op.length() - 1; i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127 || op[i] == '"') throw Invaild();
            infor += op[i];
        }
}

void Getop_(const string &op, string &type, string &infor) {//处理modify和show后面所跟的信息，返回处理的type和内容infor
    if (op[0] != '-') throw Invaild();
    int i;
    for (i = 1; i < op.length(); i++)
        if (op[i] != '=') type += op[i];
        else break;
    if (type != "name" && type != "ISBN" && type != "author" && type != "keyword" && type != "price")
        throw Invaild();
    if (type == "price") {
        bool dot = 0;
        for (i++; i < op.length(); i++) {
            if (op[i] == '.' && !dot) {
                dot = 1;
                infor += op[i];
                continue;
            } else if (op[i] == '.' && dot) throw Invaild();
            if (op[i] > '9' || op[i] < '0')
                throw Invaild();
            infor += op[i];
        }
    } else if (type == "ISBN") {
        for (i++; i < op.length(); i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127) throw Invaild();
            infor += op[i];
        }
    } else if (type != "keyword")
        for (i += 2; i < op.length() - 1; i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127 || op[i] == '"') throw Invaild();
            infor += op[i];
        }
    else {
        for (i += 2; i < op.length() - 1; i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127 || op[i] == '"' || op[i] == '|') throw Invaild();
            infor += op[i];
        }
    }
}
int main() {
    string s;
    People *account = new Visitor;
    account->Initialize();
    int line = 0;
    while (getline(cin, s)) {
        line++;
        s += " ";
        string token;
        token = Get(s);
        if (token == "su") {
            try {
                string id = Get(s);
                if (s != "") {
                    string passwd = Get(s);
                    CheckNull(s);
                    account->Su(id, passwd);
                    NodePeople new_account = stk[stk.size() - 1];
                    if (new_account.priority == 7) {
                        delete account;
                        account = new Manager;
                    } else if (new_account.priority == 3) {
                        delete account;
                        account = new Employee;
                    } else if (new_account.priority == 1) {
                        delete account;
                        account = new Consumer;
                    }
                } else {
                    account->Su(id);
                    NodePeople new_account = stk[stk.size() - 1];
                    if (new_account.priority == 7) {
                        delete account;
                        account = new Manager;
                    } else if (new_account.priority == 3) {
                        delete account;
                        account = new Employee;
                    } else if (new_account.priority == 1) {
                        delete account;
                        account = new Consumer;
                    }
                }
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "logout") {
            try {
                CheckNull(s);
                account->Logout();
                if (stk.empty()) {
                    delete account;
                    account = new Visitor;
                } else {
                    NodePeople new_account = stk[stk.size() - 1];
                    if (new_account.priority == 7) {
                        delete account;
                        account = new Manager;
                    } else if (new_account.priority == 3) {
                        delete account;
                        account = new Employee;
                    } else if (new_account.priority == 1) {
                        delete account;
                        account = new Consumer;
                    }
                }
            }
            catch (Invaild) { cout << "Invaild" << " " << line << "\n"; }
        } else if (token == "useradd") {
            try {
                string id = Get(s);
                string passwd = Get(s);
                int priority = CheckNum(Get(s));
                string name = Get(s);
                CheckNull(s);
                account->Useradd(id, passwd, priority, name);
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "register") {
            try {
                string id = Get(s);
                string passwd = Get(s);
                string name = Get(s);
                CheckNull(s);
                account->Register(id, passwd, name);
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "delete") {
            try {
                string id = Get(s);
                CheckNull(s);
                account->Delete(id);
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "passwd") {
            try {
                string id = Get(s);
                string passwd = Get(s);
                if (s != "") {
                    string new_passwd = Get(s);
                    CheckNull(s);
                    account->Passwd(id, passwd, new_passwd);
                } else {
                    account->Passwd(id, passwd);
                }
            } catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "select") {
            try {
                string isbn = Get(s);
                CheckNull(s);
                account->Select(isbn);
            } catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "show") {
            try {
                ShowMessage mess;
                string token_;
                if (s != "") {
                    token_ = Get(s);
                    if (token_ == "finance") {
                        if (s != "") {
                            int time = CheckNum(Get(s));
                            CheckNull(s);
                            account->ShowFinance(time);
                        } else {
                            account->ShowFinance();
                        }
                        continue;
                    }
                }
                s = token_ + " " + s;
                while (s != "") {
                    string op = Get(s);
                    string type, infor;
                    Getop_(op, type, infor);
                    if (type == "ISBN") {
                        strcpy(mess.isbn, infor.c_str());
                    } else if (type == "name") {
                        strcpy(mess.book_name, infor.c_str());
                    } else if (type == "author") {
                        strcpy(mess.author, infor.c_str());
                    } else if (type == "keyword") {
                        strcpy(mess.keyword, infor.c_str());
                    }
                }
                account->Show(mess);
            } catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "buy") {
            try {
                string isbn = Get(s);
                int quantity = CheckNum(Get(s));
                CheckNull(s);
                account->Buy(isbn, quantity);
            } catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "modify") {
            try {
                while (s != "") {
                    string op = Get(s);
                    string type, infor;
                    Getop(op, type, infor);
                    if (type == "ISBN") {
                        account->ModifyIsbn(infor);
                    } else if (type == "name") {
                        account->ModifyName(infor);
                    } else if (type == "author") {
                        account->ModifyAuthor(infor);
                    } else if (type == "keyword") {
                        account->ModifyKeyword(infor);
                    } else if (type == "price") {
                        account->ModifyPrice(stod(infor));
                    }
                }
            } catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "import") {
            try {
                int quantity = CheckNum(Get(s));
                double total_cost = CheckDouble(Get(s));
                CheckNull(s);
                account->Import(quantity, total_cost);
            } catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "exit") {
            try {
                CheckNull(s);
                delete account;
                return 0;
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "quit") {
            try {
                CheckNull(s);
                delete account;
                return 0;
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        }
    }
    delete account;
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
protected:
    NodeBook select;
public:
    virtual ~People() {//析构账号的时候，如果还有修改没写进文件就写进去
        if (select.isbn[0] != '\0') Select(string(select.isbn));
    }

    virtual void Initialize() {//初始化root
        file_people.Initialize<NodePeople>({"root", "", "sjtu", 7});
    }

    virtual void Su(string id, string password) {//密码不对就抛出异常，否则存入vector
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

    virtual void Logout() {//vector pop_back
        if (stk.empty()) {
            throw Invaild();
        } else
            stk.pop_back();
    }

    virtual void Register(string id, string password, string user_name) {//用insert存进文件（文件里如果重名就要throw）
        NodePeople people(id, user_name, password, 1);
        try {
            file_people.Insert(people);
        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Passwd(string id, string old_passwd, string new_passwd) {//先find找到，再delete，再insert（文件里如果重名就要throw）
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

    virtual void Delete(string id) {//遍历vector，若在登陆栈，则throw
        for (int i = 0; i < stk.size(); i++)
            if (stk[i].user_id == id)
                throw Invaild();
        try {
            file_people.Delete(id);
        } catch (Invaild) { throw Invaild(); }
    }
/*struct ShowMessage {
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
};*/
    virtual void Show(ShowMessage infor) {//如果读入的message有ISBN就读isbn文件，否则book_name,否则author，最后keyword，如果全空就遍历isbn文件输出
        try {
            if (select.isbn[0] != '\0') Select(string(select.isbn));
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
                    keyword += "|";
                    while (keyword != "") {
                        string keyword_ = GetKey(keyword);
                        if (keyword_ == string(infor.keyword)) {
                            cout << book;
                            return;
                        }
                    }
                    throw Invaild();
                }
                cout << book;
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
                            keyword += "|";
                            while (keyword != "") {
                                string keyword_ = GetKey(keyword);
                                if (keyword_ == string(infor.keyword)) {
                                    cout << block.size[i];
                                    ok = 1;
                                }
                            }
                        } else {
                            cout << block.size[i];
                            ok = 1;
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
                            keyword += "|";
                            while (keyword != "") {
                                string keyword_ = GetKey(keyword);
                                if (keyword_ == string(infor.keyword)) {
                                    cout << block.size[i];
                                    ok = 1;
                                }
                            }
                        } else {
                            cout << block.size[i];
                            ok = 1;
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
                        if (string(block.size[i].keyword_) == string(infor.keyword)) {
                            cout << block.size[i];
                            ok = 1;
                        }
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
        } catch (Invaild) { cout << "Invaild" << '\n'; }
    }

    virtual void Buy(string isbn, int quantity) {//只改变isbn文件中的价格，以省下时间
        try {
            if (string(select.isbn) != isbn) {
                NodeBook find_book = file_book.Find<NodeBook>(isbn);
                if (find_book.quantity >= quantity) {
                    file_book.Delete(isbn);
                    find_book.quantity -= quantity;
                    cout << fixed << setprecision(2) << quantity * find_book.price << '\n';
                    FinanceInsert(quantity * find_book.price);
                } else throw Invaild();
                file_book.Insert(find_book);
            } else {
                if (select.quantity >= quantity) {
                    select.quantity -= quantity;
                    cout << fixed << setprecision(2) << quantity * select.price << '\n';
                    FinanceInsert(quantity * select.price);
                } else throw Invaild();
            }

        } catch (Invaild) { throw Invaild(); }
    }

    virtual void Select(string isbn) {//将上次select的存进所有文件中，共四个文件，再将select从文件中读出来
        try {
            if (select.isbn[0] != '\0') {
                NodeBook book = file_book.Find<NodeBook>(string(select.isbn));
                file_book.Delete(string(select.isbn));
                file_book.Insert(select);
                NodeBookName book_name = book;
                file_name.Delete(book_name);
                book_name = select;
                file_name.Insert(book_name);
                NodeBookAuthor book_author = book;
                file_author.Delete(book_author);
                book_author = select;
                file_author.Insert(book_author);
                NodeBookKeyword book_key = book;
                string keyword = string(book.keyword);
                keyword += "|";
                while (keyword != "") {
                    string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Delete(book_key);
                }
                book_key = select;
                keyword = string(select.keyword);
                keyword += "|";
                while (keyword != "") {
                    string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Insert(book_key);
                }
            }
        } catch (Invaild) {
            file_book.Insert(select);
            NodeBookName book_name = select;
            file_name.Insert(book_name);
            NodeBookAuthor book_author = select;
            file_author.Insert(book_author);
            NodeBookKeyword book_key = select;
            string keyword = string(select.keyword);
            keyword += "|";
            while (keyword != "") {
                string keyword_ = GetKey(keyword);
                strcpy(book_key.keyword_, keyword_.c_str());
                file_keyword.Insert(book_key);
            }
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

    virtual void ModifyIsbn(string isbn) {//修改ISBN，不能修改成已有的或是自己
        if (select.isbn[0] == '\0' || string(select.isbn) == isbn)
            throw Invaild();
        bool ok = 0;
        try {
            file_book.Find<NodeBook>(isbn);
            ok = 1;
        } catch (Invaild) { strcpy(select.isbn, isbn.c_str()); }
        if (ok) throw Invaild();
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
        FinanceInsert(-1 * cost);
    }

    virtual void ReportMyself() {

    }

    virtual void ShowFinance(int time) {//finance 存进一个文件，开头存笔数，之后每次交易收入就是正，支出就是负，show就将最后time笔读出来加起来
        fstream file;
        file.open("file_finance");
        if (!file)
            throw Invaild();
        int time_;
        file.read(reinterpret_cast<char *>(&time_), sizeof(int));
        if (time_ < time) throw Invaild();
        file.seekg(sizeof(int) + sizeof(double) * (time_ - time));
        double finance_plus = 0, finance_minus = 0, finance;
        for (int i = 1; i <= time; i++) {
            file.read(reinterpret_cast<char *>(&finance), sizeof(double));
            if (finance > 0) finance_plus += finance;
            else finance_minus -= finance;
        }
        cout << "+ " << fixed << setprecision(2) << finance_plus << " - " << fixed << setprecision(2) << finance_minus
             << '\n';
    }

    virtual void ShowFinance() {
        fstream file;
        file.open("file_finance");
        if (!file)
            throw Invaild();
        int time_;
        file.read(reinterpret_cast<char *>(&time_), sizeof(int));
        file.seekg(sizeof(int));
        double finance_plus = 0, finance_minus = 0, finance;
        for (int i = 1; i <= time_; i++) {
            file.read(reinterpret_cast<char *>(&finance), sizeof(double));
            if (finance > 0) finance_plus += finance;
            else finance_minus -= finance;
        }
        cout << "+ " << fixed << setprecision(2) << finance_plus << " - " << fixed << setprecision(2) << finance_minus
             << '\n';
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

    virtual void Show(ShowMessage infor) {
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
```

## 具体算法说明

```c++
    virtual void Su(string id, string pass_word);//以栈来维护，登入账号推入栈
    
    virtual void Su(string id);//特殊处理

    virtual void Logout();//退出栈

    virtual void Register(string id, string pass_word, string user_name);//以块链维护账户信息

    virtual void Passwd(string id, string old_passwd, string new_passed);//通过块链找到账户信息

    virtual void Useradd(string id, string pass_word, int priority, string user_name);//以块链维护账户信息

    virtual void Delete(string id);//先通过栈寻找是否登陆，再通过块链删除

    virtual void Show(string isbn, string name, string author, string keyword);//图书信息由另一个文件的块链储存

    virtual void Show();

    virtual void Buy(string isbn, int quantity);//通过块链找到信息并修改

    virtual void Select(string isbn);//通过块链找到信息，同时在该类中记录选中的图书

    virtual void Modify(string isbn, string name, string author, string keyword, double price);//通过记录的信息在块链中修改

    virtual void Import(int quantity, double cost);//通过记录的信息在块链中修改

    virtual void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    virtual void ShowFinance(int time);

    virtual void ShowFinance();

    virtual void ReportFinance();

    virtual void ReportEmployee();

    virtual void Log();//以上三个操作均存一个不同的ASCLL文件
```

## 块状链表

```c++
class NodePeople {//人节点
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
        if (this==&nod) return (*this);
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

class NodeBook {//以ISBN为关键字的书的节点
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
        if (this==&nod) return (*this);
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

class NodeBookName : public NodeBook {//以book_name为关键字，isbn为副关键字进行排序的书的节点
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

class NodeBookAuthor : public NodeBook {//以author为关键字，isbn为副关键字进行排序的书的节点
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
        return (string(this->author) > string(b.author) ||
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

class NodeBookKeyword : public NodeBook {//以keyword为关键字，isbn为副关键字进行排序的书的节点,同时将一个书不同的关键词拆成单一的关键词进行多次储存，这部分信息储存于keyword_中
public:
    char keyword_[62];

    NodeBookKeyword() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        keyword_[0] = '\0';
        quantity = price = 0;
    }

    NodeBookKeyword(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->keyword_[0] = '\0';
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookKeyword &b) {
        return (string(this->keyword_) > string(b.keyword_) ||
                (string(this->keyword_) == string(b.keyword_) && string(this->isbn) > string(b.isbn)));
    }

    bool operator>=(const NodeBookKeyword &b) {
        return (string(this->keyword_) > string(b.keyword_) ||
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
    virtual NodeBookKeyword &operator=(const NodeBookKeyword &nod) {
        if (this==&nod) return (*this);
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        strcpy(this->keyword_, nod.keyword_);
        this->quantity = nod.quantity;
        this->price = nod.price;
        return (*this);
    }
};

template<class Node>
struct Block_ {//模板的块
    static const int maxn = 3;
    Node size[maxn + 2];
    int now = 0;
};
template<class Node>
struct NodeIndex_ {//模板的索引
    long long next = -1;
    long long pre = -1;
    Node end;
    long long block_begin = 0;
};
```

## 日志系统

report myself输出形式

name:

|did XXX|

|did XX|

......

report finance

|cost XXX to did XXX|

|earn XXX from did XXX|

......

report employee

|XXX did XXX|

......

log

同上述输出
