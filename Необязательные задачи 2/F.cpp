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

    int children = 0;

    for (auto edge : edg[cur]) {
        int nb = edge.first;
        int edgeId = edge.second;

        if (edgeId == parentEdge) {
            continue;
        }

        if (used[nb]) {
            hight[cur] = min(hight[cur], h[nb]);
        } else {
            children++;

            dfs(nb, edgeId);

            hight[cur] = min(hight[cur], hight[nb]);

            if (parentEdge != -1 && hight[nb] >= h[cur]) {
                res.push_back(cur);
            }
        }
    }

    if (parentEdge == -1 && children > 1) {
        res.push_back(cur);
    }
}


int main(){
    int n;
    cin >> n;
    
    edg.resize(n);
    edges.resize(n - 1);

    for (int i = 0; i < n - 1; i++) {
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
    res.erase(unique(res.begin(), res.end()), res.end());

    cout << res.size() << "\n";
}