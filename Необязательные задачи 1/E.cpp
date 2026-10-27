#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> e;
vector<int> colors;

bool paint(int v, int color) {
    if (colors[v] != -1 && colors[v] != color) {
        return false;
    }
    if (colors[v] != -1) {
        return true;
    }
    
    colors[v] = color;
    color = (color + 1) % 2;
    for (int nb : e[v]) {
        if (!paint(nb, color)) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    e.resize(n);
    colors.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;

        e[a].push_back(b);
        e[b].push_back(a);
    }

    bool is_correct = true;
    for (int i = 0; i < n; ++i) {
        if (colors[i] == -1) {
            is_correct &= paint(i, 1);
        }
    }
    
    if (is_correct) {
        cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            if (colors[i] == 1) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
}