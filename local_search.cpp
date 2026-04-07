/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const long double INF = 1e18;
const int N = 111;
int n;
long double d[N][N];

struct Point {
    long long x;
    long long y;
} a[N];

long double dist(Point A, Point B) {
    long long sqx = (A.x - B.x) * (A.x - B.x);
    long long sqy = (A.y - B.y) * (A.y - B.y);
    long double res = sqrt(sqx + sqy);
    return res;
}

namespace algo1 {
    int p[N];
    int best_p[N];
    long double ans;

    long double cal() {
        long double res = 0.0;
        for (int i = 1; i <= n; i++) res += d[p[i]][p[i + 1]];
        return res;
    }

    void process() {
        for (int i = 2; i <= n; i++) p[i] = i;
        shuffle(p + 2, p + n + 1, rng);
        while (true) {
            bool oke = true;
            for (int i = 2; i <= n - 1; i++) {
                for (int j = i + 1; j <= n; j++) {
                    swap(p[i], p[j]);
                    long double tmp = cal();
                    if (tmp < ans) {
                        ans = tmp;
                        for (int i = 2; i <= n; i++) best_p[i] = p[i];
                        oke = false;
                    }
                    else swap(p[i], p[j]);
                }
            }
            if (oke) break;
        }
        return;
    }

    void sol() {
        srand(time(0));

        p[1] = p[n + 1] = 1;
        best_p[1] = 1;
        ans = INF;

        clock_t start = clock();
        while ((double)(clock() - start) / CLOCKS_PER_SEC < 0.86) process();

        cout << fixed << setprecision(12) << ans << "\n";
        for (int i = 1; i <= n; i++) cout << best_p[i] << " ";
        cout << "\n";

        return;
    }
}

namespace algo2 {
    int p[N];
    int best_p[N];
    long double ans;

    void process() {
        for (int i = 2; i <= n; i++) p[i] = i;
        shuffle(p + 2, p + n + 1, rng);
        while (true) {
            bool oke = true;
            for (int i = 2; i <= n - 1; i++) {
                for (int j = i + 1; j <= n; j++) {
                    long double d1 = d[p[i - 1]][p[i]] + d[p[j]][p[j + 1]];
                    long double d2 = d[p[i - 1]][p[j]] + d[p[i]][p[j + 1]];
                    if (d2 < d1) {
                        reverse(p + i, p + j + 1);
                        oke = false;
                    }
                }
            }
            if (oke) break;
        }
        long double total = 0.0;
        for (int i = 1; i <= n; i++) total += d[p[i]][p[i + 1]];
        if (total < ans) {
            ans = total;
            for (int i = 2; i <= n; i++) best_p[i] = p[i];
        }
        return;
    }

    void sol() {
        srand(time(0));

        p[1] = p[n + 1] = 1;
        best_p[1] = 1;
        ans = INF;

        clock_t start = clock();
        while ((double)(clock() - start) / CLOCKS_PER_SEC < 0.86) process();

        cout << fixed << setprecision(12) << ans << "\n";
        for (int i = 1; i <= n; i++) cout << best_p[i] << " ";
        cout << "\n";

        return;
    }
}

namespace algo3 {
    int p[N];
    int best_p[N];
    long double ans;
    long double cur;
    long double t = 10000.0;
    long double cooling = 0.999995;

    bool acpt(long double delta, long double _t) {
        if (delta < 0) return true; 
        return exp(-delta / _t) > (long double)rng() / rng.max(); 
    }

    void process() {
        int u = uniform_int_distribution<int>(2, n)(rng);
        int v = uniform_int_distribution<int>(2, n)(rng);
        if (u == v) return;
        if (u > v) swap(u, v);
        long double delta = (d[p[u - 1]][p[v]] + d[p[u]][p[v + 1]]) - (d[p[u - 1]][p[u]] + d[p[v]][p[v + 1]]);
        if (acpt(delta, t)) {
            cur += delta;
            reverse(p + u, p + v + 1); 
            if (cur < ans) {
                ans = cur;
                for (int i = 1; i <= n; i++) best_p[i] = p[i];
            }
        }
        t *= cooling;
        return;
    }

