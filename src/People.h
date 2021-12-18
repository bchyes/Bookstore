#ifndef MAIN_1_CPP_PEOPLE_H
#define MAIN_1_CPP_PEOPLE_H

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

class NodeBook {
public:
    char isbn[22];
    char book_name[62];
    char author[62];
    char keyword[62];
    int quantity;
    double price;

    explicit NodeBook() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    explicit NodeBook(std::string isbn_, std::string name, std::string author_, std::string key, int quantity_,
                      double price_) {
        strcpy(isbn, isbn_.c_str());
        strcpy(book_name, name.c_str());
        strcpy(author, author_.c_str());
        strcpy(keyword, key.c_str());
        quantity = quantity_;
        price = price_;
    }

    bool operator>(const NodeBook &b) {
        return (std::string(this->isbn) > std::string(b.isbn));
    }

    bool operator>=(const NodeBook &b) {
        return (std::string(this->isbn) >= std::string(b.isbn));

    }

    bool operator==(const NodeBook &b) {
        return (std::string(this->isbn) == std::string(b.isbn));
    }

    bool operator>=(const std::string &b) {
        return (std::string(this->isbn) >= b);
    }

    bool operator>(const std::string &b) {
        return (std::string(this->isbn) > b);
    }

    bool operator==(const std::string &b) {
        return (std::string(this->isbn) == b);
    }

    NodeBook &operator=(const NodeBook &nod) {
        if (this == &nod) return (*this);
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
        return (*this);
    }

    friend std::ostream &operator<<(std::ostream &os, const NodeBook &nod) {
        os << std::string(nod.isbn) << '\t' << std::string(nod.book_name) << '\t' << std::string(nod.author) << '\t'
           << std::string(nod.keyword) << '\t' << std::fixed << std::setprecision(2) << nod.price << '\t'
           << nod.quantity
           << '\n';
        return os;
    }
};

class NodeBookName : public NodeBook {
public:
    explicit NodeBookName() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    explicit NodeBookName(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookName &b) {
        return (std::string(this->book_name) > std::string(b.book_name) ||
                (std::string(this->book_name) == std::string(b.book_name) &&
                 std::string(this->isbn) > std::string(b.isbn)));
    }

    bool operator>=(const NodeBookName &b) {
        return (std::string(this->book_name) > std::string(b.book_name) ||
                (std::string(this->book_name) == std::string(b.book_name) &&
                 std::string(this->isbn) >= std::string(b.isbn)));

    }

    bool operator==(const NodeBookName &b) {
        return (std::string(this->book_name) == std::string(b.book_name) &&
                std::string(this->isbn) == std::string(b.isbn));
    }

    bool operator>=(const std::string &b) {
        return (std::string(this->book_name) >= b);
    }

    bool operator>(const std::string &b) {
        return (std::string(this->book_name) > b);
    }

    bool operator==(const std::string &b) {
        return (std::string(this->book_name) == b);
    }

    NodeBookName &operator=(const NodeBookName &nod) {
        if (this == &nod) return (*this);
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
        return (*this);
    }
};

class NodeBookAuthor : public NodeBook {
public:
    explicit NodeBookAuthor() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        quantity = price = 0;
    }

    explicit NodeBookAuthor(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookAuthor &b) {
        return (std::string(this->author) > std::string(b.author) ||
                (std::string(this->author) == std::string(b.author) && std::string(this->isbn) > std::string(b.isbn)));
    }

    bool operator>=(const NodeBookAuthor &b) {
        return (std::string(this->author) > std::string(b.author) ||
                (std::string(this->author) == std::string(b.author) && std::string(this->isbn) >= std::string(b.isbn)));

    }

    bool operator==(const NodeBookAuthor &b) {
        return (std::string(this->author) == std::string(b.author) && std::string(this->isbn) == std::string(b.isbn));
    }

    bool operator>=(const std::string &b) {
        return (std::string(this->author) >= b);
    }

    bool operator>(const std::string &b) {
        return (std::string(this->author) > b);
    }

    bool operator==(const std::string &b) {
        return (std::string(this->author) == b);
    }

    NodeBookAuthor &operator=(const NodeBookAuthor &nod) {
        if (this == &nod) return (*this);
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->quantity = nod.quantity;
        this->price = nod.price;
        return (*this);
    }
};

