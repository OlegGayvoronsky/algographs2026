#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> m(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> m[i][j];
        }
    }

    int n_roads = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            n_roads += m[i][j];
        }
    }
    cout << n_roads << endl;
}