#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm> // Required for std::transform

using namespace std;

// Structure for a student node in BST
struct StudentNode {
    long studentNumber;
    string fullName;
    string ueEmail;
    string section;
    float grade;
    StudentNode* left;
    StudentNode* right;

    StudentNode(long sn, const string& fn, const string& ue, const string& sc, float gr)
        : studentNumber(sn), fullName(fn), ueEmail(ue), section(sc), grade(gr), left(nullptr), right(nullptr) {}
};

// Class for the Binary Search Tree managing students
class AcademicBST {
private:
    StudentNode* root;

    StudentNode* insert(StudentNode* node, long studentNumber, const string& fullName, const string& ueEmail, const string& section, float grade) {
        if (node == nullptr)
            return new StudentNode(studentNumber, fullName, ueEmail, section, grade);

        if (studentNumber < node->studentNumber)
            node->left = insert(node->left, studentNumber, fullName, ueEmail, section, grade);
        else if (studentNumber > node->studentNumber)
            node->right = insert(node->right, studentNumber, fullName, ueEmail, section, grade);
        return node;
    }

    StudentNode* searchByNumber(StudentNode* node, long studentNumber) {
        if (node == nullptr || node->studentNumber == studentNumber)
            return node;

        if (studentNumber < node->studentNumber)
            return searchByNumber(node->left, studentNumber);
        else
            return searchByNumber(node->right, studentNumber);
    }

