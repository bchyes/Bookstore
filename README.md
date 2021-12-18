

# Bookstore

> 包晨豪

## 文件储存

所有账户与所有图书 均以二进制文件储存，并用块状链表维护

财务收支用二进制，顺序储存

所有员工的操作 以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

财务信息 日志类 以ASCLL文件直接储存

## 代码文件结构

main函数

```c++
#include"store.h"//储存块链的系统
#include"Node.h"//储存块链的每个实例化的Node节点的定义
#include"People.h"//储存People类的操作，即每个账户的操作
vector<NodePeople> stk;//登陆栈
vector<NodeBook> stk_;//储存登陆栈中的人所选择的书，在后面对于选择的书有操作的时候，需要进行刷新
Store<NodeIndex_<NodePeople>, Block_<NodePeople>> file_people("file_people", "file_people_index", "file_people_delete");
Store<NodeIndex_<NodeBook>, Block_<NodeBook>> file_book("file_book", "file_book_index", "file_book_delete");
Store<NodeIndex_<NodeBookName>, Block_<NodeBookName>> file_name("file_name", "file_name_index", "file_name_delete");
Store<NodeIndex_<NodeBookAuthor>, Block_<NodeBookAuthor>> file_author("file_author", "file_author_index",
                                                                      "file_author_delete");
Store<NodeIndex_<NodeBookKeyword>, Block_<NodeBookKeyword>> file_keyword("file_keyword", "file_keyword_index",
                                                                         "file_keyword_delete");
//模板类储存文件，储存形式及节点内容于块状链表下方内描述
string GetKey(string &key);//得到一个keyword中的一个关键词

string Get(string &s);//得到一个以空格分开的一个字符串,并处理多余空格

long long CheckNum_(string num);//判断是否是long long，否则throw，用于处理文件读写的位置
int CheckNum(string num);//判断是否是int，否则throw,需要考虑题中的大于int上限的情况

double CheckDouble(string num); //判断是否是double，否则throw，需要判断是否是点和数字构成，和长度，且精度为小数点后两位

void CheckNull(string s); //判断字符串是否为空，用来检查鲁棒性

void GetModify(const string &op, string &type, string &infor);//处理modify后面所跟的信息，返回处理的type和内容infor，记得判断长度

void GetShow(const string &op, string &type, string &infor); //处理show后面所跟的信息，返回处理的type和内容infor,记得判断长度

People *account;//处理每个账户的权限，见下文的处理

void ProcessLine(const string &type,string op);//处理信息

int main() {
    string s;
    account = new Visitor;//新建一个Visitor的账户
    account->Initialize();//初始化root
    while (getline(cin, s)) {
        s += " ";
        string token;
        token = Get(s);
        ProcessLine(type,s);//将指令类型和需要处理的内容传进函数处理
}
```

通过如上的算法来调用指令

## 接口与成员说明

账户与图书系统

```c++
class People {

};

class Manager : public People {

};

class Employee : public People {

};

class Custom : public People {

};

class Visitor : public People {

};
```

定义如上的类

将功能的实现写于People中

在派生类中实现没有权限就抛出异常

```c++
class Invaild{};
class People {
    virtual void Su(string id,string pass_word);
};

class Visitor : public People {
public:
    virtual void Su(string id,string pass_word){
        throw Invaild();
    }
};
```

任何main函数的指令通过People进行调用

