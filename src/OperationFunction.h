#ifndef MAIN_1_CPP_OPERATIONFUNCTION_H
#define MAIN_1_CPP_OPERATIONFUNCTION_H

#include <string>

//获取keyword中以|分开的一个keyword
std::string GetKey(std::string &key);

//获取空格分开的字符串
std::string Get(std::string &s);

//检查是不是数字，并返回long long
long long CheckNum_(std::string num);

//检查是不是数字，并返回int
int CheckNum(std::string num);

//检查是不是数字，并返回double
double CheckDouble(std::string num);

//检查是不是空字符串
void CheckNull(std::string s);

//获得modify操作的信息，操作的种类返回在type中，信息在infor中
void GetModify(const std::string &op, std::string &type, std::string &infor);

//获得show操作的信息，操作的种类返回在type中，信息在infor中
void GetShow(const std::string &op, std::string &type, std::string &infor);

//检查数字，字母，下划线
void Check_(std::string s);

//检查不可见字符
void Check_See(std::string s);

void CheckIsbn(std::string s);

#endif //MAIN_1_CPP_OPERATIONFUNCTION_H
