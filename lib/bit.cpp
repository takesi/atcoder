#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "dump.hpp"
#else
#define dump(...)
#define dumpv(...)
#endif

#define rep(i, n) for (int i = 0; i < (n); i++)
#define mins(x, y) (x = min(x, y))
#define maxs(x, y) (x = max(x, y))
typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
const int MOD = 1e9 + 7;
const int INF = 1001001001;
const ll LINF = 1001002003004005006ll;

template<typename T>
struct Bit {
  int n; // 2のべき乗でなくてもOK
  vector<T> node;
  Bit(int n) : n(n), node(n + 1, 0) {}
  void add(int i, T w) { // node[i] += w
    for (int x = ++i; x <= n; x += x & -x) node[x] += w;
  }
  T sum(int i) { // return sum [0, i)
    T ans = 0;
    for (int x = i; x > 0; x -= x & -x) ans += node[x];
    return ans;
  }
  T sum(int i, int j) { // return sum [i, j)
    return sum(j) - sum(i);
  }
  vector<T> debug() { // for debug
    vector<T> a;
    rep(i, n) a.push_back(sum(i, i + 1));
    return a;
  }
};

template<typename T>
struct Bit2D {
  int h, w; // 2のべき乗でなくてもOK
  vector<vector<T>> node;
  Bit2D(int h, int w) : h(h), w(w), node(h + 1, vector<T>(w + 1, 0)) {}
  void add(int y, int x, T w) { // node[y][x] += w
    ++y, ++x;
    for (int j = y; j <= h; j += j & -j)
      for (int i = x; i <= w; i += i & -i) node[j][i] += w;
  }
  T sum(int y, int x) { // return sum [0, 0] x (y, x)
    T ans = 0;
    for (int j = y; j > 0; j -= j & -j)
      for (int i = x; i > 0; i -= i & -i) ans += node[j][i];
    return ans;
  }
  T sum(int y1, int x1, int y2, int x2) { // return sum [y1, x1] x (y2, x2)
    return sum(y2, x2) - sum(y1, x2) - sum(y2, x1) + sum(y1, x1);
  }
};

void solve() {
  int N = 8;
  int v, ans;
  vector<int> data(N);
  for (int i = 0; i < N; i++) {
    data[i] = rand() % 2;
  }
  dump(data);
  Bit<int> bit(N);
  for (int i = 0; i < N; i++) {
    bit.add(i, data[i]);
  }
  dump(bit.node);
  v = bit.sum(1, 4);
  ans = 0;
  for (int i = 1; i < 4; i++) {
    ans += data[i];
  }
  dump(v, ans);

  vector<vector<int>> data2(N, vector<int>(N * 2));
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N * 2; i++) {
      v = rand() % 2;
      data2[j][i] = rand() % 2;
    }
  }
  dumpv(data2, N);
  Bit2D<int> bit2(N, N * 2);
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N * 2; i++) {
      bit2.add(j, i, data2[j][i]);
    }
  }
  dump(bit2.node);
  v = bit2.sum(1, 1, 4, 4);
  ans = 0;
  for (int j = 1; j < 4; j++) {
    for (int i = 1; i < 4; i++) {
      ans += data2[j][i];
    }
  }
  dump(v, ans);
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  // freopen("temp.1", "r", stdin);
  solve();
  return 0;
}