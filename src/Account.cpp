#include "Account.h"
BaseAccount::~BaseAccount() {
    if (select.isbn[0] != '\0') Select(std::string(select.isbn));
}

void BaseAccount::Initialize() {
    People root("root", "", "sjtu", 7);
    file_BaseAccount.Initialize<People>(root);
}

void BaseAccount::Su(std::string id, std::string password) {
    People BaseAccount = file_BaseAccount.Find<People>(id);
    if (BaseAccount.password == password) {
        stk.push_back(BaseAccount);
        stk_.push_back(select);
    } else throw Invalid();
}

void BaseAccount::Su(std::string id) {
    if (stk.empty()) throw Invalid();
    People BaseAccount = file_BaseAccount.Find<People>(id);
    People peo = stk[stk.size() - 1];
    if (peo.priority > BaseAccount.priority) {
        stk.push_back(BaseAccount);
        stk_.push_back(select);
    } else throw Invalid();
}

void BaseAccount::Logout() {
    stk.pop_back();
}

void BaseAccount::GetSelect() {
    select = stk_[stk_.size() - 1];
    stk_.pop_back();
    if (select.isbn[0] != '\0') select = file_book.Find<NodeBook>(std::string(select.isbn));
}

void BaseAccount::Register(std::string id, std::string password, std::string user_name) {
    People BaseAccount(id, user_name, password, 1);
    try {
        file_BaseAccount.Insert(BaseAccount);
    } catch (Invalid) { throw Invalid(); }
}

void BaseAccount::Passwd(std::string id, std::string old_passwd, std::string new_passwd) {
    try {
        People BaseAccount = file_BaseAccount.Find<People>(id);
        if (BaseAccount.password == old_passwd) {
            strcpy(BaseAccount.password, new_passwd.c_str());
            file_BaseAccount.Delete(id);
            file_BaseAccount.Insert(BaseAccount);
        } else throw Invalid();
    } catch (Invalid) { throw Invalid(); }
}

void BaseAccount::Passwd(std::string id, std::string new_passwd) {
    try {
        People BaseAccount = file_BaseAccount.Find<People>(id);
        strcpy(BaseAccount.password, new_passwd.c_str());
        file_BaseAccount.Delete(id);
        file_BaseAccount.Insert(BaseAccount);
    } catch (Invalid) { throw Invalid(); }
}

void BaseAccount::Useradd(std::string id, std::string password, int priority, std::string user_name) {
    People now_BaseAccount = stk[stk.size() - 1];
    if (priority >= now_BaseAccount.priority) throw Invalid();
    People BaseAccount(id, user_name, password, priority);
    try {
        file_BaseAccount.Insert(BaseAccount);
    } catch (Invalid) { throw Invalid(); }
}

void BaseAccount::Delete(std::string id) {
    for (int i = 0; i < stk.size(); i++)
        if (stk[i].user_id == id)
            throw Invalid();
    try {
        file_BaseAccount.Delete(id);
    } catch (Invalid) { throw Invalid(); }
}

void BaseAccount::Show(ShowMessage infor) {
    try {
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
                Block_ <NodeBookName> block;
                long long locate = CheckNum_(Get(ans));
                file.seekg(locate);
                file.read(reinterpret_cast<char *>(&block), sizeof(Block_ < NodeBookName > ));
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
                Block_ <NodeBookAuthor> block;
                long long locate = CheckNum_(Get(ans));
                file.seekg(locate, std::ios::beg);
                file.read(reinterpret_cast<char *>(&block), sizeof(Block_ < NodeBookAuthor > ));
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
                Block_ <NodeBookKeyword> block;
                long long locate = CheckNum_(Get(ans));
                file.seekg(locate);
                file.read(reinterpret_cast<char *>(&block), sizeof(Block_ < NodeBookKeyword > ));
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
            NodeIndex_ <NodeBook> idx;
            Block_ <NodeBook> block;
            file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_ < NodeBook > ));
            if (idx.next == -1) {
                file.close();
                file_index.close();
                throw Invalid();
            }
            file_index.seekg(idx.next, std::ios::beg);
            file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_ < NodeBook > ));
            while (1) {
                file.seekg(idx.block_begin);
                file.read(reinterpret_cast<char *>(&block), sizeof(Block_ < NodeBook > ));
                for (int i = 1; i <= block.now; i++)
                    std::cout << block.size[i];
                if (idx.next == -1) {
                    file.close();
                    file_index.close();
                    return;
                }
                file_index.seekg(idx.next, std::ios::beg);
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex_ < NodeBook > ));
            }
        }
    } catch (Invalid) { std::cout << '\n'; }
}

