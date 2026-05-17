#include "Transaction.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace {
string currentTimestamp() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    if (localTime == nullptr) {
        return "Unknown time";
    }

    ostringstream output;
    output << put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return output.str();
}
}

Transaction::Transaction(const string& transactionType, double transactionAmount, double newBalance)
    : type(transactionType),
      amount(transactionAmount),
      balanceAfter(newBalance),
      timestamp(currentTimestamp()) {}

void Transaction::print() const {
    cout << left << setw(22) << timestamp
              << setw(30) << type
              << right << setw(12) << fixed << setprecision(2) << amount
              << setw(18) << balanceAfter << '\n';
}

string Transaction::toFileString() const {
    ostringstream output;
    output << timestamp
           << " | " << type
           << " | Amount: " << fixed << setprecision(2) << amount
           << " | Balance after: " << balanceAfter;
    return output.str();
}
