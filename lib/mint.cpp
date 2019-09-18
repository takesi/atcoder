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

struct mint
{
  ll v;
  mint() : v(0) {}
  mint(ll v) : v((v % MOD + MOD) % MOD) {}
  mint pow(ll t) const;
  mint inv() const;
};
mint& operator+=(mint& a, mint b) { return a = a.v + b.v; }
mint& operator-=(mint& a, mint b) { return a = a.v - b.v; }
mint& operator*=(mint& a, mint b) { return a = a.v * b.v; }
mint operator+(mint a, mint b) { return a += b; }
mint operator-(mint a, mint b) { return a -= b; }
mint operator*(mint a, mint b) { return a *= b; }
mint operator-(mint a) { return 0 - a; }
mint& operator/=(mint& a, mint b) { return a *= b.inv(); }
mint operator/(mint a, mint b) { return a /= b; }
mint mint::pow(ll t) const
{
  if (!t)
    return 1;
  mint a = pow(t >> 1);
  a *= a;
  if (t & 1)
    a *= *this;
  return a;
}
mint mint::inv() const { return pow(MOD - 2); }
bool operator==(mint a, mint b) { return a.v == b.v; }
bool operator!=(mint a, mint b) { return a.v != b.v; }
istream& operator>>(istream& os, mint& a) { return (os >> a.v); }
ostream& operator<<(ostream& os, const mint& a) { return (os << a.v); }

static vector<mint> mfact(1, 1); // n! (mod MOD)
mint nPk(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (k == 0) return 1;
  int pn = mfact.size();
  if (pn < n + 1) {
    mfact.resize(n + 1);
    for (int i = pn; i <= n; i++) mfact[i] = mfact[i - 1] * i;
  }
  return mfact[n] * mfact[n - k].inv();
}
mint nCk(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  if (k == 0) return 1;
  int pn = mfact.size();
  if (pn < n + 1) {
    mfact.resize(n + 1);
    for (int i = pn; i <= n; i++) mfact[i] = mfact[i - 1] * i;
  }
  return mfact[n] * mfact[k].inv() * mfact[n - k].inv();
}

// 何度もcomb/permを呼ぶ場合はこっちの方が早いかも
struct mcount
{
  vector<mint> fact;  // n! (mod MOD)
  vector<mint> ifact; // k!^{M-2} (mod MOD)
  mcount(int n) : fact(n + 1), ifact(n + 1)
  {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
      fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i)
      ifact[i - 1] = ifact[i] * i;
  }
  mint perm(int n, int k)
  { // nPk (mod MOD)
    if (k < 0 || n < k)
      return 0;
    return fact[n] * ifact[n - k];
  }
  mint comb(int n, int k)
  { // nCk (mod MOD)
    if (k < 0 || n < k)
      return 0;
    return fact[n] * ifact[k] * ifact[n - k];
  }
};

int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("template.1", "r", stdin);

  mint a, b, c, d;
  a = rand();
  b = rand();
  c = rand();
  d = rand();
  dump(a, b, c, d);
  cout << (a * b + c - d) << endl;

  mset ms(10000);
  int n = rand() % 10000;
  int k = rand() % n;
  cout << "nPk : " << ms.perm(n, k) << endl;
  cout << "nCk : " << ms.comb(n, k) << endl;

  return 0;
}
