#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

using namespace std;

class Account;

class Menu {
private:
    vector<Account*> accounts;

    void printMainMenu() const;
    void clearInput();
    int readInt(const string& prompt);
    double readDouble(const string& prompt);
    string readLine(const string& prompt);

    Account* findAccount(const string& accountId) const;
    void printAccountDetails(const Account* account) const;

    // Functionality 1 - Create / View account (CRUD)
    void createAccount();
    void viewAccount();

    // Functionality 2 - Deposit
    void depositToAccount();

    // Functionality 3 - Withdraw
    void withdrawFromAccount();

    // Functionality 4 - Transfer
    void transferBetweenAccounts();

    // Functionality 5 - Transaction history
    void showTransactionHistory();

    // Functionality 6 - Balance report
    void showBalanceReport();

public:
    Menu() = default;
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    ~Menu();

    void run();
};

#endif