    void sol() {
        for (int i = 1; i <= n; i++) p[i] = i;
        p[n + 1] = 1;
        shuffle(p + 2, p + n + 1, rng);
        for (int i = 1; i <= n; i++) cur += d[p[i]][p[i + 1]];
        ans = cur;
        for (int i = 1; i <= n; i++) best_p[i] = p[i];

        clock_t start = clock();
        while ((double)(clock() - start) / CLOCKS_PER_SEC < 0.86) process();

        cout << fixed << setprecision(12) << ans << "\n";
        for (int i = 1; i <= n; i++) cout << best_p[i] << " ";
        cout << "\n";

        return;
    }
}
 
namespace algo4 {
    int p[N];
    int best_p[N];
    long double ans;
    long double dc[8];

    void rev_seg(int l, int r) {
        reverse(p + l, p + r + 1);
    }

    void swap_seg(int i, int j, int k) {
        rotate(p + i + 1, p + j + 1, p + k + 1);
    }

    void process() {
        for (int i = 2; i <= n; i++) p[i] = i;
        shuffle(p + 2, p + n + 1, rng);
        while (true) {
            bool oke = true;
            for (int i = 2; i <= n - 2; i++) {
                for (int j = i + 1; j <= n - 1; j++) {
                    for (int k = j + 1; k <= n; k++) {
                        dc[0] = d[p[i]][p[i + 1]] + d[p[j]][p[j + 1]] + d[p[k]][p[k + 1]];
                        dc[1] = d[p[i]][p[j]] + d[p[i + 1]][p[j + 1]] + d[p[k]][p[k + 1]]; 
                        dc[2] = d[p[i]][p[i + 1]] + d[p[j]][p[k]] + d[p[j + 1]][p[k + 1]]; 
                        dc[3] = d[p[i]][p[k]] + d[p[j + 1]][p[j]] + d[p[i + 1]][p[k + 1]]; 
                        dc[4] = d[p[i]][p[j + 1]] + d[p[k]][p[i + 1]] + d[p[j]][p[k + 1]];
                        dc[5] = d[p[i]][p[j + 1]] + d[p[k]][p[j]] + d[p[i + 1]][p[k + 1]];
                        dc[6] = d[p[i]][p[k]] + d[p[j + 1]][p[i + 1]] + d[p[j]][p[k + 1]];
                        dc[7] = d[p[i]][p[k]] + d[p[j + 1]][p[j]] + d[p[i + 1]][p[k + 1]];
                        int best_case = -1;
                        for (int c = 1; c <= 7; c++) {
                            if (dc[c] < dc[0]) {
                                dc[0] = dc[c];
                                best_case = c;
                            }
                        }
                        if (best_case != -1) {
                            if (best_case == 1) rev_seg(i + 1, j);
                            else if (best_case == 2) rev_seg(j + 1, k);
                            else if (best_case == 3) rev_seg(i + 1, k);
                            else if (best_case == 4) swap_seg(i, j, k);
                            else if (best_case == 5) { 
                                rev_seg(i + 1, j); 
                                swap_seg(i, j, k); 
                            }
                            else if (best_case == 6) { 
                                rev_seg(j + 1, k); 
                                swap_seg(i, j, k); 
                            }
                            else if (best_case == 7) { 
                                rev_seg(i + 1, j); 
                                rev_seg(j + 1, k); 
                                swap_seg(i, j, k); 
                            }
                            oke = false;
                        }  
                    }
                }
            }
            if (oke) break;
        }
        long double total = 0.0;
        for (int i = 1; i <= n; i++) total += d[p[i]][p[i + 1]];
        if (total < ans) {
            ans = total;
            for (int i = 2; i <= n; i++) best_p[i] = p[i];
        }
        return;
    }

    void sol() {
        srand(time(0));

        p[1] = p[n + 1] = 1;
        best_p[1] = 1;
        ans = INF;

        clock_t start = clock();
        while ((double)(clock() - start) / CLOCKS_PER_SEC < 0.86) process();

        cout << fixed << setprecision(12) << ans << "\n";
        for (int i = 1; i <= n; i++) cout << best_p[i] << " ";
        cout << "\n";

        return;
    }
}

void sol() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = dist(a[i], a[j]);
        }
    }

    // algo1::sol();
    // algo2::sol();
    // algo3::sol();    
    algo4::sol();

    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    freopen("local_search.inp", "r", stdin);
    // freopen("local_search.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}