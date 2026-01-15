#include <iostream>
using namespace std;

int main() {
    int n, quantum;
    int bt[10], rem_bt[10];
    int wt[10] = {0}, tat[10];
    int time = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> bt[i];
        rem_bt[i] = bt[i];   // remaining burst time
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    cout << "\n--- Round Robin Scheduling ---\n";
    cout << "Gantt Chart: ";

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                cout << "| P" << i + 1 << " ";

                if (rem_bt[i] > quantum) {
                    time += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }

        if (done)
            break;
    }
    cout << "|\n";

    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << endl;

    return 0;
}
