#include"store.h"
#include"OperationFunction.h"
#include"PeopleNode.h"
#include"BookNode.h"
#include"People.h"
#include"Command.h"

int main() {
    freopen("test_robust.txt", "r", stdin);
    freopen("test_robust.out", "w", stdout);
    std::string s;
    People *account = new Visitor;
    account->Initialize();
    int line = 0;
    while (getline(std::cin, s)) {
        line++;
        Command(s,account);
    }
    delete account;
}