#ifndef MAIN_1_CPP_PEOPLE_H
#define MAIN_1_CPP_PEOPLE_H

class EmployeeLog {
public:
    char type[22];
    char op[102];
    int time;
    char name[62];

    explicit EmployeeLog() {
        type[0] = '\0';
        op[0] = '\0';
        time = 0;
        name[0] = '\0';
    }

    explicit EmployeeLog(const EmployeeLog &nod) {
        strcpy(this->type, nod.type);
        strcpy(this->op, nod.op);
        strcpy(this->name, nod.name);
        this->time = nod.time;
    }

    bool operator>(const EmployeeLog &b) {
        return (std::string(this->name) > std::string(b.name) ||
                (std::string(this->name) == std::string(b.name) &&
                 this->time > b.time));
    }

    bool operator>=(const EmployeeLog &b) {
        return (std::string(this->name) > std::string(b.name) ||
                (std::string(this->name) == std::string(b.name) &&
                 this->time >= b.time));
    }

    bool operator==(const EmployeeLog &b) {
        return ((std::string(this->name) == std::string(b.name) && this->time == b.time));
    }

    bool operator>=(const std::string &b) {
        return (std::string(this->name) >= b);
    }

    bool operator>(const std::string &b) {
        return (std::string(this->name) > b);
    }

    bool operator==(const std::string &b) {
        return (std::string(this->name) == b);
    }

    EmployeeLog &operator=(const EmployeeLog &nod) {
        if (this == &nod) return (*this);
        strcpy(this->type, nod.type);
        strcpy(this->op, nod.op);
        strcpy(this->name, nod.name);
        this->time = nod.time;
        return (*this);
    }

    friend std::ostream &operator<<(std::ostream &os, const EmployeeLog &nod) {
        os << std::string(nod.type) << "\t" << std::string(nod.op) << '\n';
        return os;
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
Store<NodeIndex_<EmployeeLog>, Block_<EmployeeLog>> file_employee("file_employee", "file_employee_index",
                                                                  "file_employee_delete");

void AddEmployeeMessage(EmployeeLog message) {
    std::fstream file;
    file.open("file_employee_all");
    if (!file) {
        file.open("file_employee_all", std::fstream::out);
        file.close();
        file.open("file_employee_all");
    }
    file.seekp(0, std::ios::end);
    std::cout << message;
    file.close();
}

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
        std::cout << "+ " << std::fixed << std::setprecision(2) << finance_plus << " - " << std::fixed
                  << std::setprecision(2)
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
