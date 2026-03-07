/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const long long N = 1e6 + 5;
int n;
long long a[N];

vector<long long> comp;
int mxrank;

int getrank(long long x) {
    return lower_bound(comp.begin(), comp.end(), x) - comp.begin() + 1;
}

void sol() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) comp.push_back(a[i]);

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    mxrank = comp.size();

    for (int i = 1; i <= n; i++) {
        cout << getrank(a[i]) << " ";
    }

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("digital_compression.inp", "r", stdin);
    // freopen("digital_compression.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}