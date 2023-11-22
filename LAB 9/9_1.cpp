#include <bits/stdc++.h>
using namespace std;

bool issafe(vector<int>& available, vector<vector<int>>& allocated, vector<vector<int>>& maxrequired, int process) {
    for (int i = 0; i < available.size(); ++i) {
        if (available[i] < maxrequired[process][i] - allocated[process][i]){
            return false;
        }
    }
    return true;
}

void findsafe(vector<int>& available, vector<vector<int>>& allocated, vector<vector<int>>& maxrequired,
vector<int>& sequence, vector<bool>& visited){
    bool found = false;
    for (int i = 0; i < allocated.size(); ++i) {
        if (!visited[i] && issafe(available, allocated, maxrequired, i)) {
            visited[i] = true;
            for (int j = 0; j < available.size(); ++j) {
                available[j] += allocated[i][j];
            }
            sequence.push_back(i);
            findsafe(available, allocated, maxrequired, sequence, visited);
            visited[i] = false;
            sequence.pop_back();
            for (int j = 0; j < available.size(); ++j) {
                available[j] -= allocated[i][j];
            }
            found = true;
        }
    }
    if(!found){
        for (int i : sequence) {
            cout << i << " ";
        }
        cout << ",";
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> available(3);
        cin >> available[0] >> available[1] >> available[2];
        vector<vector<int>> allocated(n, vector<int>(3));
        vector<vector<int>> maxrequired(n, vector<int>(3));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                cin >> allocated[i][j];
            }
            for (int j = 0; j < 3; ++j) {
                cin >> maxrequired[i][j];
            }
        }
        vector<int> sequence;
        vector<bool> visited(n, false);
        findsafe(available, allocated, maxrequired, sequence, visited);
        cout << endl;
    }
    return 0;
}