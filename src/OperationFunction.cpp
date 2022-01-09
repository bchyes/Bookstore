#include "OperationFunction.h"
#include "exception.h"

std::string GetKey(std::string &key) {
    for (int i = 0; i < key.length(); i++) {
        if (key[i] == '|') {
            std::string s_ = key.substr(0, i);
            key = key.substr(i + 1);
            return s_;
        }
    }
}

std::string Get(std::string &s) {
    if (s == "") throw Invalid();
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            std::string s_ = s.substr(0, i);
            int j;
            for (j = i + 1; j < s.length(); j++)
                if (s[j] != ' ') break;
            s = s.substr(j);
            return s_;
        }
    }
}

long long CheckNum_(std::string num) {
    long long ans = 0;
    for (int i = 0; i < num.length(); i++) {
        if (num[i] > '9' || num[i] < '0')
            throw Invalid();
        else ans = ans * 10 + (long long) (num[i] - '0');
    }
    return ans;
}

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

void Check_(std::string s) {
    if (s.length() > 30) throw Invalid();
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
            s[i] == '_')
            continue;
        throw Invalid();
    }
}

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