class NodeBookKeyword : public NodeBook {
public:
    char keyword_[62];

    explicit NodeBookKeyword() {
        isbn[0] = '\0';
        book_name[0] = '\0';
        author[0] = '\0';
        keyword[0] = '\0';
        keyword_[0] = '\0';
        quantity = price = 0;
    }

    explicit NodeBookKeyword(const NodeBook &nod) {
        strcpy(this->isbn, nod.isbn);
        strcpy(this->book_name, nod.book_name);
        strcpy(this->author, nod.author);
        strcpy(this->keyword, nod.keyword);
        this->keyword_[0] = '\0';
        this->quantity = nod.quantity;
        this->price = nod.price;
    }

    bool operator>(const NodeBookKeyword &b) {
        return (std::string(this->keyword_) > std::string(b.keyword_) ||
                (std::string(this->keyword_) == std::string(b.keyword_) &&
                 std::string(this->isbn) > std::string(b.isbn)));
    }

    bool operator>=(const NodeBookKeyword &b) {
        return (std::string(this->keyword_) > std::string(b.keyword_) ||
                (std::string(this->keyword_) == std::string(b.keyword_) &&
                 std::string(this->isbn) >= std::string(b.isbn)));

    }

    bool operator==(const NodeBookKeyword &b) {
        return (std::string(this->keyword_) == std::string(b.keyword_) &&
                std::string(this->isbn) == std::string(b.isbn));
    }

    bool operator>=(const std::string &b) {
        return (std::string(this->keyword_) >= b);
    }

    bool operator>(const std::string &b) {
        return (std::string(this->keyword_) > b);
    }

    bool operator==(const std::string &b) {
        return (std::string(this->keyword_) == b);
    }

    NodeBookKeyword &operator=(const NodeBookKeyword &nod) {
        if (this == &nod) return (*this);
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

std::vector<NodePeople> stk;
std::vector<NodeBook> stk_;
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

/*struct FinanceMessage{
    char message[32];
    FinanceMessage(){
        message[0]='\0';
    }
};*/
void FinanceInsert(double finance) {
    std::fstream file;
    file.open("file_finance");
    if (!file) {
        file.open("file_finance", std::fstream::out);
        file.close();
        file.open("file_finance");
        int time = 1;
        file.write(reinterpret_cast<char *>(&time), sizeof(int));
        file.write(reinterpret_cast<char *>(&finance), sizeof(double));
        file.close();
        return;
    }
    int time;
    file.read(reinterpret_cast<char *>(&time), sizeof(int));
    time++;
    file.seekp(0);
    file.write(reinterpret_cast<char *>(&time), sizeof(int));
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<char *>(&finance), sizeof(double));
    file.close();
}

std::string GetKey(std::string &key) {
    for (int i = 0; i < key.length(); i++) {
        if (key[i] == '|') {
            std::string s_ = key.substr(0, i);
            key = key.substr(i + 1);
            return s_;
        }
    }
}

std::string Get(std::string &s) {
    if (s == "") throw Invalid();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            std::string s_ = s.substr(0, i);
            int j;
            for (j = i + 1; j < s.length(); j++)
                if (s[j] != ' ') break;
            s = s.substr(j);
            return s_;
        }
    }
}

long long CheckNum_(std::string num) {
    long long ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invalid();
        else ans = ans * 10 + (long long) (num[i] - '0');
    }
    return ans;
}

class People {
protected:
    NodeBook select;
public:
    virtual ~People() {
        if (select.isbn[0] != '\0') Select(std::string(select.isbn));
    }

    virtual void Initialize() {
        NodePeople root("root", "", "sjtu", 7);
        file_people.Initialize<NodePeople>(root);
    }

