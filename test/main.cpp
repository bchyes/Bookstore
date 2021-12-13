#include <iostream>
#include<bits/stdc++.h>

using namespace std;
/*struct Node {
    long long ans = -1;
};*/
fstream file;
class Node{
public:
    int num=2;
    virtual void print(){cout<<num;}
};
class NodeP:public Node{
public:
    int num1=1;
    void print(){cout<<num1;}
};
int main() {
    file.open("file");
    if (!file) {
        file.open("file", fstream::out);
        file.close();
        file.open("file");
    }
    Node *ac=new NodeP;
    Node *ak=new NodeP;
    file.write(reinterpret_cast<char *>(ac),sizeof(NodeP));
    file.read(reinterpret_cast<char *>(ak),sizeof(NodeP));
    cout<<ak->num<<" ";
    ak->print();
    /*int k;

    file.seekg(0);
    cout << file.tellg() << '\n';
    int i = 0;
    //file.seekp(0, ios::end);
    while (!file.eof()) {
        file.read(reinterpret_cast<char *>(&k), sizeof(int));
        cout<<file.tellg()<<" ";
    }
    file.write(reinterpret_cast<char *>(&i), sizeof(int));
    file.seekg(0, ios::end);
    cout << file.tellg() << '\n';
    Node nod;
    //cout << nod.ans << '\n';
    char c[50];
    c[0] = '\0';
    string s = string(c);
    string s1;
    //s="1"+"\n"+"1";
    //cin >> s1;
    //cout << s << '\n';
    //cout << (s < s1);*/
    return 0;
}
