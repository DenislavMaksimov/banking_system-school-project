#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

using namespace std;

class Client;
class Transaction;

class Account {
protected:
    string id;
    Client* owner;
    double balance;
    bool frozen;
    double withdrawLimit;
    vector<Transaction*> transactions;

    void addTransaction(const string& type, double amount);

public:
    Account(const string& accountId, Client* accountOwner, double initialBalance, double limit);
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;
    virtual ~Account();

    bool deposit(double amount);
    bool deposit(double amount, const string& transactionType);
    bool withdraw(double amount);
    bool transfer(Account* target, double amount);
    double getBalance() const;
    void freeze();
    void unfreeze();
    void getHistory() const;
    bool exportHistory(const string& fileName) const;

    const string& getId() const;
    Client* getOwner() const;
    double getWithdrawLimit() const;
    bool isFrozen() const;
    bool setWithdrawLimit(double limit);
    const vector<Transaction*>& getTransactions() const;

    virtual string getType() const = 0;
    virtual void applyInterest();
};

#endif
