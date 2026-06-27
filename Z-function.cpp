/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

vector<int> build_z_function(string s) {
    int n = s.length();
    vector<int> z(n, 0);

    int l = 0;
    int r = 0;

    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

void sol() {
    string s; cin >> s;

    vector<int> z = build_z_function(s);

    int n = s.size();

    for (int i = 0; i < n; i++) {
        cout << z[i] << "\n";
    }

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("Z-function.inp", "r", stdin);
    // freopen("Z-function.out", "w", stdout);
    sol();
    return 0;
}