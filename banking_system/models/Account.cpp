#include "Account.h"

#include "../utils/FileExporter.h"
#include "Client.h"
#include "Transaction.h"

#include <iomanip>
#include <iostream> 

using namespace std;

Account::Account(const string& accountId, Client* accountOwner, double initialBalance, double limit)
    : id(accountId),
      owner(accountOwner),
      balance(initialBalance),
      frozen(false),
      withdrawLimit(limit) {
    if (initialBalance > 0) {
        addTransaction("Initial deposit", initialBalance);
    }
}

Account::~Account() {
    for (Transaction* transaction : transactions) {
        delete transaction;
    }

    transactions.clear();
}

void Account::addTransaction(const string& type, double amount) {
    transactions.push_back(new Transaction(type, amount, balance));
}

bool Account::deposit(double amount) {
    return deposit(amount, "Deposit");
}

bool Account::deposit(double amount, const string& transactionType) {
    if (frozen) {
        cout << "Error: Account is frozen. Deposit rejected.\n";
        return false;
    }

    if (amount <= 0) {
        cout << "Error: Deposit amount must be positive.\n";
        return false;
    }

    balance += amount;
    addTransaction(transactionType, amount);
    return true;
}

bool Account::withdraw(double amount) {
    if (frozen) {
        cout << "Error: Account is frozen. Withdrawal rejected.\n";
        return false;
    }

    if (amount <= 0) {
        cout << "Error: Withdrawal amount must be positive.\n";
        return false;
    }

    if (amount > withdrawLimit) {
        cout << "Error: Amount exceeds withdrawal limit of "
                  << fixed << setprecision(2) << withdrawLimit << ".\n";
        return false;
    }

    if (amount > balance) {
        cout << "Error: Insufficient funds.\n";
        return false;
    }

    balance -= amount;
    addTransaction("Withdrawal", amount);
    return true;
}

bool Account::transfer(Account* target, double amount) {
    if (target == nullptr) {
        cout << "Error: Target account not found.\n";
        return false;
    }

    if (target == this) {
        cout << "Error: Cannot transfer to the same account.\n";
        return false;
    }

    if (frozen) {
        cout << "Error: Source account is frozen. Transfer rejected.\n";
        return false;
    }

    if (target->isFrozen()) {
        cout << "Error: Target account is frozen. Transfer rejected.\n";
        return false;
    }

    if (amount <= 0) {
        cout << "Error: Transfer amount must be positive.\n";
        return false;
    }

    if (amount > balance) {
        cout << "Error: Insufficient funds for transfer.\n";
        return false;
    }

    balance -= amount;

    addTransaction("Transfer out to " + target->getId(), amount);
    target->deposit(amount, "Transfer in from " + id);
    return true;
}

double Account::getBalance() const {
    return balance;
}

void Account::freeze() {
    frozen = true;
}

void Account::unfreeze() {
    frozen = false;
}

void Account::getHistory() const {
    if (transactions.empty()) {
        cout << "No transactions for this account.\n";
        return;
    }

    cout << left << setw(22) << "Timestamp"
              << setw(30) << "Type"
              << right << setw(12) << "Amount"
              << setw(18) << "Balance After" << '\n';
    cout << string(82, '-') << '\n';

    for (const Transaction* transaction : transactions) {
        transaction->print();
    }
}

bool Account::exportHistory(const string& fileName) const {
    return FileExporter::exportAccountHistory(*this, fileName);
}

const string& Account::getId() const {
    return id;
}

Client* Account::getOwner() const {
    return owner;
}

double Account::getWithdrawLimit() const {
    return withdrawLimit;
}

bool Account::isFrozen() const {
    return frozen;
}

bool Account::setWithdrawLimit(double limit) {
    if (limit <= 0) {
        cout << "Error: Withdrawal limit must be positive.\n";
        return false;
    }

    withdrawLimit = limit;
    return true;
}

const vector<Transaction*>& Account::getTransactions() const {
    return transactions;
}

void Account::applyInterest() {}
