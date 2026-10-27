#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<int>> e;
vector<int> visited;
vector<int> res;
map<pair<int, int>, int> um;

bool topsort(int v) {
    for (int nb : e[v]) {
        if (visited[nb] == 1) {
            return false;
        }
        if (visited[nb] == 2) {
            continue;
        }

        visited[nb] = 1;
        if (!topsort(nb)) {
            return false;
        }
    }
    res.push_back(v + 1);
    visited[v] = 2;
    return true;
}

int main() {
    int n;
    int m;

    cin >> n >> m;

    visited.resize(n);
    e.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;        
        --a;
        --b;

        if (um[{a, b}] == 1) {
            continue;
        }

        um[{a, b}] = 1;
        e[a].push_back(b);
    }

    for (int i = 0; i < n; ++i) {
        if (visited[i] != 0) {
            continue;
        }

        visited[i] = 1;
        if (!topsort(i)) {
            cout << "No\n";
            return 0;
        }
    }

    reverse(res.begin(), res.end());
    cout << "Yes\n";
    for (int sd : res) {
        cout << sd << " ";
    }
}