#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to hold student data
struct Student {
    string name;
    int rollNumber;
    int marks[5]; // Marks in 5 subjects
    float total;
    float percentage;
    char grade;

    void calculate() {
        total = 0;
        for(int i = 0; i < 5; ++i) {
            total += marks[i];
        }
        percentage = total / 5;
        
        // Assign grade based on percentage
        if(percentage >= 90)
            grade = 'A';
        else if(percentage >= 80)
            grade = 'B';
        else if(percentage >= 70)
            grade = 'C';
        else if(percentage >= 60)
            grade = 'D';
        else
            grade = 'F';
    }

    void display() const {
        cout << "\n=== Report Card ===\n";
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Marks:\n";
        for(int i = 0; i < 5; ++i) {
            cout << "Subject " << i+1 << ": " << marks[i] << endl;
        }
        cout << "Total: " << total << endl;
        cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "Grade: " << grade << endl;
    }
};

// Function declarations
void addStudent();
void saveToFile(const Student& s);
void loadFromFile();
void generateReport();

int main() {
    int choice;
    while(true) {
        cout << "\n--- Student Report Card System ---\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Records\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                loadFromFile();
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}

void addStudent() {
    Student s;
    cout << "Enter student name: ";
    cin.ignore(); // To clear newline from previous input
    getline(cin, s.name);
    cout << "Enter roll number: ";
    cin >> s.rollNumber;

    cout << "Enter marks in 5 subjects:\n";
    for(int i = 0; i < 5; ++i) {
        cout << "Subject " << i+1 << ": ";
        cin >> s.marks[i];
    }

    s.calculate();
    s.display();
    saveToFile(s);
}

void saveToFile(const Student& s) {
    ofstream outFile("students.dat", ios::app | ios::binary);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    outFile.close();
}

void loadFromFile() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cerr << "No records found.\n";
        return;
    }

    Student s;
    while(inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        s.display();
    }

    inFile.close();
}