    virtual void Su(std::string id, std::string password) {
        NodePeople people = file_people.Find<NodePeople>(id);
        if (people.password == password) {
            stk.push_back(people);
            stk_.push_back(select);
        } else throw Invalid();
    }

    virtual void Su(std::string id) {
        if (stk.empty()) throw Invalid();
        NodePeople people = file_people.Find<NodePeople>(id);
        NodePeople peo = stk[stk.size() - 1];
        if (peo.priority > people.priority) {
            stk.push_back(people);
            stk_.push_back(select);
        } else throw Invalid();
    }

    virtual void Logout() {
        stk.pop_back();
    }

    virtual void GetSelect() {
        select = stk_[stk_.size() - 1];
        stk_.pop_back();
        if (select.isbn[0] != '\0') select = file_book.Find<NodeBook>(std::string(select.isbn));
    }

    virtual void Register(std::string id, std::string password, std::string user_name) {
        NodePeople people(id, user_name, password, 1);
        try {
            file_people.Insert(people);
        } catch (Invalid) { throw Invalid(); }
    }

    virtual void Passwd(std::string id, std::string old_passwd, std::string new_passwd) {
        try {
            NodePeople people = file_people.Find<NodePeople>(id);
            if (people.password == old_passwd) {
                strcpy(people.password, new_passwd.c_str());
                file_people.Delete(id);
                file_people.Insert(people);
            } else throw Invalid();
        } catch (Invalid) { throw Invalid(); }
    }

    virtual void Passwd(std::string id, std::string new_passwd) {
        try {
            NodePeople people = file_people.Find<NodePeople>(id);
            strcpy(people.password, new_passwd.c_str());
            file_people.Delete(id);
            file_people.Insert(people);
        } catch (Invalid) { throw Invalid(); }
    }

    virtual void Useradd(std::string id, std::string password, int priority, std::string user_name) {
        NodePeople now_people = stk[stk.size() - 1];
        if (priority >= now_people.priority) throw Invalid();
        NodePeople people(id, user_name, password, priority);
        try {
            file_people.Insert(people);
        } catch (Invalid) { throw Invalid(); }
    }

    virtual void Delete(std::string id) {
        for (int i = 0; i < stk.size(); i++)
            if (stk[i].user_id == id)
                throw Invalid();
        try {
            file_people.Delete(id);
        } catch (Invalid) { throw Invalid(); }
    }

