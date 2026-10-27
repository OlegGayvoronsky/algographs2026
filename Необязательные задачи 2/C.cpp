#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


stack<pair<int, int>> stck;
vector<vector<int>> e;
vector<int> tin;
vector<int> tout;

void dfs(int t) {
    while (!stck.empty()) {
        int v = stck.top().first;
        int &nb_i = stck.top().second;

        if (nb_i < e[v].size()) {
            int v_next = e[v][nb_i];
            
            ++nb_i;

            tin[v_next] = ++t;
            stck.push({v_next, 0});
        } else {
            stck.pop();
            tout[v] = ++t;
        }
    }
}

int main() {
    int n;
    cin >> n;

    e.resize(n);
    tin.resize(n, -1);
    tout.resize(n, -1);
    int root;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;

        if (p == 0) {
            root = i;
            continue;
        }

        --p;
        e[p].push_back(i);
    }

    stck.push({root, 0});
    tin[root] = 0;
    dfs(0);

    int m;
    cin >> m;

    vector<int> res(m, 0);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        if ((tin[a] <= tin[b]) && (tout[a] >= tout[b])) {
            res[i] = 1;
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << res[i] << "\n";
    }
}