#include "AccountManager.hpp"
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"
#include "Utils.hpp"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <vector>

AccountManager::AccountManager(){
    accts = std::map<std::string, BankAccount*>();
    numAccounts = 0;
}

void AccountManager::addAccount(std::string username){
    if(accts.find(username) == accts.end()){
        BankAccount* b = makeAccount();
        accts[username] = b;
        numAccounts++;
    }
    else {
        errorMessage("Username already exist");
    }
}

void AccountManager::deleteAccount(std::string username){
    if(accts.find(username) != accts.end()){
        delete accts[username];
        accts.erase(username);
        numAccounts--;
    }
    else {
        errorMessage("Username does not exist");
    }
}

AccountManager::~AccountManager(){
    std::map<std::string, BankAccount*>::iterator it;
    
    for (it = accts.begin(); it != accts.end(); it++){
        BankAccount *acct = it->second;
        delete acct;
    }
}

void AccountManager::addInterest(){
    std::map<std::string, BankAccount*>::iterator it;

    for(it = accts.begin(); it != accts.end(); it++){
        if(dynamic_cast<SavingsAccount*>(it->second)){
            SavingsAccount *s = dynamic_cast<SavingsAccount*>(it->second);
            s->accrueInterest();
        }
    }
}

void AccountManager::writeCheck(std::string writer, std::string receiver, double amount){
    if(accts.find(writer) == accts.end()){
        errorMessage("The writer account does not exist");

    }
    else if(accts.find(receiver) == accts.end()){
        errorMessage("The receiver account does not exist");
    }
    else{
        BankAccount *writerB = accts[writer];
        BankAccount *receiverB = accts[receiver];

        CheckingAccount *writerC = dynamic_cast<CheckingAccount*>(writerB);
        if(writerC != nullptr){
            writerC->writeCheck(*receiverB, amount);
        }
        else{
            errorMessage("The account writing the check is not a checking account");
        }

    }
}

void AccountManager::makeDeposit(std::string username, double amount){
    if(accts.find(username) != accts.end()){
        BankAccount* b = accts[username];
        b->deposit(amount);
    }
    else {
        errorMessage("Username doesn't exist");
    }
}

void AccountManager::makeWithdrawal(std::string username, double amount){
    if(accts.find(username) != accts.end()){
        BankAccount* b = accts[username];
        b->withdrawal(amount);
    }
    else {
        errorMessage("Username doesn't exist");
    }
}

void AccountManager::displayAccount(std::string username){
    if(accts.find(username) != accts.end()){
        std::cout<<accts[username]->toString()<<std::endl;
    }
    else {
        errorMessage("Username doesn't exist");
    }
}

int AccountManager::getNumAccounts(){
    return numAccounts;
}

void AccountManager::serialize(std::string file_name){
    std::ofstream MyFile(file_name);
    if (MyFile.is_open()) {
        for (const auto& pair : accts){
            std::string myAccount = pair.first;     //username is stored here
            myAccount += pair.second-> serialize() + "\n";       //adds username to string from bankaccount serializes()
            MyFile << myAccount;     //writes this string to the file
        }
    }
    else {
        std::cout<<"Unable to open file"<<std::endl;
    }
    MyFile.close();
}

void AccountManager::deserialize(std::string file_name){
    std::ifstream MyFile(file_name);
    if (MyFile.is_open()){
        std::string line;
        while (std::getline(MyFile, line)){
            std::vector<std::string> splitString;
            boost::split(splitString, line, boost::is_any_of(","));

            std::string username = splitString[0];
            std::string firstName = splitString[2];
            std::string lastName = splitString[3];
            double balance = std::stod(splitString[4]);
            BankAccount * b = nullptr;


            if (splitString[1] == "savings"){
                double int_rate = std::stod(splitString[5]);
                b = new SavingsAccount(firstName, lastName, balance, int_rate);
                accts[username] = b;
            }
            else if (splitString[1] == "checking"){
                std::list<double> remade_checkLog;
                for (int i = 5; i<splitString.size() -1; i++){
                    double check_amt = std::strtod(splitString[i].c_str(), nullptr);
                    remade_checkLog.push_back(check_amt);
                }
                b = new CheckingAccount(firstName, lastName, balance, remade_checkLog);
                accts[username] = b;
            }
        }
    }   
    else {
        std::cout<<"File could not be opened."<<std::endl;
    } 
}