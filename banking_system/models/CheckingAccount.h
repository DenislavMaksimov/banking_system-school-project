#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "Account.h"

using namespace std;

class CheckingAccount : public Account {
public:
    CheckingAccount(const string& accountId,
                    Client* accountOwner,
                    double initialBalance,
                    double limit);

    string getType() const override;
    void applyInterest() override;
};

#endif
