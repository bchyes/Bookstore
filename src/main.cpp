#include"store.h"
#include"People.h"

int CheckNum(string num) {
    int ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invaild();
        else ans = ans * 10 + int(num[i] - '0');
    }
    return ans;
}

double CheckDouble(string num) {
    bool dot = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '.' && !dot) dot = 1;
        else if (num[i] == '.' && dot) throw Invaild();
        if (num[i] > '9' || num[i] < '0')
            throw Invaild();
    }
    return stod(num);
}

void CheckNull(string s) {
    if (s != "") throw Invaild();
}

void Getop(const string &op, string &type, string &infor) {
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

void Getop_(const string &op, string &type, string &infor) {
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

/*double GetDouble(string infor) {
    double x = 0;
    int i;
    for (i = 0; i < infor.length(); i++) {
        if (infor[i] == '.') break;
        x = x * 10 + 1.0 * int(infor[i] - '0');
    }
    if (i < infor.length()) {
        x += 0.1 * int(infor[i] - '0');
        i++;
    }
    if (i < infor.length()) {
        x += 0.01 * int(infor[i] - '0');
        i++;
    }
    if (i < infor.length()) {
        if (int(infor[i] - '0') >= 5)
            x += 0.01;
    }
    return x;
}*/

int main() {
    freopen("testcase4.txt", "r", stdin);
    freopen("4.out", "w", stdout);
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
            } catch (Invaild) { cout << line << '\n'; }
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
                return 0;
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } else if (token == "quit") {
            try {
                CheckNull(s);
                return 0;
            }
            catch (Invaild) { cout << "Invaild" << " " << line << '\n'; }
        } //else cout << "Invaild" << " " << line << '\n';
    }
}