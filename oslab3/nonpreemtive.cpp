#include <iostream>
using namespace std;

int main() {
    int n;
    int bt[10], pr[10], wt[10], tat[10], temp;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst time for each process:\n";
    for (int i = 0; i < n; i++)
        cin >> bt[i];

    cout << "Enter priority for each process (lower number = higher priority):\n";
    for (int i = 0; i < n; i++)
        cin >> pr[i];

    // sorting process acc to priority
    for (int i = 0; i < n; i++) {
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos])
                pos = j;
        }
        // swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // swap priority
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;
    }

    // calculate waiting time
    wt[0] = 0;  // first process waits 0
    for (int i = 1; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++)
            wt[i] += bt[j];
    }

    // calculate turnaround time
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    // display Gantt chart
    cout << "\n--- Non-Preemptive Priority Scheduling ---\n";
    cout << "Gantt Chart: ";
    for (int i = 0; i < n; i++)
        cout << "| P" << i + 1 << " ";
    cout << "|\n";

    // display table
    cout << "\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++)
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << pr[i] 
             << "\t\t" << wt[i] << "\t" << tat[i] << endl;

    return 0;
}


