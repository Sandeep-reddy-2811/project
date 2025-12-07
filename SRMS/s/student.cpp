#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    string name, address, gender;
    int rollNo, age;
    float cgpa;

    void input() {
        cin.ignore(); // Clear leftover newline

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Roll No: ";
        cin >> rollNo;

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Gender: ";
        cin >> gender;

        cin.ignore(); // Clear newline before address

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter CGPA: ";
        cin >> cgpa;

        cout << "\nStudent Added Successfully!\n";
    }

    void display() const {
        cout << "\n-----------------------------\n";
        cout << "Name    : " << name << "\n";
        cout << "Roll No : " << rollNo << "\n";
        cout << "Age     : " << age << "\n";
        cout << "Gender  : " << gender << "\n";
        cout << "Address : " << address << "\n";
        cout << "CGPA    : " << cgpa << "\n";
    }
};

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\n===== Student Record Management =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!cin) { // Check for invalid input
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        if (choice == 1) {
            Student s;
            s.input();
            students.push_back(s);
        }
        else if (choice == 2) {
            if (students.empty()) {
                cout << "No student records available!\n";
            } else {
                for (const auto &s : students) {
                    s.display();
                }
            }
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