void BaseAccount::Buy(std::string isbn, int quantity) {
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

void BaseAccount::Select(std::string isbn) {
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

void BaseAccount::ModifyIsbn(std::string isbn) {
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

void BaseAccount::ModifyName(std::string name) {
    if (select.isbn[0] == '\0')
        throw Invalid();
    strcpy(select.book_name, name.c_str());
}

void BaseAccount::ModifyAuthor(std::string author) {
    if (select.isbn[0] == '\0')
        throw Invalid();
    strcpy(select.author, author.c_str());
}

void BaseAccount::ModifyKeyword(std::string keyword) {
    if (select.isbn[0] == '\0')
        throw Invalid();
    strcpy(select.keyword, keyword.c_str());
}

void BaseAccount::ModifyPrice(double price) {
    if (select.isbn[0] == '\0')
        throw Invalid();
    select.price = price;
}

void BaseAccount::Import(int quantity, double cost) {
    if (select.isbn[0] == '\0')
        throw Invalid();
    if ((long long) (select.quantity) + (long long) (quantity) > 2147483647)
        throw Invalid();
    select.quantity += quantity;
    FinanceInsert(-1 * cost);
}

void BaseAccount::AddMessage(const EmployeeLog &employee) {
    file_employee.Insert(employee);
}

void BaseAccount::Report(Block_<EmployeeLog> employee, std::fstream &report, int i) {
    if (std::string(employee.size[i].type) == "su") {
        report << "Su" << '\n';
        report << "Sued Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountNew(report);
    } else if (std::string(employee.size[i].type) == "logout") {
        report << "Logout" << '\n';
        if (employee.size[i].BaseAccount_new.user_id[0] == '\0') {
            report << "Nobody Sued" << '\n';
            return;
        }
        report << "Sued Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountNew(report);
    } else if (std::string(employee.size[i].type) == "useradd") {
        report << "Useradd" << '\n';
        report << "Added Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountNew(report);
    } else if (std::string(employee.size[i].type) == "register") {
        report << "Register" << '\n';
        report << "Added Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountNew(report);
    } else if (std::string(employee.size[i].type) == "delete") {
        report << "Delete" << '\n';
        report << "Delete Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountNew(report);
    } else if (std::string(employee.size[i].type) == "passwd") {
        report << "Password Change" << '\n';
        report << "Old Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountLast(report);
        report << "New Account Information" << '\n';
        employee.size[i].PrintBaseAccountTitle(report);
        employee.size[i].PrintBaseAccountNew(report);
    } else if (std::string(employee.size[i].type) == "select") {
        report << "Select" << '\n';
        report << "Select Book Information" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookNew(report);
    } else if (std::string(employee.size[i].type) == "show") {
        report << "Show" << '\n';
        report << "Show Book Information" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookNew(report);
    } else if (std::string(employee.size[i].type) == "buy") {
        report << "Buy" << '\n';
        report << "Buy Book Information" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookLast(report);
        report << "To" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookNew(report);
    } else if (std::string(employee.size[i].type) == "modify") {
        report << "Modify" << '\n';
        report << "Modify Book Information" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookLast(report);
        report << "To" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookNew(report);
    } else if (std::string(employee.size[i].type) == "import") {
        report << "Import" << '\n';
        report << "Import Book Information" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookLast(report);
        report << "To" << '\n';
        employee.size[i].PrintBookTitle(report);
        employee.size[i].PrintBookNew(report);
    }
}

void BaseAccount::ReportForFinance(Block_<EmployeeLog> employee, std::fstream &report, int i) {
    if (employee.size[i].finance > 0) {
        report << "+[收入]: [" << employee.size[i].name << "] buy ["
               << employee.size[i].book_last.quantity - employee.size[i].book_new.quantity << "] of ["
               << employee.size[i].book_new.book_name << "] (price:" << std::fixed << std::setprecision(2)
               << employee.size[i].finance << ")" << '\n';
    } else {
        report << "+[支出]: [" << employee.size[i].name << "] import ["
               << employee.size[i].book_new.quantity - employee.size[i].book_last.quantity << "] of ["
               << employee.size[i].book_new.book_name << "] (price:" << std::fixed << std::setprecision(2)
               << employee.size[i].finance << ")" << '\n';
    }
    for (int j = 1; j <= 100; j++)
        report << '-';
    report << '\n';
}

void BaseAccount::ReportMyself() {
    std::string ans = file_employee.FindMore(std::string(stk.back().user_name));
    std::fstream file;
    file.open("file_employee");
    if (!file) {
        return;
    }
    std::fstream report;
    report.open("report_myself", std::fstream::out);
    while (ans != "") {
        long long locate = CheckNum_(Get(ans));
        file.seekg(locate);
        Block_ <EmployeeLog> employee;
        file.read(reinterpret_cast<char *>(&employee), sizeof(Block_ < EmployeeLog > ));
        report << "Employee named " << std::left << std::setw(30) << std::string(stk.back().user_name) << '\n';
        report << "Report My Work" << '\n';
        report << '\n';
        for (int i = 1; i <= employee.now; i++) {
            if (std::string(employee.size[i].name) == std::string(stk.back().user_name)) {
                Report(employee, report, i);
            }
        }
    }
}

void BaseAccount::FinanceInsert(double finance) {
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

void BaseAccount::ShowFinance(int time) {
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

void BaseAccount::ShowFinance() {
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

void BaseAccount::ReportFinance() {
    std::fstream file;
    std::fstream file_index;
    std::string name = " ";
    file.open("file_employee");
    if (!file) return;
    std::fstream report("report_finance", std::fstream::out);
    file_index.open("file_employee_index");
    NodeIndex_<EmployeeLog> employee_index;
    Block_<EmployeeLog> employee;
    file_index.seekg(0);
    file_index.read(reinterpret_cast<char *>(&employee_index), sizeof(NodeIndex_<EmployeeLog>));
    while (employee_index.next != -1) {
        file_index.seekg(employee_index.next);
        file_index.read(reinterpret_cast<char *>(&employee_index), sizeof(NodeIndex_<EmployeeLog>));
        file.seekg(employee_index.block_begin);
        file.read(reinterpret_cast<char *>(&employee), sizeof(Block_<EmployeeLog>));
        for (int i = 1; i <= employee.now; i++) {
            if (!employee.size[i].finance) continue;
            if (name != std::string(employee.size[i].name)) {
                if (name != " ") {
                    report << '\n';
                    report << "Employee named " << std::left << std::setw(30) << std::string(employee.size[i].name)
                           << '\n';
                } else report << "Manager" << '\n';
                report << "Report My Finance" << '\n';
                report << '\n';
                name = std::string(employee.size[i].name);
            }

            ReportForFinance(employee, report, i);
        }
    }
}

void BaseAccount::ReportEmployee() {
    std::fstream file;
    std::fstream file_index;
    std::string name = "";
    file.open("file_employee");
    if (!file) return;
    std::fstream report("report_employee", std::fstream::out);
    file_index.open("file_employee_index");
    NodeIndex_ <EmployeeLog> employee_index;
    Block_ <EmployeeLog> employee;
    file_index.seekg(0);
    file_index.read(reinterpret_cast<char *>(&employee_index), sizeof(NodeIndex_ < EmployeeLog > ));
    while (employee_index.next != -1) {
        file_index.seekg(employee_index.next);
        file_index.read(reinterpret_cast<char *>(&employee_index), sizeof(NodeIndex_ < EmployeeLog > ));
        file.seekg(employee_index.block_begin);
        file.read(reinterpret_cast<char *>(&employee), sizeof(Block_ < EmployeeLog > ));
        for (int i = 1; i <= employee.now; i++) {
            if (employee.size[i].priority != 3) continue;
            if (name != std::string(employee.size[i].name)) {
                if (name != "") report << '\n';
                report << "Employee named " << std::left << std::setw(30) << std::string(employee.size[i].name)
                       << '\n';
                report << "Report My Work" << '\n';
                report << '\n';
                name = std::string(employee.size[i].name);
            }
            Report(employee, report, i);
        }
    }
}

void BaseAccount::Log() {
    std::fstream file;
    std::fstream file_index;
    std::string name = " ";
    file.open("file_employee");
    if (!file) return;
    std::fstream report("log", std::fstream::out);
    file_index.open("file_employee_index");
    NodeIndex_ <EmployeeLog> employee_index;
    Block_ <EmployeeLog> employee;
    file_index.seekg(0);
    file_index.read(reinterpret_cast<char *>(&employee_index), sizeof(NodeIndex_ < EmployeeLog > ));
    while (employee_index.next != -1) {
        file_index.seekg(employee_index.next);
        file_index.read(reinterpret_cast<char *>(&employee_index), sizeof(NodeIndex_ < EmployeeLog > ));
        file.seekg(employee_index.block_begin);
        file.read(reinterpret_cast<char *>(&employee), sizeof(Block_ < EmployeeLog > ));
        for (int i = 1; i <= employee.now; i++) {
            if (name != std::string(employee.size[i].name)) {
                if (name != " ") {
                    report << '\n';
                    report << "Employee named " << std::left << std::setw(30) << std::string(employee.size[i].name)
                           << '\n';
                } else report << "Manager" << '\n';
                report << "Report My Log" << '\n';
                report << '\n';
                name = std::string(employee.size[i].name);
            }
            Report(employee, report, i);
            if (employee.size[i].finance) {
                report << "Last report's finance record" << '\n';
                ReportForFinance(employee, report, i);
            }
        }
    }
}
