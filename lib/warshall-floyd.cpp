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

void solve() {
  int N, M;
  cin >> N >> M;

  vvi dist(N, vi(N, INF)); // dist[from][to]
  rep(i, N) dist[i][i] = 0; // 自分自身へは距離0
  rep(i, M) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    dist[u][v] = c;
    dist[v][u] = c; // 無向辺の場合は両側に入力
  }

  // 経路復元用の経由点リスト
  vvi next(N, vi(N)); // next[from][to]
  rep(i, N) rep(j, N) next[i][j] = j; // 次の経由点を初期化

  rep(k, N) rep(i, N) rep(j, N) { // k:経由する頂点、i:始点、j:終点
    // dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    if (dist[i][j] > dist[i][k] + dist[k][j]) {
      dist[i][j] = dist[i][k] + dist[k][j];
      next[i][j] = next[i][k]; // 経路復元用の経由頂点を覚える
    // } else if (i != k && dist[i][j] == dist[i][k] + dist[k][j]) {
    //   next[i][j] = min(next[i][j], next[i][k]); // 経路復元を辞書順にしたい場合
    }
  }

  // 最小コストを表示
  rep(i, N) { // 始点
    cout << i + 1 << " to ";
    rep(j, N) { // 終点
      if (i != j && dist[i][j] != INF) cout << j + 1 << ":" << dist[i][j] << " ";
    }
    cout << endl;
  }

  // 最長コストの経路を表示
  function<void(int, int)> path = [&](int s, int g) {
    vi v;
    for (int u = s; u != g; u = next[u][g])
      v.push_back(u);
    v.push_back(g);
    rep(i, v.size()) cout << v[i] << " ";
  };
  rep(i, N) {
    int md = 0;
    int mj = 0;
    rep(j, N) { // 終点
      if (i != j && md < dist[i][j]) {
        md = dist[i][j];
        mj = j;
      }
    }
    cout << i + 1 << " to " << mj + 1 << " : ";
    path(i, mj);
    cout << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  freopen((string(__FILE__) + ".1").c_str(), "r", stdin);
  solve();
  return 0;
}