#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


vector<vector<pair<int, int>>> parent;
vector<vector<int>> visited;
queue<pair<int, int>> q;

void bfs(pair<int, int> e, int N) {
    vector<pair<int, int>> steps = {
        {+2, +1},
        {+2, -1},
        {-2, +1},
        {-2, -1},
        {+1, +2},
        {+1, -2},
        {-1, +2},
        {-1, -2}
    };
    while (!q.empty()) {
        pair<int, int> v = q.front();
        q.pop();

        if ((v.first == e.first) && (v.second == e.second)) {
            while (!q.empty()) {
                q.pop();
            }
            return;
        }


        for (auto step : steps) {
            int new_x = v.first + step.first;
            int new_y = v.second + step.second;

            if ((new_x < 0) || (new_x >= N) || (new_y < 0) || (new_y >= N)) {
                continue;
            }

            if (visited[new_x][new_y]) {
                continue;
            }

            parent[new_x][new_y] = v;
            visited[new_x][new_y] = 1;
            q.push({new_x, new_y});
        }
    } 
}

int main() {
    int N;
    int x1, y1;
    int x2, y2;

    cin >> N >> x1 >> y1 >> x2 >> y2;

    --x1;
    --y1;
    --x2;
    --y2;
    
    visited.resize(N, vector<int>(N, 0));
    parent.resize(N, vector<pair<int, int>>(N));
    q.push({x1, y1});
    visited[x1][y1] = 1;
    bfs({x2, y2}, N);

    vector<pair<int, int>> points;
    pair<int, int> point = {x2, y2};

    while ((point.first != x1) || (point.second != y1)) {
        points.push_back(point);
        point = parent[point.first][point.second];
    }
    points.push_back(point);
    reverse(points.begin(), points.end());

    cout << points.size() - 1 << "\n";
    for (auto pt : points) {
        cout << pt.first + 1 << " " << pt.second + 1 << "\n";
    }
}