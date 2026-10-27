#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<pair<int, int>>> edg;
vector<pair<int, int>> edges;

vector<int> used;
vector<int> h;
vector<int> hight;
vector<int> res;

int t = 0;


void dfs (int cur, int parentEdge) {
    used[cur] = 1;
    h[cur] = hight[cur] = ++t;

    for (auto edge : edg[cur]) {
        int nb = edge.first;
        int edgeId = edge.second;

        if (edgeId == parentEdge) {
            continue;
        }

        if (used[nb]) {
            hight[cur] = min(hight[cur], h[nb]);
        } else {
            dfs(nb, edgeId);

            hight[cur] = min(hight[cur], hight[nb]);

            if (hight[nb] > h[cur]) {
                res.push_back(edgeId);
            }
        }
    }
}


int main(){
    int n;
    int m;
    cin >> n >> m;
    
    edg.resize(n);
    edges.resize(m);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        --a;
        --b;

        edges[i] = {a, b};

        edg[a].push_back({b, i + 1});
        edg[b].push_back({a, i + 1});
    }
    
    used.resize(n);
    h.resize(n);
    hight.resize(n);

    for(int i = 0; i < n; i++){
        if(!used[i]){
            dfs(i, -1);
        }
    }

    sort(res.begin(), res.end());

    cout << res.size() << "\n";

    for (int pt : res) {
        cout << pt << "\n";
    }
}