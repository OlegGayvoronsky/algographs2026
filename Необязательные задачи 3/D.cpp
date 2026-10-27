#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

vector<vector<pair<int, int>>> e;
vector<int> visit;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void bfs() {
    pq.push({0, 0});

    int max_dist = -1;

    while (!pq.empty()) {
        pair<int, int> pr = pq.top();
        int w = pr.first;
        int v = pr.second;
        pq.pop();

        if (visit[v]) {
            continue;
        }

        visit[v] = 1;
        if (w > max_dist) {
            max_dist = w;
        }

        for (pair<int, int> pr : e[v]) {
            int nb = pr.first;
            int w = pr.second;
            
            if (visit[nb]) {
                continue;
            }
            pq.push({w, nb});
        }
    }

    cout << max_dist << "\n";
}

int main() {
    int n;
    int k;
    cin >> n >> k;

    e.resize(n);
    visit.resize(n, 0);

    for (int i = 0; i < k; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        --a;
        --b;
        e[a].push_back({b, w});
        e[b].push_back({a, w});
    }

    bfs();
}