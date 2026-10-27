#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> e;
vector<int> visited;


void dfs(int v) {
    visited[v] = 1;

    for (int nb : e[v]) {
        if (!visited[nb]) {
            dfs(nb);
        }
    }
}

int main() {
    int n, s;
    cin >> n >> s;
    --s;

    e.resize(n);
    visited.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            cin >> a;

            if (a == 1) {
                e[i].push_back(j);
                e[j].push_back(i);
            }
        }
    }

    dfs(s);
    int answ = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            ++answ;
        }
    }

    cout << answ << "\n";
}