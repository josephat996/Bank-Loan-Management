
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Loan {
private:
    int loanID;
    string customerName;
    double loanAmount;
    double interestRate;
    double balance;

public:
    Loan(int id, string name, double amount, double rate)
        : loanID(id), customerName(name), loanAmount(amount), interestRate(rate), balance(amount) {}

    void displayDetails() {
        cout << "Loan ID: " << loanID << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << fixed << setprecision(2);
        cout << "Loan Amount: $" << loanAmount << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Balance: $" << balance << endl;
        cout << "----------------------------------------" << endl;
    }

    void makeRepayment(double amount) {
        if (amount > balance) {
            cout << "Repayment exceeds balance. Repaying full balance of $" << balance << endl;
            balance = 0;
        } else {
            balance -= amount;
            cout << "Repayment of $" << amount << " made. Remaining balance: $" << balance << endl;
        }
    }

    int getLoanID() const {
        return loanID;
    }

    double getBalance() const {
        return balance;
    }
};

class Bank {
private:
    vector<Loan> loans;

public:
    void addLoan(int id, string name, double amount, double rate) {
        loans.emplace_back(id, name, amount, rate);
        cout << "Loan added successfully for " << name << " with Loan ID: " << id << endl;
    }

    void displayAllLoans() {
        if (loans.empty()) {
            cout << "No loans available." << endl;
            return;
        }
        for (const auto& loan : loans) {
            loan.displayDetails();
        }
    }

    void repayLoan(int id, double amount) {
        for (auto& loan : loans) {
            if (loan.getLoanID() == id) {
                loan.makeRepayment(amount);
                return;
            }
        }
        cout << "Loan ID " << id << " not found." << endl;
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "
=== Bank Loan Management System ===" << endl;
        cout << "1. Add Loan" << endl;
        cout << "2. Display All Loans" << endl;
        cout << "3. Repay Loan" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                double amount, rate;
                cout << "Enter Loan ID: ";
                cin >> id;
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Loan Amount: ";
                cin >> amount;
                cout << "Enter Interest Rate (%): ";
                cin >> rate;
                bank.addLoan(id, name, amount, rate);
                break;
            }
            case 2:
                bank.displayAllLoans();
                break;
            case 3: {
                int id;
                double amount;
                cout << "Enter Loan ID: ";
                cin >> id;
                cout << "Enter Repayment Amount: ";
                cin >> amount;
                bank.repayLoan(id, amount);
                break;
            }
            case 4:
                cout << "Exiting the system. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
