/**
 *    author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n;
string s;
int pi[N];
int aut[N][26]; 

void sol() {
    cin >> s;
    n = s.size();
    s = s + " ";

    for (int i = 1; i <= n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j; 
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if (i > 0 && s[i] != (char)('a' + j)) aut[i][j] = aut[pi[i - 1]][j];
            else aut[i][j] = i + (int)(s[i] == (char)('a' + j));
        }
    }

    cout << "pi\n";
    for (int i = 0; i < n; i++) cout << pi[i] << " ";
    cout << "\n";

    cout << "automaton\n";
    for (int j = 0; j < 26; j++) {
        for (int i = 0; i <= n; i++) {
            cout << aut[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("KMP.inp", "r", stdin);
    // freopen("KMP.out", "w", stdout);
    sol();
    return 0;
}