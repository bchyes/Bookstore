#ifndef MAIN_1_CPP_STORE_H
#define MAIN_1_CPP_STORE_H

#include <fstream>
#include<bits/stdc++.h>

using namespace std;

class Invalid {
};
template<class Node>
void swap_(Node &a,Node &b){
    Node tmp=a;
    a=b;
    b=tmp;
}
template<class Node>
struct Block_ {
    static const int maxn = 320;
    Node size[maxn + 2];
    int now = 0;
};
template<class Node>
struct NodeIndex_ {
    long long next = -1;
    long long pre = -1;
    Node end;
    long long block_begin = 0;
};

template<class NodeIndex, class Block>
class Store {
    fstream file;
    fstream file_index;
    fstream file_delete;
    NodeIndex idx;
    Block blo;
    long long now_index;
    queue<long long> del;
    queue<long long> del_index;
    string file_name;
    string file_index_name;
    string file_delete_name;
public:
    Store(string file_name_, string file_index_name_, string file_delete_name_) {
        while (!del.empty()) del.pop();
        while (!del_index.empty()) del_index.pop();
        file_name = file_name_;
        file_index_name = file_index_name_;
        file_delete_name = file_delete_name_;
        file_delete.open(file_delete_name);
        if (!file_delete) return;
        long long num;
        file_delete.read(reinterpret_cast<char *>(&num), sizeof(long long));
        long long det, det_index;
        for (int i = 1; i <= num; i++) {
            file_delete.read(reinterpret_cast<char *>(&det), sizeof(long long));
            file_delete.read(reinterpret_cast<char *>(&det_index), sizeof(long long));
            del.push(det);
            del_index.push(det_index);
        }
        file_delete.close();
    }

    ~Store() {
        file_delete.open(file_delete_name);
        if (!file_delete) {
            file_delete.open(file_delete_name, fstream::out);
            file_delete.close();
            file_delete.open(file_delete_name);
        }
        long long num = del.size();
        file_delete.write(reinterpret_cast<char *>(&num), sizeof(long long));
        for (int i = 1; i <= num; i++) {
            long long det = del.front(), det_index = del_index.front();
            del.pop();
            del_index.pop();
            file_delete.write(reinterpret_cast<char *>(&det), sizeof(long long));
            file_delete.write(reinterpret_cast<char *>(&det_index), sizeof(long long));
        }
        file_delete.close();
    }

