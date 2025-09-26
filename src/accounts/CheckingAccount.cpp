#include "CheckingAccount.hpp"

bool CheckingAccount::writeCheck(BankAccount &a, double amount){
    bool success = withdrawal(amount);

    if(success){
        a.deposit(amount);
        checkLog.push_back(amount);
    }

    return success;
}

std::string CheckingAccount::toString(){
    return "Checking Account Balance: $" + std::to_string(getBalance()) + ", wrote " + std::to_string(checkLog.size()) + " checks";
}

std::string CheckingAccount::serialize(){
    std::string account; 
    account += ",checking,";
    account += getFirstName() + ",";
    account += getLastName() +",";
    account += std::to_string(getBalance()) + ",";


    std::list<double> copy_checkLog = getCheckLog();
    for (double c : copy_checkLog) {
        account += ("," + std::to_string(c));
    }
    return account; 
}

std::list<double> CheckingAccount::getCheckLog(){
    return checkLog;
}