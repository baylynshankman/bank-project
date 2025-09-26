#ifndef CHECKINGACCOUNT_HPP
#define CHECKINGACCOUNT_HPP

#include "BankAccount.hpp"
#include <list>

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(std::string first, std::string last, double initBalance) : BankAccount(first, last, initBalance) {};
    CheckingAccount(std::string first, std::string last) : BankAccount(first, last) {};
    CheckingAccount(std::string first, std::string last, double initBalance, std::list<double> imported_checkLog) : BankAccount(first, last, initBalance) {checkLog = imported_checkLog;};

    bool writeCheck(BankAccount &a, double amount);

    std::string toString();
    std::string serialize();

    std::list<double> getCheckLog();

    ~CheckingAccount() {}

private:
    std::list<double> checkLog;
};

#endif