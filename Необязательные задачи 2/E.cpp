#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<int>> e;
vector<vector<int>> er;
vector<int> topology;
vector<int> used;
vector<int> colors;
vector<int> d;


void squeeze(int cur, bool r, int clr) {
    for (int nb: (r ? er[cur] : e[cur])) {
        if (used[nb]) {
            continue;
        }

        used[nb] = 1;
        if (r) {
            colors[nb] = clr;
        }

        squeeze(nb, r, clr);
    }
}


void top_sort (vector<int> &topology, int cur) {
    for (int nb: e[cur]) {
        if (used[nb]) {
            continue;
        }

        used[nb] = 1;
        top_sort(topology, nb);
    }

    topology.push_back(cur);
}


int main() {
    int n;
    int m;

    cin >> n >> m;

    int k = 0;

    e.resize(n);
    er.resize(n);
    used.resize(n);
    colors.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        e[a].push_back(b);
        er[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (used[i]) {
            continue;
        }

        used[i] = 1;
        top_sort(topology, i);
    }

    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }

    for (int i = n - 1; i >= 0; --i) {
        int v = topology[i];

        if (used[v]) {
            continue;
        }

        used[v] = 1;
        k += 1;
        colors[v] = k;

        squeeze(v, 1, k);
    }

    cout << k << "\n";

    for (int i = 0; i < n; i++) {
        cout << colors[i] << " ";
    }
}