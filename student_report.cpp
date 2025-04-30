#include <iostream>
#include <vector>
#include <string>
#include <limits> // Required for numeric_limits
#include <ios>    // Required for streamsize
#include <iomanip> // Required for std::fixed and std::setprecision

// Structure to represent a single student
struct Student {
    int studentID;
    std::string name;
    double mathScore;
    double scienceScore;
    double englishScore;

    // Constructor
    Student(int id, std::string n, double math, double science, double english)
        : studentID(id), name(std::move(n)), mathScore(math), scienceScore(science), englishScore(english) {}

    // Calculate the average score
    double calculateAverage() const {
        return (mathScore + scienceScore + englishScore) / 3.0;
    }

    // Display student details for the report
    void displayReport() const {
        std::cout << std::left << std::setw(10) << studentID
                  << std::left << std::setw(20) << name
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << mathScore
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << scienceScore
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << englishScore
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << calculateAverage()
                  << std::endl;
    }
};

// Class to manage the list of students and generate reports
class StudentDatabase {
private:
    std::vector<Student> students;
    int nextStudentID; // To generate unique student IDs

public:
    // Constructor
    StudentDatabase() : nextStudentID(1001) {} // Start IDs from 1001

    // Add a new student
    void addStudent() {
        std::string name;
        double math, science, english;

        std::cout << "\n--- Add New Student ---" << std::endl;

        // Generate and display new ID
        int currentID = nextStudentID++;
        std::cout << "New Student ID: " << currentID << std::endl;

        // Get student name
        std::cout << "Enter Student Name: ";
        // Consume any leftover newline character from previous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        // Get scores with input validation
        std::cout << "Enter Math Score (0-100): ";
        while (!(std::cin >> math) || math < 0 || math > 100) {
            std::cout << "Invalid input. Please enter a score between 0 and 100: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter Science Score (0-100): ";
        while (!(std::cin >> science) || science < 0 || science > 100) {
            std::cout << "Invalid input. Please enter a score between 0 and 100: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter English Score (0-100): ";
        while (!(std::cin >> english) || english < 0 || english > 100) {
            std::cout << "Invalid input. Please enter a score between 0 and 100: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Add student to the vector
        students.emplace_back(currentID, name, math, science, english);
        std::cout << "\nStudent added successfully!" << std::endl;

         // Consume the newline character left by the last std::cin >> score
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Generate and display the student report
    void generateReport() const {
        std::cout << "\n===== Student Report =====" << std::endl;

        if (students.empty()) {
            std::cout << "No students in the database." << std::endl;
            return;
        }

        // Print table header
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(20) << "Name"
                  << std::right << std::setw(10) << "Math"
                  << std::right << std::setw(10) << "Science"
                  << std::right << std::setw(10) << "English"
                  << std::right << std::setw(15) << "Average"
                  << std::endl;
        std::cout << std::string(75, '-') << std::endl; // Separator line

        // Print details for each student
        for (const auto& student : students) {
            student.displayReport();
        }

        std::cout << std::string(75, '-') << std::endl; // Separator line
        std::cout << "====== End of Report ======" << std::endl;
    }
};

// Function to display the main menu
void displayMenu() {
    std::cout << "\n===== Student Reporting System =====" << std::endl;
    std::cout << "1. Add New Student" << std::endl;
    std::cout << "2. Generate Report" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    StudentDatabase db;
    int choice;

    do {
        displayMenu();

        // Input validation for menu choice
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 3: ";
            std::cin.clear(); // Clear the error flags
            // Ignore the rest of the invalid input in the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Consume the newline character left by std::cin >> choice
        // Note: This is important if the next input is a string using getline
        //       but in this specific switch, case 1 handles its own getline.
        //       However, it's good practice to clear it after any numeric read
        //       before potentially reading strings or looping for new input.
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Handled within addStudent and the while loop

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                db.generateReport();
                break;
            case 3:
                std::cout << "\nExiting Student Reporting System. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 3." << std::endl;
                break;
        }

    } while (choice != 3);

    return 0;
}