    template<class Node>
    void Initialize(Node nod) {
        file.open(file_name);
        file_index.open(file_index_name);
        if (!file || !file_index) {
            file.open(file_name, fstream::out);
            file.close();
            file.open(file_name);
            file_index.open(file_index_name, fstream::out);
            file_index.close();
            file_index.open(file_index_name);
            NodeIndex head;
            head.next = sizeof(NodeIndex);
            file_index.write(reinterpret_cast<char *>(&head), sizeof(NodeIndex));
            blo.now = 1;
            blo.size[blo.now] = nod;
            idx.end = nod;
            idx.pre = 0;
            file.write(reinterpret_cast<char *>(&blo), sizeof(Block));
            file_index.write(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        }
        file.close();
        file_index.close();
    }

    template<class Node>
    void Insert(Node nod) {
        file.open(file_name);
        file_index.open(file_index_name);
        if (!file || !file_index) {
            file.open(file_name, fstream::out);
            file.close();
            file.open(file_name);
            file_index.open(file_index_name, fstream::out);
            file_index.close();
            file_index.open(file_index_name);
            NodeIndex head;
            head.next = sizeof(NodeIndex);
            file_index.write(reinterpret_cast<char *>(&head), sizeof(NodeIndex));
            blo.now = 1;
            blo.size[blo.now] = nod;
            idx.end = nod;
            idx.pre = 0;
            file.write(reinterpret_cast<char *>(&blo), sizeof(Block));
            file_index.write(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            file.close();
            file_index.close();
            return;
        }
        file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        while (1) {
            if (idx.end == nod) {
                file.close();
                file_index.close();
                throw Invalid();
            }
            if (idx.end >= nod) break;
            else {
                if (idx.next == -1) break;
                file_index.seekg(idx.next, ios::beg);
                now_index = idx.next;
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            }
        }
        if (idx.pre == -1 && idx.next == -1) {
            NodeIndex head;
            head.next = del_index.front();
            file_index.seekp(0);
            file_index.write(reinterpret_cast<char *>(&head), sizeof(NodeIndex));
            blo.now = 1;
            blo.size[blo.now] = nod;
            idx.end = nod;
            idx.pre = 0;
            file.seekp(del.front());
            idx.block_begin = del.front();
            del.pop();
            file_index.seekp(del_index.front());
            del_index.pop();
            file.write(reinterpret_cast<char *>(&blo), sizeof(Block));
            file_index.write(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            file.close();
            file_index.close();
            return;
        }
        file.seekg(idx.block_begin, ios::beg);
        file.read(reinterpret_cast<char *>(&blo), sizeof(Block));
        blo.size[++blo.now] = nod;
        int i;
        for (i = 1; i <= blo.now - 1; i++) {
            if (blo.size[i] == nod) {
                file.close();
                file_index.close();
                throw Invalid();
            }
            if (blo.size[i] > nod) break;
        }
        for (int j = blo.now - 1; j >= i; j--) {
            swap_(blo.size[j + 1], blo.size[j]);
        }
        if (blo.now <= blo.maxn) {
            if (i == blo.now) {
                idx.end = nod;
                file_index.seekp(now_index);
                file_index.write(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            }
            file.seekp(idx.block_begin, ios::beg);
            file.write(reinterpret_cast<char *>(&blo), sizeof(Block));
        } else {
            Block blo_new;
            NodeIndex idx_new;
            if (idx.next != -1) {
                NodeIndex idx_1;
                file_index.seekg(idx.next, ios::beg);
                file_index.read(reinterpret_cast<char *>(&idx_1), sizeof(NodeIndex));
                idx_new.next = idx.next;
                idx_new.pre = idx_1.pre;
                if (!del.empty()) {
                    idx_new.block_begin = del.front();
                    idx.next = del_index.front();
                    del.pop();
                    del_index.pop();
                } else {
                    file.seekg(0, ios::end);
                    idx_new.block_begin = file.tellg();
                    file_index.seekg(0, ios::end);
                    idx.next = file_index.tellg();
                }
                idx_1.pre = idx.next;
                file_index.seekp(idx_new.next);
                file_index.write(reinterpret_cast<char *>(&idx_1), sizeof(NodeIndex));
            } else {
                if (del.empty()) {
                    file.seekg(0, ios::end);
                    idx_new.block_begin = file.tellg();
                    file_index.seekg(0, ios::end);
                    idx.next = file_index.tellg();
                } else {
                    idx_new.block_begin = del.front();
                    idx.next = del_index.front();
                    del.pop();
                    del_index.pop();
                }
                idx_new.pre = now_index;
                idx_new.next = -1;
            }
            blo.now = (blo.maxn + 1) / 2;
            idx.end = blo.size[blo.now];
            blo_new.now = blo.maxn - blo.now + 1;
            for (int i = blo.now + 1; i <= blo.maxn + 1; i++)
                blo_new.size[i - blo.now] = blo.size[i];
            idx_new.end = blo_new.size[blo_new.now];
            file_index.seekp(idx_new.pre);
            file_index.write(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            file_index.seekp(idx.next);
            file_index.write(reinterpret_cast<char *>(&idx_new), sizeof(NodeIndex));
            file.seekp(idx.block_begin, ios::beg);
            file.write(reinterpret_cast<char *>(&blo), sizeof(Block));
            file.seekp(idx_new.block_begin);
            file.write(reinterpret_cast<char *>(&blo_new), sizeof(Block));
        }
        file.close();
        file_index.close();
    }

    template<class Node>
    Node Find(string index) {
        file.open(file_name);
        file_index.open(file_index_name);
        if (!file)
            throw Invalid();
        file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        while (1) {
            if (idx.end >= index) break;
            else {
                if (idx.next == -1) {
                    file.close();
                    file_index.close();
                    throw Invalid();
                }
                file_index.seekg(idx.next, ios::beg);
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            }
        }
        file.seekg(idx.block_begin, ios::beg);
        file.read(reinterpret_cast<char *>(&blo), sizeof(Block));
        for (int i = 1; i <= blo.now; i++) {
            if (blo.size[i] == index) {
                file.close();
                file_index.close();
                return blo.size[i];
            }
        }
        file.close();
        file_index.close();
        throw Invalid();
    }

    string FindMore(string index) {
        file.open(file_name);
        file_index.open(file_index_name);
        if (!file)
            return "";
        file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        while (1) {
            if (idx.end >= index) break;
            else {
                if (idx.next == -1) {
                    file.close();
                    file_index.close();
                    return "";
                }
                file_index.seekg(idx.next, ios::beg);
                file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            }
        }
        file.seekg(idx.block_begin, ios::beg);
        file.read(reinterpret_cast<char *>(&blo), sizeof(Block));
        string ans = "";
        ans += to_string(idx.block_begin) + " ";
        bool more = 0;
        while (idx.end == index && idx.next != -1) {
            more = 1;
            file_index.seekg(idx.next, ios::beg);
            file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
            file.seekg(idx.block_begin, ios::beg);
            file.read(reinterpret_cast<char *>(&blo), sizeof(Block));
            if (idx.end > index || idx.next == -1) break;
            ans += to_string(idx.block_begin) + " ";
        }
        if (more)
            ans += to_string(idx.block_begin) + " ";
        file.close();
        file_index.close();
        return ans;
    }

    template<class Node>
    void Delete(Node nod) {
        file.open(file_name);
        file_index.open(file_index_name);
        if (!file)
            throw Invalid();
        file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        while (1) {
            if (idx.end >= nod) break;
            else {
                if (idx.next == -1) {
                    file.close();
                    file_index.close();
                    throw Invalid();
                }
            }
            file_index.seekg(idx.next, ios::beg);
            now_index = idx.next;
            file_index.read(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        }
        file.seekg(idx.block_begin, ios::beg);
        file.read(reinterpret_cast<char *>(&blo), sizeof(Block));
        if (blo.now == 1 && blo.size[blo.now] == nod) {
            blo.now = 0;
            NodeIndex idx_pre;
            if (idx.next != -1) {
                NodeIndex idx_next;
                file_index.seekg(idx.next);
                file_index.read(reinterpret_cast<char *>(&idx_next), sizeof(NodeIndex));
                idx_next.pre = idx.pre;
                file_index.seekp(idx.next);
                file_index.write(reinterpret_cast<char *>(&idx_next), sizeof(NodeIndex));
            }
            file_index.seekg(idx.pre);
            file_index.read(reinterpret_cast<char *>(&idx_pre), sizeof(NodeIndex));
            del_index.push(idx_pre.next);
            del.push(idx.block_begin);
            idx_pre.next = idx.next;
            file_index.seekp(idx.pre);
            file_index.write(reinterpret_cast<char *>(&idx_pre), sizeof(NodeIndex));
            file.close();
            file_index.close();
            return;
        }
        int i;
        for (i = 1; i <= blo.now; i++) {
            if (blo.size[i] == nod) {
                break;
            }
        }
        if (i == blo.now + 1) {
            file.close();
            file_index.close();
            throw Invalid();
        }
        for (int j = i; j <= blo.now - 1; j++)
            swap_(blo.size[j], blo.size[j + 1]);
        if (i == blo.now) {
            idx.end = blo.size[blo.now - 1];
            file_index.seekp(now_index);
            file_index.write(reinterpret_cast<char *>(&idx), sizeof(NodeIndex));
        }
        blo.now--;
        file.seekp(idx.block_begin);
        file.write(reinterpret_cast<char *>(&blo), sizeof(Block));
        file.close();
        file_index.close();
    }
};

#endif //MAIN_1_CPP_STORE_H
