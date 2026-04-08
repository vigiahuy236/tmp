/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

const long double PI = acos(-1);

struct Point {
    long double x;
    long double y;

    Point() {}
    Point(long double _x, long double _y) : x(_x), y(_y) {}
};

long double distpoint(Point A, Point B) {
    long double sqx = (A.x - B.x) * (A.x - B.x);
    long double sqy = (A.y - B.y) * (A.y - B.y);
    long double res = sqrt(sqx + sqy);
    return res;
}

struct Line {
    long double a;
    long double b;
    long double c;

    Line() {}
    Line(Point A, Point B) {
        a = A.y - B.y;
        b = B.x - A.x;
        c = -(a * A.x + b * A.y);
    }
    Line(long double _a, long double _b, long double _c) : a(_a), b(_b), c(_c) {}
};

long double distpointtoline(Point A, Line d) {
    long double tmp1 = abs(d.a * A.x + d.b * A.y + d.c);
    long double tmp2 = sqrt(d.a * d.a + d.b * d.b);
    long double res = tmp1 / tmp2;
    return res;
}

struct Vec {
    long double x;
    long double y;

    Vec() {}
    Vec(Point A, Point B) {
        x = B.x - A.x;
        y = B.y - A.y;
    }
    Vec(long double _x, long double _y) : x(_x), y(_y) {}
    
    Vec operator + (const Vec& other) {
        Vec res;
        res.x = x + other.x;
        res.y = y + other.y;
        return res;
    }
    Vec operator - (const Vec& other) {
        Vec res;
        res.x = x - other.x;
        res.y = y - other.y;
        return res;
    }
    Vec operator * (long double k) {
        Vec res;
        res.x = x * k;
        res.y = y * k;
        return res;
    }
    Vec operator / (long double k) {
        Vec res;
        res.x = x / k;
        res.y = y / k;
        return res;
    } 

    long double sqlen() {
        long double res = x * x + y * y;
        return res;
    }
    long double len() {
        long double res = sqrt(sqlen());
        return res;
    }
};

long double dot(Vec v1, Vec v2) {
    long double res = v1.x * v2.x + v1.y * v2.y;
    return res;
}

long double cross(Vec veca, Vec vecb) {
    long double res = veca.x * vecb.y - veca.y * vecb.x;
    return res;
}

long double area(Point A, Point B, Point C) {
    Vec vecab(A, B);
    Vec vecac(A, C);
    long double tmp = cross(vecab, vecac);
    long double ans = tmp / 2;
    return ans;
}

void sol() {
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // freopen("geometry.inp", "r", stdin);
    // freopen("geometry.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}