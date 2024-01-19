#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

class SJF {
public:
    SJF(vector<Process>& processes) : processes(processes) {}

    void execute() {
        sort(processes.begin(), processes.end(), compareArrivalTime);

        int currentTime = 0;
        int completedProcesses = 0;
        int totalTurnaroundTime = 0;

        while (completedProcesses < processes.size()) {
            int shortestJobIndex = findShortestJob(currentTime);

            if (shortestJobIndex == -1) {
                currentTime++;
            } else {
                Process& currentProcess = processes[shortestJobIndex];
                currentTime += currentProcess.burstTime;
                totalTurnaroundTime += currentTime - currentProcess.arrivalTime;

                cout << "Executing Process " << currentProcess.id << " at Time " << currentTime
                     << " (Turnaround Time: " << currentTime - currentProcess.arrivalTime << ")" << endl;

                currentProcess.burstTime = 0; // Mark the process as completed
                completedProcesses++;
            }
        }

        double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
        cout << fixed << setprecision(2);
        cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
    }

private:
    vector<Process> processes;

    int findShortestJob(int currentTime) {
        int shortestJobIndex = -1;
        int shortestBurstTime = INT_MAX;

        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0 &&
                processes[i].burstTime < shortestBurstTime) {
                shortestBurstTime = processes[i].burstTime;
                shortestJobIndex = i;
            }
        }

        return shortestJobIndex;
    }
};

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes;
    for (int i = 0; i < numProcesses; ++i) {
        Process process;
        process.id = i + 1;
        cout << "Enter arrival time for Process " << process.id << ": ";
        cin >> process.arrivalTime;
        cout << "Enter burst time for Process " << process.id << ": ";
        cin >> process.burstTime;
        processes.push_back(process);
    }

    SJF sjf(processes);
    sjf.execute();

    return 0;
}
