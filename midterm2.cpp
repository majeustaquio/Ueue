#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Grades {
    public:
        string name;
        string id;
        double math;
        double science;
        double english;
        double filipino;
        double hekasi;
        double average;

    public:
        double averageScore() {
            double average_score = (math + science + english + filipino + hekasi) / 5;
            return average_score;
        }

        void setData(string n, string i, double m, double s, double e, double f, double h) {
            name = n;
            id = i;
            math = m;
            science = s;
            english = e;
            filipino = f;
            hekasi = h;
            average = averageScore();
        }

        void displayInfo() {
            cout << "Name: " << name << endl;
            cout << "ID: " << id << endl;
            cout << "Average Score: " << average << endl;
        }
};

void insertionSort(vector<Grades>& grades) {
    int n = grades.size();
    for (int i = 1; i < n; ++i) {
        Grades key = grades[i];
        int j = i - 1;
        while (j >= 0 && grades[j].average > key.average) {
            grades[j + 1] = grades[j];
            --j;
        }
        grades[j + 1] = key;
    }
}

int main() {
    vector<Grades> gradeList(5);

    gradeList[0].setData("Laraquel", "20221130923", 79, 81, 85, 95, 76);
    gradeList[1].setData("Rance", "20221113019", 76, 82, 86, 97, 91);
    gradeList[2].setData("Gaspi", "20241120910", 77, 80, 87, 92, 82);
    gradeList[3].setData("Untalan", "20241100947", 78, 89, 89, 81, 75);
    gradeList[4].setData("Aldeguer", "20241100023475", 79, 84, 90, 88, 80);
     
    insertionSort(gradeList);
    
    cout << "Sorted Average Scores: " << endl;
    for (const auto& grade : gradeList) {
        cout << "ID: " << grade.id << "     " << "Average: " << grade.average << endl;
    }
    
    return 0;
}