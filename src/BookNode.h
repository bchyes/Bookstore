#ifndef MAIN_1_CPP_BOOKNODE_H
#define MAIN_1_CPP_BOOKNODE_H

#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

//以ISBN为关键词的书节点
class NodeBook {
public:
    char isbn[22];
    char book_name[62];
    char author[62];
    char keyword[62];
    int quantity;
    double price;

    explicit NodeBook();

    explicit NodeBook(std::string isbn_, std::string name, std::string author_, std::string key, int quantity_,
                      double price_);

    bool operator>(const NodeBook &b);

    bool operator>=(const NodeBook &b);

    bool operator==(const NodeBook &b);

    bool operator>=(const std::string &b);

    bool operator>(const std::string &b);

    bool operator==(const std::string &b);

    NodeBook &operator=(const NodeBook &nod);

    friend std::ostream &operator<<(std::ostream &os, const NodeBook &nod);
};

//以name为关键词
class NodeBookName : public NodeBook {
public:
    explicit NodeBookName();

    explicit NodeBookName(const NodeBook &nod);

    bool operator>(const NodeBookName &b);

    bool operator>=(const NodeBookName &b);

    bool operator==(const NodeBookName &b);

    bool operator>=(const std::string &b);

    bool operator>(const std::string &b);

    bool operator==(const std::string &b);

    NodeBookName &operator=(const NodeBookName &nod);
};

//以作者为关键词
class NodeBookAuthor : public NodeBook {
public:
    explicit NodeBookAuthor();

    explicit NodeBookAuthor(const NodeBook &nod);

    bool operator>(const NodeBookAuthor &b);

    bool operator>=(const NodeBookAuthor &b);

    bool operator==(const NodeBookAuthor &b);

    bool operator>=(const std::string &b);

    bool operator>(const std::string &b);

    bool operator==(const std::string &b);

    NodeBookAuthor &operator=(const NodeBookAuthor &nod);
};

//以keyword为关键词
class NodeBookKeyword : public NodeBook {
public:
    char keyword_[62];//处理提取出来的keyword，即单个单词

    explicit NodeBookKeyword();

    explicit NodeBookKeyword(const NodeBook &nod);

    bool operator>(const NodeBookKeyword &b);

    bool operator>=(const NodeBookKeyword &b);

    bool operator==(const NodeBookKeyword &b);

    bool operator>=(const std::string &b);

    bool operator>(const std::string &b);

    bool operator==(const std::string &b);

    NodeBookKeyword &operator=(const NodeBookKeyword &nod);
};

#endif //MAIN_1_CPP_BOOKNODE_H
