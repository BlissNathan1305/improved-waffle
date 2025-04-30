#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <ios>    // Required for streamsize
#include <algorithm> // Required for std::transform and std::tolower

// Structure to represent a single contact
struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string email;

    // Constructor
    Contact(std::string n, std::string phone, std::string mail)
        : name(std::move(n)), phoneNumber(std::move(phone)), email(std::move(mail)) {}

    // Method to display contact details
    void display() const {
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Phone: " << phoneNumber << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
};

// Class to manage the list of contacts
class ContactBook {
private:
    std::vector<Contact> contacts;

    // Helper function to convert a string to lowercase for case-insensitive search
    std::string toLower(const std::string& str) const {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return lower_str;
    }

public:
    // Add a new contact
    void addContact() {
        std::string name, phone, email;

        std::cout << "\n--- Add New Contact ---" << std::endl;

        // Get contact name
        std::cout << "Enter Name: ";
        // Consume any leftover newline character from previous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        // Get phone number
        std::cout << "Enter Phone Number: ";
        std::getline(std::cin, phone);

        // Get email address
        std::cout << "Enter Email Address: ";
        std::getline(std::cin, email);

        // Add contact to the vector
        contacts.emplace_back(name, phone, email);
        std::cout << "\nContact added successfully!" << std::endl;
    }

    // List all contacts
    void listAllContacts() const {
        std::cout << "\n===== All Contacts =====" << std::endl;
        if (contacts.empty()) {
            std::cout << "No contacts in the book." << std::endl;
        } else {
            for (const auto& contact : contacts) {
                contact.display();
            }
        }
        std::cout << "========================" << std::endl;
    }

    // Search for a contact by name (case-insensitive)
    void searchContact() const {
        std::string searchTerm;
        bool found = false;

        std::cout << "\n--- Search Contact ---" << std::endl;
        std::cout << "Enter Name to Search: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, searchTerm);

        std::string lowerSearchTerm = toLower(searchTerm);

        std::cout << "\n===== Search Results =====" << std::endl;
        for (const auto& contact : contacts) {
            if (toLower(contact.name).find(lowerSearchTerm) != std::string::npos) {
                contact.display();
                found = true;
            }
        }

        if (!found) {
            std::cout << "No contacts found matching '" << searchTerm << "'." << std::endl;
        }
        std::cout << "========================" << std::endl;
    }

    // Optional: Delete a contact by name (deletes first match)
    void deleteContact() {
        std::string nameToDelete;
        bool found = false;

        std::cout << "\n--- Delete Contact ---" << std::endl;
        std::cout << "Enter Name of Contact to Delete: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, nameToDelete);

        std::string lowerNameToDelete = toLower(nameToDelete);

        // Find and erase the contact
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (toLower(it->name) == lowerNameToDelete) {
                it = contacts.erase(it);
                std::cout << "\nContact '" << nameToDelete << "' deleted successfully!" << std::endl;
                found = true;
                break; // Assuming we delete the first match
            }
        }

        if (!found) {
            std::cout << "Contact with name '" << nameToDelete << "' not found." << std::endl;
        }
    }
};

// Function to display the main menu
void displayMenu() {
    std::cout << "\n===== Simple Contact Book =====" << std::endl;
    std::cout << "1. Add New Contact" << std::endl;
    std::cout << "2. List All Contacts" << std::endl;
    std::cout << "3. Search Contact by Name" << std::endl;
    std::cout << "4. Delete Contact by Name" << std::endl; // Added delete option
    std::cout << "5. Exit" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    ContactBook book;
    int choice;

    do {
        displayMenu();

        // Input validation for menu choice
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
            std::cin.clear(); // Clear the error flags
            // Ignore the rest of the invalid input in the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Consume the newline character left by std::cin >> choice
        // This is crucial before calling getline in the subsequent functions
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Handled within each case before getline

        switch (choice) {
            case 1:
                book.addContact();
                break;
            case 2:
                book.listAllContacts();
                break;
            case 3:
                book.searchContact();
                break;
            case 4:
                book.deleteContact();
                break;
            case 5:
                std::cout << "\nExiting Contact Book. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 5." << std::endl;
                break;
        }

    } while (choice != 5);

    return 0;
}

