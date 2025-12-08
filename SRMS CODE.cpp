#include <iostream>
#include <string>
#include <limits> 

using namespace std;

const int MAX_STUDENTS = 100;

class Student {
private:
    int id;
    string name;
    int age;
    string branch;
    float gpa;

public:
    Student() : id(0), name(""), age(0), branch(""), gpa(0.0f) {}

    void setData(int _id, const string& _name, int _age, const string& _branch, float _gpa) {
        id = _id;
        name = _name;
        age = _age;
        branch = _branch;
        gpa = _gpa;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getBranch() const { return branch; }
    float getGpa() const { return gpa; }

    void show() const {
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Branch: " << branch << "\n";
        cout << "GPA: " << gpa << "\n";
        cout << "--------------------------\n";
    }
};

class StudentManagement {
private:
    Student students[MAX_STUDENTS];
    int count;
    int findIndexById(int id) const {
        for (int i = 0; i < count; ++i) {
            if (students[i].getId() == id) return i;
        }
        return -1;
    }

public:
    StudentManagement() : count(0) {}

    bool addStudent(int id, const string& name, int age, const string& branch, float gpa) {
        if (count >= MAX_STUDENTS) {
            cout << "Error: storage full. Cannot add more students.\n";
            return false;
        }
        if (findIndexById(id) != -1) {
            cout << "Error: A student with ID " << id << " already exists.\n";
            return false;
        }
        students[count].setData(id, name, age, branch, gpa);
        ++count;
        cout << "Student added successfully.\n";
        return true;
    }

    void displayAll() const {
        if (count == 0) {
            cout << "No student records to display.\n";
            return;
        }
        cout << "---- All Student Records (" << count << ") ----\n";
        for (int i = 0; i < count; ++i) {
            students[i].show();
        }
    }

    void searchById(int id) const {
        int idx = findIndexById(id);
        if (idx == -1) {
            cout << "Student with ID " << id << " not found.\n";
            return;
        }
        cout << "Student found:\n";
        students[idx].show();
    }

    bool updateById(int id, const string& newName, int newAge, const string& newBranch, float newGpa) {
        int idx = findIndexById(id);
        if (idx == -1) {
            cout << "Student with ID " << id << " not found.\n";
            return false;
        }
        students[idx].setData(id, newName, newAge, newBranch, newGpa);
        cout << "Student updated successfully.\n";
        return true;
    }

    bool deleteById(int id) {
        int idx = findIndexById(id);
        if (idx == -1) {
            cout << "Student with ID " << id << " not found.\n";
            return false;
        }
        for (int i = idx; i < count - 1; ++i) {
            students[i] = students[i + 1];
        }
        --count;
        cout << "Student deleted successfully.\n";
        return true;
    }
    void sortByName() {
        if (count < 2) {
            cout << "Not enough records to sort.\n";
            return;
        }
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (students[j].getName() > students[j + 1].getName()) {
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        cout << "Records sorted by name.\n";
    }

    int totalStudents() const { return count; }
};
void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
int main() {
    StudentManagement sm;
    int choice = 0;

    while (true) {
        cout << "\n====== Student Record Management ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Update Student by ID\n";
        cout << "5. Delete Student by ID\n";
        cout << "6. Sort Students by Name\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        if (choice == 1) {
            int id, age;
            float gpa;
            string name, branch;

            cout << "Enter ID (integer): ";
            cin >> id;
            clearInput(); 
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            clearInput();
            cout << "Enter Branch: ";
            getline(cin, branch);
            cout << "Enter GPA (float): ";
            cin >> gpa;
            clearInput();

            sm.addStudent(id, name, age, branch, gpa);
        }
        else if (choice == 2) {
            sm.displayAll();
        }
        else if (choice == 3) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            clearInput();
            sm.searchById(id);
        }
        else if (choice == 4) {
            int id;
            cout << "Enter ID to update: ";
            cin >> id;
            clearInput();
            if (sm.totalStudents() == 0) {
                cout << "No records to update.\n";
                continue;
            }
            string name, branch;
            int age;
            float gpa;
            cout << "Enter new Name: ";
            getline(cin, name);
            cout << "Enter new Age: ";
            cin >> age;
            clearInput();
            cout << "Enter new Branch: ";
            getline(cin, branch);
            cout << "Enter new GPA: ";
            cin >> gpa;
            clearInput();
            sm.updateById(id, name, age, branch, gpa);
        }
        else if (choice == 5) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            clearInput();
            sm.deleteById(id);
        }
        else if (choice == 6) {
            sm.sortByName();
        }
        else if (choice == 7) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
