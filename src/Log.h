#ifndef MAIN_1_CPP_LOG_H
#define MAIN_1_CPP_LOG_H
class EmployeeLog {
public:
    char type[22];
    //char op[102];
    int time;
    char name[62];
    int priority;
    NodePeople people_last;
    NodePeople people_new;
    NodeBook book_last;
    NodeBook book_new;
    double finance;

    explicit EmployeeLog() {
        type[0] = '\0';
        //op[0] = '\0';
        time = 0;
        name[0] = '\0';
        priority = 0;
        finance = 0;
    }

    EmployeeLog(const EmployeeLog &nod) {
        strcpy(this->type, nod.type);
        //strcpy(this->op, nod.op);
        strcpy(this->name, nod.name);
        this->time = nod.time;
        this->priority = nod.priority;
        this->people_last = nod.people_last;
        this->people_new = nod.people_new;
        this->book_last = nod.book_last;
        this->book_new = nod.book_new;
        this->finance = nod.finance;
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
        //strcpy(this->op, nod.op);
        strcpy(this->name, nod.name);
        this->time = nod.time;
        this->finance = nod.finance;
        this->priority = nod.priority;
        people_last = nod.people_last;
        people_new = nod.people_new;
        book_last = nod.book_last;
        book_new = nod.book_new;
        return (*this);
    }

    void InsertPeopleLast(const NodePeople &peo) {
        people_last = peo;
    }

    void InsertPeopleNew(const NodePeople &peo) {
        people_new = peo;
    }

    void InsertBookLast(const NodeBook &book) {
        book_last = book;
    }

    void InsertBookNew(const NodeBook &book) {
        book_new = book;
    }

    friend std::ostream &operator<<(std::ostream &os, const EmployeeLog &nod) {
        return os;
    }

    void PrintPeopleTitle(std::fstream &report) {
        report << '|';
        report << std::left << std::setw(30) << "User-ID" << '\t' << '|';
        report << std::left << std::setw(30) << "User-name" << '\t' << '|';
        report << std::left << std::setw(10) << "Priority" << '\t' << '|';
        report << std::left << std::setw(30) << "Password" << '\t';
        report << '\n';
    }

    void PrintBookTitle(std::fstream &report) {
        report << '|';
        report << std::left << std::setw(20) << "ISBN" << '\t' << '|';
        report << std::left << std::setw(60) << "Book-Name" << '\t' << '|';
        report << std::left << std::setw(60) << "Keyword" << '\t' << '|';
        report << std::left << std::setw(13) << "Price" << '\t' << '|';
        report << std::left << std::setw(10) << "Quantity" << '\t';
        report << '\n';
    }

    void PrintPeopleLast(std::fstream &report) {
        report << '|';
        report << std::left << std::setw(30) << std::string(people_last.user_id) << '\t' << '|';
        report << std::left << std::setw(30) << std::string(people_last.user_name) << '\t' << '|';
        report << std::left << std::setw(10) << people_last.priority << '\t' << '|';
        report << std::left << std::setw(30) << std::string(people_last.password) << '\t';
        report << '\n';
    }

    void PrintPeopleNew(std::fstream &report) {
        report << '|';
        report << std::left << std::setw(30) << std::string(people_new.user_id) << '\t' << '|';
        report << std::left << std::setw(30) << std::string(people_new.user_name) << '\t' << '|';
        report << std::left << std::setw(10) << people_new.priority << '\t' << '|';
        report << std::left << std::setw(30) << std::string(people_new.password) << '\t';
        report << '\n';
        for (int i = 1; i <= 112; i++)
            report << '-';
        report << '\n';
    }

    void PrintBookLast(std::fstream &report) {
        report << '|';
        report << std::left << std::setw(20) << std::string(book_last.isbn) << '\t' << '|';
        report << std::left << std::setw(60) << std::string(book_last.book_name) << '\t' << '|';
        report << std::left << std::setw(60) << std::string(book_last.keyword) << '\t' << '|';
        report << std::left << std::setw(13) << book_last.price << '\t' << '|';
        report << std::left << std::setw(10) << book_last.quantity << '\t';
        report << '\n';
    }

    void PrintBookNew(std::fstream &report) {
        report << '|';
        report << std::left << std::setw(20) << std::string(book_new.isbn) << '\t' << '|';
        report << std::left << std::setw(60) << std::string(book_new.book_name) << '\t' << '|';
        report << std::left << std::setw(60) << std::string(book_new.keyword) << '\t' << '|';
        report << std::left << std::setw(13) << book_new.price << '\t' << '|';
        report << std::left << std::setw(10) << book_new.quantity << '\t';
        report << '\n';
        for (int i = 1; i <= 185; i++)
            report << '-';
        report << '\n';
    }
};

#endif //MAIN_1_CPP_LOG_H
