#include "CheckingAccount.h"

using namespace std;

CheckingAccount::CheckingAccount(const string& accountId,
                                 Client* accountOwner,
                                 double initialBalance,
                                 double limit)
    : Account(accountId, accountOwner, initialBalance, limit) {}

string CheckingAccount::getType() const {
    return "Checking";
}

void CheckingAccount::applyInterest() {}
