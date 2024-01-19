#include <iostream>
#include <vector>

using namespace std;

class solution{
    public:
    void bestfit(vector<int> &block_size,vector<int>&process_size){
        int m = block_size.size();
        int n = process_size.size();
        vector<int> allocation(n,-1);
        for (int i = 0; i < n;i++){
            int best = -1;
            for (int j = 0; j < m;j++){
                if (block_size[j] >= process_size[i]){
                    if (best == -1)
                        best = j;
                    else if (block_size[best] > block_size[j])
                        best = j;
                }
            }
            if (best != -1){
                allocation[i] = best;
                block_size[best] -= process_size[i];
            }
        }
        cout << "\nProcess No.\tProcess Size\tBlock no.\n";  
        for (int i = 0; i < n; i++)  
        {  
            cout << " " << i+1 << "\t\t" << process_size[i] << "\t\t";  
            if (allocation[i] != -1)  
                cout << allocation[i] + 1;  
            else
                cout << "Not Allocated";  
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
    obj.bestfit(blocksize, process_size);

    return 0;
}