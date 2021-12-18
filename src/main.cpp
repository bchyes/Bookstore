#include"store.h"
#include"People.h"

int CheckNum(std::string num) {
    if (num.length() > 10) throw Invalid();
    if (num.length() == 10) if (num > "2147483647") throw Invalid();
    int ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invalid();
        else ans = ans * 10 + int(num[i] - '0');
    }
    return ans;
}

double CheckDouble(std::string num) {
    if (num.length() > 13) throw Invalid();
    bool dot = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '.' && !dot) {
            dot = 1;
            if (i + 3 != num.length()) throw Invalid();
            continue;
        } else if (num[i] == '.' && dot) throw Invalid();
        if (num[i] > '9' || num[i] < '0')
            throw Invalid();
    }
    return stod(num);
}

void CheckNull(std::string s) {
    if (s != "") throw Invalid();
}

void GetModify(const std::string &op, std::string &type, std::string &infor) {
    if (op[0] != '-') throw Invalid();
    int i;
    for (i = 1; i < op.length(); i++)
        if (op[i] != '=') type += op[i];
        else break;
    if (i == op.length()) throw Invalid();
    if (type != "name" && type != "ISBN" && type != "author" && type != "keyword" && type != "price")
        throw Invalid();
    if (type == "price") {
        if (i + 1 >= op.length()) throw Invalid();
        bool dot = 0;
        for (i++; i < op.length(); i++) {
            if (op[i] == '.' && !dot) {
                dot = 1;
                infor += op[i];
                continue;
            } else if (op[i] == '.' && dot) throw Invalid();
            if (op[i] > '9' || op[i] < '0')
                throw Invalid();
            infor += op[i];
        }
        if (infor.length() > 13) throw Invalid();
    } else if (type == "ISBN") {
        if (i + 1 >= op.length()) throw Invalid();
        for (i++; i < op.length(); i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127) throw Invalid();
            infor += op[i];
        }
        if (infor.length() > 20) throw Invalid();
    } else {
        if (op[i + 1] != '"' || op[op.length() - 1] != '"') throw Invalid();
        if (i + 3 >= op.length()) throw Invalid();
        for (i += 2; i < op.length() - 1; i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127 || op[i] == '"') throw Invalid();
            infor += op[i];
        }
        if (infor.length() > 60) throw Invalid();
    }
}

void GetShow(const std::string &op, std::string &type, std::string &infor) {
    if (op[0] != '-') throw Invalid();
    int i;
    for (i = 1; i < op.length(); i++)
        if (op[i] != '=') type += op[i];
        else break;
    if (i == op.length()) throw Invalid();
    if (type != "name" && type != "ISBN" && type != "author" && type != "keyword")
        throw Invalid();
    if (type == "ISBN") {
        if (i + 1 >= op.length()) throw Invalid();
        for (i++; i < op.length(); i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127) throw Invalid();
            infor += op[i];
        }
        if (infor.length() > 20) throw Invalid();
    } else if (type != "keyword") {
        if (op[i + 1] != '"' || op[op.length() - 1] != '"') throw Invalid();
        if (i + 3 >= op.length()) throw Invalid();
        for (i += 2; i < op.length() - 1; i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127 || op[i] == '"') throw Invalid();
            infor += op[i];
        }
        if (infor.length() > 60) throw Invalid();
    } else {
        if (op[i + 1] != '"' || op[op.length() - 1] != '"') throw Invalid();
        if (i + 3 >= op.length()) throw Invalid();
        for (i += 2; i < op.length() - 1; i++) {
            if (int(op[i]) < 32 || int(op[i]) == 127 || op[i] == '"' || op[i] == '|') throw Invalid();
            infor += op[i];
        }
        if (infor.length() > 60) throw Invalid();
    }
}

//检查数字，字母，下划线
void Check_(std::string s) {
    if (s.length() > 30) throw Invalid();
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
            s[i] == '_')
            continue;
        throw Invalid();
    }
}

//检查不可见字符
void Check_See(std::string s) {
    if (s.length() > 30) throw Invalid();
    for (int i = 0; i < s.length(); i++) {
        if (int(s[i]) < 32 || int(s[i]) == 127) throw Invalid();
    }
}

void CheckIsbn(std::string s) {
    if (s.length() > 20) throw Invalid();
    for (int i = 0; i < s.length(); i++) {
        if (int(s[i]) < 32 || int(s[i]) == 127) throw Invalid();
    }
}

int main() {
    freopen("test_robust.txt", "r", stdin);
    freopen("test_robust.out", "w", stdout);
    std::string s;
    People *account = new Visitor;
    account->Initialize();
    int line = 0;
    while (getline(std::cin, s)) {
        line++;
        if (s.length() > 1024) {
            std::cout << "Invalid" << '\n';
            continue;
        }
        int i;
        for (i = 0; i < s.length(); i++) {
            if (s[i] != ' ') break;
        }
        if (i == s.length()) continue;
        s = s.substr(i);
        bool asc = 0;
        for (int i = 0; i < s.length(); i++) {
            if (!isascii(s[i])) {
                std::cout << "Invalid" << '\n';
                asc = 1;
                break;
            }
        }
        if (asc) continue;
        s += " ";
        std::string token;
        token = Get(s);
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
            catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "logout") {
            try {
                CheckNull(s);
                account->Logout();
                if (stk.empty()) {
                    delete account;
                    account = new Visitor;
                    account->GetSelect();
                } else {
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
            }
            catch (Invalid) { std::cout << "Invalid" << '\n'; }
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
            }
            catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "delete") {
            try {
                std::string id = Get(s);
                Check_(id);
                CheckNull(s);
                account->Delete(id);
            }
            catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "passwd") {
            try {
                std::string id = Get(s);
                Check_(id);
                std::string passwd = Get(s);
                Check_(passwd);
                if (s != "") {
                    std::string new_passwd = Get(s);
                    Check_(new_passwd);
                    CheckNull(s);
                    account->Passwd(id, passwd, new_passwd);
                } else {
                    account->Passwd(id, passwd);
                }
            } catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "select") {
            try {
                std::string isbn = Get(s);
                CheckIsbn(isbn);
                CheckNull(s);
                account->Select(isbn);
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
                        continue;
                    }
                }
                if (token_ != "")
                    s = token_ + " " + s;
                if (s != "") {
                    std::string op = Get(s);
                    CheckNull(s);
                    std::string type, infor;
                    GetShow(op, type, infor);
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
            } catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "buy") {
            try {
                std::string isbn = Get(s);
                CheckIsbn(isbn);
                int quantity = CheckNum(Get(s));
                CheckNull(s);
                account->Buy(isbn, quantity);
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
            } catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "import") {
            try {
                int quantity = CheckNum(Get(s));
                double total_cost = CheckDouble(Get(s));
                CheckNull(s);
                account->Import(quantity, total_cost);
            } catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "exit") {
            try {
                CheckNull(s);
                delete account;
                return 0;
            }
            catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else if (token == "quit") {
            try {
                CheckNull(s);
                delete account;
                return 0;
            }
            catch (Invalid) { std::cout << "Invalid" << '\n'; }
        } else std::cout << "Invalid" << '\n';
    }
    delete account;
}