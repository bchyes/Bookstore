#ifndef MAIN_1_CPP_COMMAND_H
#define MAIN_1_CPP_COMMAND_H
extern std::vector<NodePeople> stk;
extern std::vector<NodeBook> stk_;
extern Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file_people;
extern Store<NodeIndex_<NodeBook>, Block_<NodeBook>> file_book;
extern Store<NodeIndex_<NodeBookName>, Block_<NodeBookName>> file_name;
extern Store<NodeIndex_<NodeBookAuthor>, Block_<NodeBookAuthor>> file_author;
extern Store<NodeIndex_<NodeBookKeyword>, Block_<NodeBookKeyword>> file_keyword;
extern Store<NodeIndex_<EmployeeLog>, Block_<EmployeeLog>> file_employee;

void Command(std::string s, BaseAccount *account, int &line) {
    if (s.length() > 1024) {
        std::cout << "Invalid" << '\n';
        return;
    }
    int i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] != ' ') break;
    }
    if (i == s.length()) return;
    s = s.substr(i);
    bool asc = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!isascii(s[i])) {
            std::cout << "Invalid" << '\n';
            asc = 1;
            break;
        }
    }
    if (asc) return;
    s += " ";
    std::string token;
    token = Get(s);
    EmployeeLog employee;
    if (!stk.empty()) strcpy(employee.name, stk.back().user_name);
    strcpy(employee.type, token.c_str());
    employee.time = line;
    if (!stk.empty()) employee.priority = stk.back().priority;
    if (token == "su") {
        try {
            std::string id = Get(s);
            Check_(id);
            if (s != "") {
                std::string passwd = Get(s);
                Check_(passwd);
                CheckNull(s);
                account->Su(id, passwd);
                NodePeople new_account = stk[stk.size() - 1];
                employee.InsertPeopleNew(stk.back());
                account->AddMessage(employee);
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
                employee.InsertPeopleNew(stk.back());
                account->AddMessage(employee);
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
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "logout") {
        try {
            CheckNull(s);
            if (stk.size() > 1) {
                employee.InsertPeopleNew(stk[stk.size() - 2]);
                account->AddMessage(employee);
            }
            account->Logout();
            if (stk.empty()) {
                delete account;
                account = new Visitor;
                account->GetSelect();
            } else {
                employee.InsertPeopleNew(stk.back());
                NodePeople new_account = stk[stk.size() - 1];
                if (new_account.priority == 7) {
                    delete account;
                    account = new Manager;
                    account->GetSelect();
                } else if (new_account.priority == 3) {
                    delete account;
                    account = new Employee;
                    account->GetSelect();
                } else if (new_account.priority == 1) {
                    delete account;
                    account = new Consumer;
                    account->GetSelect();
                }
            }
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "useradd") {
        try {
            std::string id = Get(s);
            Check_(id);
            std::string passwd = Get(s);
            Check_(passwd);
            int priority = CheckNum(Get(s));
            if (priority != 7 && priority != 3 && priority != 1) throw Invalid();
            std::string name = Get(s);
            CheckNull(s);
            Check_See(name);
            account->Useradd(id, passwd, priority, name);
            employee.InsertPeopleNew(file_people.Find<NodePeople>(id));
            account->AddMessage(employee);
        }
        catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "register") {
        try {
            std::string id = Get(s);
            Check_(id);
            std::string passwd = Get(s);
            Check_(passwd);
            std::string name = Get(s);
            Check_See(name);
            CheckNull(s);
            account->Register(id, passwd, name);
            employee.InsertPeopleNew(file_people.Find<NodePeople>(id));
            account->AddMessage(employee);
        }
        catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "delete") {
        try {
            std::string id = Get(s);
            Check_(id);
            CheckNull(s);
            employee.InsertPeopleNew(file_people.Find<NodePeople>(id));
            account->Delete(id);
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "passwd") {
        try {
            std::string id = Get(s);
            Check_(id);
            std::string passwd = Get(s);
            Check_(passwd);
            employee.InsertPeopleLast(file_people.Find<NodePeople>(id));
            if (s != "") {
                std::string new_passwd = Get(s);
                Check_(new_passwd);
                CheckNull(s);
                account->Passwd(id, passwd, new_passwd);
            } else {
                account->Passwd(id, passwd);
            }
            employee.InsertPeopleNew(file_people.Find<NodePeople>(id));
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "select") {
        try {
            std::string isbn = Get(s);
            CheckIsbn(isbn);
            CheckNull(s);
            //employee.InsertBookLast(account->select);
            account->Select(isbn);
            employee.InsertBookNew(account->select);
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "show") {
        try {
            ShowMessage mess;
            std::string token_ = "";
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
                    //strcpy(employee.type, "show finance");
                    //account->AddMessage(employee);
                    return;
                }
            }
            if (token_ != "")
                s = token_ + " " + s;
            std::string type, infor;
            if (s != "") {
                std::string op = Get(s);
                CheckNull(s);
                GetShow(op, type, infor);
                if (account->select.isbn[0] != '\0') account->Select(std::string(account->select.isbn));
                if (type == "ISBN") {
                    strcpy(mess.isbn, infor.c_str());
                    //employee.InsertBookLast(file_book.Find<NodeBook>(infor));
                } else if (type == "name") {
                    strcpy(mess.book_name, infor.c_str());
                    //employee.InsertBookLast(file_name.Find<NodeBookName>(infor));
                } else if (type == "author") {
                    strcpy(mess.author, infor.c_str());
                    //employee.InsertBookLast(file_author.Find<NodeBookAuthor>(infor));
                } else if (type == "keyword") {
                    strcpy(mess.keyword, infor.c_str());
                    //employee.InsertBookLast(file_keyword.Find<NodeBookKeyword>(infor));
                }
            }
            account->Show(mess);
            if (type == "ISBN") {
                employee.InsertBookNew(file_book.Find<NodeBook>(infor));
            } else if (type == "name") {
                employee.InsertBookNew(file_name.Find<NodeBookName>(infor));
            } else if (type == "author") {
                employee.InsertBookNew(file_author.Find<NodeBookAuthor>(infor));
            } else if (type == "keyword") {
                employee.InsertBookNew(file_keyword.Find<NodeBookKeyword>(infor));
            }
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "buy") {
        try {
            std::string isbn = Get(s);
            CheckIsbn(isbn);
            int quantity = CheckNum(Get(s));
            CheckNull(s);
            employee.InsertBookLast(file_book.Find<NodeBook>(isbn));
            account->Buy(isbn, quantity);
            employee.InsertBookNew(file_book.Find<NodeBook>(isbn));
            employee.finance = 1.0 * quantity * file_book.Find<NodeBook>(isbn).price;
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "modify") {
        try {
            bool isbn_ = 0, name_ = 0, author_ = 0, keyword_ = 0, price_ = 0;
            std::string s_ = s;
            while (s_ != "") {
                std::string op = Get(s_);
                std::string type, infor;
                GetModify(op, type, infor);
                if (type == "ISBN") {
                    if (isbn_) throw Invalid();
                    isbn_ = 1;
                } else if (type == "name") {
                    if (name_) throw Invalid();
                    name_ = 1;
                } else if (type == "author") {
                    if (author_) throw Invalid();
                    author_ = 1;
                } else if (type == "keyword") {
                    if (keyword_) throw Invalid();
                    std::vector<std::string> key;
                    infor += "|";
                    while (infor != "") {
                        std::string key_ = GetKey(infor);
                        for (int i = 0; i < key.size(); i++)
                            if (key_ == key[i]) throw Invalid();
                        key.push_back(key_);
                    }
                    keyword_ = 1;
                } else if (type == "price") {
                    if (price_) throw Invalid();
                    price_ = 1;
                }
            }
            while (s != "") {
                std::string op = Get(s);
                std::string type, infor;
                GetModify(op, type, infor);
                employee.InsertBookLast(account->select);
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
                employee.InsertBookNew(account->select);
                account->AddMessage(employee);
                employee.time++;
                line++;
            }
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "import") {
        try {
            int quantity = CheckNum(Get(s));
            double total_cost = CheckDouble(Get(s));
            CheckNull(s);
            employee.InsertBookLast(account->select);
            account->Import(quantity, total_cost);
            employee.InsertBookNew(account->select);
            employee.finance = -1.0 * total_cost;
            account->AddMessage(employee);
        } catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "exit") {
        try {
            CheckNull(s);
            //account->AddMessage(employee);
            delete account;
            exit(0);
        }
        catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "quit") {
        try {
            CheckNull(s);
            //account->AddMessage(employee);
            delete account;
            exit(0);
        }
        catch (Invalid) { std::cout << "Invalid" << '\n'; }
    } else if (token == "report") {
        std::string token_ = Get(s);
        if (token_ == "myself") {
            account->ReportMyself();
        } else if (token_ == "employee") {
            account->ReportEmployee();
        } else if (token_ == "finance") {
            account->ReportFinance();
        }
    } else if (token == "log") {
        account->Log();
    } else std::cout << "Invalid" << '\n';
}

#endif //MAIN_1_CPP_COMMAND_H
