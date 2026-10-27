#include <algorithm>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <vector>

using namespace std;


const double TIME_LIMIT = 450.0;
const int MAX_NO_IMPROVE = 5000;

volatile sig_atomic_t stop_flag = 0;

void on_sigterm(int) {
    stop_flag = 1;
}

chrono::steady_clock::time_point start_time;

double elapsed() {
    return chrono::duration<double>(chrono::steady_clock::now() - start_time).count();
}

int n;
vector<vector<int>> e;
vector<vector<int>> reverse_e;

vector<char> alive;
vector<int> comp;
vector<int> comp_sz;
vector<int> indeg;
vector<int> outdeg;
vector<double> noise;
int alive_cnt;

vector<char> used;
vector<int> order;

vector<int> trivial_q;
priority_queue<pair<double, int>> heap;

vector<int> visited;
int iter = 0;

mt19937 rng(12345);

void read_graph() {
    string buf;
    char tmp[1 << 16];
    size_t got;
    while ((got = fread(tmp, 1, sizeof(tmp), stdin)) > 0) {
        buf.append(tmp, got);
    }

    size_t p = 0;
    size_t len = buf.size();

    auto read_int = [&]() {
        int x = 0;
        while (p < len && (buf[p] < '0' || buf[p] > '9')) {
            ++p;
        }
        while (p < len && buf[p] >= '0' && buf[p] <= '9') {
            x = x * 10 + (buf[p] - '0');
            ++p;
        }
        return x;
    };

    n = read_int();
    read_int();
    read_int();
    while ((p < len) && (buf[p] != '\n')) {
        ++p;
    }
    ++p;

    e.resize(n);
    reverse_e.resize(n);

    for (int i = 0; i < n; ++i) {
        while ((p < len) && (buf[p] != '\n')) {
            if ((buf[p] >= '0') && (buf[p] <= '9')) {
                int v = read_int() - 1;
                e[i].push_back(v);
                reverse_e[v].push_back(i);
            } else {
                ++p;
            }
        }
        ++p;
    }
}

double key(int v) {
    return (double)indeg[v] * outdeg[v] * noise[v];
}

void push_in_heap(int v) {
    heap.push({key(v), v});
}

void remove_v(int v) {
    alive[v] = 0;
    --alive_cnt;

    for (int u : e[v]) {
        if (alive[u] && (comp[u] == comp[v])) {
            --indeg[u];
            if (indeg[u] == 0) {
                trivial_q.push_back(u);
            } else {
                push_in_heap(u);
            }
        }
    }

    for (int u : reverse_e[v]) {
        if (alive[u] && (comp[u] == comp[v])) {
            --outdeg[u];
            if (outdeg[u] == 0) {
                trivial_q.push_back(u);
            } else {
                push_in_heap(u);
            }
        }
    }
}

void drain() {
    while (!trivial_q.empty()) {
        int v = trivial_q.back();
        trivial_q.pop_back();
        if (alive[v]) {
            remove_v(v);
        }
    }
}

void dfs() {
    stack<pair<int, int>> st;

    for (int s = 0; s < n; ++s) {
        if (!alive[s] || used[s]) {
            continue;
        }

        used[s] = 1;
        st.push({s, 0});

        while (!st.empty()) {
            int v = st.top().first;
            int &i = st.top().second;

            if (i < (int)e[v].size()) {
                int u = e[v][i];
                ++i;

                if (alive[u] && !used[u]) {
                    used[u] = 1;
                    st.push({u, 0});
                }
            } else {
                order.push_back(v);
                st.pop();
            }
        }
    }
}

void kosarayu() {
    stack<int> st;

    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int s = order[i];
        if (comp[s] != -1) {
            continue;
        }

        int comp_id = comp_sz.size();
        int sz = 0;

        comp[s] = comp_id;
        st.push(s);

        while (!st.empty()) {
            int v = st.top();
            st.pop();
            ++sz;

            for (int u : reverse_e[v]) {
                if (alive[u] && (comp[u] == -1)) {
                    comp[u] = comp_id;
                    st.push(u);
                }
            }
        }

        comp_sz.push_back(sz);
    }
}

