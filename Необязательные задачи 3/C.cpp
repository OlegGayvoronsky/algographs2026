#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <iomanip>

using namespace std;

vector<vector<pair<int, double>>> e;
vector<int> visit;
priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

void bfs() {
    pq.push({0, 0});

    double sum = 0;

    while (!pq.empty()) {
        pair<double, int> pr = pq.top();
        double w = pr.first;
        int v = pr.second;
        pq.pop();

        if (visit[v]) {
            continue;
        }

        visit[v] = 1;
        sum += w;

        for (pair<int, double> pr : e[v]) {
            int nb = pr.first;
            double w = pr.second;

            if (visit[nb]) {
                continue;
            }
            pq.push({w, nb});
        }
    }

    cout << fixed << setprecision(5) << sum << "\n";
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> points(n);

    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    e.resize(n);
    visit.resize(n, 0);

    vector<vector<int>> exist(n, vector<int>(n, 0));

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        exist[a][b] = 1;
        exist[b][a] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double w;

            if (exist[i][j]) {
                w = 0;
            } else {
                double dx = points[i].first - points[j].first;
                double dy = points[i].second - points[j].second;

                w = sqrt(dx * dx + dy * dy);
            }

            e[i].push_back({j, w});
            e[j].push_back({i, w});
        }
    }

    bfs();
}