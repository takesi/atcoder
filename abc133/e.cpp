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
};
mint& operator+=(mint& a, mint b) { return a = a.v + b.v; }
mint& operator-=(mint& a, mint b) { return a = a.v - b.v; }
mint& operator*=(mint& a, mint b) { return a = a.v * b.v; }
mint operator+(mint a, mint b) { return a += b; }
mint operator-(mint a, mint b) { return a -= b; }
mint operator*(mint a, mint b) { return a *= b; }
mint operator-(mint a) { return 0 - a; }
bool operator==(mint a, mint b) { return a.v == b.v; }
bool operator!=(mint a, mint b) { return a.v != b.v; }
istream& operator>>(istream& os, mint& a) { return (os >> a.v); }
ostream& operator<<(ostream& os, const mint& a) { return (os << a.v); }

vector<int> to[100001];

// usage:
// vector<T> v; v.push_back(T(1, 2, 3)); v.emplace_back(1, 2, 3);
// queue<T> q; q.push(T(1, 2, 3));
// int x, y, z; tie(x, y, z) = q.front(); q.pop();
typedef tuple<int, int, mint> T;

int main()
{
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);

  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    dump(a, b);
    to[a].push_back(b);
    to[b].push_back(a);
  }
  dump(to[0]);
  dump(to[1]);
  dump(to[2]);
  dump(to[3]);
  queue<int> q;
  vector<int> used(N);
  q.push(0);
  mint ans;
  ans = K;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (used[v])
      continue;
    used[v] = 1;
    dumpv(v, to[v]);
    int k;
    if (v == 0) {
      k = K;
    } else {
      k = K - 1;
    }
    for (int i = 0; i < to[v].size(); i++) {
      int u = to[v][i];
      if (used[u])
        continue;
      ans *= (--k);
      dump(v, u, k+1, ans.v);
      q.push(u);
    }
  }
  cout << ans.v << endl;
  return 0;
}