    virtual void Show(ShowMessage infor) {
        try {
            if (select.isbn[0] != '\0') Select(std::string(select.isbn));
            if (infor.isbn[0] != '\0') {
                NodeBook book = file_book.Find<NodeBook>(std::string(infor.isbn));
                if (infor.book_name[0] != '\0') {
                    if (std::string(book.book_name) != std::string(infor.book_name))
                        throw Invalid();
                }
                if (infor.author[0] != '\0') {
                    if (std::string(book.author) != std::string(infor.author))
                        throw Invalid();
                }
                if (infor.keyword[0] != '\0') {
                    std::string keyword = std::string(book.keyword);
                    keyword += "|";
                    while (keyword != "") {
                        std::string keyword_ = GetKey(keyword);
                        if (keyword_ == std::string(infor.keyword)) {
                            std::cout << book;
                            return;
                        }
                    }
                    throw Invalid();
                }
                std::cout << book;
            } else if (infor.book_name[0] != '\0') {
                std::string ans = file_name.FindMore(std::string(infor.book_name));
                bool ok = 0;
                std::fstream file;
                file.open("file_name");
                while (ans != "") {
                    Block_<NodeBookName> block;
                    long long locate = CheckNum_(Get(ans));
                    file.seekg(locate);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBookName>));
                    for (int i = 1; i <= block.now; i++) {
                        if (std::string(block.size[i].book_name) != std::string(infor.book_name))
                            continue;
                        if (infor.author[0] != '\0')
                            if (std::string(block.size[i].author) != std::string(infor.author))
                                continue;
                        if (infor.keyword[0] != '\0') {
                            std::string keyword = std::string(block.size[i].keyword);
                            keyword += "|";
                            while (keyword != "") {
                                std::string keyword_ = GetKey(keyword);
                                if (keyword_ == std::string(infor.keyword)) {
                                    std::cout << block.size[i];
                                    ok = 1;
                                }
                            }
                        } else {
                            std::cout << block.size[i];
                            ok = 1;
                        }
                    }
                }
                file.close();
                if (!ok) throw Invalid();
            } else if (infor.author[0] != '\0') {
                std::string ans = file_author.FindMore(std::string(infor.author));
                bool ok = 0;
                std::fstream file;
                file.open("file_author");
                while (ans != "") {
                    Block_<NodeBookAuthor> block;
                    long long locate = CheckNum_(Get(ans));
                    file.seekg(locate, std::ios::beg);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBookAuthor>));
                    for (int i = 1; i <= block.now; i++) {
                        if (std::string(block.size[i].author) != std::string(infor.author))
                            continue;
                        if (infor.keyword[0] != '\0') {
                            std::string keyword = std::string(block.size[i].keyword);
                            keyword += "|";
                            while (keyword != "") {
                                std::string keyword_ = GetKey(keyword);
                                if (keyword_ == std::string(infor.keyword)) {
                                    std::cout << block.size[i];
                                    ok = 1;
                                }
                            }
                        } else {
                            std::cout << block.size[i];
                            ok = 1;
                        }
                    }
                }
                file.close();
                if (!ok) throw Invalid();
            } else if (infor.keyword[0] != '\0') {
                std::string ans = file_keyword.FindMore(std::string(infor.keyword));
                bool ok = 0;
                std::fstream file;
                file.open("file_keyword");
                while (ans != "") {
                    Block_<NodeBookKeyword> block;
                    long long locate = CheckNum_(Get(ans));
                    file.seekg(locate);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBookKeyword>));
                    for (int i = 1; i <= block.now; i++) {
                        if (std::string(block.size[i].keyword_) == std::string(infor.keyword)) {
                            std::cout << block.size[i];
                            ok = 1;
                        }
                    }
                }
                file.close();
                if (!ok) throw Invalid();
            } else {
                std::fstream file, file_index;
                file.open("file_book");
                file_index.open("file_book_index");
                NodeIndex_<NodeBook> idx;
                Block_<NodeBook> block;
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_<NodeBook>));
                if (idx.next == -1) {
                    file.close();
                    file_index.close();
                    throw Invalid();
                }
                file_index.seekg(idx.next, std::ios::beg);
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_<NodeBook>));
                while (1) {
                    file.seekg(idx.block_begin);
                    file.read(reinterpret_cast<char *>(&block), sizeof(Block_<NodeBook>));
                    for (int i = 1; i <= block.now; i++)
                        std::cout << block.size[i];
                    if (idx.next == -1) {
                        file.close();
                        file_index.close();
                        return;
                    }
                    file_index.seekg(idx.next, std::ios::beg);
                    file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_<NodeBook>));
                }
            }
        } catch (Invalid) { std::cout << '\n'; }
    }

    virtual void Buy(std::string isbn, int quantity) {
        try {
            if (std::string(select.isbn) != isbn) {
                NodeBook find_book = file_book.Find<NodeBook>(isbn);
                if (find_book.quantity >= quantity) {
                    file_book.Delete(isbn);
                    NodeBookName book_name(find_book);
                    file_name.Delete(book_name);
                    NodeBookAuthor book_author(find_book);
                    file_author.Delete(book_author);
                    NodeBookKeyword book_key(find_book);
                    std::string keyword = std::string(find_book.keyword);
                    keyword += "|";
                    while (keyword != "") {
                        std::string keyword_ = GetKey(keyword);
                        strcpy(book_key.keyword_, keyword_.c_str());
                        file_keyword.Delete(book_key);
                    }
                    find_book.quantity -= quantity;
                    file_book.Insert(find_book);
                    book_name.quantity -= quantity;
                    file_name.Insert(book_name);
                    book_author.quantity -= quantity;
                    file_author.Insert(book_author);
                    book_key.quantity -= quantity;
                    keyword = std::string(book_key.keyword);
                    keyword += "|";
                    while (keyword != "") {
                        std::string keyword_ = GetKey(keyword);
                        strcpy(book_key.keyword_, keyword_.c_str());
                        file_keyword.Insert(book_key);
                    }
                    std::cout << std::fixed << std::setprecision(2) << quantity * find_book.price << '\n';
                    FinanceInsert(quantity * find_book.price);
                } else throw Invalid();
            } else {
                if (select.quantity >= quantity) {
                    select.quantity -= quantity;
                    std::cout << std::fixed << std::setprecision(2) << quantity * select.price << '\n';
                    FinanceInsert(quantity * select.price);
                } else throw Invalid();
            }

        } catch (Invalid) { throw Invalid(); }
    }

    virtual void Select(std::string isbn) {
        try {
            if (select.isbn[0] != '\0') {
                NodeBook book = file_book.Find<NodeBook>(std::string(select.isbn));
                file_book.Delete(std::string(select.isbn));
                file_book.Insert(select);
                NodeBookName book_name(book);
                file_name.Delete(book_name);
                book_name = NodeBookName(select);
                file_name.Insert(book_name);
                NodeBookAuthor book_author(book);
                file_author.Delete(book_author);
                book_author = NodeBookAuthor(select);
                file_author.Insert(book_author);
                NodeBookKeyword book_key(book);
                std::string keyword = std::string(book.keyword);
                keyword += "|";
                while (keyword != "") {
                    std::string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Delete(book_key);
                }
                book_key = NodeBookKeyword(select);
                keyword = std::string(select.keyword);
                keyword += "|";
                while (keyword != "") {
                    std::string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Insert(book_key);
                }
            }
        } catch (Invalid) {
            file_book.Insert(select);
            NodeBookName book_name(select);
            file_name.Insert(book_name);
            NodeBookAuthor book_author(select);
            file_author.Insert(book_author);
            NodeBookKeyword book_key(select);
            std::string keyword = std::string(select.keyword);
            keyword += "|";
            while (keyword != "") {
                std::string keyword_ = GetKey(keyword);
                strcpy(book_key.keyword_, keyword_.c_str());
                file_keyword.Insert(book_key);
            }
            try {
                select = file_book.Find<NodeBook>(isbn);
            } catch (Invalid) {
                NodeBook new_book;
                select = new_book;
                strcpy(select.isbn, isbn.c_str());
            }
        }
        try {
            select = file_book.Find<NodeBook>(isbn);
        } catch (Invalid) {
            NodeBook new_book;
            select = new_book;
            strcpy(select.isbn, isbn.c_str());
        }
    }

    virtual void ModifyIsbn(std::string isbn) {
        if (select.isbn[0] == '\0' || std::string(select.isbn) == isbn)
            throw Invalid();
        bool ok = 0;
        try {
            file_book.Find<NodeBook>(isbn);
            ok = 1;
        } catch (Invalid) {
            try {
                file_book.Delete(std::string(select.isbn));
                NodeBookName book_name(select);
                file_name.Delete(book_name);
                NodeBookAuthor book_author(select);
                file_author.Delete(book_author);
                NodeBookKeyword book_key(select);
                std::string keyword = std::string(select.keyword);
                keyword += "|";
                while (keyword != "") {
                    std::string keyword_ = GetKey(keyword);
                    strcpy(book_key.keyword_, keyword_.c_str());
                    file_keyword.Delete(book_key);
                }
                for (int i = 0; i < stk_.size(); i++) {
                    if (std::string(stk_[i].isbn) == std::string(select.isbn)) {
                        strcpy(stk_[i].isbn, isbn.c_str());
                    }
                }
                strcpy(select.isbn, isbn.c_str());
            }
            catch (Invalid) {
                for (int i = 0; i < stk_.size(); i++) {
                    if (std::string(stk_[i].isbn) == std::string(select.isbn)) {
                        strcpy(stk_[i].isbn, isbn.c_str());
                    }
                }
                strcpy(select.isbn, isbn.c_str());
            }
        }
        if (ok) throw Invalid();
    }

    virtual void ModifyName(std::string name) {
        if (select.isbn[0] == '\0')
            throw Invalid();
        strcpy(select.book_name, name.c_str());
    }

    virtual void ModifyAuthor(std::string author) {
        if (select.isbn[0] == '\0')
            throw Invalid();
        strcpy(select.author, author.c_str());
    }

    virtual void ModifyKeyword(std::string keyword) {
        if (select.isbn[0] == '\0')
            throw Invalid();
        strcpy(select.keyword, keyword.c_str());
    }

    virtual void ModifyPrice(double price) {
        if (select.isbn[0] == '\0')
            throw Invalid();
        select.price = price;
    }

    virtual void Import(int quantity, double cost) {
        if (select.isbn[0] == '\0')
            throw Invalid();
        if ((long long) (select.quantity) + (long long) (quantity) > 2147483647)
            throw Invalid();
        select.quantity += quantity;
        FinanceInsert(-1 * cost);
    }

    virtual void ReportMyself() {

    }

    virtual void ShowFinance(int time) {
        if (!time) {
            std::cout << '\n';
            return;
        }
        std::fstream file;
        file.open("file_finance");
        if (!file)
            throw Invalid();
        int time_;
        file.read(reinterpret_cast<char *>(&time_), sizeof(int));
        if (time_ < time) throw Invalid();
        file.seekg(sizeof(int) + sizeof(double) * (time_ - time));
        double finance_plus = 0, finance_minus = 0, finance;
        for (int i = 1; i <= time; i++) {
            file.read(reinterpret_cast<char *>(&finance), sizeof(double));
            if (finance > 0) finance_plus += finance;
            else finance_minus -= finance;
        }
        std::cout << "+ " << std::fixed << std::setprecision(2) << finance_plus << " - " << std::fixed << std::setprecision(2)
                  << finance_minus
                  << '\n';
    }

    virtual void ShowFinance() {
        std::fstream file;
        file.open("file_finance");
        if (!file) {
            std::cout << '\n';
            return;
        }
        int time_;
        file.read(reinterpret_cast<char *>(&time_), sizeof(int));
        file.seekg(sizeof(int));
        double finance_plus = 0, finance_minus = 0, finance;
        for (int i = 1; i <= time_; i++) {
            file.read(reinterpret_cast<char *>(&finance), sizeof(double));
            if (finance > 0) finance_plus += finance;
            else finance_minus -= finance;
        }
        std::cout << "+ " << std::fixed << std::setprecision(2) << finance_plus << " - " << std::fixed
                  << std::setprecision(2)
                  << finance_minus
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
        throw Invalid();
    }

    virtual void ReportEmployee() {
        throw Invalid();
    }

    virtual void Log() {
        throw Invalid();
    }
};

class Consumer : public People {
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
        throw Invalid();
    }

    virtual void ShowFinance(int time) {
        throw Invalid();
    }

    virtual void ShowFinance() {
        throw Invalid();
    }

    virtual void ReportFinance() {
        throw Invalid();
    }

    virtual void ReportEmployee() {
        throw Invalid();
    }

    virtual void Log() {
        throw Invalid();
    }
};

class Visitor : public People {
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
        throw Invalid();
    }

    virtual void ShowFinance(int time) {
        throw Invalid();
    }

    virtual void ShowFinance() {
        throw Invalid();
    }

    virtual void ReportFinance() {
        throw Invalid();
    }

    virtual void ReportEmployee() {
        throw Invalid();
    }

    virtual void Log() {
        throw Invalid();
    }
};

#endif //MAIN_1_CPP_PEOPLE_H
