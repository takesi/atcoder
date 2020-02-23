/*
mintのライブラリ
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

struct mint {
  ll v;
  mint(ll v = 0) : v((v % MOD + MOD) % MOD) {}
  mint pow(ll t) const;
  mint inv() const;
};
mint& operator+=(mint& a, mint b) { return a = a.v + b.v; }
mint& operator-=(mint& a, mint b) { return a = a.v - b.v; }
mint& operator*=(mint& a, mint b) { return a = a.v * b.v; }
mint operator+(mint a, mint b) { return a += b; }
mint operator-(mint a, mint b) { return a -= b; }
mint operator*(mint a, mint b) { return a *= b; }
mint operator-(mint a) { return (mint)0 - a; }
mint& operator/=(mint& a, mint b) { return a *= b.inv(); }
mint operator/(mint a, mint b) { return a /= b; }
mint mint::pow(ll t) const {
  if (!t) return 1;
  mint a = pow(t >> 1);
  a *= a;
  if (t & 1) a *= *this;
  return a;
}
mint mint::inv() const { return pow(MOD - 2); }
bool operator==(mint a, mint b) { return a.v == b.v; }
bool operator!=(mint a, mint b) { return a.v != b.v; }
istream& operator>>(istream& os, mint& a) { return (os >> a.v); }
ostream& operator<<(ostream& os, const mint& a) { return (os << a.v); }

// こちらに置き換えると若干高速になる
// mint& operator+=(mint& a, mint b) {
//   if ((a.v += b.v) >= MOD) a.v -= MOD;
//   return a;
// }
// mint& operator-=(mint& a, mint b) {
//   if ((a.v += MOD - b.v) >= MOD) a.v -= MOD;
//   return a;
// }
// mint& operator*=(mint& a, mint b) {
//   (a.v *= b.v) %= MOD;
//   return a;
// }

mint mfact(int n, bool inv = false) {
  static vector<mint> fact(1, 1), ifact(1, 1);
  int pn = fact.size();
  if (pn < n + 1) {
    fact.resize(n + 1);
    ifact.resize(n + 1);
    for (int i = pn; i <= n; i++) fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= pn; --i) ifact[i - 1] = ifact[i] * i;
  }
  return inv ? ifact[n] : fact[n];
}
mint nPk(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (k == 0) return 1;
  return mfact(n) * mfact(n - k, true);
}
mint nCk(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (k == 0) return 1;
  return mfact(n) * mfact(k, true) * mfact(n - k, true);
}

// 何度もnPk/nCkを呼ぶ場合はこっちの方が早いかも
struct mcount {
  vector<mint> fact;  // n! (mod MOD)
  vector<mint> ifact; // n!^{M-2} (mod MOD)
  mcount(int n) : fact(n + 1), ifact(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) ifact[i - 1] = ifact[i] * i;
  }
  mint nPk(int n, int k) { // nPk (mod MOD)
    if (k < 0 || n < k) return 0;
    return fact[n] * ifact[n - k];
  }
  mint nCk(int n, int k) { // nCk (mod MOD)
    if (k < 0 || n < k) return 0;
    return fact[n] * ifact[k] * ifact[n - k];
  }
  mint operator()(int n, int k) { return nCk(n, k); }
};

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("template.1", "r", stdin);

  mint a, b, c, d;
  a = rand();
  b = rand();
  c = rand();
  d = rand();
  dump(a, b, c, d);
  a = a + 1;
  dump(a, b, c, d);
  cout << (a * b + c - d) << endl;

  int n = rand() % 10000;
  int k = rand() % n;

  mcount ms(10000);
  cout << "nPk : " << ms.nPk(n, k) << endl;
  cout << "nCk : " << ms.nCk(n, k) << endl;
  cout << "nCk : " << ms(n, k) << endl;

  cout << "nPk : " << nPk(n, k) << endl;
  cout << "nCk : " << nCk(n, k) << endl;

  return 0;
}