    StudentNode* deleteNode(StudentNode* node, long studentNumber) {
        if (node == nullptr) return node;

        if (studentNumber < node->studentNumber) {
            node->left = deleteNode(node->left, studentNumber);
        } else if (studentNumber > node->studentNumber) {
            node->right = deleteNode(node->right, studentNumber);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                StudentNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                StudentNode* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            StudentNode* temp = node->right;
            while (temp && temp->left != nullptr) {
                temp = temp->left;
            }

            // Copy the inorder successor's content to this node
            node->studentNumber = temp->studentNumber;
            node->fullName = temp->fullName;
            node->ueEmail = temp->ueEmail;
            node->section = temp->section;
            node->grade = temp->grade;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->studentNumber);
        }
        return node;
    }

    void deleteTree(StudentNode* node) {
        if (node == nullptr)
            return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void findHighestGrade(StudentNode* node, StudentNode*& highest) {
        if (node == nullptr)
            return;
        if (highest == nullptr || node->grade > highest->grade)
            highest = node;
        findHighestGrade(node->left, highest);
        findHighestGrade(node->right, highest);
    }

    void findLowestGrade(StudentNode* node, StudentNode*& lowest) {
        if (node == nullptr)
            return;
        if (lowest == nullptr || node->grade < lowest->grade)
            lowest = node;
        findLowestGrade(node->left, lowest);
        findLowestGrade(node->right, lowest);
    }

    void findFailedStudents(StudentNode* node, vector<StudentNode*>& failed, float failThreshold) {
        if (node == nullptr)
            return;
        if (node->grade < failThreshold)
            failed.push_back(node);
        findFailedStudents(node->left, failed, failThreshold);
        findFailedStudents(node->right, failed, failThreshold);
    }

    void calculatePerformance(StudentNode* node, float& totalGrades, int& count, int& passedCount, int& failedCount, float failThreshold) {
        if (node == nullptr)
            return;
        totalGrades += node->grade;
        count++;
        if (node->grade < failThreshold) {
            failedCount++;
        } else {
            passedCount++;
        }
        calculatePerformance(node->left, totalGrades, count, passedCount, failedCount, failThreshold);
        calculatePerformance(node->right, totalGrades, count, passedCount, failedCount, failThreshold);
    }

    // NEW: Helper for linear search by name (traverses the entire tree)
    void searchByNameRecursive(StudentNode* node, const string& searchNameLower, vector<StudentNode*>& results) {
        if (node == nullptr) {
            return;
        }

        // Convert current student's name to lowercase for case-insensitive comparison
        string currentNameLower = node->fullName;
        std::transform(currentNameLower.begin(), currentNameLower.end(), currentNameLower.begin(), ::tolower);

        // Check if the search name is a substring of the current student's name
        if (currentNameLower.find(searchNameLower) != string::npos) {
            results.push_back(node);
        }

        // Recursively traverse both left and right subtrees to check all nodes
        searchByNameRecursive(node->left, searchNameLower, results);
        searchByNameRecursive(node->right, searchNameLower, results);
    }

public:
    AcademicBST() : root(nullptr) {}

    ~AcademicBST() {
        deleteTree(root);
    }

    void insert(long studentNumber, const string& fullName, const string& ueEmail, const string& section, float grade) {
        root = insert(root, studentNumber, fullName, ueEmail, section, grade);
    }

    StudentNode* searchByNumber(long studentNumber) {
        return searchByNumber(root, studentNumber);
    }

    void deleteStudent(long studentNumber) {
        root = deleteNode(root, studentNumber);
    }

    StudentNode* getHighestGradeStudent() {
        StudentNode* highest = nullptr;
        findHighestGrade(root, highest);
        return highest;
    }

    StudentNode* getLowestGradeStudent() {
        StudentNode* lowest = nullptr;
        findLowestGrade(root, lowest);
        return lowest;
    }

    vector<StudentNode*> getFailedStudents(float failThreshold = 74.0f) {
        vector<StudentNode*> failed;
        findFailedStudents(root, failed, failThreshold);
        return failed;
    }

    void showOverallPerformance(float failThreshold = 75.0f) {
        float totalGrades = 0.0f;
        int count = 0;
        int passedCount = 0;
        int failedCount = 0;

        calculatePerformance(root, totalGrades, count, passedCount, failedCount, failThreshold);

        if (count == 0) {
            cout << "No student records available to calculate performance.\n";
            return;
        }

        float averageGrade = totalGrades / count;

        cout << "Overall Performance:\n";
        cout << "Total Students: " << count << endl;
        cout << "Average Grade: " << averageGrade << endl;
        cout << "Students Passed: " << passedCount << endl;
        cout << "Students Failed: " << failedCount << endl;
    }

    // New public method for searching by name
    vector<StudentNode*> searchByName(const string& name) {
        vector<StudentNode*> results;
        string searchNameLower = name;
        std::transform(searchNameLower.begin(), searchNameLower.end(), searchNameLower.begin(), ::tolower);
        searchByNameRecursive(root, searchNameLower, results); // Starts the recursive linear traversal
        return results;
    }
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
    cout << "\x1B[2J\x1B[H";  // ANSI escape code to clear screen
}

void display() {
    clearScreen();
    cout << "\n\n";
    cout << "\t\t\t\t╔════════════════════════════════════════════════════════════════════╗\n";
    cout << "\t\t\t\t║                                                                    ║\n";
    cout << "\t\t\t\t║                     UU   UU EEEEEEEEE                               ║\n";
    cout << "\t\t\t\t║                     UU   UU EE                                    ║\n";
    cout << "\t\t\t\t║                     UU   UU EE                                    ║\n";
    cout << "\t\t\t\t║                     UU   UU EEEEEE                                ║\n";
    cout << "\t\t\t\t║                     UU   UU EE                                    ║\n";
    cout << "\t\t\t\t║                      UUUUUUU EEEEEEEEE                               ║\n";
    cout << "\t\t\t\t║                                                                    ║\n";
    cout << "\t\t\t\t╚════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
    cout << "\t\t\t\t    ╭────────────────────────────────────────────╮\n";
    cout << "\t\t\t\t    │          Data Structures and Algorithms    │\n";
    cout << "\t\t\t\t    │             Course Code: NCP_1203          │\n";
    cout << "\t\t\t\t    ╰────────────────────────────────────────────╯\n\n";
}

