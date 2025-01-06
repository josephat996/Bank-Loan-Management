#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Loan class to store loan details
class Loan {
private:
    int loanID;
    string customerName;
    double loanAmount;
    double interestRate;
    double balance;

public:
    Loan(int id, string name, double amount, double rate)
        : loanID(id), customerName(name), loanAmount(amount), interestRate(rate) {
        balance = loanAmount + (loanAmount * interestRate / 100);
    }

    // Display loan details
    void displayDetails() const {
        cout << "Loan ID: " << loanID << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Loan Amount: $" << fixed << setprecision(2) << loanAmount << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Remaining Balance: $" << balance << endl;
    }

    // Repay the loan
    void repayLoan(double amount) {
        if (amount > balance) {
            cout << "Overpayment! Remaining balance is $" << fixed << setprecision(2) << balance << endl;
            balance = 0;
        } else {
            balance -= amount;
            cout << "Payment successful. Remaining balance: $" << fixed << setprecision(2) << balance << endl;
        }
    }

    // Check if the loan is fully repaid
    bool isFullyRepaid() const {
        return balance <= 0;
    }

    int getLoanID() const { return loanID; }
};

// Bank class to manage loans
class Bank {
private:
    vector<Loan> loans;
    int nextLoanID = 1;

public:
    // Apply for a loan
    void applyForLoan(const string& name, double amount, double rate) {
        Loan newLoan(nextLoanID++, name, amount, rate);
        loans.push_back(newLoan);
        cout << "Loan application successful! Your Loan ID is " << newLoan.getLoanID() << endl;
    }

    // View loan details by ID
    void viewLoan(int loanID) const {
        for (const auto& loan : loans) {
            if (loan.getLoanID() == loanID) {
                loan.displayDetails();
                return;
            }
        }
        cout << "Loan ID not found." << endl;
    }

    // Repay a loan by ID
    void repayLoan(int loanID, double amount) {
        for (auto& loan : loans) {
            if (loan.getLoanID() == loanID) {
                loan.repayLoan(amount);
                return;
            }
        }
        cout << "Loan ID not found." << endl;
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n===== Bank Loan Management =====" << endl;
        cout << "1. Apply for a Loan" << endl;
        cout << "2. View Loan Details" << endl;
        cout << "3. Repay Loan" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                double amount, rate;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter loan amount: $";
                cin >> amount;
                cout << "Enter interest rate (%): ";
                cin >> rate;
                bank.applyForLoan(name, amount, rate);
                break;
            }
            case 2: {
                int loanID;
                cout << "Enter Loan ID: ";
                cin >> loanID;
                bank.viewLoan(loanID);
                break;
            }
            case 3: {
                int loanID;
                double amount;
                cout << "Enter Loan ID: ";
                cin >> loanID;
                cout << "Enter repayment amount: $";
                cin >> amount;
                bank.repayLoan(loanID, amount);
                break;
            }
            case 4:
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}