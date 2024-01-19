#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

class RoundRobin {
public:
    RoundRobin(vector<Process>& processes, int timeQuantum) : processes(processes), timeQuantum(timeQuantum) {}

    void execute() {
        queue<Process*> processQueue;

        int currentTime = 0;
        int completedProcesses = 0;

        while (completedProcesses < processes.size()) {
            for (auto& process : processes) {
                if (process.arrivalTime <= currentTime && process.remainingTime > 0) {
                    processQueue.push(&process);
                }
            }

            if (!processQueue.empty()) {
                Process* currentProcess = processQueue.front();
                processQueue.pop();

                int executionTime = min(timeQuantum, currentProcess->remainingTime);
                currentTime += executionTime;
                currentProcess->remainingTime -= executionTime;

                cout << "Executing Process " << currentProcess->id << " at Time " << currentTime
                     << " (Remaining Time: " << currentProcess->remainingTime << ")" << endl;

                if (currentProcess->remainingTime == 0) {
                    completedProcesses++;
                } else {
                    processQueue.push(currentProcess);
                }
            } else {

                int nextArrivalTime = INT_MAX;
                for (const auto& process : processes) {
                    if (process.arrivalTime > currentTime && process.arrivalTime < nextArrivalTime) {
                        nextArrivalTime = process.arrivalTime;
                    }
                }
                currentTime = nextArrivalTime;
            }
        }
    }

private:
    vector<Process> processes;
    int timeQuantum;
};

int main() {
    int numProcesses, timeQuantum;
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
        process.remainingTime = process.burstTime;
        processes.push_back(process);
    }

    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    RoundRobin rr(processes, timeQuantum);
    rr.execute();

    return 0;
}
