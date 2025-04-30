#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <ios>    // Required for streamsize

// Structure to represent a bank account
struct Account {
    int accountNumber;
    std::string accountHolderName;
    double balance;

    // Constructor
    Account(int accNum, std::string name, double initialBalance = 0.0)
        : accountNumber(accNum), accountHolderName(std::move(name)), balance(initialBalance) {}

    // Method to display account details
    void display() const {
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolderName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
};

// Class to manage the banking system
class BankingSystem {
private:
    std::vector<Account> accounts; // Stores all accounts
    int nextAccountNumber;       // To generate unique account numbers

    // Helper function to find an account by number
    std::vector<Account>::iterator findAccount(int accountNumber) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->accountNumber == accountNumber) {
                return it; // Return iterator to the found account
            }
        }
        return accounts.end(); // Return end iterator if not found
    }

public:
    // Constructor
    BankingSystem() : nextAccountNumber(1001) {} // Start account numbers from 1001

    // Create a new account
    void createAccount() {
        std::string name;
        double initialDeposit;

        std::cout << "\n--- Create New Account ---" << std::endl;
        std::cout << "Enter Account Holder Name: ";
        // Consume any leftover newline character from previous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        std::cout << "Enter Initial Deposit Amount: $";
        while (!(std::cin >> initialDeposit) || initialDeposit < 0) {
            std::cout << "Invalid input. Please enter a non-negative number for initial deposit: $";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        accounts.emplace_back(nextAccountNumber, name, initialDeposit);
        std::cout << "\nAccount created successfully!" << std::endl;
        std::cout << "Your Account Number is: " << nextAccountNumber << std::endl;
        nextAccountNumber++; // Increment for the next account
    }

    // Deposit funds
    void deposit() {
        int accNum;
        double amount;

        std::cout << "\n--- Deposit Funds ---" << std::endl;
        std::cout << "Enter Account Number: ";
         while (!(std::cin >> accNum)) {
            std::cout << "Invalid input. Please enter the account number (a number): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        auto it = findAccount(accNum);

        if (it != accounts.end()) {
            std::cout << "Enter amount to deposit: $";
            while (!(std::cin >> amount) || amount < 0) {
                std::cout << "Invalid input. Please enter a non-negative amount: $";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            it->balance += amount;
            std::cout << "\nSuccessfully deposited $" << amount << " into account " << accNum << std::endl;
            std::cout << "New Balance: $" << it->balance << std::endl;
        } else {
            std::cout << "\nError: Account with number " << accNum << " not found." << std::endl;
        }
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline
    }

    // Withdraw funds
    void withdraw() {
        int accNum;
        double amount;

        std::cout << "\n--- Withdraw Funds ---" << std::endl;
        std::cout << "Enter Account Number: ";
        while (!(std::cin >> accNum)) {
            std::cout << "Invalid input. Please enter the account number (a number): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        auto it = findAccount(accNum);

        if (it != accounts.end()) {
            std::cout << "Enter amount to withdraw: $";
             while (!(std::cin >> amount) || amount < 0) {
                std::cout << "Invalid input. Please enter a non-negative amount: $";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            if (it->balance >= amount) {
                it->balance -= amount;
                std::cout << "\nSuccessfully withdrew $" << amount << " from account " << accNum << std::endl;
                std::cout << "New Balance: $" << it->balance << std::endl;
            } else {
                std::cout << "\nError: Insufficient funds in account " << accNum << std::endl;
                std::cout << "Current Balance: $" << it->balance << std::endl;
            }
        } else {
            std::cout << "\nError: Account with number " << accNum << " not found." << std::endl;
        }
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline
    }

    // View account details
    void viewAccount() {
        int accNum;
        std::cout << "\n--- View Account Details ---" << std::endl;
        std::cout << "Enter Account Number: ";
         while (!(std::cin >> accNum)) {
            std::cout << "Invalid input. Please enter the account number (a number): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        auto it = findAccount(accNum);

        if (it != accounts.end()) {
            it->display();
        } else {
            std::cout << "\nError: Account with number " << accNum << " not found." << std::endl;
        }
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline
    }

    // List all accounts
    void listAllAccounts() const {
        std::cout << "\n--- All Accounts ---" << std::endl;
        if (accounts.empty()) {
            std::cout << "No accounts found." << std::endl;
        } else {
            for (const auto& acc : accounts) {
                acc.display();
            }
        }
    }
};

// Function to display the main menu
void displayMenu() {
    std::cout << "\n===== Simple Banking System =====" << std::endl;
    std::cout << "1. Create New Account" << std::endl;
    std::cout << "2. Deposit" << std::endl;
    std::cout << "3. Withdraw" << std::endl;
    std::cout << "4. View Account Details" << std::endl;
    std::cout << "5. List All Accounts" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    BankingSystem system;
    int choice;

    do {
        displayMenu();

        // Input validation for menu choice
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 6: ";
            std::cin.clear(); // Clear the error flags
            // Ignore the rest of the invalid input in the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Consume the newline character left by std::cin >> choice
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        switch (choice) {
            case 1:
                system.createAccount();
                break;
            case 2:
                system.deposit();
                break;
            case 3:
                system.withdraw();
                break;
            case 4:
                system.viewAccount();
                break;
            case 5:
                system.listAllAccounts();
                break;
            case 6:
                std::cout << "\nExiting Banking System. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 6." << std::endl;
                break;
        }

    } while (choice != 6);

    return 0;
}
