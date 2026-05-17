#include "Menu.h"

#include "../models/Account.h"
#include "../models/CheckingAccount.h"

#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

Menu::~Menu() {
    for (Account* account : accounts) {
        delete account;
    }
    accounts.clear();
}

void Menu::run() {
    while (true) {
        printMainMenu();
        int choice = readInt("Choose option: ");

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                depositToAccount();
                break;
            case 4:
                withdrawFromAccount();
                break;
            case 5:
                transferBetweenAccounts();
                break;
            case 6:
                showTransactionHistory();
                break;
            case 7:
                showBalanceReport();
                break;
            case 0:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}

void Menu::printMainMenu() const {
    cout << "\n========== Banking System ==========\n";
    cout << "1. Create account\n";
    cout << "2. View account\n";
    cout << "3. Deposit\n";
    cout << "4. Withdraw\n";
    cout << "5. Transfer\n";
    cout << "6. Transaction history\n";
    cout << "7. Balance report\n";
    cout << "0. Exit\n";
    cout << "====================================\n";
}

void Menu::clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int Menu::readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInput();
            return value;
        }
        cout << "Invalid input. Please enter a whole number.\n";
        clearInput();
    }
}

double Menu::readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInput();
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        clearInput();
    }
}

string Menu::readLine(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Input cannot be empty.\n";
    }
}

Account* Menu::findAccount(const string& accountId) const {
    for (Account* account : accounts) {
        if (account->getId() == accountId) {
            return account;
        }
    }
    return nullptr;
}

void Menu::printAccountDetails(const Account* account) const {
    if (account == nullptr) {
        cout << "Account not found.\n";
        return;
    }
    cout << "\nAccount ID:     " << account->getId() << '\n';
    cout << "Type:           " << account->getType() << '\n';
    cout << "Balance:        " << fixed << setprecision(2) << account->getBalance() << '\n';
    cout << "Withdraw limit: " << account->getWithdrawLimit() << '\n';
    cout << "Status:         " << (account->isFrozen() ? "Frozen" : "Active") << '\n';
}

// Functionality 1 - Create account
void Menu::createAccount() {
    string accountId = readLine("Enter account ID: ");
    if (findAccount(accountId) != nullptr) {
        cout << "Error: An account with this ID already exists.\n";
        return;
    }

    double initialBalance = readDouble("Enter initial balance: ");
    if (initialBalance < 0) {
        cout << "Error: Initial balance cannot be negative.\n";
        return;
    }

    double withdrawLimit = readDouble("Enter withdraw limit per transaction: ");
    if (withdrawLimit <= 0) {
        cout << "Error: Withdraw limit must be positive.\n";
        return;
    }

    accounts.push_back(new CheckingAccount(accountId, nullptr, initialBalance, withdrawLimit));
    cout << "Account created successfully.\n";
}

// Functionality 1 - View account
void Menu::viewAccount() {
    string accountId = readLine("Enter account ID: ");
    printAccountDetails(findAccount(accountId));
}

// Functionality 2 - Deposit
void Menu::depositToAccount() {
    string accountId = readLine("Enter account ID: ");
    Account* account = findAccount(accountId);
    if (account == nullptr) {
        cout << "Account not found.\n";
        return;
    }

    double amount = readDouble("Enter deposit amount: ");
    if (account->deposit(amount)) {
        cout << "Deposit successful. New balance: "
             << fixed << setprecision(2) << account->getBalance() << '\n';
    }
}

// Functionality 3 - Withdraw
void Menu::withdrawFromAccount() {
    string accountId = readLine("Enter account ID: ");
    Account* account = findAccount(accountId);
    if (account == nullptr) {
        cout << "Account not found.\n";
        return;
    }

    double amount = readDouble("Enter withdrawal amount: ");
    if (account->withdraw(amount)) {
        cout << "Withdrawal successful. New balance: "
             << fixed << setprecision(2) << account->getBalance() << '\n';
    }
}

// Functionality 4 - Transfer
void Menu::transferBetweenAccounts() {
    string sourceId = readLine("Enter source account ID: ");
    Account* source = findAccount(sourceId);
    if (source == nullptr) {
        cout << "Source account not found.\n";
        return;
    }

    string targetId = readLine("Enter target account ID: ");
    Account* target = findAccount(targetId);
    if (target == nullptr) {
        cout << "Target account not found.\n";
        return;
    }

    double amount = readDouble("Enter transfer amount: ");
    if (source->transfer(target, amount)) {
        cout << "Transfer successful.\n";
        cout << "Source balance: " << fixed << setprecision(2) << source->getBalance() << '\n';
        cout << "Target balance: " << target->getBalance() << '\n';
    }
}

// Functionality 5 - Transaction history
void Menu::showTransactionHistory() {
    string accountId = readLine("Enter account ID: ");
    Account* account = findAccount(accountId);
    if (account == nullptr) {
        cout << "Account not found.\n";
        return;
    }
    account->getHistory();
}

// Functionality 6 - Balance report
void Menu::showBalanceReport() {
    if (accounts.empty()) {
        cout << "No accounts registered.\n";
        return;
    }

    cout << '\n';
    cout << left << setw(16) << "Account ID"
         << setw(14) << "Type"
         << right << setw(14) << "Balance"
         << setw(18) << "Withdraw Limit"
         << setw(10) << "Status" << '\n';
    cout << string(72, '-') << '\n';

    double total = 0;
    for (const Account* account : accounts) {
        total += account->getBalance();
        cout << left << setw(16) << account->getId()
             << setw(14) << account->getType()
             << right << setw(14) << fixed << setprecision(2) << account->getBalance()
             << setw(18) << account->getWithdrawLimit()
             << setw(10) << (account->isFrozen() ? "Frozen" : "Active") << '\n';
    }

    cout << string(72, '-') << '\n';
    cout << "Total balance: " << fixed << setprecision(2) << total << '\n';
}
