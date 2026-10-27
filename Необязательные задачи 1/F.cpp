#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> e;
vector<int> colors;

bool dfs(int v, int pred) {
    colors[v] = 1;
    for (int nb : e[v]) {
        if (nb == pred) {
            continue;
        }
        if (colors[nb] == 1) {
            return true;
        }

        if (dfs(nb, v)) {
            return true;
        }
    }
    colors[v] = 2;
    return false;
}

int main() {
    int n;
    cin >> n;

    e.resize(n);
    colors.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int a;
            cin >> a;

            if (a == 1) {
                e[i].push_back(j);
            }
        }
    }

    bool has_cycle = dfs(0, -1);
    int n_visited = 0;
    for (int i = 0; i < n; ++i) {
        if (colors[i] == 2) {
            ++n_visited;
        }
    }

    if (has_cycle || n_visited < n) {
        cout << "NO";
        return 0;
    }
    cout << "YES";
    return 0;
}