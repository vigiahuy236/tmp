/**
 *    author:  Vi Gia Huy
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n, m, timer, cnt, num[N], low[N];
vector<int> adj[N];
stack<int> stk;

//count SCCs(strongly connected components)
void dfs(int u) {
    num[u] = low[u] = ++timer;
    stk.push(u);
    for (int v : adj[u]) {
        if (num[v] != 0) low[u] = min(low[u], num[v]);
        else {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == num[u]) {
        cnt++;
        int v = 0;
        while (u != v) {
            v = stk.top();
            num[v] = n + 1;
            stk.pop();
        }
    }
    return;
}

void sol() {
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) if (num[i] == 0) dfs(i);
    cout << cnt;
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("tarjan.inp", "r", stdin);
    // freopen("tarjan.out", "w", stdout);
    sol();
    return 0;
}