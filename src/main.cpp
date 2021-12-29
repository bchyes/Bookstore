#include "store.h"
#include "OperationFunction.h"
#include "PeopleNode.h"
#include "BookNode.h"
#include "Log.h"
#include "People.h"
#include "Command.h"

int main() {
    freopen("1.in", "r", stdin);
    freopen("1.0.out", "w", stdout);
    std::string s;
    People *account = new Visitor;
    account->Initialize();
    int line = 0;
    while (getline(std::cin, s)) {
        line++;
        Command(s, account, line);
    }
    delete account;
}