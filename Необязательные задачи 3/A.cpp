#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> e;
vector<int> visit;
queue<int> q;
vector<pair<int, int>> edges;

void bfs() {
    q.push(0);
    visit[0] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int nb : e[v]) {
            if (visit[nb]) {
                continue;
            }

            edges.push_back({v + 1, nb + 1});
            visit[nb] = 1;
            q.push(nb);
        }
    }
}

int main() {
    int n;
    int m;
    cin >> n >> m;

    e.resize(n);
    visit.resize(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    bfs();

    for (const auto edge : edges) {
        cout << edge.first << " " << edge.second << "\n";
    }
}