```c++
class People {
protected:
    NodeBook select;//储存选中的文件
public:
    virtual ~People();//析构账号的时候，如果还有select修改没写进文件就写进去

    virtual void Initialize();//初始化root

    virtual void Su(string id, string password);//密码不对就抛出异常，否则存入vector

    virtual void Su(string id);//取出vector最后一个比较权限

    virtual void Logout();//vector pop_back

    virtual void Register(string id, string password, string user_name);//用insert存进文件（文件里如果重名就要throw）

    virtual void Passwd(string id, string old_passwd, string new_passwd);//先find找到，再delete，再insert（文件里如果重名就要throw）

    virtual void Passwd(string id, string new_passwd);

    virtual void Useradd(string id, string password, int priority, string user_name);//同register

    virtual void Delete(string id);//遍历vector，若在登陆栈，则throw

    virtual void Show(const string &type,string message);//type存show的类型，message存show的信息

    virtual void Buy(string isbn, int quantity);//记得修改所有储存的文件中的元素

    virtual void Select(string isbn);//将上次select的存进所有文件中，共四个文件，再将select从文件中读出来

    virtual void ModifyIsbn(string isbn);//修改ISBN，不能修改成已有的或是自己,记得遍历登陆栈修改

    virtual void ModifyName(string name);

    virtual void ModifyAuthor(string author);

    virtual void ModifyKeyword(string keyword);

    virtual void ModifyPrice(double price);

    virtual void Import(int quantity, double cost);

    virtual void ReportMyself();//以二进制文件储存，用链表维护（每一个节点的信息为操作以及下一个这个员工的操作在文件中的位置）

    virtual void ShowFinance(int time);//finance 存进一个文件，开头存笔数，之后每次交易收入就是正，支出就是负，show就将最后time笔读出来加起来

    virtual void ShowFinance();

    virtual void ReportFinance();

    virtual void ReportEmployee();

    virtual void Log();//以上三个操作均存一个不同的ASCLL文件
};

class Manager : public People {
public:
};

class Employee : public People {
public:
    virtual void Passwd(string id, string new_passwd) {
        throw Invaild();
    }

    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void ShowFinance(int time) {
        throw Invaild();
    }

    virtual void ShowFinance() {
        throw Invaild();
    }

    virtual void ReportFinance() {
        throw Invaild();
    }

    virtual void ReportEmployee() {
        throw Invaild();
    }

    virtual void Log() {
        throw Invaild();
    }
};

class Consumer : public People {
public:
    virtual void Passwd(string id, string new_passwd) {
        throw Invaild();
    }

    virtual void Useradd(string id, string pass_word, int priority, string user_name) {
        throw Invaild();
    }

    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void Select(string isbn) {
        throw Invaild();
    }

    virtual void ModifyIsbn(string isbn) {
        throw Invaild();
    }

    virtual void ModifyName(string name) {
        throw Invaild();
    }

    virtual void ModifyAuthor(string author) {
        throw Invaild();
    }

    virtual void ModifyKeyword(string keyword) {
        throw Invaild();
    }

    virtual void ModifyPrice(double price) {
        throw Invaild();
    }

    virtual void Import(int quantity, double cost) {
        throw Invaild();
    }

    virtual void ReportMyself() {
        throw Invaild();
    }

    virtual void ShowFinance(int time) {
        throw Invaild();
    }

    virtual void ShowFinance() {
        throw Invaild();
    }

    virtual void ReportFinance() {
        throw Invaild();
    }

    virtual void ReportEmployee() {
        throw Invaild();
    }

    virtual void Log() {
        throw Invaild();
    }
};

class Visitor : public People {
public:
    virtual void Passwd(string id, string old_passwd, string new_passed) {
        throw Invaild();
    }

    virtual void Passwd(string id, string new_passwd) {
        throw Invaild();
    }

    virtual void Useradd(string id, string pass_word, int priority, string user_name) {
        throw Invaild();
    }

    virtual void Delete(string id) {
        throw Invaild();
    }

    virtual void Show(const string &type,string message) {
        throw Invaild();
    }

    virtual void Buy(string isbn, int quantity) {
        throw Invaild();
    }

    virtual void Select(string isbn) {
        throw Invaild();
    }

    virtual void ModifyIsbn(string isbn) {
        throw Invaild();
    }

    virtual void ModifyName(string name) {
        throw Invaild();
    }

    virtual void ModifyAuthor(string author) {
        throw Invaild();
    }

    virtual void ModifyKeyword(string keyword) {
        throw Invaild();
    }

    virtual void ModifyPrice(double price) {
        throw Invaild();
    }

    virtual void Import(int quantity, double cost) {
        throw Invaild();
    }

    virtual void ReportMyself() {
        throw Invaild();
    }

    virtual void ShowFinance(int time) {
        throw Invaild();
    }

    virtual void ShowFinance() {
        throw Invaild();
    }

    virtual void ReportFinance() {
        throw Invaild();
    }

    virtual void ReportEmployee() {
        throw Invaild();
    }

    virtual void Log() {
        throw Invaild();
    }
};
```

## 块状链表

```c++
class NodePeople {//人节点
public:
    char user_id[32];
    char user_name[32];
    char password[32];
    int priority;

    explicit NodePeople() {
        user_id[0] = '\0';
    }

    explicit NodePeople(string id, string name, string passwd, int prior) {
        strcpy(user_id, id.c_str());
        strcpy(user_name, name.c_str());
        strcpy(password, passwd.c_str());
        priority = prior;
    }
    //可以自定义重载运算符使得满足块链储存的关键字优先级
    //还可以重载流输出运算符，节省show的麻烦
};

class NodeBook {//以ISBN为关键字的书的节点
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

    explicit NodeBook(string isbn_, string name, string author_, string key, int quantity_, double price_) {
        strcpy(isbn, isbn_.c_str());
        strcpy(book_name, name.c_str());
        strcpy(author, author_.c_str());
        strcpy(keyword, key.c_str());
        quantity = quantity_;
        price = price_;
    }
    //同上可定义
};

class NodeBookName : public NodeBook {//以book_name为关键字，isbn为副关键字进行排序的书的节点
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
};

class NodeBookAuthor : public NodeBook {//以author为关键字，isbn为副关键字进行排序的书的节点
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
};

class NodeBookKeyword : public NodeBook {//将一个书不同的关键词拆成单一的关键词进行多次储存，这部分信息储存于keyword_中，以keyword_为关键字，isbn为副关键字进行排序的书的节点
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
};

template<class Node>
struct Block_ {//模板的块
    static const int maxn = 3;
    Node size[maxn + 2];
    int now = 0;
};
template<class Node>
struct NodeIndex_ {//模板的索引
    long long next = -1;
    long long pre = -1;
    Node end;
    long long block_begin = 0;
};
```

## 日志系统

report myself输出形式

name:

|did XXX|

|did XX|

......

report finance

|cost XXX to did XXX|

|earn XXX from did XXX|

......

report employee

|XXX did XXX|

......

log

同上述输出

## 补充说明

命名规范参照Google开源项目风格指南

https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/