void rebuild() {
    fill(comp.begin(), comp.end(), -1);
    fill(used.begin(), used.end(), 0);
    comp_sz.clear();
    order.clear();

    dfs();
    kosarayu();

    for (int v = 0; v < n; ++v) {
        if (alive[v] && (comp_sz[comp[v]] == 1)) {
            alive[v] = 0;
            --alive_cnt;
        }
    }

    heap = priority_queue<pair<double, int>>();
    for (int v = 0; v < n; ++v) {
        if (!alive[v]) {
            continue;
        }

        indeg[v] = 0;
        outdeg[v] = 0;
        for (int u : e[v]) {
            if (alive[u] && (comp[u] == comp[v])) {
                ++outdeg[v];
            }
        }

        for (int u : reverse_e[v]) {
            if (alive[u] && (comp[u] == comp[v])) {
                ++indeg[v];
            }
        }

        push_in_heap(v);
    }
}

bool on_cycle(int v, const vector<char> &in_x) {
    ++iter;
    stack<int> st;
    st.push(v);

    while (!st.empty()) {
        int w = st.top();
        st.pop();

        for (int u : e[w]) {
            if (u == v) {
                return true;
            }
            if (!in_x[u] && (visited[u] != iter)) {
                visited[u] = iter;
                st.push(u);
            }
        }
    }
    return false;
}

vector<int> solve(bool use_noise) {
    alive.assign(n, 1);
    comp.assign(n, -1);
    indeg.assign(n, 0);
    outdeg.assign(n, 0);
    alive_cnt = n;
    trivial_q.clear();
    heap = priority_queue<pair<double, int>>();

    noise.assign(n, 1.0);
    if (use_noise) {
        uniform_real_distribution<double> dist(0.6, 1.4);
        for (int v = 0; v < n; ++v) {
            noise[v] = dist(rng);
        }
    }

    vector<int> x;

    while (alive_cnt > 0) {
        rebuild();

        int budget = alive_cnt / 20 + 1;
        int picks = 0;

        while ((alive_cnt > 0) && (picks < budget)) {
            if (heap.empty()) {
                break;
            }

            auto [score, v] = heap.top();
            heap.pop();

            if (!alive[v] || (score != key(v))) {
                continue;
            }

            x.push_back(v);
            ++picks;
            remove_v(v);
            drain();
        }
    }

    vector<char> in_x(n, 0);
    for (int v : x) {
        in_x[v] = 1;
    }

    for (int i = (int)x.size() - 1; i >= 0; --i) {
        if (stop_flag || elapsed() > TIME_LIMIT) {
            break;
        }

        int v = x[i];
        if (!on_cycle(v, in_x)) {
            in_x[v] = 0;
        }
    }

    vector<int> res;
    for (int v = 0; v < n; ++v) {
        if (in_x[v]) {
            res.push_back(v);
        }
    }
    return res;
}

int main() {
    signal(SIGTERM, on_sigterm);
    start_time = chrono::steady_clock::now();

    read_graph();

    used.resize(n, 0);
    visited.resize(n, 0);

    double t0 = elapsed();
    vector<int> best = solve(false);
    double last_dur = elapsed() - t0;

    int runs = 1;
    int no_improve = 0;

    while (!stop_flag && (no_improve < MAX_NO_IMPROVE)) {
        if (elapsed() + 2 * last_dur > TIME_LIMIT) {
            break;
        }

        t0 = elapsed();
        vector<int> cur = solve(true);
        last_dur = elapsed() - t0;
        ++runs;

        if (cur.size() < best.size()) {
            best = cur;
            no_improve = 0;
        } else {
            ++no_improve;
        }
    }

    cerr << "runs = " << runs << ", |X| = " << best.size() << ", time = " << elapsed() << "\n";

    string out;
    for (int v : best) {
        out += to_string(v + 1);
        out += '\n';
    }
    fputs(out.c_str(), stdout);
}