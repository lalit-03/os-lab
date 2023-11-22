#include<bits/stdc++.h>
using namespace std;
struct Process {
    int id;
    int burstTime;
    int arrivalTime;
};
bool compareArrivalTime(const Process &p1, const Process &p2) {
    return p1.arrivalTime < p2.arrivalTime;
}
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process processes[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID, Burst Time, and Arrival Time for Process " << i + 1 << ": ";
        cin >> processes[i].id >> processes[i].burstTime >> processes[i].arrivalTime;
    }
    sort(processes, processes + n, compareArrivalTime);
    int currentTime = 0;
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        int waitingTime = currentTime - processes[i].arrivalTime;
        totalWaitingTime += waitingTime;
        int turnaroundTime = waitingTime + processes[i].burstTime;
        totalTurnaroundTime += turnaroundTime;
        currentTime += processes[i].burstTime;
        cout << "Process " << processes[i].id << ":\n";
        cout << "Waiting Time: " << waitingTime << endl;
        cout << "Turnaround Time: " << turnaroundTime << endl;
    }
    double averageWaitingTime = totalWaitingTime / n;
    double averageTurnaroundTime = totalTurnaroundTime / n;
    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    return 0;
}

