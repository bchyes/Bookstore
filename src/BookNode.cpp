#include"BookNode.h"

NodeBook::NodeBook() {
    isbn[0] = '\0';
    book_name[0] = '\0';
    author[0] = '\0';
    keyword[0] = '\0';
    quantity = price = 0;
}

NodeBook::NodeBook(std::string isbn_, std::string name, std::string author_, std::string key, int quantity_,
                   double price_) {
    strcpy(isbn, isbn_.c_str());
    strcpy(book_name, name.c_str());
    strcpy(author, author_.c_str());
    strcpy(keyword, key.c_str());
    quantity = quantity_;
    price = price_;

}

bool NodeBook::operator>(const NodeBook &b) {
    return (std::string(this->isbn) > std::string(b.isbn));
}

bool NodeBook::operator>=(const NodeBook &b) {
    return (std::string(this->isbn) >= std::string(b.isbn));

}

bool NodeBook::operator==(const NodeBook &b) {
    return (std::string(this->isbn) == std::string(b.isbn));
}

bool NodeBook::operator>=(const std::string &b) {
    return (std::string(this->isbn) >= b);
}

bool NodeBook::operator>(const std::string &b) {
    return (std::string(this->isbn) > b);
}

bool NodeBook::operator==(const std::string &b) {
    return (std::string(this->isbn) == b);
}

NodeBook &NodeBook::operator=(const NodeBook &nod) {
    if (this == &nod) return (*this);
    strcpy(this->isbn, nod.isbn);
    strcpy(this->book_name, nod.book_name);
    strcpy(this->author, nod.author);
    strcpy(this->keyword, nod.keyword);
    this->quantity = nod.quantity;
    this->price = nod.price;
    return (*this);
}

std::ostream &operator<<(std::ostream &os, const NodeBook &nod) {
    os << std::string(nod.isbn) << '\t' << std::string(nod.book_name) << '\t' << std::string(nod.author) << '\t'
       << std::string(nod.keyword) << '\t' << std::fixed << std::setprecision(2) << nod.price << '\t'
       << nod.quantity
       << '\n';
    return os;
}

NodeBookName::NodeBookName() {
    isbn[0] = '\0';
    book_name[0] = '\0';
    author[0] = '\0';
    keyword[0] = '\0';
    quantity = price = 0;
}

NodeBookName::NodeBookName(const NodeBook &nod){
    strcpy(this->isbn, nod.isbn);
    strcpy(this->book_name, nod.book_name);
    strcpy(this->author, nod.author);
    strcpy(this->keyword, nod.keyword);
    this->quantity = nod.quantity;
    this->price = nod.price;
}

bool NodeBookName::operator>(const NodeBookName &b) {
    return (std::string(this->book_name) > std::string(b.book_name) ||
            (std::string(this->book_name) == std::string(b.book_name) &&
             std::string(this->isbn) > std::string(b.isbn)));
}

bool NodeBookName::operator>=(const NodeBookName &b) {
    return (std::string(this->book_name) > std::string(b.book_name) ||
            (std::string(this->book_name) == std::string(b.book_name) &&
             std::string(this->isbn) >= std::string(b.isbn)));
}

bool NodeBookName::operator==(const NodeBookName &b) {
    return (std::string(this->book_name) == std::string(b.book_name) &&
            std::string(this->isbn) == std::string(b.isbn));
}

bool NodeBookName::operator>=(const std::string &b) {
    return (std::string(this->book_name) >= b);
}

bool NodeBookName::operator>(const std::string &b) {
    return (std::string(this->book_name) > b);
}

bool NodeBookName::operator==(const std::string &b) {
    return (std::string(this->book_name) == b);
}

NodeBookName &NodeBookName::operator=(const NodeBookName &nod) {
    if (this == &nod) return (*this);
    strcpy(this->isbn, nod.isbn);
    strcpy(this->book_name, nod.book_name);
    strcpy(this->author, nod.author);
    strcpy(this->keyword, nod.keyword);
    this->quantity = nod.quantity;
    this->price = nod.price;
    return (*this);
}

