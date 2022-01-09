#include "Exception.h"
#include "PeopleNode.h"
#include "BookNode.h"
#include "Log.h"
#include "Store.h"
#include "OperationFunction.h"
#include "Account.h"
#include "Command.h"

std::vector<NodePeople> stk;
std::vector<NodeBook> stk_;
Store <NodeIndex_<NodePeople>, Block_<NodePeople>> file_people("file_people", "file_people_index",
                                                               "file_people_delete");
Store <NodeIndex_<NodeBook>, Block_<NodeBook>> file_book("file_book", "file_book_index", "file_book_delete");
Store <NodeIndex_<NodeBookName>, Block_<NodeBookName>> file_name("file_name", "file_name_index", "file_name_delete");
Store <NodeIndex_<NodeBookAuthor>, Block_<NodeBookAuthor>> file_author("file_author", "file_author_index",
                                                                       "file_author_delete");
Store <NodeIndex_<NodeBookKeyword>, Block_<NodeBookKeyword>> file_keyword("file_keyword", "file_keyword_index",
                                                                          "file_keyword_delete");
Store <NodeIndex_<EmployeeLog>, Block_<EmployeeLog>> file_employee("file_employee", "file_employee_index",
                                                                   "file_employee_delete");
int main() {
    /*freopen("1.in", "r", stdin);
    freopen("1.0.out", "w", stdout);*/
    std::string command;
    BaseAccount *account = new Visitor;
    account->Initialize();
    int line = 0;
    while (getline(std::cin, command)) {
        line++;
        Command(command, account, line);
    }
    delete account;
}