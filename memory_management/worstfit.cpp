#include <iostream>
#include <vector>

using namespace std;

class solution{
    public:
    void worstfit(vector<int>&block_size,vector<int>&process_size){
        int m = block_size.size();
        int n = process_size.size();
        vector<int>allocation(n,-1);
        for (int i = 0;i < n;i++){
            int worst = -1;
            for (int j = 0;j < m;j++){
                if (block_size[j] >= process_size[i]){
                    if (worst == -1)
                        worst = j;
                    else if (block_size[worst] < block_size[j])
                        worst = j;
                }
            }
            if (worst != -1){
                allocation[i] = worst;
                block_size[worst] -= process_size[i];
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
    obj.worstfit(blocksize, process_size);

    return 0;
}