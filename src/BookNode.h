#ifndef MAIN_1_CPP_BOOKNODE_H
#define MAIN_1_CPP_BOOKNODE_H
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

#endif //MAIN_1_CPP_BOOKNODE_H
