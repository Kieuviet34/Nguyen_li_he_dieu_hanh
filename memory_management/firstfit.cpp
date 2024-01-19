#include <iostream>
#include <vector>
using namespace std;

class solution{
    public:
    void first_fit(vector<int>blocksize, vector<int>process_size){
        int m = blocksize.size();
        int n = process_size.size();
        vector<int> allocation(n,-1);
        for (int i = 0; i < n;i++){
            for (int j = 0; j < m;j++){
                if (blocksize[j] >= process_size[i]){
                    allocation[i] = j;
                    blocksize[j] -= process_size[i];
                    break;
                }
            }
        }
        cout << "\nprocess No.\tProcess Size\t Block No.\n";
        for(int i = 0; i < n;i++){
            cout << " " << i + 1 << "\t\t" << process_size[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1;
            else
                cout << "Not allocated";
                cout << endl;
        }
    }
};
int main(){
    solution obj;
    int m, n;
    cout << "Enter the number of blocks: ";
    cin >> m;

    vector<int> blocksize(m);
    cout << "Enter the block sizes: ";
    for (int i = 0; i < m; i++) {
        cin >> blocksize[i];
    }

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> process_size(n);
    cout << "Enter the process sizes: ";
    for (int i = 0; i < n; i++) {
        cin >> process_size[i];
    }

    // Call the first_fit function with user input
    obj.first_fit(blocksize, process_size);

    return 0;
}