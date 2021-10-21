#include <iostream>
#include <fstream>
using namespace std;
class Account
{
private:
    int accNo_;
    string name_;
    char type_;
    float balance_;
    string address_;


public:
    int getAccountNum() { return accNo_; }
    int getBalance() { return balance_; }
    string getName() { return name_; }
    string getAddress() { return address_; }
    void setBalance(int b) { balance_ = b; }
    void takeData();
    void showData();
    friend std::ostream &operator<<(std::ostream &out, const Account &obj)
    {
        out << obj.accNo_ << "\n"
            << obj.name_ << "\n"
            << obj.type_ << "\n"
            << obj.balance_ << "\n"
            << obj.address_ << std::endl;
        return out;
    }
    friend std::istream &operator>>(std::istream &in, Account &obj)
    {
        in >> obj.accNo_;
        in >> obj.name_;
        in >> obj.type_;
        in >> obj.balance_;
        in >> obj.address_;
        return in;
    }
};
void Account::takeData()
{
    cout << "Enter Account number : ";
    cin >> accNo_;
    cout << "Enter Account holder name : ";
    cin >> name_;
    cout << "Enter type of account : ";
    cin >> type_;
    cout << "Enter initial balance : ";
    cin >> balance_;
    cout << "Enter address of account holder : ";
    cin >> address_;
}
void Account::showData()
{
    cout << "********Details************\n";
    cout << "Account number : " << accNo_ << "\n";
    cout << "Name : " << name_ << "\n";
    cout << "Account type : " << type_ << "\n";
    cout << "Balance : " << balance_ << "\n";
    cout << "Address : " << address_ << "\n";
}
void displayAll()
{
    string FileName = "bank_accounts.txt";
    ifstream in;
    in.open(FileName, ios::in);
    Account a;
    while (in >> a)
    {
        a.showData();
    }
    in.close();
}
void lastEntry()
{
    string FileName = "transaction_details.txt";
    ifstream in;
    in.open(FileName, ios::in);
    int accNo, balance;
    string p;
    while (in >> accNo >> p >> balance)
    {
    }
    cout << p << " " << balance << " from Account Number : " << accNo << "\n";
    in.close();
}
void displayAllTransactions()
{
    string FileName = "transaction_details.txt";
    ifstream in;
    in.open(FileName, ios::in);
    int accNo, balance;
    string p;
    while (in >> accNo >> p >> balance)
    {
        cout << p <<" "<< abs(balance) << " from Account Number : " << accNo << "\n";
    }
    in.close();
}
Account displaySpecific(int accNumber)
{
    string FileName = "bank_accounts.txt";
    ifstream in;
    in.open(FileName, ios::in);
    Account a;
    int flag = 0;
    while (in >> a)
    {
        if (a.getAccountNum() == accNumber)
        {
            in.close();
            return a;
        }
    }
    in.close();
    Account b;
    return b;
}
void deleteAccount(int accNumber)
{
    string FileName1 = "temp.txt";
    ofstream out;
    out.open(FileName1, std::ios_base::app);
    string FileName = "bank_accounts.txt";
    ifstream in;
    in.open(FileName, ios::in);
    Account a;
    int flag = 0;
    while (in >> a)
    {
        if (a.getAccountNum() == accNumber)
        {
            cout << "Data deleted : \n";
            a.showData();
        }
        else
        {
            out << a;
        }
    }
    in.close();
    out.close();
    remove("bank_accounts.txt");
    rename("temp.txt", "bank_accounts.txt");
}
void add(Account a)
{
    string FileName = "bank_accounts.txt";
    ofstream out;
    out.open(FileName, std::ios_base::app);
    out << a;
    out.close();
}
void update(int accNo, int amount)
{
    string FileName1 = "temp.txt";
    ofstream out;
    out.open(FileName1, std::ios_base::app);
    string FileName = "bank_accounts.txt";
    ifstream in;
    in.open(FileName, ios::in);
    Account a;
    int flag = 0;
    while (in >> a)
    {
        if (a.getAccountNum() == accNo)
        {
            if (amount < 0 && a.getBalance() < (-1) * amount)
            {
                cout << "Insufficient balance to withdraw...\nBalance : " << a.getBalance();
            }
            else
            {
                string File = "transaction_details.txt";
                ofstream writeData;
                writeData.open(File, std::ios_base::app);
                if (amount < 0)
                {
                    writeData << a.getAccountNum() << " withdraw " << amount << "\n";
                }
                else
                {
                    writeData << a.getAccountNum() << " deposit " << amount << "\n";
                }
                writeData.close();
                a.setBalance(a.getBalance() + amount);
                cout << "Updated successfully...\nTotal Balance : " << a.getBalance() << "\n";
            }
        }

        out << a;
    }
    in.close();
    out.close();
    remove("bank_accounts.txt");
    rename("temp.txt", "bank_accounts.txt");
}
int main()
{
    int check = 0;
    do
    {
        cout << "\n\n********************Bank System Management********************\n";
        cout << "1.Add new Account holder\n";
        cout << "2.Display all account holders\n";
        cout << "3.Display details for the account number\n";
        cout << "4.Delete Account\n";
        cout << "5.Deposit in a Account\n";
        cout << "6.Withdraw in a Account\n";
        cout << "7.Check if an account Exists or not\n";
        cout << "8.Retrieve name of Account holder\n";
        cout << "9.Retrieve address of Account holder\n";
        cout << "10.Retrieve balance of Account holder\n";
        cout << "11.Display the last Entry\n";
        cout << "12.Display Transaction details with account number\n";
        cout << "*****************************************************************\n";
        cout << "Enter the required option : ";
        int option;
        cin >> option;
        if (option == 1)
        {
            Account a;
            a.takeData();
            add(a);
            cout << "Account added successfully....\n";
        }
        else if (option == 2)
        {
            displayAll();
        }
        else if (option == 3)
        {
            cout << "\nEnter Account number to search : ";
            int accNo_;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
                acc.showData();
        }
        else if (option == 4)
        {
            cout << "\nEnter Account number to delete : ";
            int accNo_;
            cin >> accNo_;
            deleteAccount(accNo_);
        }
        else if (option == 5)
        {
            cout << "\nEnter Account number to deposit : ";
            int accNo_, amount;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
            {
                cout << "Enter amount to deposit : ";
                cin >> amount;
                update(accNo_, amount);
            }
        }
        else if (option == 6)
        {
            cout << "\nEnter Account number to withdraw : ";
            int accNo_, amount;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
            {
                cout << "Enter amount to withdraw : ";
                cin >> amount;
                update(accNo_, (-1) * amount);
            }
        }
        else if (option == 7)
        {
            cout << "Enter Account number to search : ";
            int accNo_;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
                cout << "Account number exists in the database\n";
        }
        else if (option == 8)
        {
            cout << "\nEnter Account number to search : ";
            int accNo_;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
                cout << "Name of Account holder : " << acc.getName() << "\n";
        }
        else if (option == 9)
        {
            cout << "\nEnter Account number to search : ";
            int accNo_;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
                cout << "Address of Account holder : " << acc.getAddress() << "\n";
        }
        else if (option == 10)
        {
            cout << "\nEnter Account number to search : ";
            int accNo_;
            cin >> accNo_;
            Account acc = displaySpecific(accNo_);
            if (acc.getAccountNum() == 0)
                cout << "Account Number not found...\n";
            else
                cout << "Balance of Account holder : " << acc.getBalance() << "\n";
        }
        else if (option == 11)
        {
            lastEntry();
        }
        else if (option == 12)
        {
            displayAllTransactions();
        }
        else if (option == 0)
        {
            check = 0;
        }
        else
        {
            cout << "\nInvalid operation!!\n";
        }
        cout<<"Enter 1 to continue or enter 0 to exit : ";
        cin>>check;
    } while (check);

    return 0;
}
