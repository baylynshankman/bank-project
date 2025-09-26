#include "BankAccount.hpp"
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "AccountManager.hpp"
#include "Utils.hpp"

#include <stdexcept>

int main(){
    statusMessage("Welcome to the banking software!");

    bool finished = false;

    AccountManager accts = AccountManager();
    accts.deserialize("Account_List.CSV");

    while(!finished){
        std::string inputString = getOption();
        if(inputString == "0"){
            statusMessage("Thank you for using the software");
            finished = true;
        }
        else if(inputString == "1"){
            std::string user = getString("Enter the username:");

            accts.addAccount(user);
        }  
        else if(inputString == "2"){
            std::string user = getString("Enter the username:");

            try{
                double deposit_amount = getDouble("Enter amount:");
                accts.makeDeposit(user,deposit_amount);
            }
            catch(std::invalid_argument e){
                errorMessage("I'm sorry, that is not a deposit amount.");
            }
        }
        else if(inputString == "3"){
            std::string user = getString("Enter the username:");

            try{
                double withdrawal_amount = getDouble("Enter amount:");
                accts.makeWithdrawal(user, withdrawal_amount);
            }
            catch(std::invalid_argument e){
                errorMessage("I'm sorry, that is not a withdrawal amount.");
            }
        }
        else if(inputString == "4"){
            std::string user = getString("Enter the username:");

            accts.displayAccount(user);
        }
        else if(inputString == "5"){
            accts.addInterest();
        }
        else if(inputString == "6"){
            std::string user = getString("Enter the username of the account writing the check:");
            std::string target_account = getString("Enter the username of the account cashing the check:");

            try{
                double check_amount = getDouble("Enter amount:");   
                accts.writeCheck(user, target_account, check_amount); 
            }
            catch(std::invalid_argument e){
                errorMessage("I'm sorry, that is not a withdrawal amount.");
            }
        }
        else{
            errorMessage("I'm sorry, that is not a valid choice.");
        }
    }
    accts.serialize("Account_List.CSV");
    return 0;
}