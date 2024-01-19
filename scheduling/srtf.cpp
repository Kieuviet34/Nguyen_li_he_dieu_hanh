#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;

    bool operator<(const Process& other) const {
        return remainingTime > other.remainingTime;
    }
};

class SRTF {
public:
    SRTF(vector<Process>& processes) : processes(processes) {}

    void execute() {
        int currentTime = 0;
        int completedProcesses = 0;
        priority_queue<Process> processQueue;

        while (completedProcesses < processes.size()) {
            // Add arrived processes to the queue
            for (auto& process : processes) {
                if (process.arrivalTime <= currentTime && process.remainingTime > 0) {
                    processQueue.push(process);
                }
            }

            if (!processQueue.empty()) {
                Process currentProcess = processQueue.top();
                processQueue.pop();

                int executionTime = min(currentProcess.remainingTime, 1);
                currentTime += executionTime;
                currentProcess.remainingTime -= executionTime;

                cout << "Executing Process " << currentProcess.id << " at Time " << currentTime << " (Remaining Time: " << currentProcess.remainingTime << ")" << endl;

                if (currentProcess.remainingTime == 0) {
                    completedProcesses++;
                    turnaroundTimes.push_back(currentTime - currentProcess.arrivalTime);
                } else {
                    processQueue.push(currentProcess);
                }
            } else {
                // If no process is ready, move to the next arrival time
                int nextArrivalTime = INT_MAX;
                for (const auto& process : processes) {
                    if (process.arrivalTime > currentTime && process.arrivalTime < nextArrivalTime) {
                        nextArrivalTime = process.arrivalTime;
                    }
                }
                currentTime = nextArrivalTime;
            }
        }

        printStatistics();
    }

private:
    vector<Process> processes;
    vector<int> turnaroundTimes;

    void printStatistics() {
        double totalTurnaroundTime = 0;
        for (int time : turnaroundTimes) {
            totalTurnaroundTime += time;
        }

        double averageTurnaroundTime = totalTurnaroundTime / turnaroundTimes.size();
        cout << fixed << setprecision(2);
        cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
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
        process.remainingTime = process.burstTime;
        processes.push_back(process);
    }

    SRTF srtf(processes);
    srtf.execute();

    return 0;
}
