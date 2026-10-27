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

    int shortest_cycle = 4000;
    vector<int> points;
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                int cycle_length = m[i][j] + m[j][k] + m[k][i];
                if (cycle_length < shortest_cycle) {
                    shortest_cycle = cycle_length;
                    points = {i + 1, j + 1, k + 1};
                }
            }
        }
    }
    for (int point : points) {
        cout << point << " ";
    }
    cout << endl;
}