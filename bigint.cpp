/**
 *       author:  Vi Gia Huy
 *    Vi Gia Huy will win VOI 27
**/

#include <bits/stdc++.h>

using namespace std;

struct BigInt {
    static const long long BASE = 1e9;
    static const int BASE_DIGITS = 9;

    vector<long long> digits;
    int sign;

    BigInt() : sign(1) {}

    BigInt(long long val) {
        *this = val; 
    }

    BigInt& operator=(long long val) {
        digits.clear();
        if (val == 0) sign = 1;
        else if (val > 0) sign = 1;
        else { 
            sign = -1; 
            val = -val; 
        }
        
        while (val > 0) {
            digits.push_back(val % BASE);
            val /= BASE;
        }

        return *this;
    }

    void trim() {
        while (!digits.empty() && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.empty()) sign = 1;
        
        return;
    }

    void read(string s) {
        sign = 1;
        digits.clear();
        if (s.empty()) return;

        if (s[0] == '-') {
            sign = -1;
            s.erase(0, 1);
        } 
        else if (s[0] == '+') s.erase(0, 1);

        for (int i = s.size(); i > 0; i -= BASE_DIGITS) {
            if (i < BASE_DIGITS) digits.push_back(stoll(s.substr(0, i)));
            else digits.push_back(stoll(s.substr(i - BASE_DIGITS, BASE_DIGITS)));
        }
        trim();
    }

    BigInt(const string& s) {
        read(s);
    }

    friend ostream& operator<<(ostream& os, const BigInt& a) {
        if (a.digits.empty()) {
            os << 0;
            return os;
        }
        if (a.sign == -1) os << '-';
        
        os << a.digits.back();
        
        for (int i = (int)a.digits.size() - 2; i >= 0; i--) {
            os << setfill('0') << setw(BASE_DIGITS) << a.digits[i];
        }

        return os;
    }

    static int compare_abs(const BigInt& a, const BigInt& b) {
        if (a.digits.size() != b.digits.size()) {
            return a.digits.size() < b.digits.size() ? -1 : 1;
        }
        for (int i = (int)a.digits.size() - 1; i >= 0; i--) {
            if (a.digits[i] != b.digits[i]) {
                return a.digits[i] < b.digits[i] ? -1 : 1;
            }
        }
        return 0;
    }

    bool operator==(const BigInt& other) const {
        if (sign != other.sign) return false;
        if (digits.empty() && other.digits.empty()) return true;
        return compare_abs(*this, other) == 0;
    }

    bool operator<(const BigInt& other) const {
        if (sign != other.sign) return sign < other.sign;
        if (sign == 1) return compare_abs(*this, other) == -1;
        return compare_abs(*this, other) == 1; 
    }

    bool operator!=(const BigInt& other) const { return !(*this == other); }
    bool operator>(const BigInt& other) const { return other < *this; }
    bool operator<=(const BigInt& other) const { return !(*this > other); }
    bool operator>=(const BigInt& other) const { return !(*this < other); }

    BigInt abs_add(const BigInt& other) const {
        BigInt res = *this;
        long long carry = 0;
        for (size_t i = 0; i < max(res.digits.size(), other.digits.size()) || carry; i++) {
            if (i == res.digits.size()) res.digits.push_back(0);
            long long cur = res.digits[i] + carry + (i < other.digits.size() ? other.digits[i] : 0);
            res.digits[i] = cur % BASE;
            carry = cur / BASE;
        }
        return res;
    }

    BigInt abs_sub(const BigInt& other) const {
        BigInt res = *this;
        long long carry = 0;
        for (size_t i = 0; i < other.digits.size() || carry; i++) {
            long long cur = res.digits[i] - carry - (i < other.digits.size() ? other.digits[i] : 0);
            if (cur < 0) {
                cur += BASE;
                carry = 1;
            } else carry = 0;
            res.digits[i] = cur;
        }
        res.trim();
        return res;
    }

    BigInt operator+(const BigInt& other) const {
        if (sign == other.sign) {
            BigInt res = abs_add(other);
            res.sign = sign;
            return res;
        }
        if (compare_abs(*this, other) >= 0) {
            BigInt res = abs_sub(other);
            res.sign = sign;
            return res;
        } else {
            BigInt res = other.abs_sub(*this);
            res.sign = other.sign;
            return res;
        }
    }

    BigInt operator-(const BigInt& other) const {
        if (sign != other.sign) {
            BigInt res = abs_add(other);
            res.sign = sign;
            return res;
        }
        if (compare_abs(*this, other) >= 0) {
            BigInt res = abs_sub(other);
            res.sign = sign;
            return res;
        } else {
            BigInt res = other.abs_sub(*this);
            res.sign = -sign;
            return res;
        }
    }


};

void sol() {
    BigInt a("-0009813439428937489798347982789473243423423");
    BigInt b("+002382340030428403824900"); 
    cout << a << "\n";
    cout << b << "\n";
    BigInt c = b;
    cout << c << "\n";
    cout << a + b << "\n";
    cout << a - b << "\n";
    cout << b - a << "\n";
    c = a;
    BigInt zero("0");
    c = zero - c;
    cout << c << "\n";
    cout << b - c << "\n";
    cout << a + c << "\n";
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("bigint.inp", "r", stdin);
    //freopen("bigint.out", "w", stdout);
    int T = 1;
    //cin >> T;
    while (T--) sol();
    return 0;
}