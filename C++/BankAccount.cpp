#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account{
    public:
        Account(string userName = "EnterName", double userBalance = 0.0, int userID = 0);
        Account& Deposit(double money);
        Account& Withdraw(double money);
        double GetBalance()const;
        double SetBalance(){return balance;}
        friend ostream& operator<<(ostream& out, const Account& other);
        friend void FindAccount(const int& sID);
        const int& GetAccID(){return ID;}
        void DisplayAccount(){cout<<*this;}
        int getAccountCounter() const {return AccCount;}
    private:
        static int AccCount;
        string name;
        double balance;
        int ID;
};
class Bank:Account{
    public:
        void AddAccount();
        void DisplayUsers();
        void FindAccount(const int& sID);
        const double CalculateTotalBalance();
    private:
        vector<Account> users;
};

ostream& operator<<(ostream& out, const Account& other);
int Account::AccCount = 0;


int main(){
    Bank bank;
    bank.AddAccount();
    
    bank.AddAccount();
    bank.AddAccount();
    bank.DisplayUsers();
    bank.FindAccount(1);

    return 0;
}

Account::Account(string userName, double userBalance, int userID): name(userName), balance(userBalance), ID(userID) {
    AccCount++;
}
Account& Account::Withdraw(double money){
    if (money > balance){
        cerr<<"you dont have that much money broke ass"<<endl;
        return *this;
    }
    balance = balance - money;
    return *this;
}
Account& Account::Deposit(double money){
    if (money < 0) {
        cerr<<"you can not deposit negative amount of money"<<endl;
        return *this;
    }
    balance = balance + money;
    return *this;
}
double Account::GetBalance()const{
    return this->balance;
}
ostream& operator<<(ostream& out, const Account& other){
    out<<"----------------------"<<endl;
    out<<"ID: "<<other.ID<<endl;
    out<<"User Name: "<<other.name<<endl;
    out<<"Balance: "<<other.balance<<endl;
    out<<"----------------------"<<endl;
    return out;
}

void Bank::AddAccount(){
    string AccName;
    double AccBalance = 0.0;
    cout<<"Your Name: ";
    getline(cin, AccName);
    Account newUser(AccName, AccBalance, getAccountCounter());
    users.push_back(newUser);
}
void Bank::DisplayUsers(){
    for(const Account& user : users)
        cout<<user;
}
void Bank::FindAccount(const int& sID){
    for(Account& user : users){
        if(user.GetAccID() == sID)
            user.DisplayAccount();
    }
}
const double Bank::CalculateTotalBalance(){
    double TotalBalance = 0;
    for(const Account& user : users)
        TotalBalance += user.GetBalance();
    return TotalBalance;
}