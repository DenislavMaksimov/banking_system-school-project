#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction {
private:
    string type;
    double amount;
    double balanceAfter;
    string timestamp;

public:
    Transaction(const string& transactionType, double transactionAmount, double newBalance);

    void print() const;
    string toFileString() const;
};

#endif
