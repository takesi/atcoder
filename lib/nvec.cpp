/*
vectorを使ったn進数の実装
nvec n(len, base) len: 桁数, base: 基数
 */
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "../lib/dump.hpp"
#else
#define dump(...)
#define dumpv(...)
#endif

typedef long long ll;
typedef pair<int, int> P;
const int MOD = 1e9 + 7;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

struct nvec : public vector<int> {
  int base;
  nvec(int len, int base) : vector<int>(len), base(base) {}
  nvec& operator=(ll in) {
    for (int i = 0; i < size(); i++) {
      if (in == 0) break;
      at(i) = in % base;
      in /= base;
    }
    return *this;
  };
  operator ll() const noexcept {
    ll out, b;
    out = 0;
    b = 1;
    for (int i = 0; i < size(); i++) {
      if (at(i)) out += at(i) * b;
      b *= base;
    }
    return out;
  };
  nvec& operator++() {
    for (int i = 0; i < size(); i++) {
      at(i)++;
      if (at(i) < base) break;
      at(i) = 0;
    }
    return *this;
  };
  nvec& operator--() {
    for (int i = 0; i < size(); i++) {
      if (0 < at(i)) {
        at(i)--;
        break;
      }
      at(i) = base - 1;
    }
    return *this;
  };
  nvec& operator++(int dummy) { return operator++(); }; // 後置(a++)のoverload
  nvec& operator--(int dummy) { return operator--(); }; // 後置(a--)のoverload
};
nvec& operator+=(nvec& a, int b) {
  for (int i = 0; i < a.size(); i++) {
    if (b == 0) break;
    a.at(i) += (b % a.base);
    if (0 < b) {
      b /= a.base;
      if (a.base <= a.at(i)) {
        a.at(i) -= a.base;
        b++;
      }
    } else {
      b /= a.base;
      if (a.at(i) < 0) {
        a.at(i) += a.base;
        b--;
      }
    }
  }
  return a;
}
nvec& operator-=(nvec& a, int b) { return a += -b; }
nvec operator+(nvec a, int b) { return a += b; }
nvec operator-(nvec a, int b) { return a += -b; }
ostream& operator<<(ostream& os, const nvec& a) {
  string s;
  for (int i = a.size() - 1; 0 <= i; i--) {
    s += to_string(a.at(i));
  }
  return (os << s);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);

  nvec n(10, 3); // 10桁の3進数
  n = 5;         // 初期値を5にする
  for (int i = 0; i < 3; i++) {
    n += 81;
    dump(n, (ll)n); // 値を出力
  }
  return 0;
}