int main() {
    display();

    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    AcademicBST bst;
    
    // Preload students
    bst.insert(20221112603, "Tyron Jonas Bernardo", "bernardo.tyronjonas@ue.du.ph", "1CPE-2B", 91);
    bst.insert(20241117362, "Roven Jules Respicio", "respecio.rovenjules@ue.edu.ph", "1CPE-2B", 95);
    bst.insert(20241141071, "Dwyane Allen Dela Cruz", "delacruz.dwyaneallen@ue.edu.ph", "1CPE-2B", 81);
    bst.insert(20241120682, "Patrick Alde", "alde.patrick@ue.edu.ph", "1CPE-2B", 69);
    bst.insert(20241138896, "Kate Clouie Formon", "formon.kateclouie@ue.edu.ph", "1CPE-2B", 92);
    bst.insert(20221111815, "Ellaine Jemima Castro", "castro.ellainejemima@ue.edu.ph", "1CPE-2B", 84);
    bst.insert(20241105099, "John Andrew Gungon", "gungon.johnandrew@ue.edu.ph", "1CPE-2B", 91);
    bst.insert(20221105062, "Argelina Ryle Bautista", "bautista.argelinaryle@ue.edu.ph", "1CPE-2A", 83);
    bst.insert(20221115635, "John Meynard Oguez", "oguez.johnmeynard@ue.edu.ph", "1CPE-2A", 79);
    bst.insert(20241118149, "Althea Bautista", "bautista.althea@ue.edu.ph", "1CPE-2A", 96);
    bst.insert(20221118645, "Arabela Grace Dela Cruz", "delacruz.arabelagrace@ue.edu.ph", "1CPE-2A", 97);
    bst.insert(20221111166, "Ann Nicole Gernimo", "geromino.annnicole@ue.edu.ph", "1CPE-2A", 91);
    bst.insert(20221131846, "Steven Zeddriq Natividad", "natividad.stevenzeddriq@ue.edu.ph", "1CPE-2A", 78);
    bst.insert(20241110021, "Ron Kyle Boadilla", "boadilla.ronkyle@ue.edu.ph", "1CPE-2A", 84);
    bst.insert(20241107313, "Mariane Eustaquio", "eustaquio.mariane@ue.edu.ph", "1CPE-2A", 94);
    bst.insert(20181114136, "Chang Hyun Park", "park.changhyun@ue.edu.ph", "1CPE-2B", 74);
    bst.insert(20241120810, "Jaylord Gaspi", "gaspi.jaylord@ue.edu.ph", "1CPE-2B", 95);
    bst.insert(20221112090, "Luis Gabriel Santiago", "santiago.luisgabriel@ue.edu.ph", "1CPE-2B", 94);
    bst.insert(20241120809, "Alexandria Timbol", "timbol.alexandria@ue.edu.ph", "1CPE-2B", 80);
    bst.insert(20241116336, "Rayne Bernadette Roque", "roque.raynebernadette@ue.edu.ph", "1CPE-2B", 90);
    bst.insert(20241100947, "Ian Benedict Untalan", "untalan.ianbenedict@ue.edu.ph", "1CPE-2B", 83);
    bst.insert(20221113297, "Raiden Muñoz", "munoz.raiden@ue.edu.ph", "1CPE-2B", 80);
    bst.insert(20121154856, "Moses Ivan Bartolome", "bartolome.mosesivan@ue.edu.ph", "1CPE-2B", 84);
    bst.insert(20241125382, "Andrew Jae Salas", "salas.andrewjae@ue.edu.ph", "1CPE-2B", 89);
    bst.insert(20241123079, "Ashley Astor", "astor.ashley@ue.edu.ph", "1CPE-2A", 81);
    bst.insert(20241139140, "Rakim Krishna Joven", "joven.rakimkrishna@ue.edu.ph", "1CPE-2A", 92);
    bst.insert(20221110505, "Matthew Jeric Nuñez", "nunez.matthewjeric@ue.edu.ph", "1CPE-2A", 93);
    bst.insert(20181122190, "Justine Paul Cano", "cano.justinepaul@ue.edu.ph", "1CPE-2A", 88);
    bst.insert(20241112765, "Mark Einjelo Alaba", "alaba.markeinjelo@ue.edu.ph", "1CPE-2A", 77);
    bst.insert(20241119517, "Edward Lleyton Robillos", "robillos.edwardlleyton@ue.edu.ph", "1CPE-2A", 71);
    bst.insert(20241125746, "Angela Tolentino", "tolentino.angela@ue.edu.ph", "1CPE-2B", 91);
    bst.insert(20241124685, "Patrick Ayag", "ayag.kimpatrick@ue.edu.ph", "1CPE-2A", 84);
    bst.insert(20241130596, "John Lord Zambrano", "zambrano.johnlord@ue.edu.ph", "1CPE-2A", 91);
    bst.insert(20241129475, "Jon Adrian Maula", "maula.jonadrian@ue.edu.ph", "1CPE-2A", 92);
    bst.insert(20241126669, "Jeremy Jetok Velasquez", "velasquez.jeremyjetok@ue.edu.ph", "1CPE-2A", 93);
    bst.insert(20241124674, "Jennilie Adame", "adame.jennilie@ue.edu.ph", "1CPE-2A", 94);
    bst.insert(20221104923, "Hernan Jay Nem", "nem.hernanjay@ue.edu.ph", "1CPE-2A", 93);
    bst.insert(20241110145, "Ben Justin Espiritu", "esperitu.benjustin@ue.edu.ph", "1CPE-2A", 99);
    bst.insert(20241110350, "Paul Wesley Gomez", "gomez.paulwesley@ue.edu.ph", "1CPE-2A", 84);
    bst.insert(20171140844, "Jeanne Charlotte Belle Ng", "ng.jeannecharlottebelle@ue.edu.ph", "1CPE-2A", 72);
    bst.insert(20221104592, "Christine Alcantara", "alcantara.christine1@ue.edu.ph", "1CPE-2A", 81);
    bst.insert(20241130767, "Neil Obsioma", "obsioma.neilarenz@ue.edu.ph", "1CPE-2A", 85);
    bst.insert(20221104036, "Denisse Andrew Abarro", "abarro.denisseandrew@ue.edu.ph", "1CPE-2A", 95);
    bst.insert(20241107380, "Aron Roxas", "roxas.aron@ue.edu.ph", "1CPE-2A", 97);
    bst.insert(20241130029, "Gwen Angelynn Lopez", "lopez.gwenangelynn@ue.edu.ph", "1CPE-2B", 83);
    bst.insert(20241120229, "Karl Sebastian Gabiano", "gabiano.karlsebastian@ue.edu.ph", "1CPE-2A", 90);
    bst.insert(20241120901, "John Roldan Garbin", "garbinjohnroldan@ue.edu.ph", "1CPE-2B", 83);
    bst.insert(20241139093, "Chantelle Venice Alejandrino", "alejandrino.chantellevenice@ue.edu.ph", "1CPE-2B", 89);
    bst.insert(20241100049, "Jhon Cristopher Bamo", "bamo.jhoncristopher@ue.edu.ph", "1CPE-2B", 84);
    bst.insert(20221116137, "Jonel Laraquel", "laraquel.jonel@ue.edu.ph", "1CPE-2B", 84);
    bst.insert(20221124523, "Karl Angelo Basconcillo", "basconcillo.karlangelo.@ue.edu.ph", "1CPE-2B", 82);
    bst.insert(20241110918, "Ivan Jhed Dumolong", "dumulong.ivanjhed@ue.edu.ph", "1CPE-2B", 67);


    while (true) {
        clearScreen();

        cout << "Academic Management System\n";
        cout << "1. Search student by student number\n";
        cout << "2. Add new student data\n";
        cout << "3. Update student data\n";
        cout << "4. Delete student data\n";
        cout << "5. Find student with highest grade\n";
        cout << "6. Find student with lowest grade\n";
        cout << "7. List students who failed\n";
        cout << "8. Show overall performance\n";
        cout << "9. Search student by name\n"; // New option for name search
        cout << "10. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        if (choice == 1) {
            clearScreen();
            cout << "Enter student number: ";
            long sn;
            cin >> sn;
            if (cin.fail()) {
                cout << "Invalid input for student number.\n";
                clearInputBuffer();
                continue;
            }

            StudentNode* student = bst.searchByNumber(sn);
            if (student) {
                cout << "Student found:\n";
                cout << "Student Number: " << student->studentNumber << endl;
                cout << "Name: " << student->fullName << endl;
                cout << "UE Email: " << student->ueEmail << endl;
                cout << "Section: " << student->section << endl;
                cout << "Grade: " << student->grade << endl;
            } else {
                cout << "Student with number " << sn << " not found.\n";
            }
        } else if (choice == 2) {
            clearScreen();
            cout << "Enter new student number: ";
            long newSn;
            cin >> newSn;
            if (cin.fail()) {
                cout << "Invalid input for student number.\n";
                clearInputBuffer();
                continue;
            }

            if (bst.searchByNumber(newSn) != nullptr) {
                cout << "Student number already exists! Cannot add duplicate.\n";
                continue;
            }

            cout << "Enter student's name: ";
            string fn;
            cin >> ws;
            getline(cin, fn);
            cout << "Enter student's UE email: ";
            string ue;
            cin >> ws;
            getline(cin, ue);
            cout << "Enter student's section: ";
            string sc;
            cin >> ws;
            getline(cin, sc);

            cout << "Enter grade (0.0 to 100.0): ";
            float gr;
            cin >> gr;
            if (cin.fail() || gr < 0.0 || gr > 100.0) {
                cout << "Invalid grade input.\n";
                clearInputBuffer();
                continue;
            }

            bst.insert(newSn, fn, ue, sc, gr);
            cout << "New student data added successfully.\n";
        } else if (choice == 3) {
            clearScreen();
            cout << "Enter student number to update: ";
            long sn;
            cin >> sn;
            if (cin.fail()) {
                cout << "Invalid input for student number.\n";
                clearInputBuffer();
                continue;
            }

            StudentNode* student = bst.searchByNumber(sn);
            if (student) {
                cout << "Updating data for student number: " << sn << endl;
                char updateChoice;
                
                // Update Full Name
                cout << "Current name: " << student->fullName << "\nUpdate? (y/n): ";
                cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    cout << "Enter new name: ";
                    string fn;
                    cin >> ws;
                    getline(cin, fn);
                    student->fullName = fn;
                }
                // Update UE Email
                cout << "Current UE email: " << student->ueEmail << "\nUpdate? (y/n): ";
                cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    cout << "Enter new UE email: ";
                    string ue;
                    cin >> ws;
                    getline(cin, ue);
                    student->ueEmail = ue;
                }
                // Update Section
                cout << "Current section: " << student->section << "\nUpdate? (y/n): ";
                cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    cout << "Enter new section: ";
                    string sc;
                    cin >> ws;
                    getline(cin, sc);
                    student->section = sc;
                }
                // Update Grade
                cout << "Current grade: " << student->grade << "\nUpdate? (y/n): ";
                cin >> updateChoice;
                if (updateChoice == 'y' || updateChoice == 'Y') {
                    cout << "Enter new grade (0.0 to 100.0): ";
                    float gr;
                    cin >> gr;
                    if (cin.fail() || gr < 0.0 || gr > 100.0) {
                        cout << "Invalid grade input. Grade not updated.\n";
                        clearInputBuffer();
                    } else {
                        student->grade = gr;
                    }
                }

                cout << "Student data updated successfully.\n";
            } else {
                cout << "Student with number " << sn << " not found.\n";
            }
        } else if (choice == 4) {
            clearScreen();
            cout << "Enter student number to delete: ";
            long sn;
            cin >> sn;
            if (cin.fail()) {
                cout << "Invalid input for student number.\n";
                clearInputBuffer();
                continue;
            }

            bst.deleteStudent(sn);
            cout << "Student with number " << sn << " deleted successfully (if existed).\n";
        } else if (choice == 5) {
            clearScreen();
            StudentNode* highest = bst.getHighestGradeStudent();
            if (highest) {
                cout << "Student with highest grade:\n";
                cout << "Student Number: " << highest->studentNumber << endl;
                cout << "Name: " << highest->fullName << endl;
                cout << "UE Email: " << highest->ueEmail << endl;
                cout << "Section: " << highest->section << endl;
                cout << "Grade: " << highest->grade << endl;
            } else {
                cout << "No student records found.\n";
            }
        } else if (choice == 6) {
            clearScreen();
            StudentNode* lowest = bst.getLowestGradeStudent();
            if (lowest) {
                cout << "Student with lowest grade:\n";
                cout << "Student Number: " << lowest->studentNumber << endl;
                cout << "Name: " << lowest->fullName << endl;
                cout << "UE Email: " << lowest->ueEmail << endl;
                cout << "Section: " << lowest->section << endl;
                cout << "Grade: " << lowest->grade << endl;
            } else {
                cout << "No student records found.\n";
            }
        } else if (choice == 7) {
            clearScreen();
            vector<StudentNode*> failedStudents = bst.getFailedStudents();
            if (failedStudents.empty()) {
                cout << "No students have failed.\n";
            } else {
                cout << "Students who failed (grade below 75):\n";
                for (auto student : failedStudents) {
                    cout << "----------------------------------------\n";
                    cout << "Student Number: " << student->studentNumber
                         << "\n Name: " << student->fullName
                         << "\n UE Email: " << student->ueEmail
                         << "\n Section: " << student->section
                         << "\n Grade: " << student->grade << endl;
                }
                cout << "----------------------------------------\n";
            }
        } else if (choice == 8) {
            clearScreen();
            bst.showOverallPerformance();
        } else if (choice == 9) { // New case for searching by name
            clearScreen();
            cout << "Enter student's name: ";
            string searchName;
            cin >> ws; // Consume any leftover newline character
            getline(cin, searchName);

            vector<StudentNode*> foundStudents = bst.searchByName(searchName);
            if (foundStudents.empty()) {
                cout << "No students found matching '" << searchName << "'.\n";
            } else {
                cout << "Students matching '" << searchName << "':\n";
                for (const auto& student : foundStudents) {
                    cout << "----------------------------------------\n";
                    cout << "Student Number: " << student->studentNumber << endl;
                    cout << "Name: " << student->fullName << endl;
                    cout << "UE Email: " << student->ueEmail << endl;
                    cout << "Section: " << student->section << endl;
                    cout << "Grade: " << student->grade << endl;
                }
                cout << "----------------------------------------\n";
            }
        }
        else if (choice == 10) {
            clearScreen();
            cout << "\n\n";
            cout << "\t\t\t\t████████ ██   ██  █████  ███   ██ ██   ██       ██   ██  ██████  ██   ██ ██\n";
            cout << "\t\t\t\t  ██     ██   ██ ██   ██ ████   ██ ██ ██          ██ ██  ██   ██ ██   ██ ██ \n";
            cout << "\t\t\t\t  ██     ███████ ███████ ██ ██  ██ █████           ████   ██   ██ ██   ██ ██ \n";
            cout << "\t\t\t\t  ██     ██   ██ ██   ██ ██  ██ ██ ██  ██          ██   ██   ██ ██   ██   \n";
            cout << "\t\t\t\t  ██     ██   ██ ██   ██ ██   ████ ██   ██         ██     ██████  ██████  ██ \n";
            cout << "\t\t\t\t                                                                         \n";
            cout << "\t\t\t\t                            Exiting Program.....                           \n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "\nPress Enter to return to menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