NodeBookAuthor::NodeBookAuthor() {
    isbn[0] = '\0';
    book_name[0] = '\0';
    author[0] = '\0';
    keyword[0] = '\0';
    quantity = price = 0;
}

NodeBookAuthor::NodeBookAuthor(const NodeBook &nod) {
    strcpy(this->isbn, nod.isbn);
    strcpy(this->book_name, nod.book_name);
    strcpy(this->author, nod.author);
    strcpy(this->keyword, nod.keyword);
    this->quantity = nod.quantity;
    this->price = nod.price;
}

bool NodeBookAuthor::operator>(const NodeBookAuthor &b) {
    return (std::string(this->author) > std::string(b.author) ||
            (std::string(this->author) == std::string(b.author) && std::string(this->isbn) > std::string(b.isbn)));
}

bool NodeBookAuthor::operator>=(const NodeBookAuthor &b) {
    return (std::string(this->author) > std::string(b.author) ||
            (std::string(this->author) == std::string(b.author) && std::string(this->isbn) >= std::string(b.isbn)));
}

bool NodeBookAuthor::operator==(const NodeBookAuthor &b) {
    return (std::string(this->author) == std::string(b.author) && std::string(this->isbn) == std::string(b.isbn));
}

bool NodeBookAuthor::operator>=(const std::string &b) {
    return (std::string(this->author) >= b);
}

bool NodeBookAuthor::operator>(const std::string &b) {
    return (std::string(this->author) > b);
}

bool NodeBookAuthor::operator==(const std::string &b) {
    return (std::string(this->author) == b);
}

NodeBookAuthor &NodeBookAuthor::operator=(const NodeBookAuthor &nod) {
    if (this == &nod) return (*this);
    strcpy(this->isbn, nod.isbn);
    strcpy(this->book_name, nod.book_name);
    strcpy(this->author, nod.author);
    strcpy(this->keyword, nod.keyword);
    this->quantity = nod.quantity;
    this->price = nod.price;
    return (*this);
}

NodeBookKeyword::NodeBookKeyword() {
    isbn[0] = '\0';
    book_name[0] = '\0';
    author[0] = '\0';
    keyword[0] = '\0';
    keyword_[0] = '\0';
    quantity = price = 0;
}

NodeBookKeyword::NodeBookKeyword(const NodeBook &nod) {
    strcpy(this->isbn, nod.isbn);
    strcpy(this->book_name, nod.book_name);
    strcpy(this->author, nod.author);
    strcpy(this->keyword, nod.keyword);
    this->keyword_[0] = '\0';
    this->quantity = nod.quantity;
    this->price = nod.price;
}

bool NodeBookKeyword::operator>(const NodeBookKeyword &b) {
    return (std::string(this->keyword_) > std::string(b.keyword_) ||
            (std::string(this->keyword_) == std::string(b.keyword_) &&
             std::string(this->isbn) > std::string(b.isbn)));
}

bool NodeBookKeyword::operator>=(const NodeBookKeyword &b) {
    return (std::string(this->keyword_) > std::string(b.keyword_) ||
            (std::string(this->keyword_) == std::string(b.keyword_) &&
             std::string(this->isbn) >= std::string(b.isbn)));
}

bool NodeBookKeyword::operator==(const NodeBookKeyword &b) {
    return (std::string(this->keyword_) == std::string(b.keyword_) &&
            std::string(this->isbn) == std::string(b.isbn));
}

bool NodeBookKeyword::operator>=(const std::string &b) {
    return (std::string(this->keyword_) >= b);
}

bool NodeBookKeyword::operator>(const std::string &b) {
    return (std::string(this->keyword_) > b);
}

bool NodeBookKeyword::operator==(const std::string &b) {
    return (std::string(this->keyword_) == b);
}

NodeBookKeyword &NodeBookKeyword::operator=(const NodeBookKeyword &nod) {
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